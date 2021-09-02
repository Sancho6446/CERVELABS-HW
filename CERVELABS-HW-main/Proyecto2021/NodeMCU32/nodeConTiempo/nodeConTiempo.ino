#include <ArduinoJson.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "FS.h"
#include "SD.h"
#include "SPI.h"


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
if(!SD.begin(5)){ }
  uint8_t cardType = SD.cardType();
  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
    writeFile(SD, "/Datos.txt", String(Caudalimetrol +",1-"+ Caudalimetro2 +",1-"+ Caudalimetro3 +",1 \n"));
   appendFile(SD, "/Datos.txt", String(Caudalimetrol +",1-"+ Caudalimetro2 +",1-"+ Caudalimetro3 +",1 \n"));
    readFile(SD, "/Datos.txt");
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
     
    /*deleteFile(SD, "/hello.txt");
    deleteFile(SD, "/Datos.txt");
    writeFile(SD, "/Datos.txt", String(Caudalimetrol +",1-"+ Caudalimetro2 +",1-"+ Caudalimetro3 +",1 \n"));
   appendFile(SD, "/Datos.txt", String(Caudalimetrol +",1-"+ Caudalimetro2 +",1-"+ Caudalimetro3 +",1 \n"));
    readFile(SD, "/Datos.txt");*/
    doc["record"] = String(Caudalimetrol +",1-"+ Caudalimetro2 +",1-"+ Caudalimetro3 +",1");
     
     String json;
     serializeJson(doc, json);
     //int httpResponseCode = http.POST(json);    
     http.end();
     WiFi.disconnect();
    }
    
  
  }
  
}
void readFile(fs::FS &fs, const char * path){// esto no puede ser funcion porque necesito ponerlo en una variable en vez de en el monitor
  Serial.printf("Reading file: %s\n", path);

  File file = fs.open(path);
  if(!file){
    Serial.println("Failed to open file for reading");
    return;
  }

  Serial.print("Read from file: ");
  while(file.available()){
    Serial.write(file.read());
  }
  file.close();
}

void writeFile(fs::FS &fs, const char * path, String message){
  Serial.printf("Writing file: %s\n", path);

  File file = fs.open(path, FILE_WRITE);
  if(!file){
    Serial.println("Failed to open file for writing");
    return;
  }
  if(file.print(message)){
    Serial.println("File written");
  } else {
    Serial.println("Write failed");
  }
  file.close();
}

void appendFile(fs::FS &fs, const char * path, String message){
  Serial.printf("Appending to file: %s\n", path);

  File file = fs.open(path, FILE_APPEND);
  if(!file){
    Serial.println("Failed to open file for appending");
    return;
  }
  if(file.print(message)){
      Serial.println("Message appended");
  } else {
    Serial.println("Append failed");
  }
  file.close();
}


void deleteFile(fs::FS &fs, const char * path){
  Serial.printf("Deleting file: %s\n", path);
  if(fs.remove(path)){
    Serial.println("File deleted");
  } else {
    Serial.println("Delete failed");
  }
}


  
