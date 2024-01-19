/*
analogAdcTest.ino

Description
  Test of the RLArduino Adc class
  Connect the DAC output to the ADC input
  The user can write a code or voltage calibrate DAC and ADC using a voltmeter.

Author
  Robert Reay
*/

#include "RLArduinoAnalogAdc.h"
#include "RLArduinoAnalogDac.h"
#include "RLArduinoSerial.h"

//Global Constants
static float vRef = 3.3;
RLArduinoSerial s('\n'); 
RLArduinoAnalogDac dac(A0, vRef, 10);
RLArduinoAnalogAdc adc(A2, vRef, 12, 1);

void setup() {
  Serial.begin(115200);
  while(!Serial);
  Serial.println("RLArduinoAnalog Version: " + s.version()+ "\n");
  printMenu();
  adc.setPrescaler(3);
  adc.setSamplen(63);
  #if defined(ARDUINO_SAMD_ZERO)
    Serial.println("SAMD21");
  #endif
   #if defined(__AVR__)
    Serial.println("AVR");
  #endif
  #if defined(__SAMD51__)
    Serial.println("SAMD51");
  #endif
  #if defined(ADAFRUIT_QTPY_M0)
    Serial.println("QT Py");
  #endif
 #if defined(ADAFRUIT_ITSYBITSY_M4_EXPRESS)
    Serial.println("M4 Express");
  #endif

}

void loop() {
  processCommand();
}

void printState() 
{

  Serial.println((String)"*** DAC ***");
  Serial.println((String)"Pin: " + dac.getPin());
  Serial.print("Vref: ");
  Serial.println(dac.getVref(), 4);
  Serial.println((String)"Bits: " + dac.getBits());
  Serial.println((String)"Count: " + dac.getCount()); 
  Serial.print("Offset: ");
  Serial.println(dac.getOffset(), 6); 
  Serial.print("LSB: ");
  Serial.println(dac.getLsb(), 6); 
  Serial.println();
  Serial.println((String)"*** ADC ***");
  Serial.println((String)"Pin: " + adc.getPin());
  Serial.print("Vref: ");
  Serial.println(adc.getVref(), 4);
  Serial.println((String)"Bits: " + adc.getBits());
  Serial.println((String)"Count: " + adc.getCount()); 
  Serial.print("Offset: ");
  Serial.println(adc.getOffset(), 6); 
  Serial.print("LSB: ");
  Serial.println(adc.getLsb(), 6);  
  Serial.print("Clock Prescaler: ");
  Serial.println(adc.getPrescaler()); 
  Serial.print("Samplen: ");
  Serial.println(adc.getSamplen()); 
}

void printMenu()
{
  Serial.println("\n*** Commands ***");
  Serial.println("1: Print State");
  Serial.println("2: Set DAC Code");
  Serial.println("3: Set DAC Voltage");
  Serial.println("4: Calibrate");
  Serial.println("5: Reset Calibration");
  Serial.println("6: Continuous ADC Read");
  Serial.print("Enter Command: ");
}

void processCommand()
{
  long code1;
  long code2;
  long adcCode1;
  long adcCode2;
  float voltage1;
  float voltage2;
  int command;
  long start;
  long end;
  long averageCount;

  while(!s.longAvailable(true)); //Wait for a command
  command = s.getLong();
  Serial.println(command);
  switch (command) {
    case 1:
      printState();
      Serial.println("*** Print State Complete ***\n");
    break; 
    case 2:
      Serial.print("Enter DAC Code: "); 
      while(!s.longAvailable(true)); 
      code1 = s.getLong();
      Serial.println(code1); 
      dac.writeCode(code1); 
      code2 = adc.readCode();
      delay(1);
      voltage1 = adc.readVoltage();
      Serial.println((String)"Adc Code : " + code2);
      Serial.print("ADC Voltage: ");
      Serial.println(voltage1,4);
      Serial.println("*** Set DAC Code Complete ***\n"); 
      break;
    case 3:
      Serial.print("Enter DAC Voltage: "); 
      while(!s.floatAvailable(true)); 
      voltage1 = s.getFloat();
      Serial.println(voltage1, 4); 
      dac.writeVoltage(voltage1);  
      delay(1);
      code2 = adc.readCode();
      voltage1 = adc.readVoltage();
      Serial.println((String)"Adc Code : " + code2);
      Serial.print("ADC Voltage: ");
      Serial.println(voltage1, 4);
      Serial.println("*** Set DAC Voltage Complete ***"); 
      break;
    case 4:
      code1 = dac.getCodeFromVoltage(0.1);
      code2 = dac.getCodeFromVoltage(vRef - 0.1);
      dac.startCalibration();
      Serial.print((String)"Enter Measured Voltage For Code=" + code1 + ": "); 
      while(!s.floatAvailable(true)); 
      voltage1 = s.getFloat();
      Serial.println(voltage1, 4); 
      adc.startCalibration(voltage1);
      dac.continueCalibration(voltage1);
      Serial.print((String)"Enter Measured Voltage For Code=" + code2 + ": "); 
      while(!s.floatAvailable(true)); 
      voltage2 = s.getFloat();
      Serial.println(voltage2, 4); 
      adc.finishCalibration(voltage2);
      dac.finishCalibration(voltage2);
      Serial.println("*** Calibration Complete ***\n"); 
      break;
    case 5:
      dac.resetCalibration();
      adc.resetCalibration();
      Serial.println("*** Calibration Reset Complete ***");
      break;
    case 6:
      Serial.println("Enter Average Count: ");
      while(!s.longAvailable(true));
      averageCount = s.getLong();
      adc.setAverageCount(averageCount);
      while (!s.stringAvailable(true)) {
        start = micros();
        voltage1 = adc.readVoltage();
        end = micros();
        Serial.print("ADC Voltage: ");
        Serial.print(voltage1,3);
        Serial.println((String)" in " + (end-start) + " (us)");
        delay(1000);        
      }
      Serial.println("*** Continuous ADC Complete ***");
      break;    
    default:
      Serial.print("ADC Voltage: ");
      Serial.println(voltage1,4);
      Serial.println("Command Not Recognized");
    break;
  }
  printMenu();
}