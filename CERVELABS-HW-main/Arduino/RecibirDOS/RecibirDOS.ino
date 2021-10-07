//MIPRIMERA VEZ USANDO GUT OCOMO UNA PERSONA NORMAL _ NASHEEEEE
#include <FlowMeter.h>  // https://github.com/sekdiy/FlowMeter
#include <SPI.h>
#include <SD.h>
//  0(RX), 1(TX) 19(RX), 18(TX) 17(RX), 16(TX) 15(RX), 14(TX)
File myFile;
String Caudalimetrol = "0";
String Caudalimetro2 = "0";
String Caudalimetro3 = "0";
//Calibration
const double cap = 25.0f;  // l/min
const double kf = 5.5f;     // Hz per l/min        
FlowSensorProperties Canillas = {cap, kf, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
const double capD = 6.0f;  // l/min
const double kfD = 9.3f; 
FlowSensorProperties Descarte = {capD, kfD, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};


// connect a flow meter to an interrupt pin (see notes on your Arduino model for pin numbers)
FlowMeter *Meter1;
FlowMeter *Meter2;
FlowMeter *Meter3;
long lastTime = 0;
long minutes = 0;
long hours = 0;

// set the measurement update period to 1s (1000 ms)
const unsigned long period = 1000;

// define an 'interrupt service handler' (ISR) for every interrupt pin you use
void Meter1ISR() {
    // let our flow meter count the pulses
    Meter1->count();
}
void Meter3ISR() {
    // let our flow meter count the pulses
    Meter3->count();
}

// define an 'interrupt service handler' (ISR) for every interrupt pin you use
void Meter2ISR() {
    // let our flow meter count the pulses
    Meter2->count();
}

void setup() {
    // prepare serial communication
    Serial.begin(115200);

    // get a new FlowMeter instance for an uncalibrated flow sensor and let them attach their 'interrupt service handler' (ISR) on every rising edge
    Meter1 = new FlowMeter(digitalPinToInterrupt(2), Descarte, Meter1ISR, RISING);
    
    // do this setup step for every  FlowMeter and ISR you have defined, depending on how many you need
    Meter2 = new FlowMeter(digitalPinToInterrupt(3), Canillas, Meter2ISR, RISING);
    Meter3 = new FlowMeter(digitalPinToInterrupt(18), Canillas, Meter3ISR, RISING); //2, 3, 18, 19, 20, 21
}

void loop() {
    // wait between output updates
    delay(period);

    // process the (possibly) counted ticks
    Meter1->tick(period);
    Meter2->tick(period);
    Meter3->tick(period);

    // output some measurement result
   Caudalimetrol = String(Meter1->getTotalVolume());
   Caudalimetrol =  Caudalimetrol + "+";
   Caudalimetro2 = String(Meter2->getTotalVolume());
   Caudalimetro2 =  Caudalimetro2 + "*";
   Caudalimetro3 = String(Meter3->getTotalVolume());
   Caudalimetro3 =  Caudalimetro3 + "~";
   
   Serial.print(Caudalimetrol);
   Serial.print(Caudalimetro2);
   Serial.print(Caudalimetro3);

 if(millis()-lastTime > 10000){//60000 == 60 segundos
    minutes++;
    lastTime = millis();
    
  }
  if(minutes >= 1){
    hours++;
    minutes = 0;
   //"600.12,10-300,3-210.3,21" \n
  if (!SD.begin(4)) {
    return;
  }
  
  myFile = SD.open("Datos.txt", FILE_WRITE);

  
  if (myFile) {
    myFile.print(Caudalimetrol);
    myFile.print(Caudalimetro2);
    myFile.println(Caudalimetro3);
    myFile.close();
    
  }  
  }
}
