/*------------------------------------------------------------------------------
  10/2/2018
  Author: Makerbro
  Platforms: ESP8266
  Language: C++/Arduino
  File: wifi_modes_switch.ino
  ------------------------------------------------------------------------------
  Description: 
  Code for YouTube video demonstrating how  to switch the ESP8266 between Station 
  (STA) and Access Point (AP) modes, and how to store network credentials in 
  Flash memory:
  https://youtu.be/lyoBWH92svk
  Do you like my videos? You can support the channel:
  https://patreon.com/acrobotic
  https://paypal.me/acrobotic
  ------------------------------------------------------------------------------
  Please consider buying products from ACROBOTIC to help fund future
  Open-Source projects like this! We'll always put our best effort in every
  project, and release all our design files and code for you to use. 
  https://acrobotic.com/
  https://amazon.com/acrobotic
  ------------------------------------------------------------------------------
  License:
  Please see attached LICENSE.txt file for details.
------------------------------------------------------------------------------*/
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FS.h>
#include <ArduinoJson.h>

ESP8266WebServer server;
uint8_t pin_led = 2;
char* ssid = "YOUR_SSID"; //not used
char* password = "12345678";
char* mySsid = "Medicine_Cupboard";
char* hour_1 = 0;

IPAddress local_ip(192,168,11,4);
IPAddress gateway(192,168,11,1);
IPAddress netmask(255,255,255,0);

char webpage[] PROGMEM = R"=====(
<html>
<head>
</head>
<body>
  <form>
    <fieldset>
      <div>
        <label for="ssid">SSID</label>      
        <input value="" id="ssid" placeholder="SSID">
      </div>
      <div>
        <label for="password">PASSWORD</label>
        <input type="password" value="" id="password" placeholder="PASSWORD">
      </div>
      <div>
        <input type="checkbox"  id="checkbox1" value="pre_morning" onclick="checkbox1_select()">
        <label for="checkbox">pre_morning</label>
        <input type="number" value="" id="hour_1" min="0" max="23" size="1" style="display:none" placeholder="hh" />
        <input type="number" value="" id="minute_1" min="0" max="60" size="1" style="display:none" placeholder="mm" />
      </div>
      <div>
        <input type="checkbox"  id="checkbox2" value="post_morning" onclick="checkbox2_select()">
        <label for="checkbox">post_morning</label>
        <input type="number" value="" id="hour_2" min="0" max="23" size="1" style="display:none" placeholder="hh">
        <input type="number" value="" id="minute_2" min="0" max="60" size="1" style="display:none" placeholder="mm">
      </div>
      <div>
        <input type="checkbox"  id="checkbox3" value="pre_afternoon" onclick="checkbox3_select()">
        <label for="checkbox">pre_afternoon</label>
        <input type="number" value="" id="hour_3" min="0" max="23" size="1" style="display:none" placeholder="hh">
        <input type="number" value="" id="minute_3" min="0" max="60" size="1" style="display:none" placeholder="mm">
      </div>
      <div>
        <input type="checkbox"  id="checkbox4" value="post_afternoon" onclick="checkbox4_select()">
        <label for="checkbox">post_afternoon</label>
        <input type="number" value="" id="hour_4" min="0" max="23" size="1" style="display:none" placeholder="hh">
        <input type="number" value="" id="minute_4" min="0" max="60" size="1" style="display:none" placeholder="mm">
      </div>
      <div>
        <input type="checkbox"  id="checkbox5" value="pre_evening" onclick="checkbox5_select()">
        <label for="checkbox">pre_evening</label>
        <input type="number" value="" id="hour_5" size="1" min="0" max="23" style="display:none" placeholder="hh">
        <input type="number" value="" id="minute_5" min="0" max="60" size="1" style="display:none" placeholder="mm">
      </div>
      <div>
        <input type="checkbox"  id="checkbox6" value="post_evening" onclick="checkbox6_select()">
        <label for="checkbox">post_evening</label>
        <input type="number" value="" id="hour_6" size="1" min="0" max="23" style="display:none" placeholder="hh">
        <input type="number" value="" id="minute_6" min="0" max="60" style="display:none" size="1" placeholder="mm">
      </div>
      <div>
        <input type="checkbox"  id="checkbox7" value="before_sleep" onclick="checkbox7_select()">
        <label for="checkbox">before_sleep</label>  
        <input type="number" value="" id="hour_7" min="0" max="23" style="display:none" size="1" placeholder="hh">
        <input type="number" value="" id="minute_7" min="0" max="60" style="display:none" size="1" placeholder="mm">
      </div>
      <div>
        <button class="primary" id="savebtn" type="button" onclick="myFunction()">SAVE</button>
      </div>
    </fieldset>
  </form>
