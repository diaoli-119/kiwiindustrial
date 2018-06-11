#include "DistanceMeasure_Display.h"

void setup() {
  forward = false;
  deviation = 0;
  extraSteps = 0;
  laps = 10;
  initialSteps = 200 * laps;  //initial steps. 1.8 degree/step, 200 steps a lap, S3 OFF,S4 OFF
  setup_Motor();
}

void loop() {
  if(trigMotor)
  {
    start_Motor();
  }
  else
  {
    start_Sensor(); 
  }
}
