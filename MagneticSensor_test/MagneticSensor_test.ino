int buttonState = 0;  

void setup() {
  Serial.begin(9600);   
  pinMode(D1, INPUT);     
}

void loop(){

  // read the state of the pushbutton value:

  buttonState = digitalRead(D1);
  if (buttonState == HIGH) {     
    Serial.println("High"); 
  } 

  else {
    Serial.println("Low");
  }

 

}
