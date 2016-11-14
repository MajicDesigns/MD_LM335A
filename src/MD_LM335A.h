/*
  MD_LM335A - Library for using a LM335A temperature sensor.
  
  Created by Marco Colli April 2012
  - Does not need floating point library. Temperatures held in hundredths of degree (23C = 2300)
  - Vcc parameter as LM335 is very sensitive to voltage level (nominal 5V)
  
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.
 */
#ifndef MD_LM335A_h
#define MD_LM335A_h

#include "Arduino.h"

class LM335A
{
  public:
    LM335A(int pin);
    LM335A(int pin, int Vcc);
    void Read(void);
	long dF; 	// in 1/100 of degree (32k = 3200)
	long dC;	// in 1/100 of degree
	long dK;	// in 1/100 of degree
	long raw;
	
  private:
    int _pin;
	int _Vcc; 	// in 1/100 V (5V = 500)
};

#endif

