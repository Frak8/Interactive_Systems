#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <vector>
#include "helper.hpp"

RTC_PCF8563 rtc;
WiFiClient client; 
std::vector<PillSchedule> scheduleList;

String sendGetRequest(WiFiClient client, const char* endpoint)
{
    HTTPClient http;
    String url = String("http://") + serverURL + endpoint;
    http.begin(client, url); 
    int httpCode = http.GET();
    if (httpCode > 0) 
    {
        if (httpCode == HTTP_CODE_OK)
        {
            String payload = http.getString();
            return payload;
            // Serial.println(payload);
        }
    } 

    http.end(); 
     return "NOT TRUE"; 
}




void rtcBegin()
{
    Wire.begin(RTC_SDA, RTC_SCL);

    if (!rtc.begin()) 
    {
        while (1);
        delay(10);
    }

    if (rtc.lostPower()) 
    {
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
}


DateTime rtcNow()
{
    return rtc.now();
}

void rtcAdjust(const DateTime &dt)
{
    rtc.adjust(dt);
}

void rtcSyncServer()
{
    String jsonString = sendGetRequest(client, "/api/now");
    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc, jsonString);

    if (error) {
        return;
    }
    const char* time = doc["time"];
    int hour, minute, second;
    sscanf(time, "%d:%d:%d", &hour, &minute, &second);
    DateTime now = rtcNow();
    DateTime newTime(now.year(), now.month(), now.day(), hour, minute, second);
    rtcAdjust(newTime);
}
bool server_Status() {
    String jsonString = sendGetRequest(client, server_status);
    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc, jsonString);

    if (error) {
        return false;
    }

    const char* serverStatus = doc["server_status"];
    const char* status = doc["status"];

    if (strcmp(serverStatus, "running") == 0 && strcmp(status, "success") == 0) {
        return true;
    }

    return false;
}
void updateSchedule()
{
if (server_Status()) {
        String jsonString = sendGetRequest(client, upcoming_pills);
        StaticJsonDocument<1024> doc;  // Adjust size as needed
        DeserializationError error = deserializeJson(doc, jsonString);

        if (error)
        {
            return;
        }

        if (strcmp(doc["status"], "success") != 0) {
            return;
        }

        scheduleList.clear();
        JsonArray pills = doc["upcoming_pills"].as<JsonArray>();
        for (JsonObject pill : pills) {
            PillSchedule schedule;
            schedule.pill_name = pill["pill_name"].as<String>();
            schedule.quantity = pill["quantity"];
            schedule.schedule_id = pill["schedule_id"];
            schedule.tank = pill["tank"].as<String>();
            schedule.time = pill["time"].as<String>();
            scheduleList.push_back(schedule);
        }

        Serial.println("Schedule updated:");
        // for (const auto& schedule : scheduleList) {
        //     Serial.println("Pill: " + schedule.pill_name + ", Quantity: " + String(schedule.quantity) + ", Time: " + schedule.time);
        // }
    }

}
