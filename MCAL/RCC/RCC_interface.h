/*
 * RCC_interface.h
 *
 *  Created on: Feb 14, 2022
 *      Author: noureldeen albrmky
 */

#ifndef MCAL_RCC_RCC_INTERFACE_H_
#define MCAL_RCC_RCC_INTERFACE_H_

// clock sources
typedef enum {
	RCC_HSE = 17,
	RCC_HSI = 1,
	RCC_PLL = 25
} RCC_CLOCK_SOURCE;

typedef enum {
	RCC_PLL_SOURCE_HSI_2,
	RCC_PLL_SOURCE_HSE,
	RCC_PLL_SOURCE_HSE_2
} RCC_PLL_SOURCE;

typedef enum {
	RCC_STATUS_ON = 1,
	RCC_STATUS_OFF = 0
} RCC_STATES;

// system buses
typedef enum {
	RCC_AHB_BUS = 4,
	RCC_APB1_BUS = 8,
	RCC_APB2_BUS = 11
} RCC_BUS;

// prescalers for APB buses
typedef enum {
	RCC_NO_PRESCALER_APB = 0,
	RCC_2_PRESCALER_APB = 4,
	RCC_4_PRESCALER_APB = 5,
	RCC_8_PRESCALER_APB = 6,
	RCC_16_PRESCALER_APB = 7
} RCC_APB_PRESCALER;

// prescalers for AHB bus
typedef enum {
	RCC_NO_PRECALER_AHB = 0,
	RCC_2_PRESCALER_AHB = 8,
	RCC_4_PRESCALER_AHB = 9,
	RCC_8_PRESCALER_AHB = 10,
	RCC_16_PRESCALER_AHB = 11,
	RCC_64_PRESCALER_AHB = 12,
	RCC_128PRESCALER_AHB = 13,
	RCC_256_PRESCALER_AHB = 14,
	RCC_512_PRESCALER_AHB = 15
} RCC_AHB_PRESCALER;

void MRCC_voidInit(void);

u8 MRCC_u8CheckClockSource(RCC_CLOCK_SOURCE copy_u8CLK);

void MRCC_voidSetClockSource(RCC_CLOCK_SOURCE copy_u8Source);

void MRCC_voidEnableClockSource(RCC_CLOCK_SOURCE copy_u8ClockSource,
		RCC_STATES copy_u8state);

void MRCC_voidSetBusClocks(RCC_AHB_PRESCALER copy_AHB,
		RCC_APB_PRESCALER copy_APB1, RCC_APB_PRESCALER copy_APB2);

void MRCC_voidSetPeripheralClock(RCC_BUS copy_u8Bus, u8 copy_u8PeripheralNum,
		RCC_STATES copy_periph_status);

void MRCC_voidConfigurePLL(RCC_PLL_SOURCE souce, u8 mul_factor);

#define RCC_GPIOA	RCC_APB2_BUS,2
#define RCC_GPIOB	RCC_APB2_BUS,3
#define RCC_GPIOC	RCC_APB2_BUS,4

#endif /* MCAL_RCC_RCC_INTERFACE_H_ */
