/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    TIMER0_program.c    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Ahmed Shaban
 *  Layer  : MCAL
 *  SWC    : TIMER0
 *
 */


#include "TIMER0_interface.h"
#include "TIMER0_private.h"
#include "TIMER0_config.h"


/* ===================== Timer0 Initialization ===================== */
void TIMER0_init (TIMER0_Config_t *config)
{
	/*Rest control register*/
	TCCR0=0;
	

/*select mode*/
	switch (config->mode)
	{
		case TIMER_MODE_NORMAL:	/*WGM00=0,WGM01=0*/		break;
		case TIMER_MODE_PWM   :	TCCR0|=(1<<WGM00);		break;
		case TIMER_MODE_CTC   : TCCR0|=(1<<WGM01);		break;
		TIMER_MODE_FAST_PWM   : TCCR0|=(1<<WGM00)|(1<<WGM01); 	break;
	}

/*select Compare output Mode*/
	switch (config->oc0_mode)
	{
		case TIMER0_OC0_DISCONNECTED : 					break;
		case TIMER0_OC0_TOGGLE	     : TCCR0|=(1<<COM00); 		break;
		case TIMER0_OC0_CLEAR	     : TCCR0|=(1<<COM01);		break;
		case TIMER0_OC0_SET	     : TCCR0|=(1<<COM00)|(1<<COM01); 	break;
	}

/*Enable Interrupt if needed*/
	if(config->interrupt_enable == 1)
	{
	    if (config ->mode ==TIMER0_MODE_NORMAL)
		TIMSK |=(1<<TIOE0);	// Overflow interrupt
	    else 
		TIMSK |=(1<<CIE0);	// Overflow interrupt
	}
	
/*select Clock (Prescaler)*/
	TCCR0 |= (config ->clock & 0x07);
}



/* ===================== Set Compare Value ===================== */
void TIMER0_setCompaerValue(uint8_t value)
{
	OCR0=value;
}


/* ===================== Set Counter Value ===================== */
void TIMER0_setCounterValue(uint8_t value)
{
	TCNT0=value;
}

/* ===================== Stop Timer ===================== */
void TIMER0_stop(void)
{
	TCCR0&=~((1<<CS00) | (1<<CS01) | (1<<CS02)); // Clear clock bits
}

