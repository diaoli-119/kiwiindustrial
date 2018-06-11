#include <AccelStepper.h>
#include "Motor_Control.h"

#define DRIVE 1
#define STEP  9
#define DIRECTION 8
#define MAXSPEED  2400
#define SPEED 2000
#define ACCELERATION  400
AccelStepper stepMotor(DRIVE, STEP, DIRECTION);

Motor_Control::Motor_Control()
{
  Serial.begin(2000000);
  stepMotor.setMaxSpeed(MAXSPEED);
  stepMotor.setSpeed(SPEED);
  stepMotor.setAcceleration(ACCELERATION);
  laps = 40;
  stepsToRun = 400 * laps;  //initial steps. 1.8 degree/step, this is half step, 400 steps a lap, S3 ON,S4 OFF
  Serial.println("Motor_Control Constructor");
  //delay(1);  
  setup_Motor();
}

Motor_Control::~Motor_Control()
{
  
}

void Motor_Control::setup_Motor()
{
  Serial.println("setup_Motor");
  Serial.println("stepsToRun = ");
  Serial.println(stepsToRun);
  trigMotor = true;
  deviation = 0;
  //delay(1);
}
void Motor_Control::start_Motor()
{
  Serial.println("start_Motor");
  trigMotor = false;
  stepMotor.moveTo(stepsToRun);
  stepMotor.run();
  //delay(1);
}
void Motor_Control::stop_Motor()
{
  stepMotor.stop();
}
