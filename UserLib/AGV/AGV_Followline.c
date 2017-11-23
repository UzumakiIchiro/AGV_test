#include "AGV_Followline.h"


uint8_t _FL_speedleft = 0, _FL_speedright = 0;
extern AGVValue AGV;
extern IO_input  INPUT;


void TLV_Output(uint8_t Channel, uint16_t Data_var)
{
	uint8_t cnt, Speed;
	uint16_t Buffer_Output;

	Speed = Data_var + TLV_OFFSET;                    //caculate speed
	Buffer_Output = ((uint16_t) Channel << 9); //caculate buffer data
	Buffer_Output |= TLV_RNG << 8;
	Buffer_Output |= Speed;
	
	
	
	HAL_GPIO_WritePin(TLV5620_LOAD_GPIO_Port, TLV5620_LOAD_Pin, GPIO_PIN_SET);// TLV_LOAD = 1;
	HAL_GPIO_WritePin(TLV5620_LDAC_GPIO_Port, TLV5620_LDAC_Pin, GPIO_PIN_SET);//TLV_LDAC = 1;

	uint16_t Temp = Buffer_Output;

	for (cnt = 0; cnt <= 10; cnt++)
	{
		HAL_GPIO_WritePin(TLV5620_CLK_GPIO_Port, TLV5620_CLK_Pin, GPIO_PIN_SET);  //TLV_CLK = 1;
		HAL_Delay(1);
		if(Temp & 0x400)
			HAL_GPIO_WritePin(TLV5620_DATA_GPIO_Port, TLV5620_DATA_Pin, GPIO_PIN_SET);//TLV_DATA = 1;
		else 
			HAL_GPIO_WritePin(TLV5620_DATA_GPIO_Port, TLV5620_DATA_Pin, GPIO_PIN_RESET);//TLV_DATA = 0;
		Temp = Temp << 1;                     //shift left 1 bit
		HAL_Delay(1);
		HAL_GPIO_WritePin(TLV5620_CLK_GPIO_Port, TLV5620_CLK_Pin, GPIO_PIN_RESET);//TLV_CLK = 0;
		//delay_cycles(2);
		HAL_Delay(1);
	}

	HAL_GPIO_WritePin(TLV5620_LOAD_GPIO_Port, TLV5620_LOAD_Pin, GPIO_PIN_RESET);//TLV_LOAD = 0;                               //latch to buffer
	//delay_cycles(2);
	HAL_Delay(1);
	HAL_GPIO_WritePin(TLV5620_LOAD_GPIO_Port, TLV5620_LOAD_Pin, GPIO_PIN_SET);//TLV_LOAD = 1;

	//delay_cycles(2);
	HAL_Delay(1);
	HAL_GPIO_WritePin(TLV5620_LDAC_GPIO_Port, TLV5620_LDAC_Pin, GPIO_PIN_RESET);//TLV_LDAC = 0;
	//delay_cycles(2);
	HAL_Delay(1);
	HAL_GPIO_WritePin(TLV5620_LDAC_GPIO_Port, TLV5620_LDAC_Pin, GPIO_PIN_RESET);//TLV_LDAC = 1;
}

