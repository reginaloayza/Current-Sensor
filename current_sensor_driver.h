/*
  Reads the sensor at integrals of power line frequency
  to smooth output values.
  Hardware: Modern Device Current Sensor Output on pin A0
  Arduino ground Modern Device Current Sensor ground
  Arduino +5V to Modern Device Current Sensor +5 volts
*/

const unsigned long PowerLineIntegralDelayMS = (4 * 1000/60);

float get_voltage()
{
  float total = 0;
  long reads = 0;  // just to monitor performance
  
  // read four power cycles
  unsigned long start = millis();
  while  (millis() - start < PowerLineIntegralDelayMS) {
    total = total + analogRead(A0);
    reads++;
    delayMicroseconds(100);
  }

  total = total / reads;
  float voltage = total * 5.0 / 1024.0;
  return voltage;
}
