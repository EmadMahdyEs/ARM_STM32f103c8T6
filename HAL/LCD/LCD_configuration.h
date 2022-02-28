/*
 * LCD_configuration.h
 *
 *  Created on: Feb 25, 2022
 *      Author: noureldeen albrmky
 */

#ifndef HAL_LCD_LCD_CONFIGURATION_H_
#define HAL_LCD_LCD_CONFIGURATION_H_

/*****************************************************************
 how do you like to wait
 currently work with 8-bit mode only

 LCD_WAIT_FLAG		LCD_DELAY_FUN
 ****************************************************************/
#define LCD_WAITING_TYPE	LCD_WAIT_FLAG

/******************************************************************
 specify the port for LCD pins
 options:
 GPIO_PORTA			GPIO_PORTB
 ******************************************************************/
#define LCD_DATA_PORT		GPIO_PORTA
#define LCD_CONTROL_PORT	GPIO_PORTB

/*****************************************************************
 specify the pins for the control
 options:
 0:15 depends on the port
 **************************************************************/
#define LCD_RS_PIN			0
#define LCD_RW_PIN			1
#define LCD_E_PIN			5

/**************************************************************
 function set
 options:
 LCD_4_BITS_MODE			LCD_8_BITS_MODE
 LCD_1_LINE				LCD_2_LINES
 LCD_5X7_FONT			LCD_5X10_FONT

 0b 	0 0 1 DL N F 0 0
 DL:datalines
 N :number of lines
 F :font
 ***************************************************************/
#define LCD_INTERFACE_DATA_LENGTH	LCD_8_BITS_MODE
#define LCD_NUMBER_OF_LINES			LCD_2_LINES
#define LCD_CHRACTER_FONT			LCD_5X7_FONT

/****************************************************************
 Display on/off control
 options:
 LCD_DIPLSAY_OFF				LCD_DISPLAY_ON
 LCD_CURSOR_OFF				LCD_CURSOR_ON
 LCD_BLINKING_OFF			LCD_BLINKING_ON

 NOTE:
 Blinking and cursor are independent from each other

 0b 0 0 0 0 1 D C B
 D : display state
 C : cursor state
 B : blinking state
 ***************************************************************/
#define LCD_DISPLAY_STATE		LCD_DISPLAY_ON
#define LCD_CURSOR_STATE		LCD_CURSOR_OFF
#define LCD_CURSOR_BLINK_STATE	LCD_BLINKING_OFF

/****************************************************************
 entry mode set
 options:
 LCD_INCREMENT_SHIFT				LCD_DECREMENT_SHIFT
 LCD_SHIFT_OFF					LCD_SHIFT_ON

 0b 0 0 0 0 0 0 1 D/H SH
 D/H : decrement or increment mode
 SH  : shift on/off
 ****************************************************************/
#define LCD_SHIFT_MODE			LCD_INCREMENT_SHIFT
#define LCD_SHIFT_STATE			LCD_SHIFT_OFF

/**************************************************************
 amount of delay between commands
 notes:
 first two options in microseconds
 last  two options in milliseconds
 **************************************************************/
#define LCD_DATA_TRANFER_DELAY		43
#define LCD_NORMAL_COMMAND_DELAY	39
#define LCD_SLOW_COMMAND_DELAY		2
#define LCD_INITIALIZATION_DELAY	30

/****************************************************************
 Starting address for Row one and Row two
 ****************************************************************/
#define LCD_ROW1_ADDRESS	127
#define LCD_ROW2_ADDRESS	191

#endif /* HAL_LCD_LCD_CONFIGURATION_H_ */
