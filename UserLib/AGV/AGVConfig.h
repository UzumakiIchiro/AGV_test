#ifndef _AGVCONFIG_H_
#define _AGVCONFIG_H_

#include "stm32f7xx_hal.h"

# define TIMESTART 100

#pragma anon_unions
typedef struct
{
	struct
	{
		uint16_t Voltage; // AGV's Voltage
		uint16_t Current; // AGV's Current
		uint8_t  Level;		// AGV's Level battery
	}AGV_Power;
	
	struct
	{
		
		struct 
		{
			uint8_t Speed_Base;
			uint8_t Speed_Set;
			uint8_t Speed_Min;
		} Speed;
		
		double   PID_Kp;
		double   PID_Ki;
		double   PID_Kd;
		uint16_t Timeexample;
		float    PID_integral, PID_derivative;
		uint8_t  PID_set_point;
		int8_t   PID_previous_error;
		float    PID_output;
		
		uint8_t  Guidetype;
		uint8_t  Guidevalue;
		uint8_t  Guidecount;
		uint16_t Outlinetime;
		uint8_t  FLStatus;
		uint8_t  FLControl;
		
		union 
		{
			uint16_t  Guidebit;
			struct
				{
					uint8_t  GV1 :1;
					uint8_t  GV2 :1;
					uint8_t  GV3 :1;
					uint8_t  GV4 :1;
					uint8_t  GV5 :1;
					uint8_t  GV6 :1;
					uint8_t  GV7 :1;
					uint8_t  GV8 :1;
					uint8_t  GV9 :1;
					uint8_t  GV10 :1;
					uint8_t  GV11 :1;
					uint8_t  GV12 :1;
					uint8_t  GV13 :1;
					uint8_t  GV14 :1;
					uint8_t  GV15 :1;
					uint8_t  GV16 :1;
				};
		}GUIDE;
	}AGV_Followline;
	
	struct
	{
		uint16_t MTR_RUNSTOP_PIN;
		uint16_t MTR_CCW_PIN;
		uint16_t MTL_RUNSTOP_PIN;
		uint16_t MTL_CCW_PIN;
		
		uint32_t GUIDE_0_PIN;
		uint32_t GUIDE_1_PIN;
		uint32_t GUIDE_2_PIN;
		uint32_t GUIDE_3_PIN;
		uint32_t GUIDE_4_PIN;
		uint32_t GUIDE_5_PIN;
		uint32_t GUIDE_6_PIN;
		uint32_t GUIDE_7_PIN;
		uint32_t GUIDE_8_PIN;
		uint32_t GUIDE_9_PIN;
		uint32_t GUIDE_10_PIN;
		uint32_t GUIDE_11_PIN;
		uint32_t GUIDE_12_PIN;
		uint32_t GUIDE_13_PIN;
		uint32_t GUIDE_14_PIN;
		uint32_t GUIDE_15_PIN;
	} AGV_IO;
	
} AGVValue;

void AGV_Configdefault(void);
void TimerTick(void);
#endif
