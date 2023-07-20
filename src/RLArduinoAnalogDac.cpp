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

//Record the first calibration voltage and set the second code
void RLArduinoAnalogDac::continueCalibration(float voltage)
{
  _calibration_code_2 = getCodeFromVoltage(getVref() - 0.1);
  _calibration_voltage_1 = voltage;
  writeCode(_calibration_code_2);
}

//Finish the calibration process
void RLArduinoAnalogDac::finishCalibration(float voltage)
{
  _calibration_voltage_2 = voltage;
  calibrate(_calibration_code_1, _calibration_code_2, _calibration_voltage_1, _calibration_voltage_2);
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

//Start the calibration process
void RLArduinoAnalogDac::startCalibration()
{
  resetCalibration();
  _calibration_code_1 = getCodeFromVoltage(0.1);
  writeCode(_calibration_code_1);
}
