#include "servo.hpp"
Servo Servo_TankA;
Servo Servo_TankB;
ServoState currentState_A = IDLE;
ServoState currentState_B = IDLE;
unsigned long actionStartTime_A = 0;
unsigned long actionStartTime_B = 0;
void servoSetup()
{
    Servo_TankA.attach(ServoA,SERVO_COLIB_START,SERVO_COLIB_END);
    Servo_TankB.attach(ServoB,SERVO_COLIB_START,SERVO_COLIB_END);
    Servo_TankA.write(SERVO_START_ANG);
    Servo_TankB.write(SERVO_START_ANG);
}

void ServoTransaction(String tank) {
    if (tank == "a" && currentState_A == IDLE) {
        Servo_TankA.write(SERVO_END_ANG);
        Serial.println("Servo Tank A Open");
        currentState_A = OPENING_SERVO;
        actionStartTime_A = millis();
    }
    if (tank == "b" && currentState_B == IDLE) {
        Servo_TankB.write(SERVO_END_ANG);
        Serial.println("Servo Tank B Open");
        currentState_B = OPENING_SERVO;
        actionStartTime_B = millis();
    }
}

// Function to handle servo state transitions
void handleServoMovement() {
    if (currentState_A == OPENING_SERVO) {
        if (millis() - actionStartTime_A >= SERVO_TRANSACTION_TIME) { 
            Servo_TankA.write(SERVO_START_ANG);
            Serial.println("Servo Tank A Close");
            currentState_A = CLOSING_SERVO;
            actionStartTime_A = millis();
        }
    } else if (currentState_B == OPENING_SERVO) {
        if (millis() - actionStartTime_B >= SERVO_TRANSACTION_TIME) { 
            Servo_TankB.write(SERVO_START_ANG);
            Serial.println("Servo Tank B Close");
            currentState_B = CLOSING_SERVO;
            actionStartTime_B = millis();
        }
    } else if (currentState_A == CLOSING_SERVO) {
        if (millis() - actionStartTime_A >= SERVO_TRANSACTION_TIME) { 
            currentState_A = IDLE;
        }
    } else if (currentState_B == CLOSING_SERVO) {
        if (millis() - actionStartTime_B >= SERVO_TRANSACTION_TIME) { 
            currentState_B = IDLE;
        }
    }
}




void ReleaseFunction()
{   
for (auto& schedule : scheduleList)
 {
        if (schedule.tank == "a" && 
        schedule.status == STATUS_TRANSCATION &&
        currentState_A==IDLE &&
        schedule.pills_released < schedule.quantity) {
          ServoTransaction(schedule.tank);
        }

        if (schedule.tank == "b" && 
        schedule.status == STATUS_TRANSCATION &&
        currentState_B==IDLE &&
        schedule.pills_released < schedule.quantity) {
          ServoTransaction(schedule.tank);
        }

        // if(digitalRead(SENSOR_IR_TANKA)==LOW)
        // {
        //   schedule.pills_released ++ ;
        // }

        
  }
}


