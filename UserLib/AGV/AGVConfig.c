#include "AGVConfig.h"
#include "AGV_Followline.h"
#include "IO.h"
#include "fatfs.h"

AGVValue AGV;

FIL loggingfile, configfile;

uint8_t _isSDCard ;

uint16_t _Count1s, timestart;

void AGV_Configdefault()
{
	//Speed Configuration
	AGV.AGV_Followline.Speed.Speed_Set = 255;
	AGV.AGV_Followline.Speed.Speed_Min = 30;
	//Guide Configuration
	AGV.AGV_Followline.PID_set_point = 45;
	AGV.AGV_Followline.Guidetype = 8;
	//PIN Configuration
	AGV.AGV_IO.MTR_RUNSTOP_PIN = O_10;
	AGV.AGV_IO.MTR_CCW_PIN     = O_11;
	
	
	AGV.AGV_IO.GUIDE_0_PIN     = I_20;
	AGV.AGV_IO.GUIDE_1_PIN     = I_21;
	AGV.AGV_IO.GUIDE_2_PIN     = I_22;
	AGV.AGV_IO.GUIDE_3_PIN     = I_23;
	AGV.AGV_IO.GUIDE_4_PIN     = I_24;
	AGV.AGV_IO.GUIDE_5_PIN     = I_25;
	AGV.AGV_IO.GUIDE_6_PIN     = I_26;
	AGV.AGV_IO.GUIDE_7_PIN     = I_27;
}

void TimerTick()
{
	if(AGV.AGV_Followline.Guidevalue == 0 && AGV.AGV_Followline.Outlinetime < 3000) AGV.AGV_Followline.Outlinetime ++;
	if(timestart < TIMESTART) timestart++;
	else 
		{
			if(AGV.AGV_Followline.FLStatus == FLSTATUS_RUNNING && AGV.AGV_Followline.Speed.Speed_Base < AGV.AGV_Followline.Speed.Speed_Min) AGV.AGV_Followline.Speed.Speed_Base += 1;	
			if(AGV.AGV_Followline.FLStatus == FLSTATUS_RUNNING && AGV.AGV_Followline.Speed.Speed_Base > AGV.AGV_Followline.Speed.Speed_Set && AGV.AGV_Followline.Speed.Speed_Base > AGV.AGV_Followline.Speed.Speed_Min) AGV.AGV_Followline.Speed.Speed_Base -= 1;	
			timestart=0;
		}
	if(_Count1s < 1000) _Count1s++;
	else
		{
			_Count1s = 0;
		}
}
