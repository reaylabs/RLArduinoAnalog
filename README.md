# RLArduinoAnalog
Set of classes that adds calibration functionality to the internal ADC and DAC.

To install this library, download the .zip file and move the decompressed folder to Documents/Arduino/libraries/. 

## Class Summary
Class RLArduinoAnalogBase
```C++
    explicit RLArduinoAnalogBase(float vRef, uint8_t bits);
    void calibrate(unsigned long code1, unsigned long code2, float voltage1, float voltage2);
    unsigned long getCodeFromVoltage(float voltage);
    uint8_t getBits();
    float getLsb();
    float getOffset();
    float getVoltageFromCode(unsigned long code);
    float getVref();
```
Class RLArduinoAnalogDac
```C++
    explicit RLArduinoAnalogDac(uint32_t pin, float vRef, uint8_t bits);
    uint32_t getPin();
    void writeCode(unsigned long code);
    void writeVoltage(float voltage);
```