/*
 * NVIC_program.c
 *
 *  Created on: Feb 23, 2022
 *      Author: noureldeen albrmky
 */

#include "../Inc/LIBRARY/bit_math.h"
#include "../Inc/LIBRARY/standard_types.h"

#include "../Inc/MCAL/NVIC/NVIC_interface.h"
#include "../Inc/MCAL/NVIC/NVIC_private.h"
#include "../Inc/MCAL/NVIC/NVIC_configuration.h"

//void MNVIC_voidEnableInterrupt(u8 copy_ISRNumber)
//{
//	volatile u32 *local_reg = NVIC_REG_ISER0 + copy_ISRNumber / 32;
//	*local_reg = 1 << (copy_ISRNumber % 32);
//}
//
//void MNVIC_voidDisableInterrupt(u8 copy_ISRNumber)
//{
//	volatile u32 *local_reg = NVIC_REG_ICER0 + copy_ISRNumber / 32;
//	*local_reg = 1 << (copy_ISRNumber % 32);
//}
//
//void MNVIC_voidSetPendingInterrupt(u8 copy_ISRNumber)
//{
//	volatile u32 *local_reg = NVIC_REG_ISPR0 + copy_ISRNumber / 32;
//	*local_reg = 1 << (copy_ISRNumber % 32);
//}
//
//void MNVIC_voidClearPendingInterrupt(u8 copy_ISRNumber)
//{
//	volatile u32 *local_reg = NVIC_REG_ICPR0 + copy_ISRNumber / 32;
//	*local_reg = 1 << (copy_ISRNumber % 32);
//}
//
//u8 MNVIC_u8IsINTActive(u8 copy_ISRNumber)
//{
//	volatile u32 *local_reg = NVIC_REG_IABR0 + copy_ISRNumber / 32;
//	return GET_BIT((*local_reg), copy_ISRNumber % 32);
//}

/* to enable the interrupt */
void MNVIC_voidEnableInterrupt(u8 copy_ISRNumber)
{
	NVIC->NVIC_ISER[copy_ISRNumber / 32] = 1 << (copy_ISRNumber % 32);
}

/* to disable the interrupt */
void MNVIC_voidDisableInterrupt(u8 copy_ISRNumber)
{
	NVIC->NVIC_ICER[copy_ISRNumber / 32] = 1 << (copy_ISRNumber % 32);
}

/* set the certain interrupt to pending*/
void MNVIC_voidSetPendingInterrupt(u8 copy_ISRNumber)
{
	NVIC->NVIC_ISPR[copy_ISRNumber / 32] = 1 << (copy_ISRNumber % 32);
}

void MNVIC_voidClearPendingInterrupt(u8 copy_ISRNumber)
{
	NVIC->NVIC_ICPR[copy_ISRNumber / 32] = 1 << (copy_ISRNumber % 32);
}

u8 MNVIC_u8IsINTActive(u8 copy_ISRNumber)
{
	return GET_BIT(NVIC->NVIC_ISER[copy_ISRNumber/32], (copy_ISRNumber % 32));
}

void MNVIC_voidSetPriorityGrouping(PRIORITY_GROUPING_t copy_value)
{
	SCB_REG_AIRCR = (copy_value << 8) | (0x5FA << 16);
}

void MNVIC_voidSetISRPriority(s8 copy_ISRNumber,
		PRIORITY_GROUPING_t copy_GroupingType, u8 copy_Group, u8 copy_Sub)
{
	/*
	 * 1- (copy_GroupingType - 3) to know how may bits are shifted
	 * 2- shift group value according to the previous value
	 * 3- add sub group value in the place which is now available after the shift
	 */
	u8 local = copy_Sub | (copy_Group << (copy_GroupingType - 3));
	if (copy_ISRNumber >= 0)
	{
		NVIC->NVIC_IPR[copy_ISRNumber] = local << 4;
	}
	else
	{
		INS_FIELD(*(SCB_REG_SHPR+(-copy_ISRNumber)/4 -1), 0b1111,
				((-copy_ISRNumber) % 4 * 8 + 4), local);
	}
}
