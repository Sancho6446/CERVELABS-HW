#include <SoftwareSerial.h>
SoftwareSerial linkSerial(5, 6);

void setup(){
Serial.begin(115200);
linkSerial.begin(115200);

}
void loop(){
 float prueba;
 prueba = 42.3;
//linkSerial.write(prueba);
linkSerial.println(prueba);
delay(1000);


}
