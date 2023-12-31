/*
RLArduinoTMP36.h

Description
  TMP36 Temperature sensor class

Author
  Robert Reay
*/

#ifndef _RL_ARDUINO_TMP36_H_
#define _RL_ARDUINO_TMP36_H_

#include "RLArduinoAnalogAdc.h"

class RLArduinoTMP36: public RLArduinoAnalogAdc {
  public:
    explicit RLArduinoTMP36(uint16_t pin, float vRef, uint8_t bits, uint16_t averageCount = 1);
    float readTemperatureC();
    float readTemperatureF();

};

#endif // _RL_ARDUINO_TMP36_H_