<script>
function checkbox1_select() {
    if (document.getElementById('checkbox1').checked) {
        document.getElementById('hour_1').style.display = 'inline-block';
        
        document.getElementById('minute_1').style.display = 'inline-block';
    } else {
        document.getElementById('hour_1').style.display = 'none';
        document.getElementById('hour_1').value = "";
        document.getElementById('minute_1').style.display = 'none';
        document.getElementById('minute_1').value = "";
    }
}
function checkbox2_select() {
    if (document.getElementById('checkbox2').checked) {
        document.getElementById('hour_2').style.display = 'inline-block';       
        document.getElementById('minute_2').style.display = 'inline-block';
    } else {
        document.getElementById('hour_2').style.display = 'none';
        document.getElementById('hour_2').value = "";
        document.getElementById('minute_2').style.display = 'none';
        document.getElementById('minute_2').value = "";
    }
}
function checkbox3_select() {
    if (document.getElementById('checkbox3').checked) {
        document.getElementById('hour_3').style.display = 'inline-block';       
        document.getElementById('minute_3').style.display = 'inline-block';
    } else {
        document.getElementById('hour_3').style.display = 'none';
        document.getElementById('hour_3').value = "";
        document.getElementById('minute_3').style.display = 'none';
        document.getElementById('minute_3').value = "";
    }
}
function checkbox4_select() {
    if (document.getElementById('checkbox4').checked) {
        document.getElementById('hour_4').style.display = 'inline-block';       
        document.getElementById('minute_4').style.display = 'inline-block';
    } else {
        document.getElementById('hour_4').style.display = 'none';
        document.getElementById('hour_4').value = "";
        document.getElementById('minute_4').style.display = 'none';
        document.getElementById('minute_4').value = "";
    }
}
function checkbox5_select() {
    if (document.getElementById('checkbox5').checked) {
        document.getElementById('hour_5').style.display = 'inline-block';       
        document.getElementById('minute_5').style.display = 'inline-block';
    } else {
        document.getElementById('hour_5').style.display = 'none';
        document.getElementById('hour_5').value = "";
        document.getElementById('minute_5').style.display = 'none';
        document.getElementById('minute_5').value = "";
    }
}
function checkbox6_select() {
    if (document.getElementById('checkbox6').checked) {
        document.getElementById('hour_6').style.display = 'inline-block';       
        document.getElementById('minute_6').style.display = 'inline-block';
    } else {
        document.getElementById('hour_6').style.display = 'none';
        document.getElementById('hour_6').value = "";
        document.getElementById('minute_6').style.display = 'none';
        document.getElementById('minute_6').value = "";
    }
}
function checkbox7_select() {
    if (document.getElementById('checkbox7').checked) {
        document.getElementById('hour_7').style.display = 'inline-block';       
        document.getElementById('minute_7').style.display = 'inline-block';
    } else {
        document.getElementById('hour_7').style.display = 'none';
        document.getElementById('hour_7').value = "";
        document.getElementById('minute_7').style.display = 'none';
        document.getElementById('minute_7').value = "";
    }
}
</script>
</body>
<script>
function addbox() {
    if (document.getElementById('checkbox1').checked) {
        document.getElementById('hour_1').style.display = 'block';
        document.getElementById('minute_1').style.display = 'block';
    } else {
        document.getElementById('hour_1').style.display = 'none';
        document.getElementById('minute_1').style.display = 'none';
    }
}
</script>
</body>
<script>
function myFunction()
{
  console.log("button was clicked!");
  var ssid = document.getElementById("ssid").value;
  var password = document.getElementById("password").value;
  var hour_1 = document.getElementById("hour_1").value;
  var hour_2 = document.getElementById("hour_2").value;
  var hour_3 = document.getElementById("hour_3").value;
  var hour_4 = document.getElementById("hour_4").value;
  var hour_5 = document.getElementById("hour_5").value;
  var hour_6 = document.getElementById("hour_6").value;
  var hour_7 = document.getElementById("hour_7").value;
  var data = {ssid:ssid, password:password};
  var xhr = new XMLHttpRequest();
  var url = "/settings";
  xhr.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      // Typical action to be performed when the document is ready:
      if(xhr.responseText != null){
        console.log(xhr.responseText);
      }
    }
  };
  xhr.open("POST", url, true);
  xhr.send(JSON.stringify(data));
};
</script>
</html>
)=====";

void setup()
{
  pinMode(pin_led, OUTPUT);
  Serial.begin(115200);
  SPIFFS.begin();

  wifiConnect();

  server.on("/",[](){server.send_P(200,"text/html", webpage);});
  server.on("/toggle",toggleLED);
  server.on("/settings", HTTP_POST, handleSettingsUpdate);
  
  server.begin();
}

void loop()
{
  server.handleClient();
}

void handleSettingsUpdate()
{
  String data = server.arg("plain");
  DynamicJsonBuffer jBuffer;
  JsonObject& jObject = jBuffer.parseObject(data);

  File configFile = SPIFFS.open("/config.json", "w");
  jObject.printTo(configFile);  
  configFile.close();
  
  server.send(200, "application/json", "{\"status\" : \"ok\"}");
  delay(500);
  
  wifiConnect();
}

void wifiConnect()
{
  //reset networking
  WiFi.softAPdisconnect(true);
  WiFi.disconnect();          
  delay(1000);
  //check for stored credentials
  if(SPIFFS.exists("/config.json")){
    const char * _ssid = "", *_pass = "";
    File configFile = SPIFFS.open("/config.json", "r");
    if(configFile){
      size_t size = configFile.size();
      std::unique_ptr<char[]> buf(new char[size]);
      configFile.readBytes(buf.get(), size);
      configFile.close();

      DynamicJsonBuffer jsonBuffer;
      JsonObject& jObject = jsonBuffer.parseObject(buf.get());
      if(jObject.success())
      {
        _ssid = jObject["ssid"];
        _pass = jObject["password"];
        WiFi.mode(WIFI_STA);
        WiFi.begin(_ssid, _pass);
        unsigned long startTime = millis();
        while (WiFi.status() != WL_CONNECTED) 
        {
          delay(500);
          Serial.print(".");
          digitalWrite(pin_led,!digitalRead(pin_led));
          if ((unsigned long)(millis() - startTime) >= 5000) break;
        }
      }
    }
  }

  if (WiFi.status() == WL_CONNECTED)
  {
    digitalWrite(pin_led,HIGH);
  } else 
  {
    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(local_ip, gateway, netmask);
    WiFi.softAP(mySsid, password); 
    digitalWrite(pin_led,LOW);      
  }
  Serial.println("");
  Serial.print(hour_1);
  WiFi.printDiag(Serial);
  
}

void toggleLED()
{
  digitalWrite(pin_led,!digitalRead(pin_led));
  server.send(204,"");
}
