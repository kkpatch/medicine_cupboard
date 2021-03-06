#include <TridentTD_LineNotify.h>

#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#include <PCF8574.h>

#include <Wire.h>
#include "DS1307.h"

#define LINE_TOKEN "mBNOXD1bQbQHRhooALfaodwE7vdxGGhf6pBpthGj28u"

const char *ssid     = "Jaiboon_aisfibre_2.4G";
const char *password = "Jaiboon201";

//const long utcOffsetInSeconds = 3600 * 7;
//
//char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

// bool AllLEDState = true;

//WiFiUDP ntpUDP;
//NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

PCF8574 i2c_LED(0x20);
PCF8574 i2c_MagnetSensor(0x21);

DS1307 clk;//define a object of DS1307 class

int buzzerPin = 12;

void setup(){
  Serial.begin(115200);
  
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

//--------Wifi setup-----------
  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

//  timeClient.begin();

  Serial.printf("\nWiFi connected\nIP : ");
  Serial.println(WiFi.localIP());
//

//--------Line Token------------
  LINE.setToken(LINE_TOKEN);
//------------------------------

////-------Buzzer setup-----------
  pinMode(D0, OUTPUT);
////------------------------------

//----i2c_MagnetSensor setup----
  i2c_MagnetSensor.pinMode(P0, INPUT);
  i2c_MagnetSensor.pinMode(P1, INPUT);
  i2c_MagnetSensor.pinMode(P2, INPUT);
  i2c_MagnetSensor.pinMode(P3, INPUT);
  i2c_MagnetSensor.pinMode(P4, INPUT);
  i2c_MagnetSensor.pinMode(P5, INPUT);
  i2c_MagnetSensor.pinMode(P6, INPUT);
//------------------------------

//--------RTC setup-------------
  clk.begin();
//  clk.fillByYMD(2021, 8, 17); //Jan 19,2013
//  clk.fillByHMS(1, 57, 30); //15:28 30"
//  clk.fillDayOfWeek(TUE);//Saturday
//  clk.setTime();//write time to the RTC chip
//------------------------------    
}

//void action(int LEDPin,int ServoPin,int MagnetSwitchPin){
//  digitalWrite(LEDPin,High);
//}
void ledWrite(int pin){
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
//  timeClient.update();
  clk.getTime();
  
  Serial.print(clk.hour);
  Serial.print(":");
  Serial.print(clk.minute);
  Serial.print(":");
  Serial.print(clk.second);
  Serial.println();

//--------Line Notify-----------
//  hour = timeClient.getHours();
//  minute = timeClient.getMinutes();
//    LINE.notify("????????????????????????");
//    LINE.notify(daysOfTheWeek[timeClient.getDay()]
//              +String(timeClient.getHours())+":"
//              +String(timeClient.getMinutes())+":"
//              +String(timeClient.getSeconds()));
//------------------------------  

  if(clk.hour == 7 && clk.minute == 45){
    ledWrite(P0);
    analogWrite(D0, 200);
  }
  if(clk.hour == 9 && clk.minute == 0){
    ledWrite(P1);
    analogWrite(D0, 200);
  }
  if(clk.hour == 11 && clk.minute == 45){
    ledWrite(P2);
    analogWrite(D0, 200);
  }
  if(clk.hour == 13 && clk.minute == 0){
    ledWrite(P3);
    analogWrite(D0, 200);
  }
  if(clk.hour == 17 && clk.minute == 45){
    ledWrite(P4);
    analogWrite(D0, 200);
  }
  if(clk.hour == 19 && clk.minute == 00){
    ledWrite(P5);
    analogWrite(D0, 200);
  }
  if(clk.hour == 23 && clk.minute == 33){
    ledWrite(P6);
    analogWrite(D0, 200);
  }

  if(i2c_MagnetSensor.digitalRead(P0) == LOW){  //?????????????????????????????? 1 ????????????
    i2c_LED.digitalWrite(P0, LOW);
    analogWrite(D0, 0);
  }
  if(i2c_MagnetSensor.digitalRead(P1) == LOW){  //?????????????????????????????? 2 ????????????
    i2c_LED.digitalWrite(P1, LOW);
    analogWrite(D0, 0);   
  }
  if(i2c_MagnetSensor.digitalRead(P2) == LOW){  //?????????????????????????????? 3 ????????????
    i2c_LED.digitalWrite(P2, LOW);
    analogWrite(D0, 0);   
  }
  if(i2c_MagnetSensor.digitalRead(P3) == LOW){  //?????????????????????????????? 4 ????????????
    i2c_LED.digitalWrite(P3, LOW);
    analogWrite(D0, 0);   
  }
  if(i2c_MagnetSensor.digitalRead(P4) == LOW){  //?????????????????????????????? 5 ????????????
    i2c_LED.digitalWrite(P4, LOW);
    analogWrite(D0, 0);   
  }
  if(i2c_MagnetSensor.digitalRead(P5) == LOW){  //?????????????????????????????? 6 ????????????
    i2c_LED.digitalWrite(P5, LOW);
    analogWrite(D0, 0);   
  }
  if(i2c_MagnetSensor.digitalRead(P6) == LOW){  //?????????????????????????????? 7 ????????????
    i2c_LED.digitalWrite(P6, LOW);
    analogWrite(D0, 0);   
  }


}
