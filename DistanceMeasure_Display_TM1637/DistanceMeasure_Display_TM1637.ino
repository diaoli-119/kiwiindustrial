#include "DistanceMeasure_Display_TM1637.h"

// Distance number
#define FRACTION_PART 3
#define MAXLENGTH 16

// Sensor pin
#define TRIG 9
#define ECHO 10

// Module connection pins (Digital Pins)
#define CLK 2
#define DIO 3

// The amount of time (in milliseconds) between tests
#define TEST_DELAY   2000

                     /*0*/ /*1*/ /*2*/ /*3*/ /*4*/ /*5*/ /*6*/ /*7*/ /*8*/ /*9*/
uint8_t digits[] = { 0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f };

uint8_t SEG_NUMBER[] = {
      digits[8],  // 8
      digits[8],  // 8
      digits[8],  // 8
      digits[8]   // 8
};

TM1637Display display(CLK, DIO);

void setup() {
  Serial.begin(9600);
  int k;
  uint8_t data[] = { 0xff, 0xff, 0xff, 0xff };
  display.setBrightness(0x0f);
  // All segments on
  display.setSegments(data);
  delay(TEST_DELAY);
  
  forward = false;
  deviation = 0;
  laps = 10;
  extraSteps = 200 * laps;  //initial steps. 1.8 degree/step, 200 steps a lap, S3 OFF,S4 OFF
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

void setup_Motor()
{
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
}

void start_Motor()
{
      digitalWrite(9, LOW);
      delayMicroseconds(100);
      digitalWrite(9, HIGH);
      delayMicroseconds(100);
      steps += 1;  //calculate the distance
      Serial.println("");
      if(steps >= extraSteps)
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
        /*Serial.println("Distance = ");
        Serial.println(Distance);
        Serial.println(" mm");*/
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
        /*Serial.println("Duration = ");
        Serial.println(Duration);
        Serial.println(" us ");*/
        Serial.println("str_Distance = " + str_Distance + " mm");
        digital_Display(str_Distance);
        delay(3000);
        deviation = Distance - 100;
        /*Serial.println("deviation = ");
        Serial.println(deviation);
        Serial.println(" mm");*/
        if(deviation > 1)
        {
          forward = true;
          extraSteps = (deviation * 200)/2;  //(200steps/2mm) = (extraSteps/deviation)=>extraSteps = (deviation * 200)/2
          /*Serial.println("extraSteps = ");
          Serial.println(extraSteps);*/
          setup_Motor();
        }
        else if(deviation < -1)
        {
          forward = false;
          extraSteps = -(deviation * 200)/2;
          /*Serial.println("extraSteps = ");
          Serial.println(extraSteps);*/
          setup_Motor();
        }
        else
        {
          Serial.println("stop");
          trigMotor = false;
          //AccelStepper stepMotor(1, 8, 9);
          //stepMotor.stop();
          delay(60000);
          bladeDown();
        }
      }  
}
void digital_Display(String distance)
{
  int len = distance.length();
  int first, second, third, fourth;
  switch(len)
  {
    case 1:
    {
      first = 0;
      second = 0;
      third = 0;
      fourth = distance[0] - '0';
      break;
    }
    case 2:
    {
      first = 0;
      second = 0;
      third = distance[0] - '0';
      fourth = distance[1] - '0';
      break;
    }
    case 3:
    {
      first = 0;
      second = distance[0] - '0';
      third = distance[1] - '0';
      fourth = distance[2] - '0';
      break;
    }
    case 4:
    {
      first = distance[0] - '0';
      second = distance[1] - '0';
      third = distance[2] - '0';
      fourth = distance[3] - '0';
      break;      
    }
    default:{}
  }
  SEG_NUMBER[0] = digits[first];
  SEG_NUMBER[1] = digits[second];
  SEG_NUMBER[2] = digits[third];
  SEG_NUMBER[3] = digits[fourth];
  display.setSegments(SEG_NUMBER);  
}

void bladeDown()
{
  
}
