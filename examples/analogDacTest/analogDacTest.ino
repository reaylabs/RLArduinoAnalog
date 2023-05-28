/*
analogDacTest.ino

Description
  Test of the RLArduino Dac class
  Three DAC's are set up with different bit counts. 
  The user can write a code or voltage to each DAC or calibrate DAC0 using a voltmeter.

Author
  Robert Reay

*/

#include "RLArduinoAnalogDac.h"
#include "RLArduinoSerial.h"

//Global Constants
static float vRef = 3.3;
RLArduinoSerial s('\n');  //Create serial object

//Create the DAC objects
#if defined(__AVR__)
  int dacCount = 1;
  RLArduinoAnalogDac dac[] = {
    RLArduinoAnalogDac(9, vRef, 8), //8 bit PWM DAC on pin 9
  };
#elif defined(__SAMD21__)
int dacCount = 3;
  RLArduinoAnalogDac dac[] = {
    RLArduinoAnalogDac(A0, vRef, 10),  //10 bit analog DAC on pin A0
    RLArduinoAnalogDac(A1, vRef, 10),  //10 bit analog DAC on pin A1 on SAMD51
    RLArduinoAnalogDac(9, vRef, 16)    //16 bit PWM DAC on pin 9
  };
#elif defined(__SAMD51__)
  int dacCount = 3;
  RLArduinoAnalogDac dac[] = {
    RLArduinoAnalogDac(A0, vRef, 10),  //10 bit analog DAC on pin A0
    RLArduinoAnalogDac(A1, vRef, 10),  //10 bit analog DAC on pin A1
    RLArduinoAnalogDac(9, vRef, 8)     //8 bit PWM DAC on pin 9
  };
#endif

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
  Serial.println("4: Calibrate DAC");
  Serial.println("5: Reset Calibration");
  Serial.print("Enter Command: ");
}

/*
void stripCRLF()
{
  while(Serial.peek() == 10 || Serial.peek() == 13)  
  {
    Serial.read();
  }
}
*/

void processCommand()
{
  long code1;
  long code2;
  float voltage1;
  float voltage2;
  int command;
  int dacNumber = 0;


  while(!s.longAvailable(true)); //Wait for a command
  command = s.getLong();
  Serial.println(command);
  switch (command) {
    case 1:
      printState();
      Serial.println("Print State Complete");
    break; 
    case 2:
      Serial.print("Enter DAC Code: "); 
      while(!s.longAvailable(true)); 
      code1 = s.getLong();
      Serial.println(code1); 
      dac[0].writeCode(code1); 
      delay(1);
      dac[1].writeCode(code1);  
      delay(1);
      dac[2].writeCode(code1); 
      Serial.println("Set DAC Code Complete"); 
      break;
    case 3:
      Serial.print("Enter DAC Voltage: "); 
      while(!s.floatAvailable(true)); 
      voltage1 = s.getFloat();
      Serial.println(voltage1, 4); 
      dac[0].writeVoltage(voltage1);   
      dac[1].writeVoltage(voltage1); 
      dac[2].writeVoltage(voltage1);
      Serial.println("Set DAC Voltage Complete"); 
      break;
    case 4:
      Serial.print("Enter Dac Number For Calibration (0-2): "); 
      while(!s.longAvailable(true)); 
      dacNumber = s.getLong();
      if (dacNumber > 2)
      {
        dacNumber = 2;
      }
      Serial.println(dacNumber); 
      code1 = dac[dacNumber].getCodeFromVoltage(0.1);
      code2 = dac[dacNumber].getCodeFromVoltage(vRef - 0.1);
      dac[dacNumber].writeCode(code1); 
      Serial.print((String)"Enter Measured Voltage For Code=" + code1 + ": "); 
      while(!s.floatAvailable(true)); 
      voltage1 = Serial.parseFloat();
      Serial.println(voltage1, 4); 
      dac[dacNumber].writeCode(code2); 
      Serial.print((String)"Enter Measured Voltage For Code=" + code2 + ": "); 
      while(!s.floatAvailable(true)); 
      voltage2 = Serial.parseFloat();
      Serial.println(voltage2, 4); 
      dac[dacNumber].calibrate(code1, code2, voltage1, voltage2);  
      Serial.println("Calibration Complete"); 
      break;
    case 5:
      Serial.print("Enter Dac Number For Calibration Reset(0-2): "); 
      while(!s.longAvailable(true)); 
      dacNumber = s.getLong();
      if (dacNumber > 2)
      {
        dacNumber = 2;
      }
      Serial.println(dacNumber); 
      dac[dacNumber].resetCalibration();
      Serial.println("Calibration Reset Complete");
      break;
    default:
      Serial.println("Command Not Recognized");
    break;
  }
  printMenu();
}