/**
   Written and Verified by the owner of techiesms
   Mr. Sachin Soni
   This code is open for fair use.
   If you are using it for commercial purpose, then it's mandatory to give credits
   Tutorial Video Link :- 
*/

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>

#include <SoftwareSerial.h>

SoftwareSerial mySerial(5, 4); // RX, TX

//Variables
int i = 0;
int statusCode;
const char* ssid = "text";
const char* passphrase = "text";
String st;
String content;


//Function Decalration
bool testWifi(void);
void launchWeb(void);
void setupAP(void);

//Establishing Local server at port 80 whenever required
ESP8266WebServer server(80);

void setup()
{
  pinMode(D6,INPUT);
  Serial.begin(115200); //Initialising if(DEBUG)Serial Monitor
  Serial.println();
  Serial.println("Disconnecting previously connected WiFi");
  WiFi.disconnect();
  EEPROM.begin(512); //Initialasing EEPROM
  delay(10);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println();
  Serial.println();
  Serial.println("Startup");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(115200);

  //---------------------------------------- Read eeprom for ssid and pass
  Serial.println("Reading EEPROM ssid");

  String esid;
  for (int i = 0; i < 32; ++i)
  {
    esid += char(EEPROM.read(i));
  }
  Serial.println();
  Serial.print("SSID: ");
  Serial.println(esid);
  Serial.println("Reading EEPROM pass");

  String epass = "";
  for (int i = 32; i < 64; ++i)
  {
    epass += char(EEPROM.read(i));
  }
  Serial.print("PASS: ");
  Serial.println(epass);

  String echeckbox = "";
  for (int i = 65; i < 73; ++i)
  {
    echeckbox += char(EEPROM.read(i));
  }
  Serial.print("Checkbox: ");
  Serial.println(echeckbox);
  for(int i = 0;i<echeckbox.length();i++){
    mySerial.write(echeckbox[i]);
  }
  

  WiFi.begin(esid.c_str(), epass.c_str());
  if (testWifi())
  {
    Serial.println("Succesfully Connected!!!");
    return;
  }

}
void loop() {
  if(digitalRead(D6) == 1){
    Serial.println("Turning the HotSpot On");
    launchWeb();
    setupAP();// Setup HotSpot  
    Serial.println();
    Serial.println("Waiting.");  
    while ((WiFi.status() != WL_CONNECTED)){
      Serial.print(".");
      delay(100);
      server.handleClient();
    }    
  }
  if (mySerial.available()) {
    Serial.write(mySerial.read());
  }
}


//----------------------------------------------- Fuctions used for WiFi credentials saving and connecting to it which you do not need to change 
bool testWifi(void)
{
  int c = 0;
  Serial.println("Waiting for Wifi to connect");
  while ( c < 20 ) {
    if (WiFi.status() == WL_CONNECTED)
    {
      return true;
    }
    delay(500);
    Serial.print("*");
    c++;
  }
  Serial.println("");
  Serial.println("Connect timed out, opening AP");
  return false;
}

void launchWeb()
{
  Serial.println("");
  if (WiFi.status() == WL_CONNECTED)
    Serial.println("WiFi connected");
  Serial.print("Local IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("SoftAP IP: ");
  Serial.println(WiFi.softAPIP());
  createWebServer();
  // Start the server
  server.begin();
  Serial.println("Server started");
}

void setupAP(void)
{
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0)
    Serial.println("no networks found");
  else
  {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i)
    {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*");
      delay(10);
    }
  }
  Serial.println("");
  st = "<select name=\"ssid\" id=\"ssid\">";
  st += "<option value=\"\" disabled selected hidden>Choose Wifi SSID...</option>";
  for (int i = 0; i < n; ++i)
  {
    // Print SSID and RSSI for each network found
    st += "<option value=\"";
    st += WiFi.SSID(i);
    st += "\">";
    st += WiFi.SSID(i);
    st += "</option>";
  }
  delay(100);
  WiFi.softAP("techiesms", "");
  Serial.println("softap");
  launchWeb();
  Serial.println("over");
}

