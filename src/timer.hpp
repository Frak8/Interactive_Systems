#ifndef TIMER_H
#define TIMER_H
#include <Arduino.h>
#include "helper.hpp"
extern DateTime last1Sec;
extern DateTime last5Sec;
extern DateTime last10Sec;
extern DateTime last10Min;
void initTimers();
void Intervales_Timers();
#endif