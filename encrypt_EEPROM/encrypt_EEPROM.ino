String str="ACDEG00540130023014031130";
//String str="1503";
char checkbox[7] = {'n','n','n','n','n','n','n'};
int hours[7] = {0,0,0,0,0,0,0};
int minutes[7] = {0,0,0,0,0,0,0};

int cnt = 0;
int cnt3 = 0;
int cnt_numOfSelectCheckbox = 0;
int int_tmp;
String mode = "hour";
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
//  Serial.print("---------------");
//  Serial.print(0%2);
//  Serial.print(1%2);
//  Serial.print(2%2);

  for(int i = 0;i<7;i++){
    if(str[i]>64 && str[i]<72){
      checkbox[str[i]-65] = 's';  
      cnt_numOfSelectCheckbox += 1;      
    }
  }
    for(int i = cnt_numOfSelectCheckbox;i<str.length();i++){
      if(str[i]>47 && str[i]<58){        
        if(cnt % 2 == 0){
           int_tmp = str[i] - '0';
           int_tmp = int_tmp*10;
        }
        if(cnt % 2 == 1){
            int_tmp = int_tmp+(str[i] - '0');
            if(mode == "hour" ){
              while(checkbox[cnt3]!= 's'){
                cnt3+=1;
              }
              hours[cnt3] = int_tmp;
              mode = "minute";
           }
            else if(mode == "minute"){
              minutes[cnt3] = int_tmp;
              mode = "hour";
              cnt3+=1;
          }

        }
        cnt+=1;
      }
    }
  for(int i = 0;i<7;i++){
    Serial.print("checkbox[" + String(i) +"] status: "); 
    Serial.print(checkbox[i]);     
    Serial.print("  hour[" + String(i) +"]: "); 
    Serial.print(hours[i]);
    Serial.print("  minute[" + String(i) +"]: "); 
    Serial.print(minutes[i]);
    Serial.println();
  }


}

void loop() {
  // put your main code here, to run repeatedly:


}
