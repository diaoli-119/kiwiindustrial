#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <string.h>
#include "DistanceMeasure_Display.h"

#define FRACTION_PART 3
#define MAXLENGTH 16
#define TRIG 9
#define ECHO 10

LiquidCrystal_I2C lcd(0x27,16,2);

void setup_Motor()
{
      Serial.begin(9600);
      trigMotor = true;
      steps = 0;
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

void setup_Sensor()
{
      //Serial.println("Start Sensor");
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

void start_Motor()
{
      digitalWrite(9, LOW);
      delayMicroseconds(500);
      digitalWrite(9, HIGH);
      delayMicroseconds(500);
      steps += 1;  //calculate the distance
      if(steps >= initialSteps)
      {
        trigMotor = false;
        setup_Sensor();
      }
}

bool start_Sensor()
{
      digitalWrite(TRIG,LOW);
      delayMicroseconds(1);
      digitalWrite(TRIG,HIGH);
      delayMicroseconds(11);
      digitalWrite(TRIG,LOW);
      
      int Duration; 
      float Distance;
      Duration = pulseIn(ECHO,HIGH);
      if (Duration>0) {
        Distance = Duration/2;
        Distance = Distance*340*1000/1000000; // ultrasonic speed is 340m/s = 34000cm/s = 0.034cm/us
        Serial.println("Distance = ");
        Serial.println(Distance);
        Serial.println(" mm");
        /*Get fraction part*/
        String str_Fraction;
        int pos = 0;
        String str_Distance;
        str_Distance = String(Distance);
        pos = str_Distance.indexOf('.');
        str_Fraction = str_Distance.substring(pos + 1);
    
        /*number rounded*/
        long long_Fraction;
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
        pos = str_Distance.indexOf('.');
        str_Distance = str_Distance.substring(0, pos);
        /*Serial.print("Duration = ");
        Serial.print(Duration);
        Serial.print(" us ");
        Serial.print(str_Distance);
        Serial.println(" mm");*/
        lcd.setCursor(0,0);
        lcd.print(str_Distance);
        lcd.setCursor(4,0);
        lcd.print("mm");
        //delay(2000);
        //lcd.clear();
        deviation = Distance - 100;
        /*Serial.println("deviation = ");
        Serial.println(deviation);
        Serial.println(" mm");*/
        //steps = 0;
        if(deviation > 1)
        {
          forward = true;
          extraSteps = (deviation * 200)/2;  //(200steps/2mm) = (extraSteps/deviation)=>extraSteps = (deviation * 200)/2
          /*Serial.println("extraSteps = ");
          Serial.println(extraSteps);*/
          delay(3000);
          setup_Motor();
        }
        else if(deviation < -1)
        {
          forward = false;
          extraSteps = -(deviation * 200)/2;
          /*Serial.println("extraSteps = ");
          Serial.println(extraSteps);*/
          delay(3000);
          setup_Motor();
        }
        else
        {
          trigMotor = false;
          bladeDown();
        }
      }  
}

void bladeDown()
{
  
}

