#ifndef VARIABELS_H
#define VARIABELS_H
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Servo.h>
#include "../RTC/rtc.hpp"
#include "../LCD/LCD.hpp"
#define RTC_SCL D1
#define RTC_SDA D2
#define RX_LCD D4
#define TX_LCD D3
#define SENSOR_IR_TANKA D5
#define SENSOR_IR_TANKB D6
#define ServoA D7
#define ServoB D8
#define LIST_UPDATE 3
#define SERVO_START_ANG 0
#define SERVO_END_ANG 180
#define SERVO_COLIB_START 500
#define SERVO_COLIB_END 2500
#define SERVO_TRANSACTION_TIME 800
#define DEBOUNCE_DELAY 100
#define STATUS_IDLE 1
#define STATUS_WAITING 2
#define STATUS_TRANSCATION 3
#define STATUS_MISSED 4
#define STATUS_TAKE 5
#define STATUS_FAILED 6
#define LCD_RESET "rest"
extern WiFiClient client;
extern const char* ssid;
extern const char* password;
extern const char* serverIP;
extern const char* router;
extern const char* serverURL;
extern const char* now_time;
extern const char* server_status;
extern const char* upcoming_pills;
extern const char* logs;

#endif