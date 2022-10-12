/*
RLArduinoAnalogDac.h

Description
  ADC data aquisition class

Author
  Robert Reay

Revision History
  10-10-2022 : Initial Code
*/

#ifndef _RL_ARDUINO_ANALOG_ADC_H_
#define _RL_ARDUINO_ANALOG_ADC_H_

#include "RLArduinoAnalogBase.h"

class RLArduinoAnalogAdc: public RLArduinoAnalogBase {
  public:
    explicit RLArduinoAnalogAdc(uint16_t pin, float vRef, uint8_t bits);
    uint32_t getAverageCount();
    uint16_t getPin();
    uint32_t readCode();
    float readVoltage();
    void setAverageCount(uint32_t averageCount);

  private:
    uint16_t _pin;
    uint32_t _averageCount;
    uint32_t _readAdc();

};

#endif // _RL_ARDUINO_ANALOG_ADC_H_