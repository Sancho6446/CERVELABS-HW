#include <ArduinoJson.h>
#include <WiFi.h>
#include <HTTPClient.h>


const char* ssid = "EDU-SPECIAL";
const char* password = "TiC_1996$";
unsigned long timerDelay = 5000;
unsigned long lastTime = 0;
String serverName = "https://cervelabs.herokuapp.com/arduino/pub/add-record";
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
  if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;
      http.begin(serverName);
      http.addHeader("Content-Type", "application/json");
    const int capacity = JSON_OBJECT_SIZE(2);
    StaticJsonDocument<capacity> doc;

     doc["pubId"] = "6080c42b0e51a121c4c75e5a";
      doc["record"] = "2100,21-3330,33-2500,25";
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
  
}

void loop() {
 
}
