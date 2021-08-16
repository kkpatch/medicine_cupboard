

void setup(){

pinMode(D0,OUTPUT);
}
void loop(){

analogWrite(D0, 200);
delay(1000);
analogWrite(D0, 0);
delay(1000);


}
