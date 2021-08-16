#include <TridentTD_LineNotify.h>

#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#include <PCF8574.h>

#define LINE_TOKEN "mBNOXD1bQbQHRhooALfaodwE7vdxGGhf6pBpthGj28u"

const char *ssid     = "Jaiboon_aisfibre_2.4G";
const char *password = "Jaiboon201";

const long utcOffsetInSeconds = 3600 * 7;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

int hour = 0;
int minute = 0;

bool AllLEDState = true;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

PCF8574 i2c_LED(0x20);

void setup(){
  Serial.begin(115200);
  
//--------Wifi setup-----------
  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

  timeClient.begin();

  Serial.printf("\nWiFi connected\nIP : ");
  Serial.println(WiFi.localIP());
//------------------------------

//--------12c_LED setup---------
  i2c_LED.pinMode(P0, OUTPUT, LOW);
  i2c_LED.pinMode(P1, OUTPUT, LOW);
  i2c_LED.pinMode(P2, OUTPUT, LOW);
  i2c_LED.pinMode(P3, OUTPUT, LOW);
  i2c_LED.pinMode(P4, OUTPUT, LOW);
  i2c_LED.pinMode(P5, OUTPUT, LOW);
  i2c_LED.pinMode(P6, OUTPUT, LOW);

  i2c_LED.begin();
//------------------------------

//--------Line Token------------
  LINE.setToken(LINE_TOKEN);
//------------------------------



  
}

//void action(int LEDPin,int ServoPin,int MagnetSwitchPin){
//  digitalWrite(LEDPin,High);
//}
void pcfWrite(int pin){
  i2c_LED.digitalWrite(P0, LOW);
  i2c_LED.digitalWrite(P1, LOW);
  i2c_LED.digitalWrite(P2, LOW);
  i2c_LED.digitalWrite(P3, LOW);
  i2c_LED.digitalWrite(P4, LOW);
  i2c_LED.digitalWrite(P5, LOW);
  i2c_LED.digitalWrite(P6, LOW);
  i2c_LED.digitalWrite(pin, HIGH);
}
void loop() {
  timeClient.update();

  hour = timeClient.getHours();
  minute = timeClient.getMinutes();

  
  if(hour == 7 && minute == 45){
    LINE.notify("ก่อนเช้า");
    LINE.notify(daysOfTheWeek[timeClient.getDay()]
              +String(timeClient.getHours())+":"
              +String(timeClient.getMinutes())+":"
              +String(timeClient.getSeconds()));
    pcfWrite(P0);
  }
  if(hour == 9 && minute == 00){
    LINE.notify("หลังเช้า");
    LINE.notify(daysOfTheWeek[timeClient.getDay()]
              +String(timeClient.getHours())+":"
              +String(timeClient.getMinutes())+":"
              +String(timeClient.getSeconds()));
    pcfWrite(P1);
  }
  if(hour == 11 && minute == 45){
    LINE.notify("ก่อนกลางวัน");
    LINE.notify(daysOfTheWeek[timeClient.getDay()]
              +String(timeClient.getHours())+":"
              +String(timeClient.getMinutes())+":"
              +String(timeClient.getSeconds()));
    pcfWrite(P2);
  }
  if(hour == 13 && minute == 00){
    LINE.notify("หลังกลางวัน");
    LINE.notify(daysOfTheWeek[timeClient.getDay()]
              +String(timeClient.getHours())+":"
              +String(timeClient.getMinutes())+":"
              +String(timeClient.getSeconds()));
    pcfWrite(P3);
  }
  if(hour == 17 && minute == 45){
    LINE.notify("ก่อนเย็น");
    LINE.notify(daysOfTheWeek[timeClient.getDay()]
              +String(timeClient.getHours())+":"
              +String(timeClient.getMinutes())+":"
              +String(timeClient.getSeconds()));
    pcfWrite(P4);
  }
  if(hour == 19 && minute == 00){
    LINE.notify("หลังเย็น");
    LINE.notify(daysOfTheWeek[timeClient.getDay()]
              +String(timeClient.getHours())+":"
              +String(timeClient.getMinutes())+":"
              +String(timeClient.getSeconds()));
    pcfWrite(P5);
  }
  if(hour == 21 && minute == 00){
    LINE.notify("ก่อนนอน");
    LINE.notify(daysOfTheWeek[timeClient.getDay()]
              +String(timeClient.getHours())+":"
              +String(timeClient.getMinutes())+":"
              +String(timeClient.getSeconds()));
    pcfWrite(P6);
  }



}
