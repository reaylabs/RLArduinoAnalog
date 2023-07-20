/*
analogBaseTest.ino

Description
  Test of the RLArduino Analog base class

Author
  Robert Reay
*/

#include "RLArduinoAnalogBase.h"

//Global Constants
static float vRef = 4096;
static uint8_t bits = 12;
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
  Serial.println("*** Starting RLArduinoAnalogBase Test ***\n");
  testInitialConditions();
  testCalibration();
  Serial.println("\n *** RLArduinoAnalogBase Test Complete***\n");
}


void printState()
{
  Serial.println((String)"Bits: " + daq.getBits());
  Serial.println((String)"Vref: " + daq.getVref());
  Serial.println((String)"LSB: " + daq.getLsb());
  Serial.println((String)"Offset: " + daq.getOffset());
}

void printVoltageToCode(float testVoltage)
{
  Serial.print("Code at Voltage=");
  Serial.print(testVoltage);
  Serial.print(": ");
  Serial.println(daq.getCodeFromVoltage(testVoltage));
}

void printCodeToVoltage(long testCode)
{
  Serial.print("Voltage at code=");
  Serial.print(testCode);
  Serial.print(": ");
  Serial.println(daq.getVoltageFromCode(testCode));
}

void testCalibration()
{
  unsigned long code1 = 0;
  unsigned long code2 = 8192;
  float voltage1 = 10e-3;
  float voltage2 = 4096.01;
  Serial.println("\n*** Testing Calibration ****"); 
  Serial.println((String)"Code1: " + code1);
  Serial.println((String)"Code2: " + code2);
  Serial.print("Voltage1: ");
  Serial.println(voltage1,4); 
  Serial.print("Voltage2: ");
  Serial.println(voltage2,4); 
  daq.calibrate(code1, code2, voltage1, voltage2);
  printState();
}

void testInitialConditions()
{
  Serial.println("*** Testing Initial Conditions ****");
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