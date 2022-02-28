/*
 * LCD_program.c
 *
 *  Created on: Feb 25, 2022
 *      Author: noureldeen albrmky
 */

#include "../Inc/LIBRARY/bit_math.h"
#include "../Inc/LIBRARY/standard_types.h"

#include "../Inc/MCAL/GPIO/GPIO_interface.h"
#include "../Inc/MCAL/SYSTICK/SYSTICK_interface.h"

#include "../Inc/HAL/LCD/LCD_interface.h"
#include "../Inc/HAL/LCD/LCD_private.h"
#include "../Inc/HAL/LCD/LCD_configuration.h"

/****************************************************************************
 1 - All other functions depend on two functions SendCommand and SendData
 2 - SH bit in entry mode command cause problems???????
 *****************************************************************************/

/************************************************************************
 initialize the LCD (this order specified in the data sheet
 ************************************************************************/
void HLCD_voidInit(void)
{

	MSYSTICK_voidDelay_MS(LCD_INITIALIZATION_DELAY);

	// this sequence is according to data sheet
	HLCD_voidSendCommand(LCD_COMMAND_FUNCTION_SET);
	HLCD_voidSendCommand(LCD_COMMAND_DISPLAY_CONTROL);
	HLCD_voidSendCommand(LCD_COMMAND_CLEAR_DISPLAY);
	HLCD_voidSendCommand(LCD_COMMAND_ENTRY_SET);
}

/************************************************************************
 send command to LCD
 ->>>when writing
 1- setup time for asserting R/W and RS before the rising edge of E is at least 40ns
 2- setup time for asserting data before the falling edge of E is at least 80ns
 3- hold up time for R/W,RS and data after the falling edge of E is at least 10ns
 4- the pulse width for E signal is at least 230ns
 5- minimum E signal clock cycle is 500ns which means mx frequency is 2MHz
 6- max time for falling and rising time is 20ns
 ************************************************************************/
void HLCD_voidSendCommand(u8 copy_u8Command)
{

	// choose the type of delay according to the configuration
#if LCD_WAITING_TYPE == LCD_DELAY_FUN
	MSYSTICK_voidDelay_MS(LCD_SLOW_COMMAND_DELAY);
#elif	LCD_WAITING_TYPE == LCD_WAIT_FLAG
	while (HLCD_u8GetFlag());
#endif

	MGPIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_RS_PIN, GPIO_LOW); //select instruction register
	MGPIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_RW_PIN, GPIO_LOW); //write mode
	/*when writing at least 40ns between these two commands*/
	MGPIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_E_PIN, GPIO_HIGH); // E rising edge

	//MSYSTICK_voidDelay_MS(1);

	MGPIO_voidWriteField(LCD_DATA_PORT, GPIO_LOWER_BYTE_MASK, copy_u8Command);
	//MSYSTICK_voidDelay_MS(1);
	MGPIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_E_PIN, GPIO_LOW); // E falling edge
	/* data must be retained after the falling edge for at least 10nsec */

}

/************************************************************************
 send Data to LCD
 ************************************************************************/
void HLCD_voidSendData(u8 copy_u8Char)
{

	// choose the type of delay according to the configuration
#if LCD_WAITING_TYPE == LCD_DELAY_FUN
	MSYSTICK_voidDelay_MS(LCD_SLOW_COMMAND_DELAY);
#elif	LCD_WAITING_TYPE == LCD_WAIT_FLAG
	while (HLCD_u8GetFlag());
#endif

	MGPIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_RS_PIN, GPIO_HIGH); //select data register
	MGPIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_RW_PIN, GPIO_LOW); //	write mode
	/*when writing at least 40ns between these two commands*/
	MGPIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_E_PIN, GPIO_HIGH); // E rising edge

	//MSYSTICK_voidDelay_MS(1);

	MGPIO_voidWriteField(LCD_DATA_PORT, GPIO_LOWER_BYTE_MASK, copy_u8Char);
	//MSYSTICK_voidDelay_MS(1);
	MGPIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_E_PIN, GPIO_LOW); // E falling edge

}

/************************************************************************
 display String
 ************************************************************************/
void HLCD_voidDisplayString(char *copy_pu8String)
{
	while (*copy_pu8String != '\0')
	{
		HLCD_voidSendData(*copy_pu8String++);
	}
}

/************************************************************************
 display number
 ************************************************************************/
void HLCD_voidDisplayNumber(s32 copy_s32Number)
{
	s32 temp = 5;
	//check if the number is negative
	if (copy_s32Number < 0)
	{
		HLCD_voidSendData('-');
		copy_s32Number *= -1;
	}

	if (copy_s32Number == 0)
	{
		HLCD_voidSendData('0');
		return;
	}

	//cascade numbers in reverse order
	while (copy_s32Number != 0)
	{
		temp = temp * 10 + copy_s32Number % 10;
		copy_s32Number /= 10;
	}
	//display them one by one
	while (temp != 5)
	{
		HLCD_voidSendData(temp % 10 + '0');
		temp /= 10;
	}

}

