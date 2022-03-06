#include "../Inc/LIBRARY/bit_math.h"
#include "../Inc/LIBRARY/standard_types.h"

#include "../Inc/MCAL/RCC/RCC_interface.h"
#include "../Inc/MCAL/NVIC/NVIC_interface.h"
#include "../Inc/MCAL/DMA/DMA_interface.h"
#include "../Inc/MCAL/SYSTICK/SYSTICK_interface.h"

u32 array1[1000];
u32 array2[1000];
u8 flag;

// DMA 769
// processor 2629
u32 time;
u32 time_dma;
u32 tim_processor;

void FOO(void)
{

}

void ISR(void)
{
	MDMA_voidClearFlag(DMA_CHANNEL_1, DMA_TRANSFER_COMPLETE_FLAG);
	time_dma = MSYSTICK_u32GetElapsedTime();
	flag = 1;
}

int main(void)
{
	// RCC
	MRCC_voidInit();
	MRCC_voidSetPeripheralClock(RCC_DMA1, RCC_STATUS_ON);

	// NVIC
	MNVIC_voidEnableInterrupt(NVIC_DMA1_CH_1);

	// initiaize array
	for (u16 i; i < 1000; i++)
	{
		array1[i] = i;
	}

	// DMA
	/*
	 * 1- use configuration function
	 * 2- set address
	 * 3- enable interrupt event
	 * 4- set call back function
	 * 5- enable DMA
	 */
	MDMA_voidConfigure(DMA_CHANNEL_1, DMA_MODE_MEMORY_TO_MEMORY,
			DMA_PERIPHERAL_INC_ENABLE, DMA_MEMORY_INC_ENABLE,
			DMA_ELEMENT_SIZE_32, DMA_ELEMENT_SIZE_32, DMA_PRIORITY_VERY_HIGH);

	MDMA_voidSetAddress(DMA_CHANNEL_1, array1, array2, 1000);

	MDMA_voidInterruptStatus(DMA_CHANNEL_1, DMA_EVENT_TRANSFER_COMPLETE,
			DMA_ENABLE);
	MDMA_voidSetCallBack(DMA_CHANNEL_1, ISR);

	//systick
	MSYSTICK_voidInit();

//	MSYSTICK_voidSetIntervalSingle(100000000, FOO);
//	MDMA_voidChannelStatus(DMA_CHANNEL_1, DMA_ENABLE);

//	while (flag == 0);
//
	MSYSTICK_voidSetIntervalSingle(100000000, FOO);

	MDMA_voidChannelStatus(DMA_CHANNEL_1, DMA_ENABLE);
	for (u16 i; i < 1000; i++)
	{
		array1[i] = array2[i];
	}

	tim_processor = MSYSTICK_u32GetElapsedTime();

	int x = time + 6; // just to stop the debugger after the previous command
	x++;
	while (1)
	{

	}

	return 1;
}
