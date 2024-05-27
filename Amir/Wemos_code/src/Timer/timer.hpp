#ifndef TIMER_H
#define TIMER_H
#include <Arduino.h>
#include "../HTTP/helper.hpp"
#include "../RTC/rtc.hpp"
#include "../Variables_Pin_setup/variabels.hpp"
#include "../LCD/LCD.hpp"
extern DateTime last1Sec;
extern DateTime last5Sec;
extern DateTime last10Sec;
extern DateTime last10Min;
void initTimers();
void Intervales_Timers();
void checkScheduleTimes();
#endif