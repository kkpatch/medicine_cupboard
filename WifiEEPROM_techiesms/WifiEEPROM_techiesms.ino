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

  Serial.begin(115200); //Initialising if(DEBUG)Serial Monitor
  
  pinMode(D1,INPUT);
  
  Serial.println();
  Serial.println("Disconnecting previously connected WiFi");
  WiFi.disconnect();
  EEPROM.begin(512); //Initialasing EEPROM
  delay(10);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println();
  Serial.println();
  Serial.println("Startup");

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


  WiFi.begin(esid.c_str(), epass.c_str());
  if (testWifi())
  {
    Serial.println("Succesfully Connected!!!");
    return;
  }
  else
  {
    Serial.println("Turning the HotSpot On");
    launchWeb();
    setupAP();// Setup HotSpot
  }

  Serial.println();
  Serial.println("Waiting.");
  
  while ((WiFi.status() != WL_CONNECTED))
  {
    Serial.print(".");
    delay(100);
    server.handleClient();
  }

}
void loop() {
  if ((WiFi.status() == WL_CONNECTED))
  {
    if(digitalRead(D1) == 1){
      WiFi.disconnect();  
      Serial.println("Turning the HotSpot On");
      launchWeb();
      setupAP();// Setup HotSpot
      Serial.println();
      Serial.println("Waiting.");
  
      while ((WiFi.status() != WL_CONNECTED))
      {
        Serial.print(".");
        delay(100);
        server.handleClient();
      }
    }
//
//    for (int i = 0; i < 10; i++)
//    {
//      digitalWrite(LED_BUILTIN, HIGH);
//      delay(1000);
//      digitalWrite(LED_BUILTIN, LOW);
//      delay(1000);
//    }

  }
//  else
//  {
//  }
  

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
  for (int i = 0; i < n; ++i)
  {
    // Print SSID and RSSI for each network found
    st += "<option value=\"";
    st += WiFi.SSID(i);
    st += "\">";
    st += WiFi.SSID(i);
    st += "</option>";
    
//    st += " (";
//    st += WiFi.RSSI(i);
//
//    st += ")";
//    st += (WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*";
//    st += "</li>";
  }
  st += "</select>";
  delay(100);
  WiFi.softAP("medicine_cupboard", "");
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








      
      content = "<!DOCTYPE HTML>\r\n<html>Hello from ESP8266 at ";
      content += "<form action=\"/scan\" method=\"POST\"><input type=\"submit\" value=\"scan\"></form>";
      content += ipStr;
      content += "<p>";
      content += "</p><form method='get' action='setting'><label>SSID: </label>";
      content += st;
      content += "<p>";
      content += "<input name='pass' length=64>";
      content += "      <div>";
      content += "        <input type='checkbox'  id='checkbox1' name='checkbox1'value='pre_morning' onclick='checkbox1_select()'>";
      content += "        <label for='checkbox'>pre_morning</label>";
      content += "        <input type='time'  id='time_1' name='time_1' style='display:none'/>";
//      content += "        <input type='number'  id='hour_1' name='hour_1' min='0' max='23' size='1' style='display:none' placeholder='hh' />";
//      content += "        <input type='number'  id='minute_1' name='minute_1' min='0' max='60' size='1' style='display:none' placeholder='mm' />";
      content += "      </div>";
      content += "      <div>";
      content += "        <input type='checkbox' id='checkbox2' name='checkbox2' value='post_morning' onclick='checkbox2_select()'>";
      content += "        <label for='checkbox'>post_morning</label>";
      content += "        <input type='time'  id='time_2' name='time_2' style='display:none'/>";
//      content += "        <input type='number'  id='hour_2' name='hour_2' min='0' max='23' size='1' style='display:none' placeholder='hh'>";
//      content += "        <input type='number'  id='minute_2' name='minute_2' min='0'  max='60' size='1' style='display:none' placeholder='mm'>";
      content += "      </div>";
      content += "      <div>";
      content += "        <input type='checkbox' id='checkbox3' name='checkbox3' value='pre_afternoon' onclick='checkbox3_select()'>";
      content += "        <label for='checkbox'>pre_afternoon</label>";
      content += "        <input type='time'  id='time_3' name='time_3' style='display:none'/>";
//      content += "        <input type='number'  id='hour_3' name='hour_3' min='0' max='23' size='1' style='display:none' placeholder='hh'>";
//      content += "        <input type='number'  id='minute_3' name='minute_3' min='0'  max='60' size='1' style='display:none' placeholder='mm'>";
      content += "      </div>";
      content += "      <div>";
      content += "        <input type='checkbox' id='checkbox4' name='checkbox4' value='post_afternoon' onclick='checkbox4_select()'>";
      content += "        <label for='checkbox'>post_afternoon</label>";
      content += "        <input type='time'  id='time_4' name='time_4' style='display:none'/>";
//      content += "        <input type='number'  id='hour_4' name='hour_4' min='0' max='23' size='1' style='display:none' placeholder='hh'>";
//      content += "        <input type='number'  id='minute_4' name='minute_4' min='0'  max='60' size='1' style='display:none' placeholder='mm'>";
      content += "      </div>";
      content += "      <div>";
      content += "        <input type='checkbox' id='checkbox5' name='checkbox5' value='pre_evening' onclick='checkbox5_select()'>";
      content += "        <label for='checkbox'>pre_evening</label>";
      content += "        <input type='time'  id='time_5' name='time_5' style='display:none'/>";
//      content += "        <input type='number'  id='hour_5' name='hour_5' size='1' min='0' max='23' style='display:none' placeholder='hh'>";
//      content += "        <input type='number'  id='minute_5' name='minute_5' min='0'  max='60' size='1' style='display:none' placeholder='mm'>";
      content += "      </div>";
      content += "      <div>";
      content += "        <input type='checkbox' id='checkbox6' name='checkbox6' value='post_evening' onclick='checkbox6_select()'>";
      content += "        <label for='checkbox'>post_evening</label>";
      content += "        <input type='time'  id='time_6' name='time_6' style='display:none'/>";
//      content += "        <input type='number'  id='hour_6' name='hour_6' size='1' min='0' max='23' style='display:none' placeholder='hh'>";
//      content += "        <input type='number'  id='minute_6' name='minute_6' min='0' max='60' style='display:none' size='1' placeholder='mm'>";
      content += "      </div>";
      content += "      <div>";
      content += "        <input type='checkbox' id='checkbox7' name='checkbox7' value='before_sleep' onclick='checkbox7_select()'>";
      content += "        <label for='checkbox'>before_sleep</label>";
      content += "        <input type='time'  id='time_7' name='time_7' style='display:none'/>";
//      content += "        <input type='number'  id='hour_7' name='hour_7' min='0' max='23' style='display:none' size='1' placeholder='hh'>";
//      content += "        <input type='number'  id='minute_7' name='minute_7' min='0' max='60' style='display:none' size='1' placeholder='mm'>";
      content += "      </div>";
      content += "<script>";
      content += "function checkbox1_select() {";
      content += "    if (document.getElementById('checkbox1').checked) {";
//      content += "        document.getElementById('hour_1').style.display = 'inline-block';";
//      content += "        ";
//      content += "        document.getElementById('minute_1').style.display = 'inline-block';";
      content += "        document.getElementById('time_1').style.display = 'inline-block';";
      content += "    } else {";
//      content += "        document.getElementById('hour_1').style.display = 'none';";
//      content += "        document.getElementById('hour_1').value = '';";
//      content += "        document.getElementById('minute_1').style.display = 'none';";
//      content += "        document.getElementById('minute_1').value = '';";
      content += "        document.getElementById('time_1').style.display = 'none';";
      content += "    }";
      content += "}";
      content += "function checkbox2_select() {";
      content += "    if (document.getElementById('checkbox2').checked) {";
//      content += "        document.getElementById('hour_2').style.display = 'inline-block';       ";
//      content += "        document.getElementById('minute_2').style.display = 'inline-block';";
      content += "        document.getElementById('time_2').style.display = 'inline-block';";
      content += "    } else {";
//      content += "        document.getElementById('hour_2').style.display = 'none';";
//      content += "        document.getElementById('hour_2').value = '';";
//      content += "        document.getElementById('minute_2').style.display = 'none';";
//      content += "        document.getElementById('minute_2').value = '';";
      content += "        document.getElementById('time_2').style.display = 'none';";
      content += "    }";
      content += "}";
      content += "function checkbox3_select() {";
      content += "    if (document.getElementById('checkbox3').checked) {";
//      content += "        document.getElementById('hour_3').style.display = 'inline-block';       ";
//      content += "        document.getElementById('minute_3').style.display = 'inline-block';";
      content += "        document.getElementById('time_3').style.display = 'inline-block';";
      content += "    } else {";
//      content += "        document.getElementById('hour_3').style.display = 'none';";
//      content += "        document.getElementById('hour_3').value = '';";
//      content += "        document.getElementById('minute_3').style.display = 'none';";
//      content += "        document.getElementById('minute_3').value = '';";
      content += "        document.getElementById('time_3').style.display = 'none';";
      content += "    }";
      content += "}";
      content += "function checkbox4_select() {";
      content += "    if (document.getElementById('checkbox4').checked) {";
//      content += "        document.getElementById('hour_4').style.display = 'inline-block';       ";
//      content += "        document.getElementById('minute_4').style.display = 'inline-block';";
      content += "        document.getElementById('time_4').style.display = 'inline-block';";
      content += "    } else {";
//      content += "        document.getElementById('hour_4').style.display = 'none';";
//      content += "        document.getElementById('hour_4').value = '';";
//      content += "        document.getElementById('minute_4').style.display = 'none';";
//      content += "        document.getElementById('minute_4').value = '';";
      content += "        document.getElementById('time_4').style.display = 'none';";
      content += "    }";
      content += "}";
      content += "function checkbox5_select() {";
      content += "    if (document.getElementById('checkbox5').checked) {";
//      content += "        document.getElementById('hour_5').style.display = 'inline-block';       ";
//      content += "        document.getElementById('minute_5').style.display = 'inline-block';";
      content += "        document.getElementById('time_5').style.display = 'inline-block';";
      content += "    } else {";
//      content += "        document.getElementById('hour_5').style.display = 'none';";
//      content += "        document.getElementById('hour_5').value = '';";
//      content += "        document.getElementById('minute_5').style.display = 'none';";
//      content += "        document.getElementById('minute_5').value = '';";
      content += "        document.getElementById('time_5').style.display = 'none';";
      content += "    }";
      content += "}";
      content += "function checkbox6_select() {";
      content += "    if (document.getElementById('checkbox6').checked) {";
//      content += "        document.getElementById('hour_6').style.display = 'inline-block';       ";
//      content += "        document.getElementById('minute_6').style.display = 'inline-block';";
      content += "        document.getElementById('time_6').style.display = 'inline-block';";
      content += "    } else {";
//      content += "        document.getElementById('hour_6').style.display = 'none';";
//      content += "        document.getElementById('hour_6').value = '';";
//      content += "        document.getElementById('minute_6').style.display = 'none';";
//      content += "        document.getElementById('minute_6').value = '';";
      content += "        document.getElementById('time_6').style.display = 'none';";
      content += "    }";
      content += "}";
      content += "function checkbox7_select() {";
      content += "    if (document.getElementById('checkbox7').checked) {";
//      content += "        document.getElementById('hour_7').style.display = 'inline-block';       ";
//      content += "        document.getElementById('minute_7').style.display = 'inline-block';";
      content += "        document.getElementById('time_7').style.display = 'inline-block';";
      content += "    } else {";
//      content += "        document.getElementById('hour_7').style.display = 'none';";
//      content += "        document.getElementById('hour_7').value = '';";
//      content += "        document.getElementById('minute_7').style.display = 'none';";
//      content += "        document.getElementById('minute_7').value = '';";
      content += "        document.getElementById('time_7').style.display = 'none';";
      content += "    }";
      content += "}";
      content += "</script>";
      content += "<input type='submit'></form>";
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
//      String qhour_1 = server.arg("hour_1");
//      String qminute_1 = server.arg("minute_1");
//      String qhour_2 = server.arg("hour_2");
//      String qminute_2 = server.arg("minute_2");
//      String qhour_3 = server.arg("hour_3");
//      String qminute_3 = server.arg("minute_3");
//      String qhour_4 = server.arg("hour_4");
//      String qminute_4 = server.arg("minute_4");
//      String qhour_5 = server.arg("hour_5");
//      String qminute_5 = server.arg("minute_5");
//      String qhour_6 = server.arg("hour_6");
//      String qminute_6 = server.arg("minute_6");
//      String qhour_7 = server.arg("hour_7");
//      String qminute_7 = server.arg("minute_7");
      String qtime_1 = server.arg("time_1");
      String qtime_2 = server.arg("time_2");
      String qtime_3 = server.arg("time_3");
      String qtime_4 = server.arg("time_4");
      String qtime_5 = server.arg("time_5");
      String qtime_6 = server.arg("time_6");
      String qtime_7 = server.arg("time_7");
//      Serial.print("---------------\n");
//      Serial.print(qtime_1);
//      Serial.print("\n---------------\n");
      
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

        EEPROM.write(65, qtime_1[0]);
        EEPROM.write(66, qtime_1[1]);
        EEPROM.write(67, qtime_1[3]);
        EEPROM.write(68, qtime_1[4]);

        EEPROM.write(69, qtime_2[0]);
        EEPROM.write(70, qtime_2[1]);
        EEPROM.write(71, qtime_2[3]);
        EEPROM.write(72, qtime_2[4]);

        EEPROM.write(73, qtime_3[0]);
        EEPROM.write(74, qtime_3[1]);
        EEPROM.write(75, qtime_3[3]);
        EEPROM.write(76, qtime_3[4]);

        EEPROM.write(77, qtime_4[0]);
        EEPROM.write(78, qtime_4[1]);
        EEPROM.write(79, qtime_4[3]);
        EEPROM.write(80, qtime_4[4]);

        EEPROM.write(81, qtime_5[0]);
        EEPROM.write(82, qtime_5[1]);
        EEPROM.write(83, qtime_5[3]);
        EEPROM.write(84, qtime_5[4]);

        EEPROM.write(85, qtime_6[0]);
        EEPROM.write(86, qtime_6[1]);
        EEPROM.write(87, qtime_6[3]);
        EEPROM.write(88, qtime_6[4]);

        EEPROM.write(89, qtime_7[0]);
        EEPROM.write(90, qtime_7[1]);
        EEPROM.write(91, qtime_7[3]);
        EEPROM.write(92, qtime_7[4]);

        EEPROM.write(93, qcheckbox1[0]);
        EEPROM.write(94, qcheckbox2[0]);
        EEPROM.write(95, qcheckbox3[0]);
        EEPROM.write(96, qcheckbox4[0]);
        EEPROM.write(97, qcheckbox5[0]);
        EEPROM.write(98, qcheckbox6[0]);
        EEPROM.write(99, qcheckbox7[0]);
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
