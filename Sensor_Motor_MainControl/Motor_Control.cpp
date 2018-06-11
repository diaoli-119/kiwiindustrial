#include "AccelStepper.h"
#include "Motor_Control.h"

//#ifdef WITHAccelStepper
  #define STEP  9
  #define DIRECTION 8
  #define MAXSPEED  2500
  #define SPEED 2000
  #define ACCELERATION  100
  AccelStepper stepMotor(1, STEP, DIRECTION);
//#endif

Motor_Control::Motor_Control()
{
  Serial.begin(9600);
  Serial.println("1");
  forward = true;
  laps = 10;
  stepsToRun = 400 * laps;  //initial steps. 1.8 degree/step, this is half step, 400 steps a lap, S3 ON,S4 OFF
  //setup_Motor();
}

Motor_Control::~Motor_Control()
{
  
}

#ifdef WITHAccelStepper
  void Motor_Control::setup_Motor()
  {
  Serial.println("2");
    stepMotor.setMaxSpeed(MAXSPEED);
    stepMotor.setSpeed(SPEED);
    stepMotor.setAcceleration(ACCELERATION);
    trigMotor = true;
    currentSteps = 0;
    deviation = 0;
  }
  void Motor_Control::start_Motor()
  {
  Serial.println("3");
    stepMotor.moveTo(stepsToRun);
  }
  void Motor_Control::stop_Motor()
  {
  Serial.println("4");
    stepMotor.stop();
  }
#else
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
        delayMicroseconds(500);
        digitalWrite(9, HIGH);
        delayMicroseconds(500);
        currentSteps += 1;  //calculate the distance
  }
  
  void Motor_Control::stop_Motor()
  {
        Serial.println("Stop Motor");
        digitalWrite(9, INPUT);
  }
#endif

