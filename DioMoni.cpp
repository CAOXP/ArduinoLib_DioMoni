

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "DioMoni.h"

DioMoni::DioMoni(unsigned char _pin)
{
	pinMode(_pin,INPUT_PULLUP);
	this->interval_millis = INTERVAL_MILLIS_DEFAULT;
	
}


DioMoni::DioMoni(unsigned char _pin, unsigned long interval_millis)
{	
	pinMode(_pin,INPUT_PULLUP);
	this->interval_millis = interval_millis;	
}


void DioMoni::interval(unsigned long interval_millis)
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


