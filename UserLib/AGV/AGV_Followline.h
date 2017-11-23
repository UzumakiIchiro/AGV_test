#ifndef _FOLLOWLINW_H_
#define _FOLLOWLINW_H_

#include "stm32f7xx_hal.h"
#include "IO.h"
#include "AGVConfig.h"

#define TLV_ChannelLeft    	(uint16_t)0x01
#define TLV_ChannelRight 		(uint16_t)0x00
#define TLV_RNG         		(uint16_t)0x01
#define TLV_OFFSET      		(uint16_t)0x00

#define MT_STOP        0
#define MT_BRAKE       1
#define MT_FORWARD     2
#define MT_BACKWARD    3
#define MT_TURN_RIGHT  4
#define MT_TURN_LEFT   5

#define MODE_STOP      0
#define MODE_BRAKE     1
#define MODE_FOR       2
#define MODE_REV       3
#define MODE_RIGHT     4
#define MODE_LEFT      5

#define FLSTATUS_STOPPING  0
#define FLSTATUS_RUNNING   1
#define FLSTATUS_BREAKING  2
#define FLSTATUS_OUTLINE   3

#define FLCONTROL_STOP          0
#define FLCONTROL_RUN           1
#define FLCONTROL_BREAK         2
#define FLCONTROL_ALARM_LEFT    3
#define FLCONTROL_ALARM_RIGHT   4
#define FALSE 0
#define TRUE  1

extern uint8_t _FL_speedleft, _FL_speedright;
extern IO_output OUTPUT;

void TLV_Output(uint8_t Channel, uint16_t Data_var);
void MT_Right(uint8_t mode);
void MT_Left(uint8_t mode);
void MT_Control(uint8_t control);
uint8_t Guide_Read(void);
void PID_Control(void);
void FollowLine_Control(void);

#endif
