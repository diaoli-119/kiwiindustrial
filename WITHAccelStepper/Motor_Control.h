#ifndef MOTOR_CONTROL
#define MOTOR_CONTROL
#include "Arduino.h"

class Motor_Control
{
  public:
    Motor_Control();
    ~Motor_Control();

  public:
    void setup_Motor();
    void start_Motor();
    void stop_Motor();
    
  public:
    bool trigMotor; //trig the motor to start
    bool forward; //go forward
    int stepsToRun; //steps of the motor to run to the expected position
    int deviation;  //deviation value between expected value and actual value    
    int currentSteps; //current steps of the motor
    
  private:
    int laps;  //laps of step motor
};

#endif
