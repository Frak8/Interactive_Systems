#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "HTTP/helper.hpp"
#include "RTC/rtc.hpp"
#include "Timer/timer.hpp"
#include "Variables_Pin_setup/variabels.hpp"
#include "servo/servo.hpp"
#include "LCD/LCD.hpp"

void setup() {
    pinMode(SENSOR_IR_TANKA,INPUT);
    pinMode(SENSOR_IR_TANKB,INPUT);
    pinMode(RX_LCD,INPUT);
    pinMode(TX_LCD,OUTPUT);
    Serial.begin(9600);  //init serial port
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }
    servoSetup();
    Serial.println();
    Serial.print("We are Connected to server! Our IP is:");
    Serial.println(WiFi.localIP());

    rtcBegin();                         // init rtc 
    rtcSyncServer();                    //sync rtc with server 
    initTimers();                       // init timers
    initLCD();

    Serial.println();
     Serial.println(sendGetRequest(client, now_time));
    // Serial.println(sendGetRequest(client, server_status));
    // Serial.println(sendGetRequest(client, upcoming_pills));

}

void loop() {
    // Your code here
    Intervales_Timers();
    checkScheduleTimes();
    ReleaseFunction();
   
}

