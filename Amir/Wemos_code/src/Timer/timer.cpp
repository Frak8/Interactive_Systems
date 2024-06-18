#include <Arduino.h>
#include "timer.hpp"
DateTime last1Sec;
DateTime last2Sec;
DateTime last5Sec;
DateTime last10Sec;
DateTime last1Min;
DateTime last10Min;

void initTimers() {
    DateTime now = rtcNow();
    last1Sec = now;
    last5Sec = now;
    last10Sec = now;
    last1Min = now;
    last10Min = now;

}

void Intervales_Timers() 
{
    DateTime now = rtcNow();
    // 1-second interval actions
    if (now.unixtime() - last1Sec.unixtime() >= 1) {
        last1Sec = now;
        // later UPDATE LCD values 
    }
 // 2-second interval actions
    if (now.unixtime() - last2Sec.unixtime() >= 2) {
        last2Sec = now;
    }
    // 5-second interval actions
    if (now.unixtime() - last5Sec.unixtime() >= 5) {
        last5Sec = now;
        updateSchedule();    // UPDATE schdule
        postIntakeStatus();   //
        heartbeat();        //heartbeat
        
    }
    

    // 10-second interval actions
    if (now.unixtime() - last10Sec.unixtime() >= 10) {
        last10Sec = now;
        // NO action for now maybe later 
    }

    // 1-Min
    if (now.unixtime() - last1Min.unixtime() >= 60) {
        last1Min = now;
        rtcSyncServer();
        // NO action for now maybe later          
    }

    // 10-minute interval actions
    if (now.unixtime() - last10Min.unixtime() >= 600) {
        last10Min = now;
        // Later For Notification      
    }
}

void checkScheduleTimes()
{
    DateTime now = rtcNow();
    char currentTime[6];
    sprintf(currentTime, "%02d:%02d", now.hour(), now.minute());
    for (auto& schedule : scheduleList) {
        if (schedule.time == String(currentTime) && schedule.status == STATUS_IDLE ) {
            // Perform actions if the current time matches the schedule time
            schedule.status = STATUS_WAITING;  //  set status to "waiting for push button"
            //TODO
            schedule.status = STATUS_TRANSCATION;
        }
  
      }
}



