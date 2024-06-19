#include"LCD.hpp"
SoftwareSerial LCD_Serial(RX_LCD, TX_LCD);
Nextion nex(LCD_Serial);
void initLCD()
{
    LCD_Serial.begin(9600);
    nex.init();
    Serial.print("LCD init");
    
}

void LCD_Command(const String &command) {
    LCD_Serial.print(command);
    LCD_Serial.write(0xFF);
    LCD_Serial.write(0xFF);
    LCD_Serial.write(0xFF);
    Serial.print("Sent command To LCD: ");
    Serial.println(command);
}