void MT_Left(uint8_t mode)
{
    switch(mode)
    {
        case MODE_STOP:
            HAL_GPIO_WritePin(MT_LEFT_RB_GPIO_Port,MT_LEFT_RB_Pin, 0); //Break
            //MT_RUNSTOP_PIN = 0;
						IO_Setlow(AGV.AGV_IO.MTL_RUNSTOP_PIN);
            break;
        case MODE_BRAKE:
            //MT_RUNSTOP_PIN = 0;
						IO_Setlow(AGV.AGV_IO.MTL_RUNSTOP_PIN);
            HAL_GPIO_WritePin(MT_LEFT_RB_GPIO_Port,MT_LEFT_RB_Pin, 1); //Break
            break;
        case MODE_FOR:
            //MT_RUNSTOP_PIN = 1;
						IO_Sethigh(AGV.AGV_IO.MTL_RUNSTOP_PIN);
            HAL_GPIO_WritePin(MT_LEFT_RB_GPIO_Port,MT_LEFT_RB_Pin, 0); //Break
            //OUTPUT.O_11 = 0;
						IO_Setlow(AGV.AGV_IO.MTL_CCW_PIN);
            break;
        case MODE_REV:
            //MT_RUNSTOP_PIN = 1;
						IO_Sethigh(AGV.AGV_IO.MTL_RUNSTOP_PIN);
            HAL_GPIO_WritePin(MT_LEFT_RB_GPIO_Port,MT_LEFT_RB_Pin, 0); //Break
            //OUTPUT.O_11 = 1;
						IO_Sethigh(AGV.AGV_IO.MTL_CCW_PIN);
            break;
    }
}
void MT_Right(uint8_t mode)
{
    switch(mode)
    {
        case MODE_STOP:
            HAL_GPIO_WritePin(MT_RIGHT_RB_GPIO_Port,MT_RIGHT_RB_Pin, 0); //Break
            //MT_RUNSTOP_PIN = 0;
						IO_Setlow(AGV.AGV_IO.MTR_RUNSTOP_PIN);
            break;
        case MODE_BRAKE:
            //MT_RUNSTOP_PIN = 0;
						IO_Setlow(AGV.AGV_IO.MTR_RUNSTOP_PIN);
            HAL_GPIO_WritePin(MT_RIGHT_RB_GPIO_Port,MT_RIGHT_RB_Pin, 1); //Break
            break;
        case MODE_FOR:
            //MT_RUNSTOP_PIN = 1;
						IO_Sethigh(AGV.AGV_IO.MTR_RUNSTOP_PIN);
            HAL_GPIO_WritePin(MT_RIGHT_RB_GPIO_Port,MT_RIGHT_RB_Pin, 0); //Break
            //OUTPUT.O_11 = 0;
						IO_Setlow(AGV.AGV_IO.MTR_CCW_PIN);
            break;
        case MODE_REV:
            //MT_RUNSTOP_PIN = 1;
						IO_Sethigh(AGV.AGV_IO.MTR_RUNSTOP_PIN);
            HAL_GPIO_WritePin(MT_RIGHT_RB_GPIO_Port,MT_RIGHT_RB_Pin, 0); //Break
            //OUTPUT.O_11 = 1;
						IO_Sethigh(AGV.AGV_IO.MTR_CCW_PIN);
            break;
    }
}

void MT_Control(uint8_t control)
{
	    switch(control)
    {
        case MODE_STOP:
            MT_Right(MODE_STOP);
						MT_Left(MODE_STOP);
            break;
        case MODE_BRAKE:
						MT_Right(MODE_BRAKE);
            MT_Left(MODE_BRAKE);
            break;
        case MODE_FOR:
            MT_Left(MODE_REV);
            MT_Right(MODE_FOR);
            break;
        case MODE_REV:
            MT_Left(MODE_FOR);
            MT_Right(MODE_REV);
            break;
        case MODE_RIGHT:
            MT_Left(MODE_REV);
            MT_Right(MODE_REV);
            break;
        case MODE_LEFT:
            MT_Left(MODE_FOR);
            MT_Right(MODE_FOR);
            break;
    }
}


