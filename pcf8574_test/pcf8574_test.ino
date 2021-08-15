#include <PCF8574.h>

// Set address ไว้ที่ 0x20 (จั๊ม 0 0 0)
PCF8574 PCF(0x20);

void setup() {
  Serial.begin(115200);
  PCF.digitalWrite(P0, LOW);
  PCF.pinMode(P0, OUTPUT, LOW);
  PCF.pinMode(P1, OUTPUT, LOW);
  PCF.pinMode(P2, OUTPUT, LOW);
  PCF.pinMode(P3, OUTPUT, LOW);
  PCF.pinMode(P4, OUTPUT, LOW);
  PCF.pinMode(P5, OUTPUT, LOW);
  PCF.pinMode(P6, OUTPUT, LOW);
  PCF.pinMode(P7, OUTPUT, LOW);
  PCF.begin();
}

void dWrite(int pin,bool state){
    PCF.digitalWrite(pin, state);
}

void loop() {
  dWrite(P0,LOW);
  dWrite(P1,LOW);
  dWrite(P2,LOW);
  dWrite(P3,LOW);
  dWrite(P4,LOW);
  dWrite(P5,LOW);
  dWrite(P6,LOW);
  dWrite(P7,LOW);

  Serial.print("LOW");
  Serial.println();
  delay(1000);
  PCF.digitalWrite(P0, HIGH);
  PCF.digitalWrite(P1, HIGH);
  PCF.digitalWrite(P2, HIGH);
  PCF.digitalWrite(P3, HIGH);
  PCF.digitalWrite(P4, HIGH);
  PCF.digitalWrite(P5, HIGH);
  PCF.digitalWrite(P6, HIGH);
  PCF.digitalWrite(P7, HIGH);
  Serial.print("HIGH");
  Serial.println();
  delay(1000);
}
