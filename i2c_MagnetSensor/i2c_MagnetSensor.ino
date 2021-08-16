#include <PCF8574.h>

PCF8574 i2c_MagnetSensor(0x21);
bool state;
bool state2;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  i2c_MagnetSensor.pinMode(P0, INPUT);
  i2c_MagnetSensor.pinMode(P1, INPUT);

  i2c_MagnetSensor.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  state = i2c_MagnetSensor.digitalRead(P0);
  state2 = i2c_MagnetSensor.digitalRead(P1);
  Serial.print(state);
  Serial.print(state2);
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
