#include <PCF8574.h>

#include <Wire.h>
#include "DS1307.h"

#include <SoftwareSerial.h>

#include <Servo.h>
SoftwareSerial mySerial(10, 11); // RX, TX

#include <EEPROM.h>

PCF8574 i2c_LED(0x23);
DS1307 clk;//define a object of DS1307 class

char cupboardSelected[7] = {'n','n','n','n','n','n','n'};   //(n)ot selected, (s)elected

char cupboardState_now[7] = {'c','c','c','c','c','c','c'};  //(c)lose,(o)pen     
char cupboardState_pre[7] = {'c','c','c','c','c','c','c'};  

char servoState_now[7] = {'l','l','l','l','l','l','l'};     //(l)ock,(u)nlock  

int check[7] = {0,0,0,0,0,0,0};

Servo m[7];

unsigned long period = 1000; 
unsigned long last_time = 0; 

void ledWriteHigh(int);
void ledWriteLow();
void showFloorSelected();

void setup() {
////-------Buzzer setup-----------
//  pinMode(A0, OUTPUT);
////------------------------------

//-----Open All Floor setup-----
//  pinMode(, INPUT);
//------------------------------
  
  Serial.begin(115200);
  
//--------RTC setup-------------
  clk.begin();
  clk.fillByYMD(2021, 8, 24); //Jan 19,2013
  clk.fillByHMS(1, 47, 30); //15:28 30"
  clk.fillDayOfWeek(TUE);//Saturday
  clk.setTime();//write time to the RTC chip
//------------------------------    

//--------SWSerial setup--------  
  mySerial.begin(115200);
//------------------------------
//  
  // put your setup code here, to run once:
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
//
//-----MagnetSensor setup-------
  pinMode(31, INPUT);
  pinMode(33, INPUT);
  pinMode(35, INPUT);
  pinMode(37, INPUT);
  pinMode(39, INPUT);
  pinMode(41, INPUT);
  pinMode(43, INPUT);
//------------------------------

//  mySerial.println("Hello, world?");
//-------Servo setup------------
  for(int i = 0; i < 7;i++){
    m[i].attach(i+2);
    m[i].write(90);
    delay(100); // หน่วงเวลา 1000ms   
  }

  String echeckbox;
  for (int i = 0; i < 6; ++i)
  {
    echeckbox += char(EEPROM.read(i));
  }
  for(int i = 0;i<7;i++){
    cupboardSelected[i] = 'n';
  }
  for(int i = 0;i<echeckbox.length();i++){
    cupboardSelected[echeckbox[i]-65] = 's';
  }
  for(int i = 0;i<2;i++){
    showFloorSelected();
  }
}

