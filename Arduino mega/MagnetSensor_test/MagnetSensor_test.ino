
char cupboardState_now[7] = {'c','c','c','c','c','c','c'};     
char cupboardState_pre[7] = {'c','c','c','c','c','c','c'};   
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
//  Serial.print(digitalRead(31));
//  Serial.print(digitalRead(33));
//  Serial.print(digitalRead(35));
//  Serial.print(digitalRead(37));
//  Serial.print(digitalRead(39));
//  Serial.print(digitalRead(41));
//  Serial.print(digitalRead(43));
//  Serial.println();

    for(int i = 0;i<7;i++){
      if(digitalRead(31+(2*i)) == 0){
        cupboardState_now[i] = 'o';
      }
    }
    for(int i = 0;i<7;i++){
      if(digitalRead(31+(2*i)) == 1){
        cupboardState_now[i] = 'c';
      }
    }

    for(int i = 0;i<7;i++){
      if(cupboardState_pre[i] == 'o' && cupboardState_now[i] == 'c'){
        Serial.print("floor "+String(i)+" open then close");
        Serial.println();
      }
    }

    for(int i = 0;i<7;i++){
      if(cupboardState_pre[i] == 'c' && cupboardState_now[i] == 'o'){
        Serial.print("floor "+String(i)+" close then open");
        Serial.println();
      }
    }
    
    for(int i = 0;i<7;i++){
      cupboardState_pre[i] = cupboardState_now[i];    
    }
//    Serial.println();
    delay(500);
    
//  if(digitalRead(31) == 0){  //ตู้ชั้นที่ 1 เปิด
//    cupboardState_now = "Open";
//  }
//  if(digitalRead(31) == 1){  //ตู้ชั้นที่ 1 เปิด
//    cupboardState_now = "Close";
//  }
//
//  if(cupboardState_now == "Open" && cupboardState_pre == "Close"){
//    Serial.print("Close then Open\n");
//  }
//  if(cupboardState_now == "Close" && cupboardState_pre == "Open"){
//    Serial.print("Open then Close\n");
//  }
//  cupboardState_pre = cupboardState_now;
}
