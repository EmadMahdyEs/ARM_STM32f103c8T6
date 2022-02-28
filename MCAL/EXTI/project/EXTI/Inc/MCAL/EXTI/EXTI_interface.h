/*
 * EXTI_interface.h
 *
 *  Created on: Feb 28, 2022
 *      Author: noureldeen albrmky
 */

#ifndef MCAL_EXTI_EXTI_INTERFACE_H_
#define MCAL_EXTI_EXTI_INTERFACE_H_

typedef enum {
	EXTI_RISING,
	EXTI_FALLING,
	EXTI_CHANGE
} EXTI_INTERRUPT_t;

typedef enum {
	EXTI_DISABLE,
	EXTI_ENABLE
} EXTI_STATUS_t;

typedef enum {
	EXTI_LINE0,
	EXTI_LINE1,
	EXTI_LINE2,
	EXTI_LINE3,
	EXTI_LINE4,
	EXTI_LINE5,
	EXTI_LINE6,
	EXTI_LINE7,
	EXTI_LINE8,
	EXTI_LINE9,
	EXTI_LINE10,
	EXTI_LINE11,
	EXTI_LINE12,
	EXTI_LINE13,
	EXTI_LINE14,
	EXTI_LINE15

} EXTI_LINEx;

void MEXTI_voidSetInterruptMode(u8 copy_u8LineNum,
		EXTI_INTERRUPT_t copy_eINTType);

void MEXTI_voidEXTILineStatus(u8 copy_LineNum, EXTI_STATUS_t copy_estatus);

void MEXTI_voidTriggerSWINT(u8 copy_LineNum);

void MEXTI_voidClearPending(u8 copy_LineNum);

u8 MEXTI_u8ISPending(u8 copy_LineNum);

#endif /* MCAL_EXTI_EXTI_INTERFACE_H_ */
