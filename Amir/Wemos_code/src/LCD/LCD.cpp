#include"LCD.hpp"
SoftwareSerial LCD_Serial(RX_LCD, TX_LCD);
void initLCD()
{
    LCD_Serial.begin(9600);
    LCD_Command(LCD_RESET);
}
void LCD_Update()
{
    while(1){
    if (LCD_Serial.available()) {
        Serial.write(LCD_Serial.read());
    }

    // Bridge TTL serial to USB serial
    if (Serial.available()) {
        LCD_Serial.write(Serial.read());
    }
    }
}


void LCD_Command(const String &command) {
    LCD_Serial.print(command);
    LCD_Serial.write(0xFF);
    LCD_Serial.write(0xFF);
    LCD_Serial.write(0xFF);
    Serial.print("Sent command To LCD: ");
    Serial.println(command);
}