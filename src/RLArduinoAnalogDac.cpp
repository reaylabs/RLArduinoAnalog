/*
RLArduinoAnalogDac.cpp

Description
  DAC data aquisition class 

Author
  Robert Reay
*/

#include "RLArduinoAnalogDac.h"

//Constructor
RLArduinoAnalogDac::RLArduinoAnalogDac(uint16_t pin, float vRef, uint8_t bits):RLArduinoAnalogBase(vRef, bits) 
{
  _pin = pin;
  writeCode(0);  //Initialize to 0
 
}

uint16_t RLArduinoAnalogDac::getPin()
{
  return _pin;
}

//Write a code to the DAC
void RLArduinoAnalogDac::writeCode(uint32_t code)
{
  #if !defined(__AVR__)
  analogWriteResolution(getBits());
  #endif
  analogWrite(_pin, code);
}

//Write a voltage to the DAC
void RLArduinoAnalogDac::writeVoltage(float voltage)
{
  #if !defined(__AVR__)
  analogWriteResolution(getBits());
  #endif
  uint32_t code = getCodeFromVoltage(voltage);
  analogWrite(_pin, code);
}