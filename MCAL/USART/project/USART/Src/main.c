#include "../Inc/LIBRARY/bit_math.h"
#include "../Inc/LIBRARY/standard_types.h"

#include "../Inc/MCAL/RCC/RCC_interface.h"
#include "../Inc/MCAL/GPIO/GPIO_interface.h"
#include "../Inc/MCAL/USART/USART_interface.h"
#include "../Inc/MCAL/NVIC/NVIC_interface.h"

void USART1_IRQHandler(void)
{
	u8 local = MUSART_u8ReceiveChar();
	static u8 x = 0;
	if (local == 'O')
	{
		if (x == 0)
		{
			MGPIO_voidSetPinValue(GPIO_PORTA, 0, GPIO_HIGH);
			x = 1;
			MUSART_voidTransmittString("LED IS ON\r\n");

		}
		else
		{
			MGPIO_voidSetPinValue(GPIO_PORTA, 0, GPIO_LOW);
			x = 0;
			MUSART_voidTransmittString("LED IS OFF\r\n");
		}
	}
}

int main(void)
{
	MRCC_voidInit();
	MRCC_voidSetPeripheralClock(RCC_GPIOA, RCC_STATUS_ON);
	MRCC_voidSetPeripheralClock(RCC_AFIO, RCC_STATUS_ON);
	MRCC_voidSetPeripheralClock(RCC_USART1, RCC_STATUS_ON);

	MGPIO_voidSetPinDirection(GPIO_PORTA, 9, GPIO_MODE_OUTPUT_10_MHZ,
			GPIO_OUTPUT_CNFG_ALT_PP); //TX
	MGPIO_voidSetPinDirection(GPIO_PORTA, 10, GPIO_MODE_INPUT,
			GPIO_INPUT_CNFG_PUSH_PULL); //RX
	MGPIO_voidSetPinDirection(GPIO_PORTA, 0, GPIO_MODE_OUTPUT_10_MHZ,
			GPIO_OUTPUT_CNFG_GP_PP);

	MNVIC_voidEnableInterrupt(NVIC_USART1);

	MUSART_voidInit();
	MUSART_SetINTStatus(USART_READ_DATA_REG_NOT_EMPTY, USART_ENABLE);

	while (1)
	{

	}
	return 1;
}
