/*
 * GPIO_interface.h
 *
 *  Created on: Feb 15, 2022
 *      Author: noureldeen albrmky
 */

#ifndef MCAL_GPIO_GPIO_INTERFACE_H_
#define MCAL_GPIO_GPIO_INTERFACE_H_

typedef enum {
	GPIO_MODE_INPUT,
	GPIO_MODE_OUTPUT_10_MHZ,
	GPIO_MODE_OUTPUT_2_MHZ,
	GPIO_MODE_OUTPUT_50_MHZ

} GPIO_MODE;

typedef enum {
	GPIO_OUTPUT_CNFG_GP_PP,
	GPIO_OUTPUT_CNFG_GP_OD,
	GPIO_OUTPUT_CNFG_ALT_PP,
	GPIO_OUTPUT_CNFG_ALT_OD,
	GPIO_INPUT_CNFG_ANALOG,
	GPIO_INPUT_CNFG_FLOATING,
	GPIO_INPUT_CNFG_PUSH_PULL

} GPIO_CONFIGURATION;

//typedef enum {
//	GPIO_INPUT_MODE_ANALOG,
//	GPIO_INPUT_MODE_FLOATING,
//	GPIO_INPUT_MODE_PUSH_PULL
//
//} GPIO_INPUT_MODE;

typedef enum {
	GPIO_PORTA,
	GPIO_PORTB,
	GPIO_PORTC
} GPIO_PORT;

typedef enum {
	GPIO_LOW,
	GPIO_HIGH,
} GPIO_VALUE;

void MGPIO_voidSetPinDirection(GPIO_PORT copy_u8Port, u8 copy_u8Pin,
		GPIO_MODE copy_u8Mode, GPIO_CONFIGURATION copy_u8CNFG);

void MGPIO_voidSetPinValue(GPIO_PORT copy_u8Port, u8 copy_u8Pin,
		GPIO_VALUE copy_u8Value);

STATUS MGPIO_u8GetPinValue(GPIO_PORT copy_u8Port, u8 copy_u8Pin);

void MGPIO_voidLockPins(GPIO_PORT copy_u8Port, u16 copy_u8LockPattern);

#endif /* MCAL_GPIO_GPIO_INTERFACE_H_ */
