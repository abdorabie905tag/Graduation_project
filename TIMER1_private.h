#ifndef _TIMER1_PRIVATE_H
#define _TIMER1_PRIVATE_H

#define TCCR1A_Register    *((volatile u8*) 0x4F)
#define TCCR1B_Register    *((volatile u8*) 0x4E)
#define TCNT1H_Register    *((volatile u8*) 0x4D)
#define TCNT1L_Register    *((volatile u8*) 0x4C)
#define TCNT1_Register     *((volatile u16*)0x4C)
#define OCR1AH_Register    *((volatile u8*) 0x4B)
#define OCR1AL_Register    *((volatile u8*) 0x4A)
#define OCR1BH_Register    *((volatile u8*) 0x49)
#define OCR1BL_Register    *((volatile u8*) 0x48)
#define ICR1L_Register     *((volatile u8*) 0x46)
#define ICR1H_Register     *((volatile u8*) 0x47)
#define ICR1_Register      *((volatile u16*)0x46)
#define TIMSK_Register     *((volatile u8*) 0x59)
#define TIFR_Register      *((volatile u8*) 0x58)
void __vector_6 (void) __attribute__((signal));
#endif
