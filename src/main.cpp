#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "helper.hpp"
#include "timer.hpp"
static int counter = 0 ;



void setup() {
    Serial.begin(9600);  //init serial port
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }
    servoSetup();
    Serial.println();
    Serial.println("client connect!");

    rtcBegin();                         // init rtc 
    rtcSyncServer();                    //sync rtc with server 
    // Serial.println(WiFi.localIP());

    Serial.println();
    // Serial.println(sendGetRequest(client, now_time));
    // Serial.println(sendGetRequest(client, server_status));
    // Serial.println(sendGetRequest(client, upcoming_pills));

}

void loop() {
    // Your code here
    Intervales_Timers();
    checkScheduleTimes();
    // servoSweep("b");
}

