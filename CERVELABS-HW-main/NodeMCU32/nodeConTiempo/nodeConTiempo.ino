#include <ArduinoJson.h>
#include <WiFi.h>
#include <HTTPClient.h>


/*const char* ssid = "Fibertel WiFi000 2.4GHz";
const char* password = "0141840184";*/
const char* ssid = "EDU-SPECIAL";
const char* password = "TiC_1996$";
String serverName = "https://cervelabs.herokuapp.com/arduino/pub/add-record";
String datos= "0";
long lastTime = 0;
long minutes = 0;
long hours = 0;
String Caudalimetrol = "0";
String Caudalimetro2 = "0";
String Caudalimetro3 = "0";
void setup() {
Serial.begin(115200);
   
}
void loop() { 
if (Serial.available() > 0) {
Caudalimetrol = Serial.readStringUntil('+');
Caudalimetro2 = Serial.readStringUntil('*');
Caudalimetro3 = Serial.readStringUntil('~');
}
if(Caudalimetrol == NULL){Caudalimetrol = 0.0;}
if(Caudalimetro2 == NULL){Caudalimetro2 = 0.0;}
if(Caudalimetro3 == NULL){Caudalimetro3 = 0.0;}
/*if(datos.indexOf("*") > 0){
    datos.replace("*", "");
    Caudalimetrol = datos;
 
    }
    if(datos.indexOf("+") > 0){
    datos.replace("+", "");
    Caudalimetro2 = datos;
  Serial.println(Caudalimetro2);
    }
    if(datos.indexOf("~") > 0){
    datos.replace("~", "");
    Caudalimetro3 = datos; 
 
    }*/
   if(millis()-lastTime > 10000){//60000 == 60 segundos
    minutes++;
    lastTime = millis();
    
  }
  if(minutes >= 1){
    hours++;
    minutes = 0;
    WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) {
    
  }

  if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;
      http.begin(serverName);
      http.addHeader("Content-Type", "application/json");
    const int capacity = JSON_OBJECT_SIZE(2)+64;
    StaticJsonDocument<capacity> doc; 
    doc["pubId"] = "60e8797fde943f2afc94b8b2";
    doc["record"] = String(Caudalimetrol +","+ Caudalimetro3+"-"+ Caudalimetro2 +","+ Caudalimetro3+"-");
    String json;
    serializeJson(doc, json);
    int httpResponseCode = http.POST(json);    
    http.end();
    WiFi.disconnect();
    }
  }
}
