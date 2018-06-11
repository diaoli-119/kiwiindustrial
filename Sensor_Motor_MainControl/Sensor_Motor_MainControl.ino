#include "Motor_Control.h"
#include "Sensor_Control.h"

#define WITHAccelStepper

int lengthToBeCut = 100;

Motor_Control MoC;
Sensor_Control SeC;

void setup() {
  // put your setup code here, to run once:
  Serial.println("setup()");
}

void loop() {
  // put your main code here, to run repeatedly:
  if(MoC.trigMotor)
  {
  Serial.println(MoC.trigMotor);
    MoC.start_Motor();
#ifdef WITHAccelStepper
    
#else
    if(MoC.currentSteps >= MoC.stepsToRun)
    {
      MoC.trigMotor = false;
      MoC.stop_Motor();
      SeC.setup_Sensor();
    }
#endif
  }
  else
  {
        MoC.deviation = SeC.start_Sensor();
        Serial.println("deviation = ");
        Serial.println(MoC.deviation);
        Serial.println(" mm");
#ifdef WITHAccelStepper
        if(MoC.deviation < -1 || MoC.deviation > 1)
        {
          MoC.stepsToRun = (MoC.deviation * 400)/2;
          delay(100);
          MoC.setup_Motor();
        }
        else
        {
          MoC.stop_Motor();
        }
#else
        //Make sure the deviation between (lengthToBeCut - 1) and (lengthToBeCut + 1)
        if(MoC.deviation > 1)
        {
          MoC.forward = true;
          MoC.stepsToRun = (MoC.deviation * 400)/2;  //(400steps/2mm) = (stepsToRun/deviation)=>extraSteps = (deviation * 400)/2
          /*Serial.println("extraSteps = ");
          Serial.println(extraSteps);*/
          delay(100);
          MoC.setup_Motor();
        }
        else if(MoC.deviation < -1)
        {
          MoC.forward = false;
          MoC.stepsToRun = (MoC.deviation * 400)/2;
          /*Serial.println("extraSteps = ");
          Serial.println(extraSteps);*/
          delay(100);
          MoC.setup_Motor();
        }
        else
        {
          MoC.stop_Motor();
          SeC.setup_Sensor();
          //bladeDown();
        }
#endif
  }
}
