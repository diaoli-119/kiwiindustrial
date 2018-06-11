#include "Motor_Control.h"

Motor_Control::Motor_Control()
{
  Serial.begin(9600);
  forward = false;
  deviation = 0;
  currentSteps = 0;
  laps = 10;
  stepsToRun = 400 * laps;  //initial steps. 1.8 degree/step, 200 steps a lap, S3 OFF,S4 OFF
  setup_Motor();
}

Motor_Control::~Motor_Control()
{
  
}

void Motor_Control::setup_Motor()
{
      trigMotor = true;
      currentSteps = 0;
      pinMode(8, OUTPUT);
      pinMode(9, OUTPUT);
      if(forward)
      {
        digitalWrite(8,HIGH);  //change the pulse
      }
      else
      {
        digitalWrite(8,LOW);
      }
      digitalWrite(9, LOW);
}

void Motor_Control::start_Motor()
{
      digitalWrite(9, LOW);
      delayMicroseconds(100);
      digitalWrite(9, HIGH);
      delayMicroseconds(100);
      currentSteps += 1;  //calculate the distance
}

void Motor_Control::stop_Motor()
{
      Serial.println("stop_Motor");
      digitalWrite(9, INPUT);
}

