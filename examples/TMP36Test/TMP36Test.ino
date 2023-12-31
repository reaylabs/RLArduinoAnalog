/*
TMP36Test.ino

Description
  Test of the Fan Controller board

Author
  Robert Reay

Revision History
  12-30-23 : Initial Code
*/

#include "RLArduinoTMP36.h"
#include "RLArduinoSerial.h"

//global Constants
static float vRef = 3.3;
RLArduinoSerial s('\n');  //Create serial object

//pin definitions
#define temp_pin A3

//class constructors
RLArduinoTMP36 fan_temp = RLArduinoTMP36(temp_pin, vRef, 10, 1);  

void setup() {
  Serial.begin(9600);
  while(!Serial);
  printMenu();
}

void loop() {

  int cmd;
  uint8_t channel;
  uint16_t code;
  float voltage;
  //Wait for a user command over the serial port
  while(!s.longAvailable(true)); //Wait for a command
  cmd = s.getLong();
  switch (cmd) {
     case 1: 
      //read temperature
      float temp = fan_temp.readTemperatureC();
      float voltage = fan_temp.readVoltage();
      Serial.print("voltage: ");
      Serial.println(voltage);
      Serial.print("temperature: ");
      Serial.println(temp);
    break;  
  }
  printMenu();
}

void printMenu()
{
  Serial.println("\n\n*** Commands ***");
  Serial.println("1: Read Temperature");
  Serial.print("Enter Command: ");
}

