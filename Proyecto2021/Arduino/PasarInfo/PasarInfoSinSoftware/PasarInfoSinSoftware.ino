void setup(){
Serial.begin(115200); 
}
void loop(){
 float prueba;
 prueba = 23.8;
//linkSerial.write(prueba);
Serial.println(prueba);
delay(1000);


}
