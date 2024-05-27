#ifndef RTC_H
#define RTC_H
#include <Arduino.h>
#include <Wire.h>
#include <RTClib.h>
#include <SPI.h>
#include "../Variables_Pin_setup/variabels.hpp"
void rtcBegin();
DateTime rtcNow();
void rtcAdjust(const DateTime &dt);
String getDayOfWeek(uint8_t dayOfWeek);
#endif
