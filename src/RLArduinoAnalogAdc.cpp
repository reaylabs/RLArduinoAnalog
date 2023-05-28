/*
RLArduinoAnalogAdc.cpp

Description
  ADC data aquisition class 

Author
  Robert Reay

*/

#include "RLArduinoAnalogAdc.h"

//Constructor
RLArduinoAnalogAdc::RLArduinoAnalogAdc(uint16_t pin, float vRef, uint8_t bits, uint16_t averageCount):RLArduinoAnalogBase(vRef, bits) 
{
  _pin = pin;
  _averageCount = averageCount;
}

void RLArduinoAnalogAdc::finishCalibration(float voltage) {
  _calibration_code_2 = _readAdc(); 
  _calibration_voltage_2 = voltage;
  calibrate(_calibration_code_1, _calibration_code_2, _calibration_voltage_1, _calibration_voltage_2);
}

uint32_t RLArduinoAnalogAdc::getAverageCount()
{
    return _averageCount;
}

uint16_t RLArduinoAnalogAdc::getPin()
{
  return _pin;
}

//Get the ADC clock prescaler
uint16_t RLArduinoAnalogAdc::getPrescaler()
{
  #if defined(ARDUINO_SAMD_ZERO)
    return ADC->CTRLB.bit.PRESCALER;
  #elif defined(__SAMD51__)
    return ADC0->CTRLA.bit.PRESCALER;
  #else
    return 0;
  #endif
}

//Get the ADC samplen
uint16_t RLArduinoAnalogAdc::getSamplen()
{
  #if defined(ARDUINO_SAMD_ZERO)
    return ADC->SAMPCTRL.bit.SAMPLEN;
  #elif defined(__SAMD51__)
    return ADC0->SAMPCTRL.bit.SAMPLEN;
  #else
    return 0;
  #endif
}

uint32_t RLArduinoAnalogAdc::_readAdc()
{
  uint32_t average = 0;
  #if !defined(__AVR__)
  analogReadResolution(getBits());
  #endif
  for (uint32_t i = 0; i < _averageCount; i++)
  {
    average += analogRead(_pin);
  }
  average /= _averageCount;
  return average;
 
}

uint32_t RLArduinoAnalogAdc::readCode()
{
  return _readAdc();
}

float RLArduinoAnalogAdc::readVoltage()
{
  return getVoltageFromCode(_readAdc());
}

void RLArduinoAnalogAdc::setAverageCount(uint32_t averageCount)
{
  _averageCount = averageCount;
  if (_averageCount < 1) 
  {
    _averageCount = 1;
  }
}

//Set the ADC clock prescaler
void RLArduinoAnalogAdc::setPrescaler(uint16_t prescaler)
{
  prescaler < 0 ? 0 : prescaler;
  prescaler > 7 ? 7 : prescaler;
  #if defined(ARDUINO_SAMD_ZERO)
    ADC->CTRLB.bit.PRESCALER = prescaler;
    while(ADC->STATUS.bit.SYNCBUSY);  
  #elif defined(__SAMD51__)
    ADC0->CTRLA.bit.PRESCALER = prescaler;
    while( ADC0->SYNCBUSY.reg & ADC_SYNCBUSY_CTRLB);
  #endif
}

//Set the ADC samplen
void RLArduinoAnalogAdc::setSamplen(uint16_t samplen)
{
  samplen < 0 ? 0 : samplen;
  samplen > 63 ? 63 : samplen;
  #if defined(ARDUINO_SAMD_ZERO)
    ADC->SAMPCTRL.bit.SAMPLEN = samplen;
    while(ADC->STATUS.bit.SYNCBUSY);  
  #elif defined(__SAMD51__)
    ADC0->SAMPCTRL.bit.SAMPLEN = samplen;
    while(ADC0->SYNCBUSY.reg & ADC_SYNCBUSY_SAMPCTRL); 
  #endif
}

void RLArduinoAnalogAdc::startCalibration(float voltage) {
  resetCalibration();
  _calibration_code_1 = _readAdc(); 
  _calibration_voltage_1 = voltage;
}