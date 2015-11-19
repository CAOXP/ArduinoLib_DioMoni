

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
	static uint8_t KeyState   = 0;        //����״̬,״̬��ʹ��.
	static boolean bKeyBurst  = false;    //��־������ʼ

	static uint8_t KeyPrev    = 0;        		//������һ�ΰ���,��ֹ������������.
	uint8_t KeyPress  = IO_STAT_IDLE;           //����ֵ
	uint8_t KeyReturn = IO_STAT_IDLE;           //��������ֵ

	KeyPress = digitalRead( pin );

	KeyReturn =  KeyPress;
	
	switch(KeyState)
	{
		//������ʼ̬00
		case 0:
			if( KeyPress !=IO_STAT_IDLE )
			{
				KeyState = 1;
				KeyPrev  = KeyPress;
			}
			break;
		//����ȷ��̬01
		case 1:
			if( KeyPress !=IO_STAT_IDLE  )
			{
				//����Ϊ�������´���
				KeyState  = 2;
				KeyReturn = IO_STAT_HIGH2LOW ;         					//��������
			}
			else
			{//����̧��,�Ƕ���,����Ӧ����
				KeyState = 0;
			}
			break;
		//��������̬11
		case 2:
			if( KeyPress !=IO_STAT_IDLE )
			{
			 	KeyHoldDly++;
				if( (bKeyBurst ==true) && (KeyHoldDly>keyBurstSpace) )
				{
					KeyHoldDly = 0;
					KeyReturn  = IO_STAT_HIGH2LOW_HOLD_BURST;      		//����
					break;
				}
				if(KeyHoldDly>keyBurstFirst)
				{
					bKeyBurst  = true;
					KeyHoldDly = 0;
					KeyReturn  = IO_STAT_HIGH2LOW_HOLD;       			//�������ֵ
					break;
				}
			}
		//�����ͷ�̬10
		case 3:
			if(KeyPress == IO_STAT_IDLE )
			{
				KeyState   = 0;
				KeyHoldDly = 0;
				bKeyBurst  = false;
				KeyReturn  = IO_STAT_LOW2HIGH;              		//̧��ֵ
			}
			break;
		default :break;
	}


	return KeyReturn;
}