#ifndef SENSOR_CONTROL
#define SENSOR_CONTROL

#include <string.h>
#include "Arduino.h"

class Sensor_Control
{
  public:
    Sensor_Control();
    ~Sensor_Control();

   public:
    void setup_Sensor();
    int start_Sensor();

   private:
    int Duration; 
    int dot_Pos;
    float Distance;
    long long_Fraction;
    String str_Fraction;
    String str_Distance;
};
#endif
