#ifndef HELPER_H
#define HELPER_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <RTClib.h>
#include <SPI.h>
#include <vector>
#include <Servo.h>

// port define 

#define RTC_SCL D1
#define RTC_SDA D2
#define Introupt_RTC D3
#define BUZZER D4
#define SENSOR_IR_TANKA D5
#define SENSOR_IR_TANKB D6
#define ServoA D7
#define ServoB D8
#define LIST_UPDATE 3
#define SERVO_START_ANG 0
#define SERVO_END_ANG 180
#define SERVO_COLIB_START 500
#define SERVO_COLIB_END 2500
#define STATUS_IDLE 1
#define STATUS_WAITING 2
#define STATUS_TRANSCATION 3
#define STATUS_MISSED 4
#define STATUS_TAKE 5




extern WiFiClient client;
extern Servo Servo_TankA;
extern Servo Servo_TankB;
extern const char* ssid;
extern const char* password;
extern const char* serverIP;
extern const char* router;
extern const char* serverURL;
extern const char* now_time;
extern const char* server_status;
extern const char* upcoming_pills;
extern const char* logs;

struct PillSchedule {
    String pill_name;
    int quantity;
    int schedule_id;
    int status;  // 1.idle , 2.waiting for push button , 3.transcation , 4.missed , 5.take
    String tank;
    String time;
};

extern std::vector<PillSchedule> scheduleList;
String sendGetRequest(WiFiClient client, const char* endpoint);
String sendPostRequest(WiFiClient& client, const char* endpoint, const String& payload);
void rtcBegin();
DateTime rtcNow();
void rtcAdjust(const DateTime &dt);
void rtcSyncServer();
bool server_Status();
void updateSchedule();
void postIntakeStatus();
void servoSetup();
void ReleaseFunction();
#endif // HELPER_H