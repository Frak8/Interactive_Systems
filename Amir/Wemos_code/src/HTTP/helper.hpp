#ifndef HELPER_H
#define HELPER_H
#include <ArduinoJson.h>
#include <vector>
#include <ESP8266HTTPClient.h>
#include "../Variables_Pin_setup/variabels.hpp"
#include "../RTC/rtc.hpp"

struct PillSchedule {
    String pill_name;
    int quantity;
    int schedule_id;
    int status;  // 1.idle , 2.waiting for push button , 3.transcation , 4.missed , 5.take , 6 Failed
    String tank;
    String time;
    int pills_released;  // To track the number of pills released
    int retries;         // To track the number of retries
};

extern std::vector<PillSchedule> scheduleList;
String sendGetRequest(WiFiClient client, const char* endpoint);
String sendPostRequest(WiFiClient& client, const char* endpoint, const String& payload);
void rtcSyncServer();
bool server_Status();
void updateSchedule();
void postIntakeStatus();
#endif 