int state; // 0 close - 1 open wwitch

void setup()
{
  pinMode(5, INPUT_PULLUP);
  Serial.begin (9600);
}

void loop()
{
  state = digitalRead(5);
  
  if (state == HIGH){
    Serial.print("Not Connected");
    Serial.println();
  }
  else{
    Serial.print("Connected");
    Serial.println();
  }
  delay(200);
}
