/*
analogBaseTest.ino

Description
  Test of the RLArduino Analog base class

Author
  Robert Reay

Revision History
  10-04-2022 : Initial Code
*/

#include "RLArduinoAnalogBase.h"

//Global Constants
static float vRef = 4096;
static uint8_t bits = 12;
RLArduinoAnalogBase daq(vRef, bits);

void setup() {
  SerialUSB.begin(9600);
  while(!Serial);
  testDaq();
}

void loop() {
}

void testDaq()
{
  SerialUSB.println("\n *** Starting RLArduinoAnalogBase Test ***\n");
  testInitialConditions();
  testCalibration();
  SerialUSB.println("\n *** RLArduinoAnalogBase Test Complete***\n");
}


void printState()
{
  SerialUSB.println((String)"Bits: " + daq.getBits());
  SerialUSB.println((String)"Vref: " + daq.getVref());
  SerialUSB.println((String)"LSB: " + daq.getLsb());
  SerialUSB.println((String)"Offset: " + daq.getOffset());
}

void printVoltageToCode(float testVoltage)
{
  SerialUSB.print("Code at Voltage=");
  SerialUSB.print(testVoltage);
  SerialUSB.print(": ");
  SerialUSB.println(daq.getCodeFromVoltage(testVoltage));
}

void printCodeToVoltage(long testCode)
{
  SerialUSB.print("Voltage at code=");
  SerialUSB.print(testCode);
  SerialUSB.print(": ");
  SerialUSB.println(daq.getVoltageFromCode(testCode));
}

void testCalibration()
{
  unsigned long code1 = 0;
  unsigned long code2 = 8192;
  float voltage1 = 10e-3;
  float voltage2 = 4096.01;
  SerialUSB.println("\n*** Testing Calibration ****"); 
  SerialUSB.println((String)"Code1: " + code1);
  SerialUSB.println((String)"Code2: " + code2);
  SerialUSB.print("Voltage1: ");
  SerialUSB.println(voltage1,4); 
  SerialUSB.print("Voltage2: ");
  SerialUSB.println(voltage2,4); 
  daq.calibrate(code1, code2, voltage1, voltage2);
  printState();
}

void testInitialConditions()
{
  SerialUSB.println("*** Testing Initial Conditions ****");
  printState();
  printVoltageToCode(0);
  printVoltageToCode(0.49);
  printVoltageToCode(0.51);
  printVoltageToCode(2048);
  printVoltageToCode(4094.49);
  printVoltageToCode(4094.51);
  printVoltageToCode(4095.0);
  printVoltageToCode(4095.49);
  printVoltageToCode(4095.51);
  printVoltageToCode(4096.0);
  printCodeToVoltage(0);
  printCodeToVoltage(daq.getVref()/2);
  printCodeToVoltage(daq.getVref() - daq.getLsb());
}
