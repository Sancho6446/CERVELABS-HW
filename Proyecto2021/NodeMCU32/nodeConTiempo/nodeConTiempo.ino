#include <ArduinoJson.h>
#include <WiFi.h>
#include <HTTPClient.h>


/*const char* ssid = "Fibertel WiFi000 2.4GHz";
const char* password = "0141840184";*/
const char* ssid = "EDU-SPECIAL";
const char* password = "TiC_1996$";
String serverName = "https://cervelabs.herokuapp.com/arduino/pub/add-record";
String datos;
long lastTime = 0;
long minutes = 0;
long hours = 0;
String Caudal;
String Cauda2;
String Cauda3;

void setup() {
Serial.begin(115200);
}
void loop() { 
   datos = Serial.readString();
  if(datos.indexOf("*") > 0){
    datos.replace("*", "");
    Caudal = datos;
 Serial.println(datos);
    }
    if(datos.indexOf("+") > 0){
    datos.replace("+", "");
    Cauda2 = datos;
 Serial.println(datos);
    }
    if(datos.indexOf("~") > 0){
    datos.replace("~", "");
    Cauda3 = datos;
 Serial.println(datos);
    }
    
      
      
   
   if(millis()-lastTime > 60000){//60000 == 60 segundos
    minutes++;
    lastTime = millis();
    
  }
  if(minutes > 59){
    hours++;
    minutes = 0;
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
    
    doc["pubId"] = "60e8797fde943f2afc94b8b2"; 
    doc["record"] = datos;
     String json;
     serializeJson(doc, json);
     int httpResponseCode = http.POST(json);      
     http.end();
     WiFi.disconnect();
    }
    
  
  }
  
}

  
