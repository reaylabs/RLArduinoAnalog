/*
RLArduinoAnalogBase.h

Description
  Base data aquisition class 

Author
  Robert Reay

Revision History
  10-09-2022 : Initial Code
*/

#ifndef _RLARDUINOANALOGBASE_H_
#define _RLARDUINOANALOGBASE_H_

#include "Arduino.h"

class RLArduinoAnalogBase {
  public:
    explicit RLArduinoAnalogBase(float vRef, uint8_t bits);
    void calibrate(unsigned long code1, unsigned long code2, float voltage1, float voltage2);
    unsigned long getCodeFromVoltage(float voltage);
    uint8_t getBits();
    float getLsb();
    float getOffset();
    float getVoltageFromCode(unsigned long code);
    float getVref();

  private:
    uint8_t _bits;
    uint64_t _count;
    float _vRef;
    float _offset;
    float _lsb;
};

#endif // _RLARDUINOANALOGBASE_H_