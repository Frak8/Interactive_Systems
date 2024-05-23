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


String sendPostRequest(WiFiClient& client, const char* endpoint, const String& payload) {
    HTTPClient http;
    String url = String("http://") + serverURL + endpoint;
    http.begin(client, url);
    http.addHeader("Content-Type", "application/json");

    int httpCode = http.POST(payload);
    String response;
    if (httpCode > 0) {
        response = http.getString();
    } else {
        response = "POST request failed";
    }

    http.end();
    return response;
}

void rtcBegin()
{   
    Wire.begin(RTC_SDA, RTC_SCL);
    delay(100);
    if (!rtc.begin()) 
    {
        while (1)
        {
            delay(500);
            Serial.println("RTC error");;
        }
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
        JsonArray pills = doc["upcoming_pills"].as<JsonArray>();
 for (JsonObject pill : pills) {
            bool exists = false;
            int schedule_id = pill["schedule_id"];

            for (auto& existingSchedule : scheduleList) {
                if (existingSchedule.schedule_id == schedule_id) {
                    // Update all fields except status
                    existingSchedule.pill_name = pill["pill_name"].as<String>();
                    existingSchedule.quantity = pill["quantity"];
                    existingSchedule.tank = pill["tank"].as<String>();
                    existingSchedule.time = pill["time"].as<String>();
                    exists = true;
                    break;
                }
            }

            if (!exists) {
                // Create a new schedule entry if it doesn't exist
                PillSchedule newSchedule;
                newSchedule.pill_name = pill["pill_name"].as<String>();
                newSchedule.quantity = pill["quantity"];
                newSchedule.schedule_id = pill["schedule_id"];
                newSchedule.tank = pill["tank"].as<String>();
                newSchedule.time = pill["time"].as<String>();
                newSchedule.status = 1;  // Default to idle

                scheduleList.push_back(newSchedule);
            }
        }

        Serial.println("Schedule updated:");
        for (const auto& schedule : scheduleList) {
            Serial.println("Pill: " + schedule.pill_name +", Id "+schedule.schedule_id+ ", Quantity: " + String(schedule.quantity) + ", Time: " + schedule.time + ", Status: " + String(schedule.status));
        }
    } else {
        Serial.println("Server is not running.");
    }
}

void postIntakeStatus() 
{
    for (auto& schedule : scheduleList) {
        if (schedule.status == 3 || schedule.status == 4) {
            StaticJsonDocument<200> jsonDoc;
            jsonDoc["intake_status"] = (schedule.status == 4) ? "taken" : "missed";
            jsonDoc["schedule_id"] = schedule.schedule_id;

            String jsonString;
            serializeJson(jsonDoc, jsonString);

            String response = sendPostRequest(client, "/api/logs", jsonString);
            Serial.println(response);
        }
    }
}   