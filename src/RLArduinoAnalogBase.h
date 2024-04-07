/*
RLArduinoAnalogBase.h

Description
  Base data aquisition class 

Author
  Robert Reay
*/

#ifndef _RL_ARDUINO_ANALOG_BASE_H_
#define _RL_ARDUINO_ANALOG_BASE_H_

#include "Arduino.h"
#if defined(__AVR__)
  #include <EEPROM.h>
#else
  #include <avr/pgmspace.h> 
#endif

#define RL_ARDUINO_ANALOG_BASE_LIB_VERSION  (F("1.5.0"))

enum encoding {UNIPOLAR, BIPOLAR};

class RLArduinoAnalogBase {
  public:
    //Functions
    explicit RLArduinoAnalogBase(float vRef, uint8_t bits);
    explicit RLArduinoAnalogBase(float vRef, uint8_t bits, float gain, encoding encoding);
    explicit RLArduinoAnalogBase(float vRef, uint8_t bits, float gain, float offset, encoding encoding);
    void calibrate(long code1, long code2, float voltage1, float voltage2);
    void clearBit(uint8_t &reg, uint8_t bit);
    uint32_t getCodeFromVoltage(float voltage);
    uint8_t getBits();
    uint8_t getCalibrationSize();
    float getGain();
    uint32_t getCount();
    float getLsb();
    float getOffset();
    float getVoltageFromCode(long code);
    float getVref();
    void resetCalibration();
    void setBit(uint8_t &reg, uint8_t bit);
    void  setDefaultCalibration(float vRef, uint8_t bits, float gain, encoding encoding);
    void  setDefaultCalibration(float vRef, uint8_t bits, float gain, float offset, encoding encoding);
    void  setCalibration(float lsb, float offset);
    String version();
  
  private:
    uint8_t _bits;
    long _count;
    float _vRef;
    float _offset;
    float _lsb;
    float _gain = 1;
    encoding _encoding = UNIPOLAR;
    const String _version = RL_ARDUINO_ANALOG_BASE_LIB_VERSION;
};

#endif // _RL_ARDUINO_ANALOG_BASE_H_