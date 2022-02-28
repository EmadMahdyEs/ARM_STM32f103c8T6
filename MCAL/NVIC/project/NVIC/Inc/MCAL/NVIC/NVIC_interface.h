/*
 * NVIC_interface.h
 *
 *  Created on: Feb 23, 2022
 *      Author: noureldeen albrmky
 */

#ifndef MCAL_NVIC_NVIC_INTERFACE_H_
#define MCAL_NVIC_NVIC_INTERFACE_H_

typedef enum {
	NVIC_16_GROUP_ZERO_SUB = 3,
	NVIC_8_GROUP_2_SUB,
	NVIC_4_GROUP_4_SUB,
	NVIC_2_GROUP_8_SUB,
	NVIC_ZERO_GROUP_16_SUB

} PRIORITY_GROUPING_t;

void MNVIC_voidEnableInterrupt(u8 copy_ISRNumber);
void MNVIC_voidDisableInterrupt(u8 copy_ISRNumber);
void MNVIC_voidSetPendingInterrupt(u8 copy_ISRNumber);
void MNVIC_voidClearPendingInterrupt(u8 copy_ISRNumber);
u8 MNVIC_u8IsINTActive(u8 copy_ISRNumber);

void MNVIC_voidSetPriorityGrouping(PRIORITY_GROUPING_t copy_value);

void MNVIC_voidSetISRPriority(s8 copy_ISRNumber,
		PRIORITY_GROUPING_t copy_GroupingType, u8 copy_Group, u8 copy_Sub);

#define NVIC_MEM_MANG 		-4
#define NVIC_BUS_FAULT		-5
#define NVIC_USAGE_FAULT	-6

#define NVIC_SVCALL			-11
#define NVIC_PENDSV			-14
#define NVIC_SYSTICK		-15

#endif /* MCAL_NVIC_NVIC_INTERFACE_H_ */
