#include <SoftwareSerial.h>
SoftwareSerial espSerial(5, 6);
void setup(){
Serial.begin(115200);
espSerial.begin(115200);

}
void loop(){
 int prueba;
 prueba = 323;
espSerial.println(prueba);
delay(1000);
}
