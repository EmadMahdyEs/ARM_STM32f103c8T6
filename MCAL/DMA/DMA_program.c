/*
 * DMA_program.c
 *
 *  Created on: Mar 4, 2022
 *      Author: noureldeen albrmky
 */

#include "../Inc/LIBRARY/bit_math.h"
#include "../Inc/LIBRARY/standard_types.h"

#include "../Inc/MCAL/DMA/DMA_interface.h"
#include "../Inc/MCAL/DMA/DMA_private.h"
#include "../Inc/MCAL/DMA/DMA_configuration.h"

static void (*IRQ_ARRAY[7])(void)=
{	NULL,NULL,NULL,NULL,NULL,NULL,NULL };

void MDMA_voidConfigure(DMA_CHANNELS_t copy_eChannel, DMA_MODE_t copy_eMode,
		DMA_PERIPHERAL_INC_STATUS_t copy_ePINC,
		DMA_MEMORY_INC_STATUS_t copy_eMINC,
		DMA_ELEMENT_SIZT_t copy_eMemoryElement,
		DMA_ELEMENT_SIZT_t copy_ePeripheralElement,
		DMA_PRIORITY_t copy_ePriority)
{
	// disable DMA Channel first
	MDMA_voidChannelStatus(copy_eChannel, DMA_DISABLE);

	// set mode
	switch (copy_eMode)
	{
		case DMA_MODE_MEMORY_TO_MEMORY:
			SET_BIT(DMA1->CHANNEL[copy_eChannel].DMA_CCR, MEM2MEM_BIT);
			CLR_BIT(DMA1->CHANNEL[copy_eChannel].DMA_CCR, CIRC_BIT); // no circular mode
			CLR_BIT(DMA1->CHANNEL[copy_eChannel].DMA_CCR, DIR_BIT); // peripheral to memory
			break;

		case DMA_MODE_PERIPHERAL_TO_MEMORY:
			CLR_BIT(DMA1->CHANNEL[copy_eChannel].DMA_CCR, MEM2MEM_BIT);
			CLR_BIT(DMA1->CHANNEL[copy_eChannel].DMA_CCR, CIRC_BIT); // no circular mode
			CLR_BIT(DMA1->CHANNEL[copy_eChannel].DMA_CCR, DIR_BIT); // peripheral to memory
			break;

		case DMA_MOODE_MEMORY_TO_PERIPHERAL:
			CLR_BIT(DMA1->CHANNEL[copy_eChannel].DMA_CCR, MEM2MEM_BIT);
			CLR_BIT(DMA1->CHANNEL[copy_eChannel].DMA_CCR, CIRC_BIT); // no circular mode
			SET_BIT(DMA1->CHANNEL[copy_eChannel].DMA_CCR, DIR_BIT); // memory to peripheral
			break;

		case DMA_MODE_PERIPHERAL_TO_MEMORY_CIRCULAR:
			CLR_BIT(DMA1->CHANNEL[copy_eChannel].DMA_CCR, MEM2MEM_BIT);
			SET_BIT(DMA1->CHANNEL[copy_eChannel].DMA_CCR, CIRC_BIT); // no circular mode
			CLR_BIT(DMA1->CHANNEL[copy_eChannel].DMA_CCR, DIR_BIT); // peripheral to memory
			break;

		case DMA_MOODE_MEMORY_TO_PERIPHERAL_CIRCULAR:
			CLR_BIT(DMA1->CHANNEL[copy_eChannel].DMA_CCR, MEM2MEM_BIT);
			SET_BIT(DMA1->CHANNEL[copy_eChannel].DMA_CCR, CIRC_BIT); // no circular mode
			SET_BIT(DMA1->CHANNEL[copy_eChannel].DMA_CCR, DIR_BIT); // memory to peripheral
			break;
	} //switch

	// peripheral increment
	INS_BIT(DMA1->CHANNEL[copy_eChannel].DMA_CCR, PINC_BIT, copy_ePINC);

	// memory increment
	INS_BIT(DMA1->CHANNEL[copy_eChannel].DMA_CCR, MINC_BIT, copy_eMINC);

	// peripheral element size
	INS_FIELD(DMA1->CHANNEL[copy_eChannel].DMA_CCR, 0b11, 8,
			copy_ePeripheralElement);

	// memory element size
	INS_FIELD(DMA1->CHANNEL[copy_eChannel].DMA_CCR, 0b11, 10,
			copy_eMemoryElement);

	// priority
	INS_FIELD(DMA1->CHANNEL[copy_eChannel].DMA_CCR, 0b11, 12, copy_ePriority);

}

void MDMA_voidSetAddress(DMA_CHANNELS_t copy_eChannel, u32 *Peripheral_Address,
		u32 *Memory_Address, u16 Block_size)
{
	DMA1->CHANNEL[copy_eChannel].DMA_CPAR = (u32) Peripheral_Address;
	DMA1->CHANNEL[copy_eChannel].DMA_CMAR = (u32) Memory_Address;
	DMA1->CHANNEL[copy_eChannel].DMA_CNDTR = Block_size;
}

u8 MDMA_u8ReadFlag(DMA_CHANNELS_t copy_eChannel, DMA_FLAGS_t copy_eFlag)
{
	u8 local = GET_BIT(DMA1 ->DMA_ISR, (copy_eChannel * 4 + copy_eFlag));
	return local;
}

void MDMA_voidClearFlag(DMA_CHANNELS_t copy_eChannel, DMA_FLAGS_t copy_eFlag)
{
	SET_BIT(DMA1 ->DMA_IFCR, (copy_eChannel * 4 + copy_eFlag));
}

void MDMA_voidChannelStatus(DMA_CHANNELS_t copy_eChannel,
		DMA_STATUS_t copy_eStatus)
{
	INS_BIT(DMA1->CHANNEL[copy_eChannel].DMA_CCR, 0, copy_eStatus);
}

void MDMA_voidInterruptStatus(DMA_CHANNELS_t copy_eChannel,
		DMA_EVENT_t copy_eEvent, DMA_STATUS_t copy_eStatus)
{
	INS_BIT(DMA1->CHANNEL[copy_eChannel].DMA_CCR, copy_eEvent, copy_eStatus);
}

void MDMA_voidSetCallBack(DMA_CHANNELS_t copy_eChannel, void (*ptr)(void))
{
	IRQ_ARRAY[copy_eChannel] = ptr;
}

/////////////////////////////////////////IRQs/////////////////////////////////////////

void DMA1_Channel1_IRQHandler(void)
{
	if (IRQ_ARRAY[0] != NULL) IRQ_ARRAY[0]();

}

void DMA1_Channel2_IRQHandler(void)
{
	if (IRQ_ARRAY[1] != NULL) IRQ_ARRAY[1]();

}

void DMA1_Channel3_IRQHandler(void)
{
	if (IRQ_ARRAY[2] != NULL) IRQ_ARRAY[2]();

}

void DMA1_Channel4_IRQHandler(void)
{
	if (IRQ_ARRAY[3] != NULL) IRQ_ARRAY[3]();

}

void DMA1_Channel5_IRQHandler(void)
{
	if (IRQ_ARRAY[4] != NULL) IRQ_ARRAY[4]();

}

void DMA1_Channel6_IRQHandler(void)
{
	if (IRQ_ARRAY[5] != NULL) IRQ_ARRAY[5]();

}

void DMA1_Channel7_IRQHandler(void)
{
	if (IRQ_ARRAY[6] != NULL) IRQ_ARRAY[6]();

}
