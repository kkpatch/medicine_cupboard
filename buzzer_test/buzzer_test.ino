

void setup(){

pinMode(13,OUTPUT);
}
void loop(){
tone(13,600);

delay(1000);
noTone(13);
delay(1000);


}
