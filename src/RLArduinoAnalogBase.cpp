/*
RLArduinoAnalogBase.cpp

Description
  Base data aquisition class 

Author
  Robert Reay
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
    _lsb = 1;
    if (_count != 0)
    {
      _lsb = vRef / _count;
    }   
}

//Calibrate
void RLArduinoAnalogBase::calibrate(uint32_t code1, uint32_t code2, float voltage1, float voltage2)
{
  //Two point linear calibration
  uint32_t codeDiff = code2 - code1;
  if (codeDiff != 0)
  {
    _lsb = (voltage2 - voltage1) / (float)(codeDiff); 
    _offset = voltage1 - (_lsb * code1);
  }
  
}


//Get the bits
uint8_t RLArduinoAnalogBase::getBits()
{
  return _bits;
}

//Get the calibration memory size
uint8_t RLArduinoAnalogBase::getCalibrationSize()
{
  return sizeof(_lsb) + sizeof(_offset);
}

//Get the count
uint32_t RLArduinoAnalogBase::getCount()
{
  return _count;
}

//Get the code from the voltage
uint32_t RLArduinoAnalogBase::getCodeFromVoltage(float voltage)
{
  uint32_t code = 0;
  if (_lsb != 0)
  {
    code = (uint32_t)(round((voltage - _offset) / _lsb));
  }
  
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
float RLArduinoAnalogBase::getVoltageFromCode(uint32_t code)
{
  return  _offset + ((float)code * _lsb);
}

//Get Vref
float RLArduinoAnalogBase::getVref()
{
  return _vRef;
}

//Set the calibration
void RLArduinoAnalogBase::setCalibration(float lsb, float offset)
{
  _lsb = lsb;
  /*
  if (_lsb < 0 && _count != 0)
  {
    _lsb = _vRef / _count;
  }*/
  _offset = offset;
}

//Reset the calibration
void RLArduinoAnalogBase::resetCalibration()
{
  if (_count != 0)
  {
    _lsb = _vRef / _count;
  }  
  _offset = 0;  
}