void loop() {
  // put your main code here, to run repeatedly:    
  if (mySerial.available()) {
    char tmp_mySerial = mySerial.read();
    Serial.write(tmp_mySerial);
    if(tmp_mySerial > 64 && tmp_mySerial < 91){
      if(tmp_mySerial == 'H'){
        for (int i = 0; i < 10; i++){
          EEPROM.write(i, 0);
        }
        for(int i = 0;i<7;i++){
          cupboardSelected[i] = 'n';
        }        
      }
      else {
        EEPROM.write(tmp_mySerial-65, tmp_mySerial);
        cupboardSelected[tmp_mySerial - 65] = 's';
        for(int i = 0;i<2;i++){
          showFloorSelected();
        }
      }
    }
  }
  if( millis() - last_time > period) {
    clk.getTime();

    Serial.print(clk.hour);
    Serial.print(":");
    Serial.print(clk.minute);
    Serial.print(":");
    Serial.print(clk.second);
    Serial.print(" ");
    Serial.print(digitalRead(31));
    Serial.print(digitalRead(33));
    Serial.print(digitalRead(35));
    Serial.print(digitalRead(37));
    Serial.print(digitalRead(39));
    Serial.print(digitalRead(41));
    Serial.print(digitalRead(43));
    Serial.println();
    last_time = millis();
    for(int i = 0;i<7;i++){
      Serial.print(cupboardSelected[i]);
      if(i == 6){
        Serial.println();
      }
   }
  }
  if(clk.hour == 7 && clk.minute == 45){
    if(cupboardSelected[0] == 's'){
      if(check[0] == 0){
        ledWriteHigh(P0);
//        tone(A0,600);
        check[0] = 1;      
        //----Set servo to unlock---------
        m[0].write(0);
      //--------------------------------
      }      
    }

  }
  if(clk.hour == 9 && clk.minute == 0){
    if(cupboardSelected[1] == 's'){
      if(check[1] == 0){
        ledWriteHigh(P1);
//        tone(A0,600);
        check[1] = 1;
        m[1].write(0);
      }
    }      
  }
  if(clk.hour == 11 && clk.minute == 45){
    if(cupboardSelected[2] == 's'){
      if(check[2] == 0){
        ledWriteHigh(P2);
//        tone(A0,600);
        check[2] = 1;
        m[2].write(0);
      }
    }
  }
  if(clk.hour == 13 && clk.minute == 0){
    if(cupboardSelected[3] == 's'){
      if(check[3] == 0){
        ledWriteHigh(P3);
//        tone(A0,600);
        check[3] = 1;
        m[3].write(0);
      }
    }
  }
  if(clk.hour == 15 && clk.minute == 58){
    if(cupboardSelected[4] == 's'){
      if(check[4] == 0){
        ledWriteHigh(P4);
//        tone(A0,600);
        check[4] = 1;
        m[4].write(0);
      }
    }
  }
  if(clk.hour == 13 && clk.minute == 47){
    if(cupboardSelected[5] == 's'){
      if(check[5] == 0){
//      //--Set buzzer to stop working----        
        mySerial.write('X');
        ledWriteHigh(P5);
//        tone(A0,600);
        check[5] = 1;
        m[5].write(0);
      }
    }    
  }
  if(clk.hour == 16 && clk.minute == 51){
    if(cupboardSelected[6] == 's'){
      if(check[6] == 0){
        ledWriteHigh(P6);
//        tone(A0,600);
        check[6] = 1;
        m[6].write(0);      
      }
    }
  }
  if(clk.hour == 0 && clk.minute == 0){
    for(int i = 0;i<7;i++){
      check[i] = 0;
    }
  }

  for(int i = 0;i<7;i++){
    if(digitalRead(31+(2*i)) == 0){
      cupboardState_now[i] = 'o';
    }
  }
  for(int i = 0;i<7;i++){
    if(digitalRead(31+(2*i)) == 1){
      cupboardState_now[i] = 'c';
    }
  }

  for(int i = 0;i<7;i++){
    if(cupboardState_pre[i] == 'c' && cupboardState_now[i] == 'o'){
      Serial.print("floor "+String(i)+" close then open");
      Serial.println();
    }
  }
  for(int i = 0;i<7;i++){
    if(cupboardState_pre[i] == 'o' && cupboardState_now[i] == 'c'){
        Serial.print("floor "+String(i)+" open then close");
        Serial.println();
//        noTone(A0);
        ledWriteLow();
//      //--Set buzzer to stop working----        
        mySerial.write('Y');
        //--------Line notify-------------
        delay(1000);
        mySerial.write('Z');
        //--------------------------------      
//      //-----Set servo to lock----------
        m[i].write(90);
//      //--------------------------------



    }
  }
  
  for(int i = 0;i<7;i++){
    cupboardState_pre[i] = cupboardState_now[i];    
  }
//  delay(1000);
}
void ledWriteHigh(int pin){
  i2c_LED.digitalWrite(P0, LOW);
  i2c_LED.digitalWrite(P1, LOW);
  i2c_LED.digitalWrite(P2, LOW);
  i2c_LED.digitalWrite(P3, LOW);
  i2c_LED.digitalWrite(P4, LOW);
  i2c_LED.digitalWrite(P5, LOW);
  i2c_LED.digitalWrite(P6, LOW);
  i2c_LED.digitalWrite(pin, HIGH);
}
void ledWriteLow(){
  i2c_LED.digitalWrite(P0, LOW);
  i2c_LED.digitalWrite(P1, LOW);
  i2c_LED.digitalWrite(P2, LOW);
  i2c_LED.digitalWrite(P3, LOW);
  i2c_LED.digitalWrite(P4, LOW);
  i2c_LED.digitalWrite(P5, LOW);
  i2c_LED.digitalWrite(P6, LOW);
}
void showFloorSelected(){
  if(cupboardSelected[0] == 's')    i2c_LED.digitalWrite(P0, HIGH);
  if(cupboardSelected[1] == 's')    i2c_LED.digitalWrite(P1, HIGH);
  if(cupboardSelected[2] == 's')    i2c_LED.digitalWrite(P2, HIGH);
  if(cupboardSelected[3] == 's')    i2c_LED.digitalWrite(P3, HIGH);
  if(cupboardSelected[4] == 's')    i2c_LED.digitalWrite(P4, HIGH);
  if(cupboardSelected[5] == 's')    i2c_LED.digitalWrite(P5, HIGH);
  if(cupboardSelected[6] == 's')    i2c_LED.digitalWrite(P6, HIGH);
  delay(500);  
  ledWriteLow();
  delay(500);  
}
