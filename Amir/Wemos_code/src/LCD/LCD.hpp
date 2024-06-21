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
#include "../NeoNextion/NextionText.h"
#include "../NeoNextion/NextionButton.h"
#include "../NeoNextion/NextionPicture.h"
#include <cstring> 
void initLCD();
void convert(const std::string& str, std::function<void(char*)> callback);
void LCD_get_page();
void Function_page3();
void Function_page5();
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