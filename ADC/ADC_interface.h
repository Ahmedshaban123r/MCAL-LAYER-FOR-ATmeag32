//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  ADC_interface.h   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//Layer: MCAL
//SWC  : ADC


/* 
   adc.h  -- simple configurable ADC driver for ATmega32
   Usage: include <avr/io.h> and this header. Implemented with avr-gcc ISR(ADC_vect).
*/


#ifndef ADC_INTERFACE_H
#define ADC_INTERFACE_H


#include <stdint.h>
#include <stdbool.h>


/* Reference selections (maps to ADMUX REFS1:REFS0) */
typedef enum {
	ADC_REF_AREF=0x00,
	ADC_REF_AVCC=0x40,
	ADC_REF_INTERNAL_2V56=0xC0
}adc_ref_t;

/*Result alignment*/
typedef enum{
	ADC_ALIGN_RIGHT =0,
	ADC_ALIGN_LEFT 	=1
}adc_align_t;

/* Prescaler value to write into ADPS2..0 (0..7) — use defined constants below */
typedef uint8_t adc_prescaler_t;


/* Auto-trigger sources (ADTS2..0 in SFIOR) */
typedef enum {
	ADC_TRIG_FREE_RUNNING =0,
	ADC_TRIG_ANALOG_COMP  =1,
	ADC_TRIG_EXT_INT0     =2,
	ADC_TRIG_TIMER0_COMP  =3,
	ADC_TRIG_TIMER0_OVF   =4,
	ADC_TRIG_TIMER1_COMPB =5,
	ADC_TRIG_TIMER1_OVF   =6,
	ADC_TRIG_TIMER1_CAPTURE =7
}adc_trig_t;

/* ADC channels (single ended) - values are MUX4..0 */
typedef enum {
    ADC_CH0 = 0,
    ADC_CH1 = 1,
    ADC_CH2 = 2,
    ADC_CH3 = 3,
    ADC_CH4 = 4,
    ADC_CH5 = 5,
    ADC_CH6 = 6,
    ADC_CH7 = 7
} adc_channel_t;

typedef void (*adc_callback_t)(uint16_t adc_value);


/* Configuration structure */

typedef struct {
	adc_ref_t	ref;			/* reference selection */
	adc_align_t	align;			/* left/right adjust */
	adc_prescaler	prescaler:		/* ADPS2..0 (0..7) */
	bool		auto_trigger;	 	/* ADATE */
	adc_trig_t	trigger_src;		/* ADTS */
	bool		interrupt_enable;	/* ADIE */
	uint8_t		didr_mask;		/* bits to set in DIDR0 to disable digital inputs (bit i = ADCi) */
} ADC_Config_t;




/* API */
void ADC_init(const ADC_Config_t *cfg);
void ADC_enable(void);
void ADC_disable(void);
uint16_t ADC_readBlocking(adc_channel_t ch); /* returns 0..1023 */
uint8_t  ADC_read8(adc_channel_t ch);        /* returns 0..255 using left adjust */
void     ADC_startConversion(adc_channel_t ch);
bool     ADC_conversionInProgress(void);
void     ADC_setAutoTrigger(adc_trigger_t src, bool enable);
void     ADC_setCallback(adc_callback_t cb); /* enable interrupt in config to use callback */


#endif /* ADC_INTERFACE_H */
























