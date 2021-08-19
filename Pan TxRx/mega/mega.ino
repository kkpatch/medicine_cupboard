#include <Servo.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // RX, TX
Servo m[7];
char incomingByte = 0; // for incoming serial data
int i=0;
int delayTime = 250;

void setup() {
  // put your setup code here, to run once:
  mySerial.begin(115200);
  Serial.begin(9600);
  for(i=0;i<7;i++){
    m[i].attach(i+2);
    m[i].write(0);
  }
  delay(delayTime);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  if (Serial.available()) {
    mySerial.write(Serial.read());
  }
//  if (Serial.available() > 0) {
//    // read the incoming byte:
//    incomingByte = Serial.read();
//    m[incomingByte-'0'].write(90);
//    delay(delayTime);
//    m[incomingByte-'0'].write(0);
//    delay(delayTime);
//  }

//    for(incomingByte='0';incomingByte<'7';incomingByte++){
//    m[incomingByte-'0'].write(90);
//    delay(delayTime);
//  }
//  delay(delayTime);
//  
//    for(incomingByte='0';incomingByte<'7';incomingByte++){
//    m[incomingByte-'0'].write(0);
//    delay(delayTime);
//  }
//  delay(delayTime);
}
