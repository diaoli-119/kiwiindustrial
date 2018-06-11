#include "Sensor_Control.h"
#include <LiquidCrystal_I2C.h>

extern int lengthToBeCut;

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
        Serial.println("setup_Sensor()");

  delay(3);
}

int Sensor_Control::start_Sensor()
{
        Serial.println("setup_Sensor()");

  delay(3);
      digitalWrite(TRIG,LOW);
      delayMicroseconds(11);
      digitalWrite(TRIG,HIGH);
      delayMicroseconds(11);
      digitalWrite(TRIG,LOW);
      
      duration = pulseIn(ECHO,HIGH);
      if (duration>0) {
        distance = duration/2;
        distance = distance*340*1000/1000000; // ultrasonic speed is 340m/s = 340000mm/s = 0.34mm/us
        /*Serial.println("distance = ");
        Serial.println(distance);
        Serial.println(" mm");*/
        
        /*Get fraction part*/
        str_Distance = String(distance);
        dot_Pos = str_Distance.indexOf('.');
        str_Fraction = str_Distance.substring(dot_Pos + 1);
    
        /*number rounded*/
        long_Fraction = str_Fraction.toInt();
        if(long_Fraction >= 50)
        {
          distance = ceil(distance);
        }
        else
        {
          distance = floor(distance);
        }
        str_Distance = String(distance);
        //dot_Pos = str_Distance.indexOf('.');
        //str_Distance = str_Distance.substring(0, dot_Pos);
        /*Serial.print("duration = ");
        Serial.print(duration);
        Serial.print(" us ");
        Serial.print(str_Distance);
        Serial.println(" mm");*/
        lcd.setCursor(0,0);
        lcd.print(str_Distance);
        lcd.setCursor(4,0);
        lcd.print("mm");
        return (distance - lengthToBeCut); 
      }
      return 0;
}
