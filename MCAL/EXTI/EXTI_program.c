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

static void (*EXTI_IRQ_array[6])(void)=
{	NULL,NULL,NULL,NULL,NULL,NULL };

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

void MEXTI_voidAssignInterruptFun(EXTIx_EVENTS_t copy_eEvent, void (*ptr)(void))
{
	EXTI_IRQ_array[copy_eEvent] = ptr;
}

void EXTI0_IRQHandler(void)
{
	if (EXTI_IRQ_array[EXTI_0_EVENT] != NULL)
	{
		EXTI_IRQ_array[EXTI_0_EVENT]();
	}
}

void EXTI1_IRQHandler(void)
{
	if (EXTI_IRQ_array[EXTI_1_EVENT] != NULL)
	{
		EXTI_IRQ_array[EXTI_1_EVENT]();
	}
}

void EXTI2_IRQHandler(void)
{
	if (EXTI_IRQ_array[EXTI_2_EVENT] != NULL)
	{
		EXTI_IRQ_array[EXTI_2_EVENT]();
	}
}

void EXTI3_IRQHandler(void)
{
	if (EXTI_IRQ_array[EXTI_3_EVENT] != NULL)
	{
		EXTI_IRQ_array[EXTI_3_EVENT]();
	}
}

void EXTI4_IRQHandler(void)
{
	if (EXTI_IRQ_array[EXTI_4_EVENT] != NULL)
	{
		EXTI_IRQ_array[EXTI_4_EVENT]();
	}
}

void EXTI9_5_IRQHandler(void)
{
	if (EXTI_IRQ_array[EXTI_5_9_EVENT] != NULL)
	{
		EXTI_IRQ_array[EXTI_5_9_EVENT]();
	}
}
void EXTI15_10_IRQHandler(void)
{
	if (EXTI_IRQ_array[EXTI_10_15_EVENT] != NULL)
	{
		EXTI_IRQ_array[EXTI_10_15_EVENT]();
	}
}
