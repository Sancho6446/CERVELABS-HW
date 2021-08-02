const int sensorPin = 2;
const int measureInterval = 1000;
volatile int pulseConter;
// YF-S201
const float factorK = 9.3;
//
float volume = 0;
long t0 = 0;
void ISRCountPulse()
{
   pulseConter++;
}
float GetFrequency()
{
   pulseConter = 0;
   interrupts();
   delay(measureInterval);
   noInterrupts();
   return (float)pulseConter * 1000 / measureInterval;
}
void SumVolume(float dV)
{
   volume += dV / 60 * (millis() - t0) / 1000.0;
   t0 = millis();
}
void setup()
{
   Serial.begin(115200);
   attachInterrupt(digitalPinToInterrupt(sensorPin), ISRCountPulse, RISING);
   t0 = millis();
}
void loop()
{
   // obtener frecuencia en Hz
   float frequency = GetFrequency();
   // calcular caudal L/min
   float flow_Lmin = frequency / factorK;
   SumVolume(flow_Lmin);
   Serial.println(volume, 1);

}
