/*
analogBaseBipolarTest.ino

Description
  Test of the RLArduino Analog base class for a voltmeter front end with +- 125V input range and 24 bit ADC

Author
  Robert Reay
*/

#include "RLArduinoAnalogBase.h"

//Global Constants
float vRef = 3.3;
uint8_t bits = 10;
float gain = 1;

RLArduinoAnalogBase daq(vRef, bits);

void setup() {
  Serial.begin(115200);
  while(!Serial);
  testDaq();
}

void loop() {
}

void testDaq()
{
  Serial.println("RLArduinoAnalogBase Version: " + daq.version()+ "\n");
  testBipolar1();
  testUnipolar1();
  testUnipolar2();
}

void printState()
{
  Serial.println((String)"Bits: " + daq.getBits());
  Serial.print("Vref: ");
  Serial.println(daq.getVref(),5);
  Serial.print("LSB: ");
  Serial.println(daq.getLsb(),8);
  Serial.print("Offset: ");
  Serial.println(daq.getOffset(),5);
  Serial.print("Gain: ");
  Serial.println(daq.getGain(),5);
}

void printVoltageToCode(float testVoltage)
{
  Serial.print("Code at ");
  Serial.print(testVoltage,4);
  Serial.print("V : 0x");
  Serial.println(daq.getCodeFromVoltage(testVoltage),HEX);
}

void printCodeToVoltage(long testCode)
{
  Serial.print("Voltage at code 0x");
  Serial.print(testCode, HEX);
  Serial.print(": ");
  Serial.println(daq.getVoltageFromCode(testCode));
}

void testBipolar1()
{
  Serial.println("\n*** Bipolar Test #1 ****");
  vRef = 2.5;
  bits = 24;
  gain = 50;
  daq.setDefaultCalibration(vRef, bits, gain, daq.BIPOLAR);
  printState();
  printVoltageToCode(-126);
  printVoltageToCode(-125);
  printVoltageToCode(0);
  printVoltageToCode(125);
  printVoltageToCode(126);
  printCodeToVoltage(0);
  printCodeToVoltage(0x800000);
  printCodeToVoltage(0xFFFFFF);
}

void testUnipolar1()
{
  Serial.println("\n*** Unipolar Test #1 ****");
  vRef = 3.3;
  bits = 10;
  gain = 1;
  daq.setDefaultCalibration(vRef, bits, gain, daq.UNIPOLAR);
  printState();
  printVoltageToCode(-1);
  printVoltageToCode(0);
  printVoltageToCode(vRef/2);
  printVoltageToCode(3.3);
  printVoltageToCode(3.4);
}

void testUnipolar2()
{
  Serial.println("\n*** Unipolar Test #1 ****");
  vRef = 2.048;
  bits = 12;
  gain = 2;
  daq.setDefaultCalibration(vRef, bits, gain, daq.UNIPOLAR);
  printState();
  printVoltageToCode(-1);
  printVoltageToCode(0);
  printVoltageToCode(vRef/2);
  printVoltageToCode(2*vRef);
  printVoltageToCode(2.1*vRef);
}