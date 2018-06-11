#include "Motor_Control.h"
#include "Sensor_Control.h"

Motor_Control MoC;
Sensor_Control SeC;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(MoC.trigMotor)
  {
    MoC.start_Motor();
    if(MoC.currentSteps >= MoC.stepsToRun)
      {
        Serial.println("currentSteps = " + MoC.currentSteps);
        Serial.println("stepsToRun = " + MoC.stepsToRun);
        MoC.trigMotor = false;
        MoC.stop_Motor();
        SeC.setup_Sensor();
      }
  }
  else
  {
    MoC.deviation = SeC.start_Sensor();
    /*Serial.println("deviation = ");
        Serial.println(MoC.deviation);
        Serial.println(" mm");*/
        if(MoC.deviation > 1)
        {
          MoC.forward = true;
          MoC.stepsToRun = (MoC.deviation * 400)/2;  //(200steps/2mm) = (extraSteps/deviation)=>extraSteps = (deviation * 200)/2
          /*Serial.println("extraSteps = ");
          Serial.println(extraSteps);*/
          delay(100);
          MoC.setup_Motor();
        }
        else if(MoC.deviation < -1)
        {
          MoC.forward = false;
          MoC.stepsToRun = -(MoC.deviation * 400)/2;
          /*Serial.println("extraSteps = ");
          Serial.println(extraSteps);*/
          delay(100);
          
          MoC.setup_Motor();
        }
        else
        {
          Serial.println("stop");
          MoC.stop_Motor();
          SeC.setup_Sensor();
          //bladeDown();
        }
  }
}
