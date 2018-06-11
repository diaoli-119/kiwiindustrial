#include "Button.h"
/*-------------------------------
 *Function:lighten LED while measuring button
 *-------------------------------
 */
void Button::buttonFun(int buttonpin,int ledpin)
{
  buttonState = digitalRead(buttonpin);
  if(buttonState ==LOW)
  {
    digitalWrite(ledpin,HIGH);
  }
  else
  {
    digitalWrite(ledpin,LOW);
  }
}
