
#include "IO.h"

IO_output OUTPUT;
IO_input  INPUT;

uint8_t IO_compcount=0;
uint32_t IO_oldinput = 0;

void IO_Sethigh(uint8_t IO_Pin)
{
	OUTPUT.data |= IO_Pin; 
}

void IO_Setlow(uint8_t IO_Pin)
{
	OUTPUT.data &= ~IO_Pin; 
}

void IO_Write(uint8_t IO_Pin, uint8_t value)
{
	if(!value) IO_Setlow(IO_Pin);
	else IO_Sethigh(IO_Pin);
}

uint8_t IO_Read(uint8_t IO, uint32_t IO_Pin) //in = 0; out =1;
{
	uint32_t temp;
	if(IO == 0)
	{
		temp =  INPUT.data;
		return ((temp &= IO_Pin) != 0)? 1:0;
	}
	else
	{
		temp =  OUTPUT.data;
		return ((temp &= IO_Pin) != 0)? 1:0;
	}
}


void IO_Inputupdate()
{
	int8_t count;
	uint32_t temp = 0;
	
	HAL_GPIO_WritePin(EXT_LOAD_GPIO_Port,EXT_LOAD_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(EXT_LOAD_GPIO_Port,EXT_LOAD_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(EXT_LOAD_GPIO_Port,EXT_LOAD_Pin,GPIO_PIN_SET);
	for(count=31;count>=0;count--)
	{
		temp |= HAL_GPIO_ReadPin(EXT_SO_GPIO_Port,EXT_SO_Pin) << count;
		HAL_GPIO_WritePin(EXT_CLk_GPIO_Port,EXT_CLk_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(EXT_CLk_GPIO_Port,EXT_CLk_Pin,GPIO_PIN_RESET);
	}
	if(temp == IO_oldinput) IO_compcount++; else IO_compcount = 0;
	IO_oldinput = temp;
	if(IO_compcount >= INPUTCOUNT)
	{
		INPUT.data = ~temp;
	}
}

void IO_outputupdate()
{
	uint8_t i;
	for(i=0;i<16;i++)
		{
			
			HAL_GPIO_WritePin(HC595_DATA_GPIO_Port,HC595_DATA_Pin, OUTPUT.data & (0x8000>>i));
			HAL_GPIO_WritePin(HC595_CLK_GPIO_Port,HC595_CLK_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(HC595_CLK_GPIO_Port,HC595_CLK_Pin,GPIO_PIN_SET);
			
		}
		HAL_GPIO_WritePin(HC595_LATC_GPIO_Port,HC595_LATC_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(HC595_LATC_GPIO_Port,HC595_LATC_Pin,GPIO_PIN_SET);
}
