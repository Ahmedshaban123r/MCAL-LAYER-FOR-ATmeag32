/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    TIMER0_config.h    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Ahmed Shaban
 *  Layer  : MCAL
 *  SWC    : TIMER0
 *
 */

#ifndef TIMER0_CONFIG_H_
#define TIMER0_CONFIG_H_


/*========================================User Default Config========================================*/
#define TIMER0_DEFAULT_MODE		TIMER0_MODE_FAST_PWM
#define TIMER0_DEFAULT_CLOCK		TIMER0_PRESCALER_64
#define	TIMER0_DEFAULT_OC0_MODE		TIMER0_OC0_CLEAR	// Non-inverting mode
#define TIMER0_DEFAULT_INTERRUPT	0			// Disabled by default

#endif		/* TIMER0_CONFIG_H_ */
