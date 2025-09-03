/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    TIMER0_interface.h    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Ahmed Shaban
 *  Layer  : MCAL
 *  SWC    : TIMER0
 *
 */

#ifndef TIMER0_INTERFACE_H_
#define TIMER0_INTERFACE_H_

#include <stdint.h>

/*==========================================Timer0 Modes=======================================*/
typedef enum {
	TIMER_MODE_NORMAL =0	,	// Overflow mode
	TIMER_MODE_PWM		,	// Phase Correct PWM
	TIMER_MODE_CTC		,	// Clear Timer on Compare Match
	TIMER_MODE_FAST_PWM	,	// Fast PWM
}TIMER0_Mode_t;



/* ===================== Timer0 Clock Sources ===================== */
typedef enum {
	TIMER0_NO_CLOCK =0	,	//Timer Stopped
	TIMER_PRESCALER_1	,
	TIMER_PRESCALER_8	,
	TIMER_PRESCALER_64	,
	TIMER_PRESCALER_256	,
	TIMER_PRESCALER_1024	,	
	TIMER0_EXT_FALLING	,	// External clock on T0 pin, falling edge
	TIMER0_EXT_RISING		// External clock on T0 pin, falling edge
}TIMER0_Clock_t;


/* ===================== Timer0 Compare Output Modes ===================== */
typedef enum {
	TIMER0_OC0_DISCONNECTED=0	,
	TIMER0_OC0_TOGGLE		,
	TIMER0_OC0_CLEAR		,	// Non-inverting mode for PWM
	TIMER0_OC0_SET				// Inverting mode for PWM
}TIMER0_OC0Mode_t;

/* ===================== Timer0 Config Structure ===================== */
typedef struct {
	TIMER0_Mode_t		mode			;	// Timer0 mode
	TIMER0_Clock_t		clock			;	// Clock source (prescaler)
	TIMER0_OC0Mode_t	oc0_mode		;	// Compare Output Mode
	uint8_t 		interrupt_enable 	;	// 0 = Disabled, 1 = Enabled
}TIMER0_Config_t;

/* ===================== Public Functions ===================== */
void TIMER0_init 		(TIMER0_Config_t *config);
void TIMER0_setCompaerValue	(uint8_t Value		);
void TIMER0_setCounterValue	(uint8_t Value		);
void TIMER0_stop	   	(void			);


#endif /* TIMER0_INTERFACE_H_ */

























