
#include <ArduinoJson.h>
#include <WiFi.h>
#include <HTTPClient.h>
int datos;
const char* ssid = "Fibertel WiFi000 2.4GHz";
const char* password = "0141840184";
String serverName = "https://cervelabs.herokuapp.com/arduino/pub/add-record";
void setup() {
// Open serial communications and wait for port to open:
Serial.begin(115200);
while (!Serial) {
; // wait for serial port to connect. Needed for native USB port only
}
}
void loop() { // run over and over




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
     doc["record"] = Serial.read();
     String json;
     serializeJson(doc, json);

      int httpResponseCode = http.POST(json);      
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      Serial.print(http.getString());
          
      http.end();
    }
    
}
  
