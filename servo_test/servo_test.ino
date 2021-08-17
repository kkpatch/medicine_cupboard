#include <Servo.h>
Servo myservo1; //ประกาศตัวแปรแทน Servo
Servo myservo2; //ประกาศตัวแปรแทน Servo
Servo myservo3; //ประกาศตัวแปรแทน Servo
Servo myservo4; //ประกาศตัวแปรแทน Servo
Servo myservo5; //ประกาศตัวแปรแทน Servo
Servo myservo6; //ประกาศตัวแปรแทน Servo
Servo myservo7; //ประกาศตัวแปรแทน Servo
int stat = 0;
void setup()
{
myservo1.attach(2); // กำหนดขา 9 ควบคุม Servo
myservo2.attach(3); // กำหนดขา 9 ควบคุม Servo
myservo3.attach(4); // กำหนดขา 9 ควบคุม Servo
myservo4.attach(5); // กำหนดขา 9 ควบคุม Servo
myservo5.attach(6); // กำหนดขา 9 ควบคุม Servo
myservo6.attach(9); // กำหนดขา 9 ควบคุม Servo
//myservo7.attach(6); // กำหนดขา 9 ควบคุม Servo
}
void loop()
{
  if(stat == 0){

    myservo1.write(0); // สั่งให้ Servo หมุนไปองศาที่ 0
    delay(1000); // หน่วงเวลา 1000ms
    myservo1.write(90); // สั่งให้ Servo หมุนไปองศาที่ 0
    delay(1000); // หน่วงเวลา 1000ms
    myservo1.write(0); // สั่งให้ Servo หมุนไปองศาที่ 0
    delay(1000); // หน่วงเวลา 1000ms



      stat = 1;
  }


}
