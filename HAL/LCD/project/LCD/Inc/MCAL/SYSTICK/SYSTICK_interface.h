/*
 * SYSTICK_interface.h
 *
 *  Created on: Feb 24, 2022
 *      Author: noureldeen albrmky
 */

#ifndef MCAL_SYSTICK_SYSTICK_INTERFACE_H_
#define MCAL_SYSTICK_SYSTICK_INTERFACE_H_

typedef enum {
	SYSTICK_STATUS_DISABLE,
	SYSTICK_STATUS_ENABLE
} SYSTICK_STATUS_t;

typedef enum {
	SYSTICK_PRELOAD_IMMEDIATE,
	SYSTICK_PRELOAD_WAIT_UF
} SYSTICK_PRELOAD_t;

void MSYSTICK_voidInit(void);
void MSYSTICK_voidSTATUS(SYSTICK_STATUS_t status);
void MSYSTICK_voidPreload(SYSTICK_PRELOAD_t type, u32 value);
void MSYSTICK_voidBusyWait(u32 NumberOfTicks);
void MSYSTICK_voidDelay_MS(u32 Delay_In_MS);
void MSYSTICK_voidDelay_uS(u32 Delay_In_uS);

#endif /* MCAL_SYSTICK_SYSTICK_INTERFACE_H_ */
