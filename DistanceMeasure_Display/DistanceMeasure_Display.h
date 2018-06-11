#ifndef DISTANCEMEASURE_DISPLAY
#define DISTANCEMEASURE_DISPLAY

bool trigMotor;
bool stopMotor;
bool forward; //go forward
bool change;  //reverse
int steps; //current steps of the motor
int extraSteps; //more steps of the motor to reach the expected position
int initialSteps;  //steps the motor move to the position at the beginning
int deviation;  //deviation value between expected value and actual value
int laps;  //laps of step motor

void setup_Sensor();
void setup_Motor();
bool start_Sensor();
void start_Motor();
void bladeDown();

#endif
