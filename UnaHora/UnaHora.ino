long lastTime = 0;
long minutes = 0;
long hours = 0;

void setup() {
  Serial.begin(115200);

}

void loop() {

  if(millis()-lastTime > 60000){
    minutes++;
    
    lastTime = millis();
  }
  if(minutes > 59){
    hours++;
    minutes = 0;
  }
  

}
