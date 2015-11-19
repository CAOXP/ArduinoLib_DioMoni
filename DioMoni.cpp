

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "DioMoni.h"

DioMoni::DioMoni(unsigned char _pin)
{
	pin = _pin;
	pinMode(pin,INPUT_PULLUP);
	this->interval_millis = INTERVAL_MILLIS_DEFAULT;
	
}


DioMoni::DioMoni(unsigned char _pin, unsigned long interval_millis)
{	
	pin = _pin;
	pinMode(pin,INPUT_PULLUP);
	this->interval_millis = interval_millis;	
}


void DioMoni::setinterval(unsigned long interval_millis)
{
	if(interval_millis == 0) this->interval_millis = INTERVAL_MILLIS_DEFAULT;
	else 					 this->interval_millis = interval_millis;
}

uint8_t DioMoni::check()
{
	unsigned long now = millis(); 

	if ( (now - previous_millis) < interval_millis) 
	{		
		//...
		return 0;
	}

	
	//time is up
	previous_millis = now ; 
	
	//...

	return 0;

}

void DioMoni::reset() 
{ 
  this->previous_millis = millis();
}



#define 	IO_STAT_IDLE		LOW
#define 	IO_STAT_PRESSED		HIGH

uint8_t DioMoni::getKey()
{
	static uint8_t KeyState   = 0;        //按键状态,状态机使用.
	static boolean bKeyBurst  = false;    //标志连发开始

	static uint8_t KeyPrev    = 0;        		//保存上一次按键,防止出现乱码现象.
	uint8_t KeyPress  = IO_STAT_IDLE;           //按键值
	uint8_t KeyReturn = IO_STAT_IDLE;           //按键返回值

	KeyPress = digitalRead( pin );

	KeyReturn =  KeyPress;
	
	switch(KeyState)
	{
		//按键初始态00
		case 0:
			if( KeyPress !=IO_STAT_IDLE )
			{
				KeyState = 1;
				KeyPrev  = KeyPress;
			}
			break;
		//按键确认态01
		case 1:
			if( KeyPress !=IO_STAT_IDLE  )
			{
				//以下为按键按下处理
				KeyState  = 2;
				KeyReturn = IO_STAT_HIGH2LOW ;         					//按键按下
			}
			else
			{//按键抬起,是抖动,不响应按键
				KeyState = 0;
			}
			break;
		//按键连续态11
		case 2:
			if( KeyPress !=IO_STAT_IDLE )
			{
			 	KeyHoldDly++;
				if( (bKeyBurst ==true) && (KeyHoldDly>keyBurstSpace) )
				{
					KeyHoldDly = 0;
					KeyReturn  = IO_STAT_HIGH2LOW_HOLD_BURST;      		//连发
					break;
				}
				if(KeyHoldDly>keyBurstFirst)
				{
					bKeyBurst  = true;
					KeyHoldDly = 0;
					KeyReturn  = IO_STAT_HIGH2LOW_HOLD;       			//长按后的值
					break;
				}
			}
		//按键释放态10
		case 3:
			if(KeyPress == IO_STAT_IDLE )
			{
				KeyState   = 0;
				KeyHoldDly = 0;
				bKeyBurst  = false;
				KeyReturn  = IO_STAT_LOW2HIGH;              		//抬起值
			}
			break;
		default :break;
	}


	return KeyReturn;
}