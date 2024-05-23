#include <Arduino.h>
#include "timer.hpp"
DateTime last1Sec;
DateTime last5Sec;
DateTime last10Sec;
DateTime last10Min;

void initTimers() {
    DateTime now = rtcNow();
    last1Sec = now;
    last5Sec = now;
    last10Sec = now;
    last10Min = now;
}

void Intervales_Timers() 
{
    DateTime now = rtcNow();
    // 1-second interval actions
    if (now.unixtime() - last1Sec.unixtime() >= 1) {
        last1Sec = now;
        // UPDATE LCD values 
    }

    // 5-second interval actions
    if (now.unixtime() - last5Sec.unixtime() >= 5) {
        last5Sec = now;
        updateSchedule();    // UPDATE schdule
    }

    // 10-second interval actions
    if (now.unixtime() - last10Sec.unixtime() >= 10) {
        last10Sec = now;
        // NO action         
    }

    // 10-minute interval actions
    if (now.unixtime() - last10Min.unixtime() >= 600) {
        last10Min = now;
        // Later For Notification      
    }
}

