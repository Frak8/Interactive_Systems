#include"LCD.hpp"
SoftwareSerial LCD_Serial(RX_LCD, TX_LCD);
unsigned long Update_page = 0;
LCD_Page current_lcd_page = page0;
Nextion nex(LCD_Serial);
/*
PAGE 0
NOTHING
*/


/*
PAGE 1
NOTHING
*/


/*
PAGE 2
NOTHING
*/


/*
PAGE 3
NOTHING
*/

/*
PAGE 4
NOTHING
*/


/*
PAGE 5
*/
NextionText Serial_status(nex,5,9,"t2");
NextionText Network_status(nex,5,3,"t9");
NextionText Server_status(nex,5,4,"t10");
NextionButton Retry_serial(nex,5,10,"b0");
NextionButton Retry_all(nex,5,11,"b1");
NextionButton Retry_network(nex,5,5,"b3");
NextionButton Retry_server(nex,5,6,"b4");
NextionProgressBar Progress(nex,5,12,"j0");

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
            Function_page5();
            break;

        default:
            break;
        }
    }
}

void Function_page5()
{
 Serial_status.setText("Connected");
 Serial_status.setColour("pco",1024,true);
 Progress.setValue(20);
  Progress.setColour("pco",63488,true);
 if(WiFi.status() == WL_CONNECTED)
 {
    Network_status.setText("Connected");
    Network_status.setColour("pco",1024,true);
    Progress.setValue(60);
     Progress.setColour("pco",64512,true);
 }
if(server_Status())
{
Server_status.setText("Connected");
Server_status.setColour("pco",1024,true);
Progress.setValue(100);
Progress.setColour("pco",1024,true);

}

Retry_all.setText("Next");
}

