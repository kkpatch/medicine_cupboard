#include <PCF8574.h>

#include <Wire.h>
#include "DS1307.h"

PCF8574 i2c_LED(0x23);
DS1307 clk;//define a object of DS1307 class

int state = 0;
int state2 = 0;
char cupboardState_now[7] = {'c','c','c','c','c','c','c'};  //(c)lose,(o)pen     
char cupboardState_pre[7] = {'c','c','c','c','c','c','c'};  

char servoState_now[7] = {'l','l','l','l','l','l','l'};     //(l)ock,(u)nlock  

int check[7] = {0,0,0,0,0,0,0};

void setup() {
  Serial.begin(115200);
  
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

//-----MagnetSensor setup-------
  pinMode(31, INPUT);
  pinMode(33, INPUT);
  pinMode(35, INPUT);
  pinMode(37, INPUT);
  pinMode(39, INPUT);
  pinMode(41, INPUT);
  pinMode(43, INPUT);
//------------------------------

//-------Buzzer setup-----------
  pinMode(A0, OUTPUT);
//------------------------------

//--------RTC setup-------------
  clk.begin();
//  clk.fillByYMD(2021, 8, 17); //Jan 19,2013
//  clk.fillByHMS(1, 57, 30); //15:28 30"
//  clk.fillDayOfWeek(TUE);//Saturday
//  clk.setTime();//write time to the RTC chip
//------------------------------    
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

void loop() {
  // put your main code here, to run repeatedly:
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
  
  if(clk.hour == 7 && clk.minute == 45){
    if(check[0] == 0){
      ledWriteHigh(P0);
      tone(A0,600);
      check[0] = 1;      
      //----Set servo to unlock---------

      //--------------------------------
    }
  }
  if(clk.hour == 9 && clk.minute == 0){
    if(check[1] == 0){
      ledWriteHigh(P1);
      tone(A0,600);
      check[1] = 1;
    }      
  }
  if(clk.hour == 11 && clk.minute == 45){
    if(check[2] == 0){
      ledWriteHigh(P2);
      tone(A0,600);
      check[2] = 1;
    }
  }
  if(clk.hour == 13 && clk.minute == 0){
    if(check[3] == 0){
      ledWriteHigh(P3);
      tone(A0,600);
      check[3] = 1;
    }
  }
  if(clk.hour == 17 && clk.minute == 45){
    if(check[4] == 0){
      ledWriteHigh(P4);
      tone(A0,600);
      check[4] = 1;
    }
  }
  if(clk.hour == 17 && clk.minute == 39){
    if(check[5] == 0){
      ledWriteHigh(P5);
      tone(A0,600);
      check[5] = 1;
    }    
  }
  if(clk.hour == 23 && clk.minute == 33){
    if(check[6] == 0){
      ledWriteHigh(P6);
      tone(A0,600);
      check[6] = 1;      
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
      noTone(A0);
      ledWriteLow();
      //--------Line notify-------------

      //--------------------------------

    }
  }
  for(int i = 0;i<7;i++){
    if(cupboardState_pre[i] == 'o' && cupboardState_now[i] == 'c'){
      Serial.print("floor "+String(i)+" open then close");
      Serial.println();
      //-----Set servo to lock----------

      //--------------------------------
    }
  }
  
  for(int i = 0;i<7;i++){
    cupboardState_pre[i] = cupboardState_now[i];    
  }

}
