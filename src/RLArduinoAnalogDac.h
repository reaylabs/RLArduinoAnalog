/*
RLArduinoAnalogDac.h

Description
  DAC data aquisition class

Author
  Robert Reay

Revision History
  10-10-2022 : Initial Code
*/

#ifndef _RL_ARDUINO_ANALOG_DAC_H_
#define _RL_ARDUINO_ANALOG_DAC_H_

#include "RLArduinoAnalogBase.h"

class RLArduinoAnalogDac: public RLArduinoAnalogBase {
  public:
    explicit RLArduinoAnalogDac(uint16_t pin, float vRef, uint8_t bits);
    uint16_t getPin();
    void writeCode(uint32_t code);
    void writeVoltage(float voltage);

  private:
    uint16_t _pin;

};

#endif // _RL_ARDUINO_ANALOG_DAC_H_