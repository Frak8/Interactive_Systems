#include <Arduino.h>
#include <Servo.h>
// put function declarations here:

Servo myServo;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  myServo.attach(D4);
}

void loop() {
  // put your main code here, to run repeatedly:
  int pos;
  while (Serial.available()>0)
  {
    int val = Serial.parseInt();
    Serial.println(val);
    myServo.write(val);
    delay(5);
  }
  
  

  

}

// put function definitions here:
