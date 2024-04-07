#  RLArduinoAnalog Change Log

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).


## [1.0.0] - 2023-07-18
- Initial release

## [1.1.0] - 2023-07-20
- Remove the #define LIB_VERSION
- Add the version() function
- Update the keywords
- Update the examples with the version() function

## [1.2.0] - 2023-12-30
- Add the RLArduinoTMP36 class

## [1.3.0] - 2024-01-19
- Added the UNIPOLAR and BIPOLAR and Gain capability to the RLArduinoBase class
- Added the setDefaultCalibration function to the RLArduinoBase class
- Added the analogBaseBiolarTest.ino sketch

## [1.3.1] - 2024-01-19
- Added the clearBit and setBit functions
- Modified the analogBaseTest.ino sketch to test the clearBit and setBit functions

## [1.4.0] - 2024-02-18
- Changed the calibration code variables from uint32_t to long

## [1.5.0] - 2024-04-07
- Added the RLArduinoAnalogBase(float vRef, uint8_t bits, float gain, float offset, encoding encoding) that includes the offset
- Modified the offset check in the RLAnalogBase.cpp getCodeFromVoltage to allow for negative gain
- Added the testUnipolar3() test in the analogBaseBipolarTest.ino example