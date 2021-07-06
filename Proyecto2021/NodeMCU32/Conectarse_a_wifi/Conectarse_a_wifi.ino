#include <ArduinoJson.h>
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Fibertel WiFi000 2.4GHz";
const char* password = "0141840184";
unsigned long timerDelay = 5000;
unsigned long lastTime = 0;
String serverName = "https://cervelabs.herokuapp.com/arduino/pub/add-record";
void setup() {
  Serial.begin(115200); 
  WiFi.begin(ssid, password);
  Serial.print("Connectando");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("ip:");
  Serial.println(WiFi.localIP());
 //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;
      // Your Domain name with URL path or IP address with path
      http.begin(serverName);
      // Specify content-type header
      http.addHeader("Content-Type", "application/json");
      // Data to send with HTTP POST
      const int capacity = JSON_OBJECT_SIZE(2);
      StaticJsonDocument<capacity> doc;
      doc["pubId"] = "60cfbba8c2aa352bc0e94090";
      doc["record"] = "100,10; 300,30;210,21";
      String json;
      serializeJson(doc, json);
      Serial.println(json);
      int httpResponseCode = http.POST(json);      
      Serial.print("HTTP code: ");
      Serial.println(httpResponseCode);
      Serial.print(http.getString());
      // Free resources
      http.end();
    
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
  
  


void loop() {
  
  /*if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;
      
      // Your Domain name with URL path or IP address with path
      http.begin(serverName);

      // Specify content-type header
      http.addHeader("Content-Type", "application/json");
      // Data to send with HTTP POST
     DynamicJsonDocument doc(2048);
     doc["text"] = "LICHU POBRE";
     String json;
     serializeJson(doc, json);

      int httpResponseCode = http.POST(json);      
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      Serial.print(http.getString());
      // Free resources
      http.end();
      
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }*/
 
}
