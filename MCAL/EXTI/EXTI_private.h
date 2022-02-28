/*
 * EXTI_private.h
 *
 *  Created on: Feb 28, 2022
 *      Author: noureldeen albrmky
 */

#ifndef MCAL_EXTI_EXTI_PRIVATE_H_
#define MCAL_EXTI_EXTI_PRIVATE_H_

typedef struct {
	volatile u32 EXTI_IMR;
	volatile u32 EXTI_EMR;
	volatile u32 EXTI_RTSR;
	volatile u32 EXTI_FTSR;
	volatile u32 EXTI_SWIER;
	volatile u32 EXTI_PR;
} EXTI_t;

#define EXTI ( (volatile EXTI_t*)(0x40010400) )

#endif /* MCAL_EXTI_EXTI_PRIVATE_H_ */
