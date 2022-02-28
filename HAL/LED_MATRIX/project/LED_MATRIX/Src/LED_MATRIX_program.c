/*
 * LED_MATRIX_program.c
 *
 *  Created on: Feb 25, 2022
 *      Author: noureldeen albrmky
 */

#include "../Inc/LIBRARY/bit_math.h"
#include "../Inc/LIBRARY/standard_types.h"

#include "../Inc/MCAL/GPIO/GPIO_interface.h"
#include "../Inc/MCAL/SYSTICK/SYSTICK_interface.h"

#include "../Inc/HAL/LED_MATRIX/LED_MATRIX_interface.h"
#include "../Inc/HAL/LED_MATRIX/LED_MATRIX_private.h"
#include "../Inc/HAL/LED_MATRIX/LED_MATRIX_configuration.h"

u8 lMTX_ROWS[16] = {
LMTRX_ROW1,
LMTRX_ROW2,
LMTRX_ROW3,
LMTRX_ROW4,
LMTRX_ROW5,
LMTRX_ROW6,
LMTRX_ROW7,
LMTRX_ROW8 };

u8 lMTX_COLS[16] = {
LMTRX_COL1,
LMTRX_COL2,
LMTRX_COL3,
LMTRX_COL4,
LMTRX_COL5,
LMTRX_COL6,
LMTRX_COL7,
LMTRX_COL8 };

void LMTRX_voidDisableAllColumns(void)
{
	for (int i = 0; i < 16; i += 2)
	{
		MGPIO_voidSetPinValue(lMTX_COLS[i], lMTX_COLS[i + 1], GPIO_HIGH);
	}
}

void LMTRX_voidSetRowValue(u8 copy_pattern)
{
	for (int i = 0; i < 16; i += 2)
	{
		if (GET_BIT(copy_pattern, i / 2))
		{
			MGPIO_voidSetPinValue(lMTX_ROWS[i], lMTX_ROWS[i + 1], GPIO_HIGH);
		}
		else
		{
			MGPIO_voidSetPinValue(lMTX_ROWS[i], lMTX_ROWS[i + 1], GPIO_LOW);
		}

	}
}

void LMTRX_voidDisplayPattern(u8 arr[])
{
	for (int i = 0; i < 16; i += 2)
	{
		LMTRX_voidDisableAllColumns();
		LMTRX_voidSetRowValue(arr[i / 2]);
		MGPIO_voidSetPinValue(lMTX_COLS[i], lMTX_COLS[i + 1], GPIO_LOW);
		MSYSTICK_voidDelay_MS(2);
	}
}

void LMTRX_voidDisplayPattern2(u8 arr[], u8 arr2[])
{
	for (int j = 0; j < 8; j++)
	{
		for (int i = 0; i < 16; i += 2)
		{
			LMTRX_voidDisableAllColumns();
			if (i / 2 <= j)
			{
				LMTRX_voidSetRowValue(arr[i / 2]);
			}
			else
			{
				LMTRX_voidSetRowValue(arr2[i / 2]);
			}

			MGPIO_voidSetPinValue(lMTX_COLS[i], lMTX_COLS[i + 1], GPIO_LOW);
			MSYSTICK_voidDelay_MS(4);
		}
	}
}
