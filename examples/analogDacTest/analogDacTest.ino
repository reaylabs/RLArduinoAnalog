/*
analogDacTest.ino

Description
  Test of the RLArduino Dac class

Author
  Robert Reay

Revision History
  1010-2022 : Initial Code
*/

#include "RLArduinoAnalogDac.h"

//Global Constants
static float vRef = 3.3062;
static uint32_t pin = A0;
static uint8_t bits = 10;
RLArduinoAnalogDac dac(pin, vRef, bits);

void setup() {
  SerialUSB.begin(9600);
  while(!Serial);
  printMenu();
}

void loop() {
  processCommand();
}

void printState() 
{
  SerialUSB.println((String)"Pin: " + dac.getPin());
  SerialUSB.print("Vref: ");
  SerialUSB.println(dac.getVref(), 4);
  SerialUSB.println((String)"Bits: " + dac.getBits()); 
  SerialUSB.print("Offset: ");
  SerialUSB.println(dac.getOffset(), 6); 
  SerialUSB.print("LSB: ");
  SerialUSB.println(dac.getLsb(), 6); 
}

void printMenu()
{
  SerialUSB.println("\n*** Commands ***");
  SerialUSB.println("1: Print State");
  SerialUSB.println("2: Set DAC Code");
  SerialUSB.println("3: Set DAC Voltage");
  SerialUSB.println("4: Calibrate");
  Serial.print("Enter Command: ");
}

void stripCRLF()
{
  while(SerialUSB.peek() == 10 || SerialUSB.peek() == 13)  
  {
    SerialUSB.read();
  }
}

void processCommand()
{
  long code1;
  long code2;
  float voltage1;
  float voltage2;
  while (SerialUSB.available() > 0)
  {
    int command = SerialUSB.parseInt();
    stripCRLF();
    SerialUSB.println(command);
    switch (command) {
      case 1:
        printState();
        SerialUSB.println("Print State Complete");
      break; 
      case 2:
        SerialUSB.print("Enter DAC Code: "); 
        while(!SerialUSB.available()); 
        code1 = SerialUSB.parseInt();
        stripCRLF();
        SerialUSB.println(code1); 
        dac.writeCode(code1);   
        SerialUSB.println("Set DAC Code Complete"); 
        break;
      case 3:
        SerialUSB.print("Enter DAC Voltage: "); 
        while(!SerialUSB.available()); 
        voltage1 = SerialUSB.parseFloat();
        stripCRLF();
        SerialUSB.println(voltage1, 4); 
        dac.writeVoltage(voltage1);   
        SerialUSB.println("Set DAC Voltage Complete"); 
        break;
      case 4:
        code1 = 50;
        code2 = 974;
        dac.writeCode(code1); 
        SerialUSB.print((String)"Enter Measured Voltage For Code=" + code1 + ": "); 
        while(!SerialUSB.available()); 
        voltage1 = SerialUSB.parseFloat();
        stripCRLF();
        SerialUSB.println(voltage1, 4); 
        dac.writeCode(code2); 
        SerialUSB.print((String)"Enter Measured Voltage For Code=" + code2 + ": "); 
        while(!SerialUSB.available()); 
        voltage2 = SerialUSB.parseFloat();
        stripCRLF();
        SerialUSB.println(voltage2, 4); 
        dac.calibrate(code1, code2, voltage1, voltage2);  
        SerialUSB.println("Calibration Complete"); 
        break;
      default:
        SerialUSB.println("Command Not Recognized");
      break;
    }
    printMenu();
  }
}