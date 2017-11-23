#ifndef _IO_H_
#define _IO_H_

#include "stm32f7xx_hal.h"
#include "main.h"

#define O_10  0x0001
#define O_11  0x0002
#define O_12  0x0004
#define O_13  0x0008
#define O_14  0x0010
#define O_15  0x0020
#define O_16  0x0040
#define O_17  0x0080
#define O_20  0x0100
#define O_21  0x0200
#define O_22  0x0400
#define O_23  0x0800
#define O_24  0x1000
#define O_25  0x2000
#define O_26  0x4000
#define O_27  0x8000

#define I_03  0x00000001
#define I_01  0x00000002
#define I_02  0x00000004
#define I_00  0x00000008
#define I_04  0x00000010
#define I_05  0x00000020
#define I_06  0x00000040
#define I_07  0x00000080
#define I_13  0x00000100
#define I_11  0x00000200
#define I_12  0x00000400
#define I_10  0x00000800
#define I_14  0x00001000
#define I_15  0x00002000
#define I_16  0x00004000
#define I_17  0x00008000
#define I_23  0x00010000
#define I_21  0x00020000
#define I_22  0x00040000
#define I_20  0x00080000
#define I_24  0x00100000
#define I_25  0x00200000
#define I_26  0x00400000
#define I_27  0x00800000
#define I_30  0x10000000
#define I_31  0x20000000
#define I_32  0x40000000
#define I_33  0x80000000

#define I_MTRALARM 0x01000000
#define I_MTLALARM 0x02000000

#define INPUTCOUNT 5

#pragma anon_unions
typedef  union 
{
	uint16_t data;
	struct
	{
		uint8_t GO_10 : 1;
		uint8_t GO_11 : 1;
		uint8_t GO_12 : 1;
		uint8_t GO_13 : 1;
		uint8_t GO_14 : 1;
		uint8_t GO_15 : 1;
		uint8_t GO_16 : 1;
		uint8_t GO_17 : 1;
		uint8_t GO_20 : 1;
		uint8_t GO_21 : 1;
		uint8_t GO_22 : 1;
		uint8_t GO_23 : 1;
		uint8_t GO_24 : 1;
		uint8_t GO_25 : 1;
		uint8_t GO_26 : 1;
		uint8_t GO_27 : 1;
	};
}IO_output;

typedef  union 
{
	uint32_t data;
	struct
	{
		uint8_t GI_03 : 1;
		uint8_t GI_01 : 1;
		uint8_t GI_02 : 1;
		uint8_t GI_00 : 1;
		uint8_t GI_04 : 1;
		uint8_t GI_05 : 1;
		uint8_t GI_06 : 1;
		uint8_t GI_07 : 1;
		uint8_t GI_13 : 1;
		uint8_t GI_11 : 1;
		uint8_t GI_12 : 1;
		uint8_t GI_10 : 1;
		uint8_t GI_14 : 1;
		uint8_t GI_15 : 1;
		uint8_t GI_16 : 1;
		uint8_t GI_17 : 1;
		uint8_t GI_23 : 1;
		uint8_t GI_21 : 1;
		uint8_t GI_22 : 1;
		uint8_t GI_20 : 1;
		uint8_t GI_24 : 1;
		uint8_t GI_25 : 1;
		uint8_t GI_26 : 1;
		uint8_t GI_27 : 1;
		uint8_t GI_MTRALARM : 1;
		uint8_t GI_MTLALARM : 1;
		uint8_t GI_NONE1 : 1;
		uint8_t GI_NONE2 : 1;
		uint8_t GI_30 : 1;
		uint8_t GI_31 : 1;
		uint8_t GI_32 : 1;
		uint8_t GI_33 : 1;
	};
}IO_input;

void IO_Sethigh(uint8_t IO_Pin);
void IO_Setlow(uint8_t IO_Pin);
void IO_Write(uint8_t IO_Pin, uint8_t value);
uint8_t IO_Read(uint8_t IO, uint32_t IO_Pin);
void IO_Inputupdate(void);
void IO_outputupdate(void);

#endif
