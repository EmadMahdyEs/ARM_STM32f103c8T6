#include "../Inc/LIBRARY/bit_math.h"
#include "../Inc/LIBRARY/standard_types.h"

#include "../Inc/MCAL/RCC/RCC_interface.h"
#include "../Inc/MCAL/GPIO/GPIO_interface.h"
#include "../Inc/MCAL/NVIC/NVIC_interface.h"
#include "../Inc/MCAL/EXTI/EXTI_interface.h"
#include "../Inc/MCAL/SYSTICK/SYSTICK_interface.h"

volatile u32 data[100];
volatile u8 counter;
volatile u8 flag;
volatile u32 value;
volatile u8 address;
volatile u8 button;

u8 RED = 1;
u8 GREEN = 2;
u8 BLUE = 3;

void play(void)
{
	if (button == 12)
	{
		MGPIO_voidSetPinValue(GPIO_PORTA, RED, GPIO_LOW);
		MGPIO_voidSetPinValue(GPIO_PORTA, GREEN, GPIO_HIGH);
		MGPIO_voidSetPinValue(GPIO_PORTA, BLUE, GPIO_HIGH);
	}
	else if (button == 24)
	{
		MGPIO_voidSetPinValue(GPIO_PORTA, RED, GPIO_HIGH);
		MGPIO_voidSetPinValue(GPIO_PORTA, GREEN, GPIO_LOW);
		MGPIO_voidSetPinValue(GPIO_PORTA, BLUE, GPIO_HIGH);
	}
	else if (button == 94)
	{
		MGPIO_voidSetPinValue(GPIO_PORTA, RED, GPIO_HIGH);
		MGPIO_voidSetPinValue(GPIO_PORTA, GREEN, GPIO_HIGH);
		MGPIO_voidSetPinValue(GPIO_PORTA, BLUE, GPIO_LOW);
	}
	else if (button == 8)
	{
		MGPIO_voidSetPinValue(GPIO_PORTA, RED, GPIO_LOW);
		MGPIO_voidSetPinValue(GPIO_PORTA, GREEN, GPIO_LOW);
		MGPIO_voidSetPinValue(GPIO_PORTA, BLUE, GPIO_HIGH);
	}
	else if (button == 28)
	{
		MGPIO_voidSetPinValue(GPIO_PORTA, RED, GPIO_HIGH);
		MGPIO_voidSetPinValue(GPIO_PORTA, GREEN, GPIO_LOW);
		MGPIO_voidSetPinValue(GPIO_PORTA, BLUE, GPIO_LOW);
	}
	else if (button == 90)
	{
		MGPIO_voidSetPinValue(GPIO_PORTA, RED, GPIO_LOW);
		MGPIO_voidSetPinValue(GPIO_PORTA, GREEN, GPIO_HIGH);
		MGPIO_voidSetPinValue(GPIO_PORTA, BLUE, GPIO_LOW);
	}

}

void TakeAction(void)
{
	// check first element is about 13500 which is the time of the start bit
	if (data[0] < 15000 && data[0] > 10000)
	{
		for (int i = 0; i <= 32; i++)
		{
			// take action on 1 only to set the corresponding bits
			if (data[i] < 2400 && data[i] > 2000)
			{
				value |= 1 << (i - 1);
			}
		}
	}

	// extract the address
	address = value & 0x000000FF;
	// extract the data
	button = (value & 0x00FF0000) >> 16;
	// clear first element to avoid any noise causing the diode to go LOW
	data[0] = 0;

	flag = 0; // to enter the start condition again
	counter = 0; // to write data from begining again
	value = 0; // to take the new data

	play();
}

void GetFrame(void)
{
	if (flag == 0)
	{
		// first falling edge for the begining of start bit
		MSYSTICK_voidSetIntervalSingle(500000, TakeAction);
		flag = 1;
	}
	else
	{
		data[counter++] = MSYSTICK_u32GetElapsedTime();
		MSYSTICK_voidSetIntervalSingle(500000, TakeAction);
	}
	MEXTI_voidClearPending(EXTI_LINE0);
}

int main(void)
{

//RCC
	MRCC_voidInit();
	MRCC_voidSetPeripheralClock(RCC_GPIOA, RCC_STATUS_ON);
	MRCC_voidSetPeripheralClock(RCC_AFIO, RCC_STATUS_ON);

//GPIO
//EXTI0 PIN
	MGPIO_voidSetPinDirection(GPIO_PORTA, 0, GPIO_MODE_INPUT,
			GPIO_INPUT_CNFG_PUSH_PULL); // A0
	MGPIO_voidSetPinValue(GPIO_PORTA, 0, GPIO_HIGH);

//RGB_LED
	MGPIO_voidSetPinDirection(GPIO_PORTA, 1, GPIO_MODE_OUTPUT_2_MHZ,
			GPIO_OUTPUT_CNFG_GP_PP); //RED
	MGPIO_voidSetPinDirection(GPIO_PORTA, 2, GPIO_MODE_OUTPUT_2_MHZ,
			GPIO_OUTPUT_CNFG_GP_PP); //GREEN
	MGPIO_voidSetPinDirection(GPIO_PORTA, 3, GPIO_MODE_OUTPUT_2_MHZ,
			GPIO_OUTPUT_CNFG_GP_PP); //BLUE

//AFIO
	MAFIO_voidSetEXTILineSource(AFIO_EXTI0_LINE, AFIO_EXTI_GPIOA);

//EXTI
	MEXTI_voidSetInterruptMode(EXTI_LINE0, EXTI_FALLING);
	MEXTI_voidAssignInterruptFun(EXTI_0_EVENT, GetFrame);
	MEXTI_voidEXTILineStatus(EXTI_LINE0, EXTI_ENABLE);

	MNVIC_voidEnableInterrupt(NVIC_EXTI0);

	MSYSTICK_voidInit();

	while (1)
	{

	}
}
