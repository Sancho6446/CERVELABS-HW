#include <ArduinoJson.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <TimeLib.h>

const char* ssid = "EDU-SPECIAL";
const char* password = "TiC_1996$";
unsigned long timerDelay = 5000;
unsigned long lastTime = 0;
String serverName = "https://proyecto-5to.herokuapp.com/test";
double valorCaudalimetro1 = 0;
double valorCaudalimetro2 = 0;

void setup() {
  Serial.begin(115200); 

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  
}

void loop() {
  //Send an HTTP POST request every 10 minutes
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED && ){
      HTTPClient http;
      http.begin(serverName);
      http.addHeader("Content-Type", "application/json");
     DynamicJsonDocument doc(2048);
     doc["pubId"] = "6080c42b0e51a121c4c75e5a";
     doc["record"] = "[[1000,10],[530,0]]";
      
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
    lastTime = millis();
  }
}