void createWebServer()
{
 {
    server.on("/", []() {

      IPAddress ip = WiFi.softAPIP();
      String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
//      content = "<!DOCTYPE HTML>\r\n<html>Hello from ESP8266 at ";
//      content += "<form action=\"/scan\" method=\"POST\"><input type=\"submit\" value=\"scan\"></form>";
//      content += ipStr;
//      content += "";
      content += "<form method='get' action='setting'>";
      content += "  <label>SSID: </label>";
      content +=    st;
      content += "  <br><br>";
      content += "  <div>";  
      content += "  <br><label>Password: </label><input type = 'password' name='pass' length=32>";
      content += "      </div>";
      content += "      <div>";  
      content += "      </div>";
      content += "      <div>";  
      content += "        <br><label>Select Time Interval </label>"; 
      content += "      </div>";
      content += "      <div>";     
      content += "        <input type='checkbox'  id='checkbox1' name='checkbox1'value='A''>";
      content += "        <label for='checkbox'>Before Breakfast (06.30)</label><br>";
      content += "        <input type='checkbox'  id='checkbox2' name='checkbox2'value='B''>";
      content += "        <label for='checkbox'>After  Breakfast (07.30)</label><br>";
      content += "        <input type='checkbox'  id='checkbox3' name='checkbox3'value='C''>";
      content += "        <label for='checkbox'>Before Lunch     (11.30)</label><br>";
      content += "        <input type='checkbox'  id='checkbox4' name='checkbox4'value='D''>";
      content += "        <label for='checkbox'>After  Lunch     (12.30)</label><br>";
      content += "        <input type='checkbox'  id='checkbox5' name='checkbox5'value='E''>";
      content += "        <label for='checkbox'>Before Dinner    (16.30)</label><br>";
      content += "        <input type='checkbox'  id='checkbox6' name='checkbox6'value='F''>";
      content += "        <label for='checkbox'>After  Dinner    (17.30)</label><br>";
      content += "        <input type='checkbox'  id='checkbox7' name='checkbox7'value='G''>";
      content += "        <label for='checkbox'>Before Bedtime   (20.00)</label><br><br><br>";
      content += "        <input type='submit'></form>";
      content += "      </div>";
      content += "</html>";
      server.send(200, "text/html", content);
    });
    server.on("/scan", []() {
      //setupAP();
      IPAddress ip = WiFi.softAPIP();
      String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);

      content = "<!DOCTYPE HTML>\r\n<html>go back";
      server.send(200, "text/html", content);
    });

    server.on("/setting", []() {
      String qsid = server.arg("ssid");
      String qpass = server.arg("pass");
      
      String qcheckbox1 = server.arg("checkbox1");
      String qcheckbox2 = server.arg("checkbox2");
      String qcheckbox3 = server.arg("checkbox3");
      String qcheckbox4 = server.arg("checkbox4");
      String qcheckbox5 = server.arg("checkbox5");
      String qcheckbox6 = server.arg("checkbox6");
      String qcheckbox7 = server.arg("checkbox7");
      
      if (qsid.length() > 0 && qpass.length() > 0) {
        Serial.println("clearing eeprom");
        for (int i = 0; i < 96; ++i) {
          EEPROM.write(i, 0);
        }
        Serial.println(qsid);
        Serial.println("");
        Serial.println(qpass);
        Serial.println("");

        Serial.println("writing eeprom ssid:");
        for (int i = 0; i < qsid.length(); ++i)
        {
          EEPROM.write(i, qsid[i]);
          Serial.print("Wrote: ");
          Serial.println(qsid[i]);
        }
        Serial.println("writing eeprom pass:");
        for (int i = 0; i < qpass.length(); ++i)
        {
          EEPROM.write(32 + i, qpass[i]);
          Serial.print("Wrote: ");
          Serial.println(qpass[i]);
        }
        Serial.println(qcheckbox1);
        Serial.println("");
        Serial.println(qcheckbox2);
        Serial.println("");
        Serial.println(qcheckbox3);
        Serial.println("");
        Serial.println(qcheckbox4);
        Serial.println("");
        Serial.println(qcheckbox5);
        Serial.println("");
        Serial.println(qcheckbox6);
        Serial.println("");
        Serial.println(qcheckbox7);
        Serial.println("");

        EEPROM.write(65, qcheckbox1[0]);
        EEPROM.write(66, qcheckbox2[0]);
        EEPROM.write(67, qcheckbox3[0]);
        EEPROM.write(68, qcheckbox4[0]);
        EEPROM.write(69, qcheckbox5[0]);
        EEPROM.write(70, qcheckbox6[0]);
        EEPROM.write(71, qcheckbox7[0]);
        EEPROM.commit();

        content = "{\"Success\":\"saved to eeprom... reset to boot into new wifi\"}";
        statusCode = 200;
        ESP.reset();
      } else {
        content = "{\"Error\":\"404 not found\"}";
        statusCode = 404;
        Serial.println("Sending 404");
      }
      server.sendHeader("Access-Control-Allow-Origin", "*");
      server.send(statusCode, "application/json", content);

    });
  } 
}
