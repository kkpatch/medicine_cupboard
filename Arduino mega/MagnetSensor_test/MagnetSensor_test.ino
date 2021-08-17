

void setup() {
  // put your setup code here, to run once:
  pinMode(31, INPUT);
  pinMode(33, INPUT);
  pinMode(35, INPUT);
  pinMode(37, INPUT);
  pinMode(39, INPUT);
  pinMode(41, INPUT);
  pinMode(43, INPUT);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(digitalRead(31));
  Serial.print(digitalRead(33));
  Serial.print(digitalRead(35));
  Serial.print(digitalRead(37));
  Serial.print(digitalRead(39));
  Serial.print(digitalRead(41));
  Serial.print(digitalRead(43));
  Serial.println();
}
