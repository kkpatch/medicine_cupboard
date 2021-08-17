#include <PCF8574.h>

PCF8574 i2c_MagnetSensor(0x21);
bool state0;
bool state1;
bool state2;
bool state3;
bool state4;
bool state5;
bool state6;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  i2c_MagnetSensor.pinMode(P0, INPUT);
  i2c_MagnetSensor.pinMode(P1, INPUT);
  i2c_MagnetSensor.pinMode(P2, INPUT);
  i2c_MagnetSensor.pinMode(P3, INPUT);
  i2c_MagnetSensor.pinMode(P4, INPUT);
  i2c_MagnetSensor.pinMode(P5, INPUT);
  i2c_MagnetSensor.pinMode(P6, INPUT);
  

  i2c_MagnetSensor.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  state0 = i2c_MagnetSensor.digitalRead(P0);
  state1 = i2c_MagnetSensor.digitalRead(P1);
  state2 = i2c_MagnetSensor.digitalRead(P2);
  state3 = i2c_MagnetSensor.digitalRead(P3);
  state4 = i2c_MagnetSensor.digitalRead(P4);
  state5 = i2c_MagnetSensor.digitalRead(P5);
  state6 = i2c_MagnetSensor.digitalRead(P6);
  Serial.print(state0);
  Serial.print(state1);
  Serial.print(state2);
  Serial.print(state3);
  Serial.print(state4);
  Serial.print(state5);
  Serial.print(state6);

//  if(i2c_MagnetSensor.digitalRead(P0) == HIGH){
//    Serial.print("P0 High\n");
//  }
//  if(i2c_MagnetSensor.digitalRead(P0) == LOW){
//    Serial.print("P0 Low\n");
//  }
//  
  Serial.println();
  delay(500);
}
