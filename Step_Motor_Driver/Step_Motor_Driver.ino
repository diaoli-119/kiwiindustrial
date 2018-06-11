#include "Step_Motor_Driver.h"

int distance = 0; // record the number of steps we have taken

void setup()
{
  //Serial.begin(9600);
  Serial.println("setup");
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
}

void loop()
{
  digitalWrite(9, LOW);
  delayMicroseconds(100);
  digitalWrite(9, HIGH);
  delayMicroseconds(100);
  //func_Reverse(false);
  distance += 1;  // caculate distance
  if(distance == 200000)  // reverse the step motor
  {
    Serial.println("Reverse the step motor");
    if(digitalRead(8) == LOW)
    {
      digitalWrite(8,HIGH);  // change the pulse
    }
    else
    {
      digitalWrite(8,LOW);
    }
    distance = 0; // initial distance
  }
}

void func_Reverse(bool isReverse)
{
  if(isReverse)
  {
    Serial.println("Reverse the step motor");
    digitalWrite(8,HIGH);  // change the pulse
  }
  else
  {
    digitalWrite(8,LOW);
  }
}

