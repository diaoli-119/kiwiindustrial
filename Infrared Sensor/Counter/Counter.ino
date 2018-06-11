int ir_pin = 8;
int counter = 0;
int hitObject = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ir_pin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int val = digitalRead(ir_pin);
  if((val == 0) && (hitObject == false))
  {
    counter++;
    hitObject = true;
    Serial.print("Counter=");
    Serial.println(counter);
  }
  else if((val == 1) && (hitObject == true))
  {
    hitObject = false;
  }
}