uint8_t Guide_Read()
{
	uint8_t bitoncount = 0, total=0;
	if(AGV.AGV_Followline.Guidetype >= 1) {AGV.AGV_Followline.GUIDE.GV1 = IO_Read(0,AGV.AGV_IO.GUIDE_0_PIN); if(AGV.AGV_Followline.GUIDE.GV1 == 1) {bitoncount++; total+= 1;}}; 
	if(AGV.AGV_Followline.Guidetype >= 2) {AGV.AGV_Followline.GUIDE.GV2 = IO_Read(0,AGV.AGV_IO.GUIDE_1_PIN); if(AGV.AGV_Followline.GUIDE.GV2 == 1) {bitoncount++; total+= 2;}}; 
	if(AGV.AGV_Followline.Guidetype >= 3) {AGV.AGV_Followline.GUIDE.GV3 = IO_Read(0,AGV.AGV_IO.GUIDE_2_PIN); if(AGV.AGV_Followline.GUIDE.GV3 == 1) {bitoncount++; total+= 3;}}; 
	if(AGV.AGV_Followline.Guidetype >= 4) {AGV.AGV_Followline.GUIDE.GV4 = IO_Read(0,AGV.AGV_IO.GUIDE_3_PIN); if(AGV.AGV_Followline.GUIDE.GV4 == 1) {bitoncount++; total+= 4;}}; 
	if(AGV.AGV_Followline.Guidetype >= 5) {AGV.AGV_Followline.GUIDE.GV5 = IO_Read(0,AGV.AGV_IO.GUIDE_4_PIN); if(AGV.AGV_Followline.GUIDE.GV5 == 1) {bitoncount++; total+= 5;}}; 
	if(AGV.AGV_Followline.Guidetype >= 6) {AGV.AGV_Followline.GUIDE.GV6 = IO_Read(0,AGV.AGV_IO.GUIDE_5_PIN); if(AGV.AGV_Followline.GUIDE.GV6 == 1) {bitoncount++; total+= 6;}}; 
	if(AGV.AGV_Followline.Guidetype >= 7) {AGV.AGV_Followline.GUIDE.GV7 = IO_Read(0,AGV.AGV_IO.GUIDE_6_PIN); if(AGV.AGV_Followline.GUIDE.GV7 == 1) {bitoncount++; total+= 7;}}; 
	if(AGV.AGV_Followline.Guidetype >= 8) {AGV.AGV_Followline.GUIDE.GV8 = IO_Read(0,AGV.AGV_IO.GUIDE_7_PIN); if(AGV.AGV_Followline.GUIDE.GV8 == 1) {bitoncount++; total+= 8;}}; 
	if(AGV.AGV_Followline.Guidetype >= 9) {AGV.AGV_Followline.GUIDE.GV9 = IO_Read(0,AGV.AGV_IO.GUIDE_8_PIN); if(AGV.AGV_Followline.GUIDE.GV9 == 1) {bitoncount++; total+= 9;}}; 
	if(AGV.AGV_Followline.Guidetype >= 10) {AGV.AGV_Followline.GUIDE.GV10 = IO_Read(0,AGV.AGV_IO.GUIDE_9_PIN); if(AGV.AGV_Followline.GUIDE.GV10 == 1) {bitoncount++; total+= 110;}}; 
	if(AGV.AGV_Followline.Guidetype >= 11) {AGV.AGV_Followline.GUIDE.GV11 = IO_Read(0,AGV.AGV_IO.GUIDE_10_PIN); if(AGV.AGV_Followline.GUIDE.GV11 == 1) {bitoncount++; total+= 11;}}; 
	if(AGV.AGV_Followline.Guidetype >= 12) {AGV.AGV_Followline.GUIDE.GV12 = IO_Read(0,AGV.AGV_IO.GUIDE_11_PIN); if(AGV.AGV_Followline.GUIDE.GV12 == 1) {bitoncount++; total+= 12;}}; 
	if(AGV.AGV_Followline.Guidetype >= 13) {AGV.AGV_Followline.GUIDE.GV13 = IO_Read(0,AGV.AGV_IO.GUIDE_12_PIN); if(AGV.AGV_Followline.GUIDE.GV13 == 1) {bitoncount++; total+= 13;}}; 
	if(AGV.AGV_Followline.Guidetype >= 14) {AGV.AGV_Followline.GUIDE.GV14 = IO_Read(0,AGV.AGV_IO.GUIDE_13_PIN); if(AGV.AGV_Followline.GUIDE.GV14 == 1) {bitoncount++; total+= 14;}}; 
	if(AGV.AGV_Followline.Guidetype >= 15) {AGV.AGV_Followline.GUIDE.GV15 = IO_Read(0,AGV.AGV_IO.GUIDE_14_PIN); if(AGV.AGV_Followline.GUIDE.GV15 == 1) {bitoncount++; total+= 15;}}; 
	if(AGV.AGV_Followline.Guidetype >= 16) {AGV.AGV_Followline.GUIDE.GV16 = IO_Read(0,AGV.AGV_IO.GUIDE_15_PIN); if(AGV.AGV_Followline.GUIDE.GV16 == 1) {bitoncount++; total+= 16;}}; 
		
	return total*10/bitoncount;
}

