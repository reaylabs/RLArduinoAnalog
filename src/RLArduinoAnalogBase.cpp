/*
RLArduinoAnalogBase.cpp

Description
  Base data aquisition class 

Author
  Robert Reay

Revision History
  10-09-2022 : Initial Code
*/

#include "RLArduinoAnalogBase.h"
#include <math.h>

//Constructor
RLArduinoAnalogBase::RLArduinoAnalogBase(float vRef, uint8_t bits)
{
    _bits = bits;
    _count = 0x1 << _bits;
    _vRef = vRef;
    _offset = 0;
    _lsb = vRef / _count;
}

//Calibrate
void RLArduinoAnalogBase::calibrate(unsigned long code1, unsigned long code2, float voltage1, float voltage2)
{
  _lsb = (voltage2 - voltage1) / (float)(code2 - code1);
  _offset = voltage1 - (_lsb * code1);
}


//Get the bits
uint8_t RLArduinoAnalogBase::getBits()
{
  return _bits;
}

//Get the code from the voltage
unsigned long RLArduinoAnalogBase::getCodeFromVoltage(float voltage)
{
  unsigned long code = (unsigned long)(round((voltage - _offset) / _lsb));
  if (code > _count -1)
  {
    code = _count - 1;
  }
  if (code < 0)
  {
    code = 0;
  }
  return code;
  
}

//Get the LSB
float RLArduinoAnalogBase::getLsb()
{
  return _lsb;
}

//Get the Offset
float RLArduinoAnalogBase::getOffset()
{
  return _offset;
}

//Get the voltage from the code
float RLArduinoAnalogBase::getVoltageFromCode(unsigned long code)
{
  return  _offset + ((float)code * _lsb);
}

//Get Vref
float RLArduinoAnalogBase::getVref()
{
  return _vRef;
}