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
struct SensorState {
    bool value;                // The value to be changed
    bool record_value;
    unsigned long lastChange;  // Timestamp of the last state change
    bool debounceActive;       // Whether debounce is active
    int last_qty_values;
};
void servoSetup();
void ReleaseFunction();
void ServoTransaction(String tank);
void handleServoMovement();
void handleSensorInput(int sensorPin, SensorState &sensorState);
#endif