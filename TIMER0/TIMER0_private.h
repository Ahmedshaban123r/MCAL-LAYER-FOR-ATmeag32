/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    TIMER0_private.h    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author :Ahmed Shaban
 *  Layer  : MCAL
 *  SWC    : TIMER0
 *
 */

#ifndef TIMER0_PRIVATE_H_
#define TIMER0_PRIVATE_H_

/* ===================== Timer0 Registers ===================== */
#define TCCR0	(*(volatile uint8_t*)0x53)
#define TCNT0	(*(volatile uint8_t*)0x52)
#define OCR0	(*(volatile uint8_t*)0x5C)
#define TIMSK	(*(volatile uint8_t*)0x59)
#define TIFR	(*(volatile uint8_t*)0x58)


/* ===================== TCCR0 Bits ===================== */
#define WGM00    6
#define WGM01    3
#define COM00    4
#define COM01    5
#define CS00     0
#define CS01     1
#define CS02     2


/* ===================== TIMSK Bits ===================== */
#define TOIE0   0   // Overflow Interrupt Enable
#define OCIE0   1   // Output Compare Match Interrupt Enable

#endif /* TIMER0_PRIVATE_H_ */



