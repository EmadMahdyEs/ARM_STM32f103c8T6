/*
 * LCD_private.h
 *
 *  Created on: Feb 25, 2022
 *      Author: noureldeen albrmky
 */

#ifndef HAL_LCD_LCD_PRIVATE_H_
#define HAL_LCD_LCD_PRIVATE_H_

#define LCD_WAIT_FLAG	0
#define LCD_DELAY_FUN	1

/**********************************************************
 options for function set macros at configuration file
 **********************************************************/
#define LCD_4_BITS_MODE		    0
#define LCD_8_BITS_MODE		    1
#define LCD_1_LINE			    0
#define LCD_2_LINES			    1
#define LCD_5X7_FONT		    0
#define LCD_5X10_FONT		    1

/**********************************************************
 options for display on/off macros at configuration file
 **********************************************************/
#define LCD_DIPLSAY_OFF		    0
#define LCD_DISPLAY_ON		    1
#define LCD_CURSOR_OFF		    0
#define LCD_CURSOR_ON		    1
#define LCD_BLINKING_OFF	    0
#define LCD_BLINKING_ON		    1

/*************************************************************
 options for entry mode macros at configuration file
 *************************************************************/
#define LCD_INCREMENT_SHIFT		1
#define LCD_DECREMENT_SHIFT		0
#define LCD_SHIFT_OFF			0
#define LCD_SHIFT_ON			1

/************************************************************
 Create  initialization commands used in the program.c file
 according to the macros in the configuration files
 *************************************************************/

#define LCD_COMMAND_FUNCTION_SET	CONC_BIT(	0,0,1,\
												LCD_INTERFACE_DATA_LENGTH,\
												LCD_NUMBER_OF_LINES,\
												LCD_CHRACTER_FONT,\
												0,0)

#define LCD_COMMAND_DISPLAY_CONTROL CONC_BIT(	0,0,0,0,1,\
												LCD_DISPLAY_STATE,\
												LCD_CURSOR_STATE,\
												LCD_CURSOR_BLINK_STATE)

#define LCD_COMMAND_ENTRY_SET		CONC_BIT(	0,0,0,0,0,1,\
												LCD_SHIFT_MODE,\
												LCD_SHIFT_STATE	)

static u8 HLCD_u8GetDDRAMAddress(void);

#endif /* HAL_LCD_LCD_PRIVATE_H_ */
