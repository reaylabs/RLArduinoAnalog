/*
RLArduinoAnalogDac.cpp

Description
  DAC data aquisition class 

Author
  Robert Reay

Revision History
  10-10-2022 : Initial Code
*/

#include "RLArduinoAnalogDac.h"

//Constructor
RLArduinoAnalogDac::RLArduinoAnalogDac(uint16_t pin, float vRef, uint8_t bits):RLArduinoAnalogBase(vRef, bits) 
{
  _pin = pin;
 
}

uint16_t RLArduinoAnalogDac::getPin()
{
  return _pin;
}

//Write a code to the DAC
void RLArduinoAnalogDac::writeCode(uint32_t code)
{
  analogWriteResolution(getBits());
  analogWrite(_pin, code);
}

//Write a voltage to the DAC
void RLArduinoAnalogDac::writeVoltage(float voltage)
{
  analogWriteResolution(getBits());
  uint32_t code = getCodeFromVoltage(voltage);
  analogWrite(_pin, code);
}