
#include <ArduinoJson.h>
#include <WiFi.h>
#include <HTTPClient.h>

/*const char* ssid = "Fibertel WiFi000 2.4GHz";
const char* password = "0141840184";*/
const char* ssid = "EDU-SPECIAL";
const char* password = "TiC_1996$";
String serverName = "https://cervelabs.herokuapp.com/arduino/pub/add-record";
float datos;
void setup() {
Serial.begin(115200);
while (!Serial) {
; 
}
}
void loop() { 
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;
      http.begin(serverName);
      http.addHeader("Content-Type", "application/json");
    const int capacity = JSON_OBJECT_SIZE(2);
    StaticJsonDocument<capacity> doc;
    datos = Serial.parseFloat();
    doc["pubId"] = "60e8797fde943f2afc94b8b2"; 
    doc["record"] = datos;
     String json;
     serializeJson(doc, json);
     int httpResponseCode = http.POST(json);      
     http.end();
    }
    
}
  
