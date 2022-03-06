/*
 * DMA_interface.h
 *
 *  Created on: Mar 4, 2022
 *      Author: noureldeen albrmky
 */

#ifndef MCAL_DMA_DMA_INTERFACE_H_
#define MCAL_DMA_DMA_INTERFACE_H_

typedef enum {
	DMA_CHANNEL_1,
	DMA_CHANNEL_2,
	DMA_CHANNEL_3,
	DMA_CHANNEL_4,
	DMA_CHANNEL_5,
	DMA_CHANNEL_6,
	DMA_CHANNEL_7
} DMA_CHANNELS_t;

typedef enum {
	DMA_GLOBAL_INT_FLAG,
	DMA_TRANSFER_COMPLETE_FLAG,
	DMA_HALF_TRANSFER_COMPLETE_FLAG,
	DMA_TRANSFER_ERROR_FLAG
} DMA_FLAGS_t;

typedef enum {
	DMA_EVENT_TRANSFER_COMPLETE = 1,
	DMA_EVENT_HALF_TRANSFER,
	DMA_EVENT_TRANSFER_ERROR

} DMA_EVENT_t;

typedef enum {
	DMA_DISABLE,
	DMA_ENABLE
} DMA_STATUS_t;

typedef enum {
	DMA_PERIPHERAL_INC_DISABLE,
	DMA_PERIPHERAL_INC_ENABLE
} DMA_PERIPHERAL_INC_STATUS_t;

typedef enum {
	DMA_MEMORY_INC_DISABLE,
	DMA_MEMORY_INC_ENABLE
} DMA_MEMORY_INC_STATUS_t;

typedef enum {
	DMA_EMEMENT_SIZE_8,
	DMA_ELEMENT_SIZE_16,
	DMA_ELEMENT_SIZE_32
} DMA_ELEMENT_SIZT_t;

typedef enum {
	DMA_PRIORITY_LOW,
	DMA_PRIORITY_MEDIUM,
	DMA_PRIORITY_HIGH,
	DMA_PRIORITY_VERY_HIGH
} DMA_PRIORITY_t;

typedef enum {
	DMA_MODE_MEMORY_TO_MEMORY,
	DMA_MODE_PERIPHERAL_TO_MEMORY,
	DMA_MOODE_MEMORY_TO_PERIPHERAL,
	DMA_MODE_PERIPHERAL_TO_MEMORY_CIRCULAR,
	DMA_MOODE_MEMORY_TO_PERIPHERAL_CIRCULAR
} DMA_MODE_t;

////////////////////////////////////////////// APIs////////////////////////////////////

void MDMA_voidConfigure(DMA_CHANNELS_t copy_eChannel, DMA_MODE_t copy_eMode,
		DMA_PERIPHERAL_INC_STATUS_t copy_ePINC,
		DMA_MEMORY_INC_STATUS_t copy_eMINC,
		DMA_ELEMENT_SIZT_t copy_eMemoryElement,
		DMA_ELEMENT_SIZT_t copy_ePeripheralElement,
		DMA_PRIORITY_t copy_ePriority);

void MDMA_voidSetAddress(DMA_CHANNELS_t copy_eChannel, u32 *Peripheral_Address,
		u32 *Memory_Address, u16 Block_size);

u8 MDMA_u8ReadFlag(DMA_CHANNELS_t copy_eChannel, DMA_FLAGS_t copy_eFlag);

void MDMA_voidClearFlag(DMA_CHANNELS_t copy_eChannel, DMA_FLAGS_t copy_eFlag);

void MDMA_voidChannelStatus(DMA_CHANNELS_t copy_eChannel,
		DMA_STATUS_t copy_eStatus);

void MDMA_voidInterruptStatus(DMA_CHANNELS_t copy_eChannel,
		DMA_EVENT_t copy_eEvent, DMA_STATUS_t copy_eStatus);

void MDMA_voidSetCallBack(DMA_CHANNELS_t copy_eChannel, void (*ptr)(void));

#endif /* MCAL_DMA_DMA_INTERFACE_H_ */
