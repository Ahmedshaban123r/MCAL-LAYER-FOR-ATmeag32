//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  ADC_program.c   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//Layer: MCAL
//SWC  : ADC






#include "ADC_interface.h"
#include "ADC_private.h"
#include "ADC_config.h"
#include <avr/io.h>
#include <avr/interrupt.h> /* for ISR macro */
#include <avr/power.h>     /* optional: power_adc_enable()/disable() */
#include <util/delay.h>    /* optional small delays */


static volatile adc_callback_t adc_cb	=0;
static adc_prescaler_t saved_prescaler	=0;


/* low-level helper: select channel (preserve REFS/ADLAR bits in ADMUX) */
static inline void adc_select_channel(adc_channel_t ch){
	ADMUX =(ADMUX&0xE0)|((uint8_t)ch & 0x1F);
}
 

/* read full 10-bit result (safe order). Assumes ADLAR==0 for 10-bit read.
   If ADLAR==1 and you want full 10-bit, you'd need to combine differently.
*/


static inline uint16_t adc_get_result_raw(void) {
	/* When reading 16-bit result split across ADCL/ADCH: read ADCL first, then ADCH */ 
	uint16_t val=ADCL;
	val |=((uint16_t)ADCH<<8;
	return val;
}


void ADC_init (const ADC_config_t *cfg) {
	if (!cfg)return;
	 /* Make sure ADC power reduction bit is clear (PRADC = 0) */
#if defined(PRR)
    PRR &= ~(1<<PRADC); /* enable ADC power domain */
#endif
 	/* configure ADMUX: reference and alignment */
	ADMUX =(uint8_t)cfg->ref; /* places bits REFS1:0 in bits7:6 */
	if (cfg->align==ADC_ALIGN_LEFT) ADMUX |=(1<<ADLAR);
	else ADMUX &=~(1<<ADLAR);
	adc_select_channel(ADC_CH0);
	saved_prescaler =cfg->prescaler &0x07;
	ADCSRA =(ADCSRA & ~0x07)|(saved_prescaler & 0x07);
	
	
	/*auto trigger*/
	if (cfg->interrupt_enable) ADCSRA|=(1<<ADIE);
	else ADCSRA&=~(1<<ADIE);
	

	 /* set trigger source in SFIOR (ADTS2:0 are bits 7..5) */	
	SFIOR =(SFIOR&~(0xE0)) |((uint8_t)(cfg->trigger_src & 0x07)<<5);
	
	
	/* configure DIDR0 to disable digital inputs on ADC pins if requested */
	#if defined (DIDR0)
		DIDR0 |=cfg->didr_mask;
	#endif

	/* Finally enable ADC */
	 ADCSRA |= (1<<ADEN);
}

void ADC_enable(void){
	#if defined(PRR)
		PRR&=~(1<<PRADC);
	#endif
	ADCSRA|=(1<<ADEN);
}
void ADC_disable(void){
	ADCSRA&=~(1<<ADEN);
	#if defined(PRR)
		PRR|=(1<<PRADC);
	#endif
}

uint16_t ADC_readBlocking(adc_channel_t ch) {
	 /* Select channel (safe updating: ADMUX is double-buffered; conversion locks values) */
	adc_select_channel(ch);
	

	/*start conversion*/
	ADCSRA|=(1<<ADSC);
	
	/* wait until ADSC cleared (conversion finished) */
	while (ADCSRA & (1<<ADSC)) { }



	/* ADCL must be read first (see datasheet) */
	return adc_get_result_raw() & 0x03FF;
}

/* Convenience 8-bit read (left adjusted -> ADCH contains the top 8 bits) */
uint8_t ADC_read8(adc_channel_t ch) {
	/*set ADLAR =1 */
	ADMUX |= (1<<ADLAR);
	adc_select_channel(ch);
	
	/* start and wait */	
	 ADCSRA |= (1<<ADSC);
	while(ADCSRA & (1<<ADSC)){}

	/* when left-adjusted, ADCH contains the top 8 bits — read ADCH */
   	 return ADCH;
}


/* Start conversion (do not wait) */
void ADC_startConversion(adc_channel_t ch) {
    adc_select_channel(ch);
    ADCSRA |= (1<<ADSC);
}



bool ADC_conversionInProgress(void) {
    return (ADCSRA & (1<<ADSC)) != 0;
}


void ADC_setAutoTrigger(adc_trigger_t src, bool enable) {
    /* write ADTS bits into SFIOR[7:5] */
    SFIOR = (SFIOR & ~(0xE0)) | ((uint8_t)(src & 0x07) << 5);
    if (enable) ADCSRA |= (1<<ADATE);
    else ADCSRA &= ~(1<<ADATE);
}



void ADC_setCallback(adc_callback_t cb) {
    adc_cb = cb;
}


/* ISR for ADC Conversion Complete - call user callback if set */
ISR(ADC_vect) {
    uint16_t v = adc_get_result_raw() & 0x03FF;
    if (adc_cb) adc_cb(v);
}





































