#include <ArduinoJson.h>
#include <WiFi.h>
#include <HTTPClient.h>
//#include <TimeLib.h>

const char* ssid = "EDU-SPECIAL";
const char* password = "TiC_1996$";
const String serverName = "https://proyecto-5to.herokuapp.com/test";
long lastTime1 = 0;
long minutes = 0;
int hours = 0;
void setup() {
  Serial.begin(115200); 
}

void loop() {
  if(hours == 1){
    hours = 0;
    //Check WiFi connection status
     if(WiFi.status()== WL_CONNECTED){
        HTTPClient http;
        http.begin(serverName);
        http.addHeader("Content-Type", "application/json");
        DynamicJsonDocument doc(2048);
        doc["text"] = "LICHU POBRE"; 
        String json;
        serializeJson(doc, json);
         int httpResponseCode = http.POST(json);      
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        Serial.print(http.getString()); 
        http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    
  
  }else
  {
      if(millis()-lastTime1 > 60000){
      minutes++;
    
      lastTime1 = millis();
             }
      if(minutes > 59){
      hours++;
      minutes = 0;
    }
  }
}
