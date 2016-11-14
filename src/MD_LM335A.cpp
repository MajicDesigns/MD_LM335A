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

#include "MD_LM335A.h"

int readVcc()
// Calculate current Vcc in mV from the 1.1V reference voltage
{
#if defined(__AVR_ATMega168__) || defined(__AVR_ATMega328__)
  long result = 5000;

  // Read 1.1V reference against AVcc
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  delay(2); 				// Wait for Vref to settle
  ADCSRA |= _BV(ADSC); 		// Convert
  while (bit_is_set(ADCSRA,ADSC));
  result = ADCL;
  result |= ADCH<<8;
  result = 1126400L / result; // Back-calculate AVcc in mV
  
  return(result);
#else
  return(5000);
#endif
  }

LM335A::LM335A(int pin)
{
  pinMode(pin, INPUT);
  _pin = pin;
  _Vcc = -1;
}

LM335A::LM335A(int pin, int Vcc)
{
  pinMode(pin, INPUT);
  _pin = pin;
  _Vcc = Vcc;
}

void LM335A::Read()
{
  if (_Vcc == -1)
	_Vcc = readVcc()/10;
  raw = analogRead(_pin);
  dK = ((100L * raw * _Vcc) / 1024L); // convert 
  dC = dK - 27315L;
  dF = 3200L + (((long)dC * 9L)/5L);
}