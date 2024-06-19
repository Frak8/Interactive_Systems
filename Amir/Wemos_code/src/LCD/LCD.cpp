#include"LCD.hpp"
SoftwareSerial LCD_Serial(RX_LCD, TX_LCD);
unsigned long Update_page = 0;
LCD_Page current_lcd_page = page0;
Nextion nex(LCD_Serial);
void initLCD()
{
    LCD_Serial.begin(9600);
    nex.init();
    current_lcd_page = page0;
    Serial.print("LCD init");    
}
void LCD_get_page()
{
    if(millis()-Update_page >= 300)
    {
        Update_page=millis();
        switch (nex.getCurrentPage())
        {
        case 0:
            current_lcd_page = page0;
            break;
         case 1:
            current_lcd_page = page1;
            break;    
        case 2:
            current_lcd_page = page2;
            break;
        case 3:
            current_lcd_page = page3;
            break;
        case 4:
            current_lcd_page = page4;
            break;    
        case 5:
            current_lcd_page = page5;
            break;

        default:
            break;
        }
    }
}

