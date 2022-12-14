# RLArduinoAnalog
Set of classes that adds calibration, averaging, and code<->voltage functionality to the internal ADC and DAC.

To install this library, download the .zip file and move the decompressed folder to Documents/Arduino/libraries/. 

## Class Summary
Class RLArduinoAnalogBase
```C++
    explicit    RLArduinoAnalogBase(float vRef, uint8_t bits);
    void        calibrate(uint32_t code1, uint32_t code2, float voltage1, float voltage2);
    uint32_t    getCodeFromVoltage(float voltage);
    uint8_t     getBits();
    uint32_t    getCount();
    float       getLsb();
    float       getOffset();
    float       getVoltageFromCode(uint32_t code);
    float       getVref();
```
Class RLArduinoAnalogDac
```C++
    explicit    RLArduinoAnalogDac(uint16_t pin, float vRef, uint8_t bits);
    uint16_t    getPin();
    void        writeCode(uint32_t code);
    void        writeVoltage(float voltage);
```
Class RLArduinoAnalogAdc
```C++
    explicit    RLArduinoAnalogAdc(uint16_t pin, float vRef, uint8_t bits);
    uint16_t    getPin();
    uint32_t    readCode();
    float       readVoltage();
    void        setAverageCount(uint32_t averageCount);
```