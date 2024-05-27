#include "rtc.hpp"
RTC_PCF8563 rtc;

void rtcBegin()
{   
    Wire.begin(RTC_SDA, RTC_SCL);
    delay(100);
    if (!rtc.begin()) 
    {
        while (1)
        {  
            delay(500);
            Serial.println("RTC error");;
        }
    }
    if (rtc.lostPower()) 
    {
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
}

DateTime rtcNow()
{
    return rtc.now();
}
void rtcAdjust(const DateTime &dt)
{
    rtc.adjust(dt);
}
String getDayOfWeek(uint8_t dayOfWeek) {
    switch(dayOfWeek) {
        case 0: return "Sunday";
        case 1: return "Monday";
        case 2: return "Tuesday";
        case 3: return "Wednesday";
        case 4: return "Thursday";
        case 5: return "Friday";
        case 6: return "Saturday";
        default: return "Unknown";
    }
}