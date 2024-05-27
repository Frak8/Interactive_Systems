#include <Arduino.h>
#include <Servo.h>
// put function declarations here:
static void dispensePill(Servo s, int amount);

Servo myServo;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  myServo.attach(D4,500,2500);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()>0){
    int amount = Serial.parseInt();
    dispensePill(myServo, amount);
  }
}

// put function definitions here:
void dispensePill(Servo s, int amount){
    for (int c = 0; c < amount;c++){
      s.write(165);
      delay(500);
      s.write(0);
      delay(500);
    }
}