/************************************************************************
 send clear screen command
 ************************************************************************/
void HLCD_voidClearDisplay(void)
{
	HLCD_voidSendCommand(LCD_COMMAND_CLEAR_DISPLAY);
}

/************************************************************************
 specify the address for the position at DDRAM
 ************************************************************************/
void HLCD_voidGoToPos(u8 copy_u8RowNum, u8 copy_u8ColNum)
{
	u8 value = 0x40 * copy_u8RowNum + copy_u8ColNum + 0b10000000;
	HLCD_voidSendCommand(value);
}

/************************************************************************
 send the custom pattern to n location from the 8 locations at CGRAM
 then display it
 ************************************************************************/
void HLCD_voidSendSpecialCharacter(u8 *copy_pu8charArr, u8 copy_u8patternNum,
		u8 copy_u8LineNum, u8 copy_ColNum)
{
	/* set address of first byte of the pattern at pattern number n*/
	HLCD_voidSendCommand(0x40 + 8 * copy_u8patternNum);

	/* send the pattern  data bytes one by one */
	for (u8 i = 0; i < 8; i++)
	{
		HLCD_voidSendData(*copy_pu8charArr++);
		MSYSTICK_voidDelay_uS(45);
	}

	/* set the address in the DDRAM instead of GCRAM */
	HLCD_voidGoToPos(copy_u8LineNum, copy_ColNum);

	HLCD_voidSendData(copy_u8patternNum);

}

/************************************************************************
 sent pattern n at n block at CGRAM only, not displaying it
 if we want to display the character we send the block number with
 HLCD_voidSendData() command
 ************************************************************************/
void HLCD_voidSetSpecialCharacterPattern(u8 *copy_pu8charArr,
		u8 copy_u8patternNum)
{

	// save the current address of DDRAM
	u8 address = HLCD_u8GetDDRAMAddress();
	/* set address of first byte in the pattern of pattern number n*/
	HLCD_voidSendCommand(0x40 + 8 * copy_u8patternNum);

	/* send the pattern  data bytes one by one */
	for (u8 i = 0; i < 8; i++)
	{
		HLCD_voidSendData(*copy_pu8charArr++);
		MSYSTICK_voidDelay_uS(45);

	}

	// set DDRAM address again from where we begin
	HLCD_voidSendCommand(0x80 + address);
}

/*****************************************************************************
 Read the busy flag before start a new command

 steps
 1- make the port as input first
 (LCD already input from previous command so there is no risk of short circuit)
 2- make the reading sequence by R/S and RW pins
 3- E rising edge
 4- according to data sheet the data will be valid to read after 120ns as a maximum
 (we work with 8MHz oscillator so one assembly instruction time will be more than enough)
 5- read data and extract the flag
 6- E falling edge
 7- make the port output again
 *****************************************************************************/
u8 HLCD_u8GetFlag(void)
{

	u8 value;

	MGPIO_voidSetPortDirection(LCD_DATA_PORT, 0, 7, GPIO_MODE_INPUT,
			GPIO_INPUT_CNFG_PUSH_PULL);

	MGPIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_RS_PIN, GPIO_LOW); //select instruction reg
	MGPIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_RW_PIN, GPIO_HIGH); //read mode
	MGPIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_E_PIN, GPIO_HIGH); //E rising edge
	/* data output delay time is at least 120ns*/
	value = MGPIO_u8GetPinValue(LCD_DATA_PORT, 7); // read data and extract the flag(bit 7)

	MGPIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_E_PIN, GPIO_LOW); //E falling edge

	MGPIO_voidSetPortDirection(GPIO_PORTA, 0, 7, GPIO_MODE_OUTPUT_2_MHZ,
			GPIO_OUTPUT_CNFG_GP_PP);

	return value;

}

/****************************************************************
 read address of the DDRAM
 ***************************************************************/
static u8 HLCD_u8GetDDRAMAddress(void)
{

	u16 address;
	u8 value;

	MGPIO_voidSetPortDirection(LCD_DATA_PORT, 0, 7, GPIO_MODE_INPUT,
			GPIO_INPUT_CNFG_PUSH_PULL);

	MGPIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_RS_PIN, GPIO_LOW); //select instruction reg
	MGPIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_RW_PIN, GPIO_HIGH); //read mode
	MGPIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_E_PIN, GPIO_HIGH); //E rising edge
	/* data output delay time is at least 120ns*/

	MGPIO_u16GetPort(LCD_DATA_PORT, &address);
	value = address & (0x007F);

	MGPIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_E_PIN, GPIO_LOW); //E falling edge

	MGPIO_voidSetPortDirection(GPIO_PORTA, 0, 7, GPIO_MODE_OUTPUT_2_MHZ,
			GPIO_OUTPUT_CNFG_GP_PP);

	return value;

}
