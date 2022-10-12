/*
analogDacTest.ino

Description
  Test of the RLArduino Dac class
  Three DAC's are set up with different bit counts. 
  The user can write a code or voltage to each DAC or calibrate DAC0 using a voltmeter.

Author
  Robert Reay

Revision History
  1010-2022 : Initial Code
*/

#include "RLArduinoAnalogDac.h"

//Global Constants
static float vRef = 3.3062;
static int dacCount = 3;

RLArduinoAnalogDac dac[] = {
  RLArduinoAnalogDac(A0, vRef, 10), //Analog DAC on AVR boards
  RLArduinoAnalogDac(A2, vRef, 16), //PWM DAC output
  RLArduinoAnalogDac(A3, vRef, 8)   //PWM DAC output
};

void setup() {
  Serial.begin(9600);
  while(!Serial);
  printMenu();
 
}

void loop() {
  processCommand();
}

void printState() 
{
  for (int i = 0; i < dacCount; i++)
  {
    Serial.println((String)"*** DAC" + i + " ***");
    Serial.println((String)"Pin: " + dac[i].getPin());
    Serial.print("Vref: ");
    Serial.println(dac[i].getVref(), 4);
    Serial.println((String)"Bits: " + dac[i].getBits());
    Serial.println((String)"Count: " + dac[i].getCount()); 
    Serial.print("Offset: ");
    Serial.println(dac[i].getOffset(), 6); 
    Serial.print("LSB: ");
    Serial.println(dac[i].getLsb(), 6); 
  }
}

void printMenu()
{
  Serial.println("\n*** Commands ***");
  Serial.println("1: Print State");
  Serial.println("2: Set DAC Code");
  Serial.println("3: Set DAC Voltage");
  Serial.println("4: Calibrate DAC0");
  Serial.print("Enter Command: ");
}

void stripCRLF()
{
  while(Serial.peek() == 10 || Serial.peek() == 13)  
  {
    Serial.read();
  }
}

void processCommand()
{
  long code1;
  long code2;
  float voltage1;
  float voltage2;
  while (Serial.available() > 0)
  {
    int command = Serial.parseInt();
    int dacNumber = 0;
    stripCRLF();
    Serial.println(command);
    switch (command) {
      case 1:
        printState();
        Serial.println("Print State Complete");
      break; 
      case 2:
        Serial.print("Enter DAC Code: "); 
        while(!Serial.available()); 
        code1 = Serial.parseInt();
        stripCRLF();
        Serial.println(code1); 
        dac[0].writeCode(code1); 
        dac[1].writeCode(code1);  
        dac[2].writeCode(code1); 
        Serial.println("Set DAC Code Complete"); 
        break;
      case 3:
        Serial.print("Enter DAC Voltage: "); 
        while(!Serial.available()); 
        voltage1 = Serial.parseFloat();
        stripCRLF();
        Serial.println(voltage1, 4); 
        dac[0].writeVoltage(voltage1);   
        dac[1].writeVoltage(voltage1); 
        dac[2].writeVoltage(voltage1);
        Serial.println("Set DAC Voltage Complete"); 
        break;
      case 4:
        Serial.print("Enter Dac Number For Calibration (0-2): "); 
        while(!Serial.available()); 
        dacNumber = Serial.parseInt();
        stripCRLF();
        if (dacNumber > 2)
        {
          dacNumber = 2;
        }
        Serial.println(dacNumber); 
        code1 = 50;
        code2 = dac[dacNumber].getCount() - 50;
        dac[dacNumber].writeCode(code1); 
        Serial.print((String)"Enter Measured Voltage For Code=" + code1 + ": "); 
        while(!Serial.available()); 
        voltage1 = Serial.parseFloat();
        stripCRLF();
        Serial.println(voltage1, 4); 
        dac[dacNumber].writeCode(code2); 
        Serial.print((String)"Enter Measured Voltage For Code=" + code2 + ": "); 
        while(!Serial.available()); 
        voltage2 = Serial.parseFloat();
        stripCRLF();
        Serial.println(voltage2, 4); 
        dac[dacNumber].calibrate(code1, code2, voltage1, voltage2);  
        Serial.println("Calibration Complete"); 
        break;
      default:
        Serial.println("Command Not Recognized");
      break;
    }
    printMenu();
  }
}