/*
RLArduinoTMP36.cpp

Description
  TMP36 temperature sensor class 

Author
  Robert Reay

*/

#include "RLArduinoTMP36.h"

//Constructor
RLArduinoTMP36::RLArduinoTMP36(uint16_t pin, float vRef, uint8_t bits, uint16_t averageCount):RLArduinoAnalogAdc(pin, vRef, bits, averageCount) 
{

}

float RLArduinoTMP36::readTemperatureC()
{
  return (readVoltage() - 0.5) * 100.0;
}

float RLArduinoTMP36::readTemperatureF()
{
  return readTemperatureC() * 1.8 + 32.0;
}
