/*
RLArduinoAnalogDac.h

Description
  DAC data aquisition class

Author
  Robert Reay

Revision History
  10-10-2022 : Initial Code
*/

#ifndef _RLARDUINOANALOGDAC_H_
#define _RLARDUINOANALOGDAC_H_

#include "RLArduinoAnalogBase.h"

class RLArduinoAnalogDac: public RLArduinoAnalogBase {
  public:
    explicit RLArduinoAnalogDac(uint32_t pin, float vRef, uint8_t bits);
    uint32_t getPin();
    void writeCode(unsigned long code);
    void writeVoltage(float voltage);

  private:
    uint32_t _pin;

};

#endif // _RLARDUINOANALOGDAC_H_