/*
 * DMA_private.h
 *
 *  Created on: Mar 4, 2022
 *      Author: noureldeen albrmky
 */

#ifndef MCAL_DMA_DMA_PRIVATE_H_
#define MCAL_DMA_DMA_PRIVATE_H_

typedef struct {
	volatile u32 DMA_CCR;
	volatile u32 DMA_CNDTR;
	volatile u32 DMA_CPAR;
	volatile u32 DMA_CMAR;
	volatile u32 RESERVED;
} DMACHANNEL_t;

typedef struct {
	volatile u32 DMA_ISR;
	volatile u32 DMA_IFCR;
	DMACHANNEL_t CHANNEL[7];

} DMA_t;

#define DMA1 ( (volatile DMA_t*)0x40020000 )

#define MEM2MEM_BIT	14
#define MINC_BIT	7
#define PINC_BIT	6
#define CIRC_BIT	5
#define DIR_BIT		4

#endif /* MCAL_DMA_DMA_PRIVATE_H_ */
