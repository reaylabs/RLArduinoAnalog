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

#define LIB_VERSION  (F("1.3.1"))

class RLArduinoAnalogBase {
  public:
    //Variables
    enum encoding {UNIPOLAR, BIPOLAR};

    //Functions
    explicit RLArduinoAnalogBase(float vRef, uint8_t bits);
    explicit RLArduinoAnalogBase(float vRef, uint8_t bits, float gain, encoding encoding);
    void  calculateDefaultCalibration(float vRef, uint8_t bits, float gain, encoding encoding);
    void calibrate(uint32_t code1, uint32_t code2, float voltage1, float voltage2);
    void clearBit(uint8_t &reg, uint8_t bit);
    uint32_t getCodeFromVoltage(float voltage);
    uint8_t getBits();
    uint8_t getCalibrationSize();
    float getGain();
    uint32_t getCount();
    float getLsb();
    float getOffset();
    float getVoltageFromCode(uint32_t code);
    float getVref();
    void resetCalibration();
    void setBit(uint8_t &reg, uint8_t bit);
    void  setDefaultCalibration(float vRef, uint8_t bits, float gain, encoding encoding);
    void  setCalibration(float lsb, float offset);
    String version();
  
  private:
    uint8_t _bits;
    uint32_t _count;
    float _vRef;
    float _offset;
    float _lsb;
    float _gain = 1;
    encoding _encoding = UNIPOLAR;
    const String _version = F("1.3.1");
};

#endif // _RL_ARDUINO_ANALOG_BASE_H_