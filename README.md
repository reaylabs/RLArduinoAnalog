# RLArduinoAnalog
Set of classes that add calibration, averaging, and code<->voltage functionality to the internal ADC and DAC.
Also includes a driver for the TMP36 temperature sensor using the internal ADC. 

To install this library, download the latest released .zip file and move the decompressed folder to Documents/Arduino/libraries/. 

## Class Summary
Class RLArduinoAnalogBase
```C++
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
```
Class RLArduinoAnalogDac
```C++
    explicit RLArduinoAnalogDac(uint16_t pin, float vRef, uint8_t bits);
    void continueCalibration(float voltage);
    void finishCalibration(float voltage);
    uint16_t getPin();
    void startCalibration();
    void writeCode(uint32_t code);
    void writeVoltage(float voltage);
```
Class RLArduinoAnalogAdc
```C++
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
```

Class RLArduinoTMP36
```C++
    explicit RLArduinoTMP36(uint16_t pin, float vRef, uint8_t bits, uint16_t averageCount = 1);
    float readTemperatureC();
    float readTemperatureF();
```