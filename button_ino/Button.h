#ifndef _C_BUTTON_H_
#define _C_BUTTON_H_
#pragma once
#include "Arduino.h"

class Button
{
  public:
    Button(void)
    {
      buttonPin = A0;
      ledPin = 13;
      buttonState = HIGH;
    }
    ~Button(void){}
     int buttonPin;
     int ledPin;
     int buttonState;
     void buttonFun(int buttonpin,int ledpin);
};
#endif
