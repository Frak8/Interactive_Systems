#include"LCD.hpp"
SoftwareSerial LCD_Serial(RX_LCD, TX_LCD);
void initLCD()
{
    LCD_Serial.begin(9600);
}
void check(){
    LCD_Serial.print("rest");
    LCD_Serial.write(0xFF);
    LCD_Serial.write(0xFF);
    LCD_Serial.write(0xFF);
}