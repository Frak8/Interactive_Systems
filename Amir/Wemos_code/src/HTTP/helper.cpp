#include "helper.hpp"
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
void rtcSyncServer()
{
    String jsonString = sendGetRequest(client, "/api/now");
    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc, jsonString);
    if (error) {
        return;
    }
    const char* date = doc["date"];
    const char* time = doc["time"];
    int year, month, day, hour, minute, second;
    sscanf(date, "%d-%d-%d", &year, &month, &day);
    sscanf(time, "%d:%d:%d", &hour, &minute, &second);
    DateTime now = rtcNow();
    DateTime newTime(year, month, day, hour, minute, second);
    if (now != newTime)
    {
        rtcAdjust(newTime);
        Serial.println("SYNC Time with server ");
    }
    
 
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
                newSchedule.status = STATUS_IDLE;  // Default to idle
                newSchedule.pills_released=0;
                newSchedule.retries=0;
                scheduleList.push_back(newSchedule);
            }
        }
        Serial.println("Schedule updated:");
        for (const auto& schedule : scheduleList) {
            Serial.println("Pill: " + schedule.pill_name +
            ", Id: "+schedule.schedule_id+
            ", Quantity: " + String(schedule.quantity) +
            ", Time: " + schedule.time + 
            ", Status: " + String(schedule.status)+
            ", released " + schedule.pills_released +
            ", retries " + schedule.retries);

        }
            Serial.print("Current date and time is: ");
            DateTime now = rtcNow();
                Serial.print(now.year(), DEC); Serial.print("/");
                Serial.print(now.month(), DEC); Serial.print("/");
                Serial.print(now.day(), DEC); Serial.print(" ");
                Serial.print(now.hour(), DEC); Serial.print(":");
                Serial.print(now.minute(), DEC); Serial.print(":");
                Serial.print(now.second(), DEC); Serial.print(" ");
                Serial.print(getDayOfWeek(now.dayOfTheWeek()));
                Serial.println();
    } else {
        Serial.println("Server is not running.");
    }
}

void postIntakeStatus() {
    auto it = scheduleList.begin();
    while (it != scheduleList.end()) {
        if (it->status == STATUS_MISSED || it->status == STATUS_TAKE) {
            StaticJsonDocument<200> jsonDoc;
            jsonDoc["intake_status"] = (it->status == STATUS_TAKE) ? "taken" : "missed";
            jsonDoc["schedule_id"] = it->schedule_id;
            String jsonString;
            serializeJson(jsonDoc, jsonString);
            String response = sendPostRequest(client, "/api/logs", jsonString);
            Serial.println(response);
            // Remove the schedule from the list
            it = scheduleList.erase(it);
        } else {
            ++it;
        }
    }
}

void heartbeat() {
            String jsonString;
            String response = sendPostRequest(client, "/api/heartbeat", jsonString);
            Serial.println("Heartbeat");      
}
