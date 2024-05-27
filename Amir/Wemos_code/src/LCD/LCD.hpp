#ifndef LCD_H
#define LCD_H
#include <SoftwareSerial.h>
#include "HTTP/helper.hpp"
#include "RTC/rtc.hpp"
#include "Timer/timer.hpp"
#include "Variables_Pin_setup/variabels.hpp"
#include "servo/servo.hpp"
void initLCD();
void check();
#endif