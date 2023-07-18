/*
RLArduinoComplexRC.cpp

Description
  A complex number represeting a series resistor and capacitor

Author
  Robert Reay

*/

#include "RLArduinoComplexRC.h"
#include <math.h>

//Constructor
RLComplexRC::RLComplexRC(float r, float c, float f)
{
  _r = r;
  _c = c;
  _f = f;
  UpdateValues();
}

void RLComplexRC::updateValues() {
    re = r;
    im = 1 / (_c * 2 * math.pi * _f)
}