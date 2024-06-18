#ifndef SERVO_H
#define SERVO_H
#include <Servo.h>
#include "../Variables_Pin_setup/variabels.hpp"
#include "../HTTP/helper.hpp"
enum ServoState {
    IDLE,
    OPENING_SERVO,
    CLOSING_SERVO
};
void servoSetup();
void ReleaseFunction();
void ServoTransaction(String tank);
void handleServoMovement();
#endif