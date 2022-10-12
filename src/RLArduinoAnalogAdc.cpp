/*
RLArduinoAnalogAdc.cpp

Description
  ADC data aquisition class 

Author
  Robert Reay

Revision History
  10-10-2022 : Initial Code
*/

#include "RLArduinoAnalogAdc.h"

//Constructor
RLArduinoAnalogAdc::RLArduinoAnalogAdc(uint16_t pin, float vRef, uint8_t bits):RLArduinoAnalogBase(vRef, bits) 
{
  _pin = pin;
}

uint32_t RLArduinoAnalogAdc::getAverageCount()
{
    return _averageCount;
}

uint16_t RLArduinoAnalogAdc::getPin()
{
  return _pin;
}

uint32_t RLArduinoAnalogAdc::_readAdc()
{

}

uint32_t RLArduinoAnalogAdc::readCode()
{

}

//Read a voltage frmo the ADC
float RLArduinoAnalogAdc::readVoltage()
{

}