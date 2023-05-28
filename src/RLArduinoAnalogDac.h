/*
RLArduinoAnalogDac.h

Description
  DAC data aquisition class

Author
  Robert Reay
*/

#ifndef _RL_ARDUINO_ANALOG_DAC_H_
#define _RL_ARDUINO_ANALOG_DAC_H_

#include "RLArduinoAnalogBase.h"

class RLArduinoAnalogDac: public RLArduinoAnalogBase {
  public:
    explicit RLArduinoAnalogDac(uint16_t pin, float vRef, uint8_t bits);
    void continueCalibration(float voltage);
    void finishCalibration(float voltage);
    uint16_t getPin();
    void startCalibration();
    void writeCode(uint32_t code);
    void writeVoltage(float voltage);

  private:
    uint16_t _pin;
    uint32_t _calibration_code_1;
    uint32_t _calibration_code_2;
    float _calibration_voltage_1;
    float _calibration_voltage_2;

};

#endif // _RL_ARDUINO_ANALOG_DAC_H_