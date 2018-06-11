#include "Motor_Control.h"
#include "Sensor_Control.h"

int lengthToBeCut = 100;

Sensor_Control SeC;
Motor_Control MoC;

void setup() {
  // put your setup code here, to run once: 
  Serial.begin(2000000);
  Serial.println("Main setup()");
  //delay(1);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(MoC.trigMotor)
  {
    Serial.println("loop1");
    MoC.start_Motor();
    //SeC.setup_Sensor();
    //delay(1);
  }
  else
  {
    Serial.println("loop2");
        //delay(1);
    MoC.deviation = SeC.start_Sensor();
    /*Serial.println("deviation = ");
    Serial.println(MoC.deviation);
    Serial.println(" mm");*/

    if(MoC.deviation < -1 || MoC.deviation > 1)
    {
      MoC.stepsToRun = (MoC.deviation * 400)/2; //400 steps a round(2mm),it should be divided by 2
      MoC.start_Motor();
    }
    else
    {
      MoC.stop_Motor();
    }
  }
}
