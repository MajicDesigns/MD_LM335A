// Temperature sensor testing
// LM335K temperature sensor on A0, read through the MD_LM335 library
#include <MD_LM335A.h>

LM335A  Temp(A0);

void setup()
{
  Serial.begin(57600);
}

void loop()
{
  // read the value from the sensor
  Temp.Read();

  // display the value - note this is returned in 1/100 of a degree
  // eg, 32F = 3200
  Serial.print(Temp.raw);
  Serial.print(" = ");
  Serial.print(Temp.dK);
  Serial.print("K, ");
  Serial.print(Temp.dC);
  Serial.print("C, ");
  Serial.print(Temp.dF);
  Serial.println("F, ");

  delay(1000);
}
