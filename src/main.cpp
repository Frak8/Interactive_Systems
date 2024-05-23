#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "helper.hpp"
DateTime lastUpdate;



void setup() {
    pinMode(BUZZER, OUTPUT);
    Serial.begin(9600);  //init serial port

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }

   // rtcBegin();                         // init rtc 
   // rtcSyncServer();                    //sync rtc with server 
   // lastUpdate = rtcNow();              // Set the initial time for the last update

    // Serial.println(WiFi.localIP());

    Serial.println();
    // Serial.println(sendGetRequest(client, now_time));
    // Serial.println(sendGetRequest(client, server_status));
    // Serial.println(sendGetRequest(client, upcoming_pills));

}

void loop() {
    // DateTime now = rtcNow();
    // if (now.unixtime() - lastUpdate.unixtime() >= 10) {  // Update every 10 seconds
    //     lastUpdate = now;
    //    // updateSchedule();  // Update schedule
    // }
    // Your code here
    
}

