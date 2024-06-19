#ifndef LCD_H
#define LCD_H
#include <SoftwareSerial.h>
#include "HTTP/helper.hpp"
#include "RTC/rtc.hpp"
#include "Timer/timer.hpp"
#include "Variables_Pin_setup/variabels.hpp"
#include "servo/servo.hpp"
#include "../NeoNextion/Nextion.h"
#include "../NeoNextion/NextionPage.h"
#include "../NeoNextion/NextionProgressBar.h"
void initLCD();
void LCD_get_page();
extern Nextion nex;
enum LCD_Page {
    page0,
    page1,
    page2,
    page3,
    page4,
    page5,
};
#endif