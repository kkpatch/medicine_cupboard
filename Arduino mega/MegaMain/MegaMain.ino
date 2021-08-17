#include <PCF8574.h>

#include <Wire.h>
#include "DS1307.h"

PCF8574 i2c_LED(0x23);
DS1307 clk;//define a object of DS1307 class

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
  // put your main code here, to run repeatedly:
  clk.getTime();

  Serial.print(clk.hour);
  Serial.print(":");
  Serial.print(clk.minute);
  Serial.print(":");
  Serial.print(clk.second);
  Serial.println();

  if(clk.hour == 7 && clk.minute == 45){
    ledWrite(P0);
    analogWrite(A0, 200);
  }
  if(clk.hour == 9 && clk.minute == 0){
    ledWrite(P1);
    analogWrite(A0, 200);
  }
  if(clk.hour == 11 && clk.minute == 45){
    ledWrite(P2);
    analogWrite(A0, 200);
  }
  if(clk.hour == 13 && clk.minute == 0){
    ledWrite(P3);
    analogWrite(A0, 200);
  }
  if(clk.hour == 17 && clk.minute == 45){
    ledWrite(P4);
    analogWrite(A0, 200);
  }
  if(clk.hour == 19 && clk.minute == 00){
    ledWrite(P5);
    analogWrite(A0, 200);
  }
  if(clk.hour == 23 && clk.minute == 33){
    ledWrite(P6);
    analogWrite(A0, 200);
  }

  if(digitalRead(31) == LOW){  //ตู้ชั้นที่ 1 เปิด
    i2c_LED.digitalWrite(P0, LOW);
    analogWrite(D0, 0);
  }
  if(digitalRead(33) == LOW){  //ตู้ชั้นที่ 2 เปิด
    i2c_LED.digitalWrite(P1, LOW);
    analogWrite(D0, 0);   
  }
  if(digitalRead(35) == LOW){  //ตู้ชั้นที่ 3 เปิด
    i2c_LED.digitalWrite(P2, LOW);
    analogWrite(D0, 0);   
  }
  if(digitalRead(37) == LOW){  //ตู้ชั้นที่ 4 เปิด
    i2c_LED.digitalWrite(P3, LOW);
    analogWrite(D0, 0);   
  }
  if(digitalRead(39) == LOW){  //ตู้ชั้นที่ 5 เปิด
    i2c_LED.digitalWrite(P4, LOW);
    analogWrite(D0, 0);   
  }
  if(digitalRead(41) == LOW){  //ตู้ชั้นที่ 6 เปิด
    i2c_LED.digitalWrite(P5, LOW);
    analogWrite(D0, 0);   
  }
  if(digitalRead(43) == LOW){  //ตู้ชั้นที่ 7 เปิด
    i2c_LED.digitalWrite(P6, LOW);
    analogWrite(D0, 0);   
  }
}
