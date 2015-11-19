
/*
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *      
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *      
 *      You should have received a copy of the GNU General Public License
 *      along with this program; 
 */


/*  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  
		DioMoni = Digital IO monitor
		
 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  */
 

#ifndef __DioMoni_h__
#define __DioMoni_h__

#include <inttypes.h>

#define		IO_STATE_VAL_BASE				0xD0

#define		IO_STAT_HIGH					(IO_STATE_VAL_BASE + 1 )
#define		IO_STAT_LOW						(IO_STATE_VAL_BASE + 2 )
#define		IO_STAT_LOW2HIGH				(IO_STATE_VAL_BASE + 3 )
#define		IO_STAT_HIGH2LOW				(IO_STATE_VAL_BASE + 4 )
#define		IO_STAT_HIGH2LOW_HOLD			(IO_STATE_VAL_BASE + 5 )
#define		IO_STAT_HIGH2LOW_HOLD_BURST		(IO_STATE_VAL_BASE + 6 )

#define		INTERVAL_MILLIS_DEFAULT			50

class DioMoni
{
	public:
	  DioMoni(unsigned char _pin);
	  DioMoni(unsigned char _pin, unsigned long interval_millis);
	  void setinterval(unsigned long interval_millis);
	  uint8_t check();
	  void reset();
		
	private:
	  unsigned long  previous_millis, interval_millis;

};

#endif


