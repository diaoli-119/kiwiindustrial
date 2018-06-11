#include "Button.h"
Button Bt;

void setup()
{
  pinMode(Bt.ledPin,OUTPUT);
  pinMode(Bt.buttonPin,INPUT);
}
void loop()
{
  Bt.buttonFun(Bt.buttonPin,Bt.ledPin);
}