void PID_Control()
{
	int8_t error;
	
	error = AGV.AGV_Followline.PID_set_point - AGV.AGV_Followline.Guidevalue;
  AGV.AGV_Followline.PID_integral = (float)(AGV.AGV_Followline.PID_integral + error)* AGV.AGV_Followline.PID_Ki;        
  AGV.AGV_Followline.PID_derivative = (float)(error -  AGV.AGV_Followline.PID_previous_error)*AGV.AGV_Followline.PID_Kd;   
	AGV.AGV_Followline.PID_previous_error = error;
  AGV.AGV_Followline.PID_output =  (error * AGV.AGV_Followline.PID_Kd) + AGV.AGV_Followline.PID_integral + AGV.AGV_Followline.PID_derivative;
}

void FollowLine_Control()
{
	uint16_t temp;
	AGV.AGV_Followline.Guidevalue = Guide_Read();
	
	//Control
	switch(AGV.AGV_Followline.FLControl)
		{
		case FLCONTROL_ALARM_RIGHT:
		case FLCONTROL_ALARM_LEFT:
			
			break;
		case FLCONTROL_BREAK:
			AGV.AGV_Followline.FLStatus = FLSTATUS_BREAKING;
			break;
		case FLCONTROL_STOP:
			AGV.AGV_Followline.FLStatus = FLSTATUS_STOPPING;
			break;
		case FLCONTROL_RUN:
			AGV.AGV_Followline.FLStatus = FLSTATUS_RUNNING;
			break;
		}
	
	// OUTLINE
	if(AGV.AGV_Followline.Guidevalue) {AGV.AGV_Followline.Outlinetime = 0; if(AGV.AGV_Followline.FLControl == FLCONTROL_RUN)  AGV.AGV_Followline.FLStatus = FLSTATUS_RUNNING;}
	if(AGV.AGV_Followline.Outlinetime >= 3000 && AGV.AGV_Followline.FLStatus == FLSTATUS_RUNNING) 
	{
		AGV.AGV_Followline.FLStatus = FLSTATUS_OUTLINE;
	}
	
	
	
	
	switch(AGV.AGV_Followline.FLStatus)
		{
		case FLSTATUS_STOPPING:
			MT_Control(MODE_STOP);
			AGV.AGV_Followline.Speed.Speed_Base = 0; 
			break;
		case FLSTATUS_RUNNING:
			if(AGV.AGV_Followline.Guidevalue)PID_Control();
			if(AGV.AGV_Followline.Guidevalue == AGV.AGV_Followline.PID_set_point && AGV.AGV_Followline.Speed.Speed_Base < AGV.AGV_Followline.Speed.Speed_Set && AGV.AGV_Followline.Speed.Speed_Base >= AGV.AGV_Followline.Speed.Speed_Min) AGV.AGV_Followline.Speed.Speed_Base++;
			temp = AGV.AGV_Followline.Speed.Speed_Base + AGV.AGV_Followline.PID_output;
			if (temp > 255) temp = AGV.AGV_Followline.Speed.Speed_Set;                     
			if (temp < 0) {temp = 0;}  
			_FL_speedright = temp;
			TLV_Output(TLV_ChannelRight,_FL_speedright);
			MT_Control(MODE_FOR);
			break;
		case FLSTATUS_BREAKING:
			MT_Control(MODE_BRAKE);
			AGV.AGV_Followline.Speed.Speed_Base = 0; 
			break;
		case FLSTATUS_OUTLINE:
			AGV.AGV_Followline.Speed.Speed_Base = 0; 
			MT_Control(MODE_BRAKE);
			break;
		}
		TLV_Output(TLV_ChannelRight,_FL_speedright);
	
	
}
