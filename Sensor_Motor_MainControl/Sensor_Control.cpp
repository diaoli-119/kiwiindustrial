#include "Sensor_Control.h"
#include <LiquidCrystal_I2C.h>

#define FRACTION_PART 3 //get 3 numbers from the fraction part
#define MAXLENGTH 16
#define TRIG 9  //pin 9 on mega 2560
#define ECHO 10 //pin 10 on mega 2560

LiquidCrystal_I2C lcd(0x27,16,2);

Sensor_Control::Sensor_Control()
{
  
}

Sensor_Control::~Sensor_Control()
{
  
}

void Sensor_Control::setup_Sensor()
{
      pinMode(TRIG,OUTPUT);
      pinMode(ECHO,INPUT);
      lcd.init();
      //Print a message to a LCD
      lcd.backlight();
      /*lcd.setCursor(1,0);
      lcd.print("LCD 1602A 2018");
      lcd.setCursor(0,1);
      lcd.print("Power By Vincent");
      delay(3000);
      lcd.clear();*/
}

int Sensor_Control::start_Sensor()
{
      digitalWrite(TRIG,LOW);
      delayMicroseconds(11);
      digitalWrite(TRIG,HIGH);
      delayMicroseconds(11);
      digitalWrite(TRIG,LOW);
      
      Duration = pulseIn(ECHO,HIGH);
      if (Duration>0) {
        Distance = Duration/2;
        Distance = Distance*340*1000/1000000; // ultrasonic speed is 340m/s = 34000cm/s = 0.034cm/us
        /*Serial.println("Distance = ");
        Serial.println(Distance);
        Serial.println(" mm");*/
        /*Get fraction part*/
        str_Distance = String(Distance);
        dot_Pos = str_Distance.indexOf('.');
        str_Fraction = str_Distance.substring(dot_Pos + 1);
    
        /*number rounded*/
        long_Fraction = str_Fraction.toInt();
        if(long_Fraction >= 50)
        {
          Distance = ceil(Distance);
        }
        else
        {
          Distance = floor(Distance);
        }
        str_Distance = String(Distance);
        dot_Pos = str_Distance.indexOf('.');
        str_Distance = str_Distance.substring(0, dot_Pos);
        /*Serial.print("Duration = ");
        Serial.print(Duration);
        Serial.print(" us ");
        Serial.print(str_Distance);
        Serial.println(" mm");*/
        lcd.setCursor(0,0);
        lcd.print(str_Distance);
        lcd.setCursor(4,0);
        lcd.print("mm");
        return (Distance - 100); 
      }
      return 0;
}
