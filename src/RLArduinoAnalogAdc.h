/*
RLArduinoAnalogDac.h

Description
  ADC data aquisition class

Author
  Robert Reay
*/

#ifndef _RL_ARDUINO_ANALOG_ADC_H_
#define _RL_ARDUINO_ANALOG_ADC_H_

#include "RLArduinoAnalogBase.h"
#include <wiring_private.h>

class RLArduinoAnalogAdc: public RLArduinoAnalogBase {
  public:
    explicit RLArduinoAnalogAdc(uint16_t pin, float vRef, uint8_t bits, uint16_t averageCount = 1);
    void finishCalibration(float voltage);
    uint32_t getAverageCount();
    uint16_t getPin();
    uint16_t getPrescaler();
    uint16_t getSamplen();
    uint32_t readCode();
    float readVoltage();
    void setAverageCount(uint32_t averageCount);
    void startCalibration(float voltage);
    void setPrescaler(uint16_t prescaler);
    void setSamplen(uint16_t samplen);

  private:
    uint32_t _calibration_code_1;
    uint32_t _calibration_code_2;
    float _calibration_voltage_1;
    float _calibration_voltage_2;
    uint16_t _pin;
    uint32_t _averageCount;
    uint32_t _readAdc();

};

#endif // _RL_ARDUINO_ANALOG_ADC_H_