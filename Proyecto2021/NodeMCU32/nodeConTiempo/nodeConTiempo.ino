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
String Caudalimetrol;
String Caudalimetro2;
String Caudalimetro3;
String CaudalimetrolimetroFinal;
void setup() {
Serial.begin(115200);
}
void loop() { 
   datos = Serial.readString();
  if(datos.indexOf("*") > 0){
    datos.replace("*", "");
    Caudalimetrol = datos;
 
    }
    if(datos.indexOf("+") > 0){
    datos.replace("+", "");
    Caudalimetro2 = datos;
 
    }
    if(datos.indexOf("~") > 0){
    datos.replace("~", "");
    Caudalimetro3 = datos;
 
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
    CaudalimetroFinal = Caudalimetro1 +",10-"+ Caudalimetro2 +",3-"+ Caudalimetro3 +",21";
    String(CaudalimetroFinal);//"1000,10-300,3-210,21" los guiones separan canillas y las comas separan consumido de perdida
    doc["pubId"] = "60e8797fde943f2afc94b8b2"; 
    doc["record"] = CaudalimetroFinal;
     String json;
     serializeJson(doc, json);
     int httpResponseCode = http.POST(json);      
     http.end();
     WiFi.disconnect();
    }
    
  
  }
  
}

  
