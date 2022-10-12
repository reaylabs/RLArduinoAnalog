/*
RLArduinoAnalogBase.h

Description
  Base data aquisition class 

Author
  Robert Reay

Revision History
  10-09-2022 : Initial Code
*/

#ifndef _RL_ARDUINO_ANALOG_BASE_H_
#define _RL_ARDUINO_ANALOG_BASE_H_

#include "Arduino.h"

class RLArduinoAnalogBase {
  public:
    explicit RLArduinoAnalogBase(float vRef, uint8_t bits);
    void calibrate(uint32_t code1, uint32_t code2, float voltage1, float voltage2);
    uint32_t getCodeFromVoltage(float voltage);
    uint8_t getBits();
    uint32_t getCount();
    float getLsb();
    float getOffset();
    float getVoltageFromCode(uint32_t code);
    float getVref();

  private:
    uint8_t _bits;
    uint32_t _count;
    float _vRef;
    float _offset;
    float _lsb;
};

#endif // _RL_ARDUINO_ANALOG_BASE_H_