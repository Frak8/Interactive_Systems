#include"LCD.hpp"
SoftwareSerial LCD_Serial(RX_LCD, TX_LCD);
unsigned long Update_page = 0;
LCD_Page current_lcd_page = page0;
Nextion nex(LCD_Serial);
bool a=false;
bool b=false ;

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
*/
NextionText Day_week(nex,3,3,"t2");
NextionText Date(nex,3,2,"t1");
NextionText Time(nex,3,1,"t0");
NextionText Pill_time_a(nex,3,11,"t7");
NextionText Pill_time_b(nex,3,16,"t12");
NextionText Pill_name_a(nex,3,10,"t6");
NextionText Pill_name_b(nex,3,15,"t11");
NextionText Pill_qty_a(nex,3,8,"t4");
NextionText Pill_qty_b(nex,3,13,"t9");
NextionPicture Server_icon(nex,3,20,"p1");
NextionPicture Network_icon(nex,3,4,"p0");
NextionButton Dispense_A(nex,3,5,"b0");
NextionButton Dispense_b(nex,3,7,"b1");


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
    nex.sendCommand("page 3");  
}
void LCD_get_page()
{
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
            Function_page3();
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







void Function_page3()
{

if(WiFi.status() == WL_CONNECTED)
   Network_icon.setPictureID(2); 
else
   Network_icon.setPictureID(3); 
if(server_Status())
    Server_icon.setPictureID(15);
else
    Server_icon.setPictureID(14);


  DateTime now = rtcNow();
  String timeString = String(now.hour()) + ":" + (now.minute() < 10 ? "0" + String(now.minute()) : String(now.minute()));
  char *timeString_chr = new char [timeString.length()+1];
    strcpy(timeString_chr, timeString.c_str());
        Time.setText(timeString_chr);
        delete[] timeString_chr;






for (auto& schedule : scheduleList)
 {
    if(schedule.tank=="a")
    {
        //
        char *pill_name = new char [schedule.pill_name.length()+1];
        strcpy(pill_name, schedule.pill_name.c_str());
        Pill_name_a.setText(pill_name);
        delete[] pill_name;

        //
        char *pill_time = new char [schedule.time.length()+1];
        strcpy(pill_time, schedule.time.c_str());
        Pill_time_a.setText(pill_time);
        delete[] pill_time;

        std::string str = std::to_string(schedule.quantity);
        char *qty_str = new char [str.length()+1];
        strcpy(qty_str, str.c_str());
        Pill_qty_a.setText(qty_str);
        delete[] qty_str;
        if(schedule.status==STATUS_WAITING)   
        a=true;
    }

    else if(schedule.tank=="b")
    {
        char *converted = new char [schedule.pill_name.length()+1];
        strcpy(converted, schedule.pill_name.c_str());
        Pill_name_b.setText(converted);
        delete[] converted;
        b=true;
    }
 }



    //   if(a==false)
    // {
    //     Pill_name_a.setText("--");
    //     Pill_time_a.setText("--:--");
    //     Pill_qty_a.setText("-");
    //     Dispense_A.setText("Not any");

    // }
    // else if(b==false)
    // {
    //     Pill_name_b.setText("--");
    //     Pill_time_b.setText("--:--");
    //     Pill_qty_b.setText("-");
    //     Dispense_b.setText("Not any");
    // }
}



