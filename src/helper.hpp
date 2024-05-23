#ifndef HELPER_H
#define HELPER_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <RTClib.h>
#include <SPI.h>
#include <vector>


#define BUZZER D4
#define RTC_SCL D1
#define RTC_SDA D2
#define Introupt_RTC D3
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

struct PillSchedule {
    String pill_name;
    int quantity;
    int schedule_id;
    int status;  // 1.idle , 2.waiting for push button , 3.missed, 4.taken
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
#endif // HELPER_H