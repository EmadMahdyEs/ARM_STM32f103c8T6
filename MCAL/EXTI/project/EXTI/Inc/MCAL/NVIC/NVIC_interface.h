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

#define NVIC_WWDG			0
#define NVIC_PVD			1
#define NVIC_TAMPER			2
#define NVIC_RTC			3
#define NVIC_FLASH			4
#define NVIC_RCC			5
#define NVIC_EXTI0			6
#define NVIC_EXTI1			7
#define NVIC_EXTI2			8
#define NVIC_EXTI3			9
#define NVIC_EXTI4			10
#define DMA1_CH_1			11
#define DMA1_CH_2			12
#define DMA1_CH_3			13
#define DMA1_CH_4			14
#define DMA1_CH_5			15
#define DMA1_CH_6			16
#define DMA1_CH_7			17
#define ADC1_2				18
#define USB_HP_CAN_TX		19
#define USB_LP_CAN_RX0		20
#define CAN_RX1				21
#define CAN_SCE				22
#define NVIC_EXTI5_9		23
#define TIM1_BRK			24
#define TIM1_UP				25
#define TIM1_TRG_COM		26
#define TIM1_CC				27
#define TIM2				28
#define TIM3				29
#define TIM4				30
#define I2C1_EV				31
#define I2C1_ER				32
#define I2C2_EV				33
#define I2C2_ER				34
#define SPI1				35
#define SPI2				36
#define USART1				37
#define USART2				38
#define USART3				39
#define NVIC_EXTI10_15		40
#define RTCALARM			41
#define USBWakeup			42
#define TIM8_BRK			43
#define TIM8_UP				44
#define TIM8_TRG_COM        45
#define TIM8_CC             46
#define ADC3                47
#define FSMC                48
#define SDIO                49
#define TIM5                50
#define SPI3                51
#define UART4               52
#define UART5               53
#define TIM6                54
#define TIM7                55
#define DMA2_Channel1       56
#define DMA2_Channel2       57
#define DMA2_Channel3       58
#define DMA2_Channel4_5     59

#endif /* MCAL_NVIC_NVIC_INTERFACE_H_ */
