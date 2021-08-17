

void setup(){

pinMode(A0,OUTPUT);
}
void loop(){
tone(A0,600);

delay(100);
noTone(A0);
delay(100);


}
