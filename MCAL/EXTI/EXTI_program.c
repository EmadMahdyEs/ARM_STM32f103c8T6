/*
 * EXTI_program.c
 *
 *  Created on: Feb 28, 2022
 *      Author: noureldeen albrmky
 */

#include "../Inc/LIBRARY/bit_math.h"
#include "../Inc/LIBRARY/standard_types.h"

#include "../Inc/MCAL/EXTI/EXTI_interface.h"
#include "../Inc/MCAL/EXTI/EXTI_private.h"
#include "../Inc/MCAL/EXTI/EXTI_configure.h"

void MEXTI_voidSetInterruptMode(EXTI_LINEx copy_eLineNum,
		EXTI_INTERRUPT_t copy_eINTType)
{
	switch (copy_eINTType)
	{
		case EXTI_FALLING:
			EXTI->EXTI_FTSR = 1 << copy_eLineNum;
			break;
		case EXTI_RISING:
			EXTI->EXTI_RTSR = 1 << copy_eLineNum;
			break;

		case EXTI_CHANGE:
			EXTI->EXTI_FTSR = 1 << copy_eLineNum;
			EXTI->EXTI_RTSR = 1 << copy_eLineNum;
			break;
	}
}

void MEXTI_voidEXTILineStatus(EXTI_LINEx copy_eLineNum,
		EXTI_STATUS_t copy_estatus)
{
	INS_BIT(EXTI->EXTI_IMR, copy_eLineNum, copy_estatus);
}

void MEXTI_voidTriggerSWINT(EXTI_LINEx copy_eLineNum)
{
	EXTI->EXTI_SWIER = 1 << copy_eLineNum;
}

void MEXTI_voidClearPending(EXTI_LINEx copy_eLineNum)
{
	EXTI->EXTI_PR = 1 << copy_eLineNum;
}

u8 MEXTI_u8ISPending(EXTI_LINEx copy_eLineNum)
{
	return GET_BIT(EXTI->EXTI_PR, copy_eLineNum);
}

