#include "servo.hpp"
Servo Servo_TankA;
Servo Servo_TankB;
void servoSetup()
{
    Servo_TankA.attach(ServoA,SERVO_COLIB_START,SERVO_COLIB_END);
    Servo_TankB.attach(ServoB,SERVO_COLIB_START,SERVO_COLIB_END);
    Servo_TankA.write(SERVO_START_ANG);
    Servo_TankB.write(SERVO_START_ANG);
}
void ReleaseFunction()
{   


for (auto& schedule : scheduleList)
 {
        if (schedule.tank == "a" && schedule.status == STATUS_WAITING ) {
            // Perform actions if the current time matches the schedule time
            Servo_TankA.write(SERVO_END_ANG); 
            schedule.status = STATUS_TRANSCATION; 

        }
        if(schedule.status == STATUS_TRANSCATION)
        {
            if(digitalRead(SENSOR_IR_TANKA)==LOW)
              {
                Servo_TankA.write(SERVO_START_ANG); 
                schedule.status = STATUS_TAKE;

              }
        }
   }
        

}