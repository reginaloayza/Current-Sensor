#include "sma_filter.h"
#define ACS712 A0

float vpp = 0.0048828125;
float sensitivity = 0.066;

float get_current() {
  int counts = analogRead(ACS712) + 1;
  float voltage = counts * vpp;
  voltage -= 2.5;
  return voltage / sensitivity;
}

void send_message_to_raspberry_pi(const int n)
{
  Serial.print("Cycle completed: ");
  Serial.println(n);
}

SMA_Filter current_filter(5);

const float CURRENT_THRESHOLD = 0.1; // amps
const int LOW_CURRENT = 0;
const int HIGH_CURRENT = 1;
int state;
int cycle_count = 0;

void setup() {
  pinMode(ACS712, INPUT);
  Serial.begin(9600);
  state = LOW_CURRENT;
}

void loop() {
  float raw_current = get_current();
  float filtered_current = current_filter(raw_current);

  if (state == LOW_CURRENT && filtered_current > CURRENT_THRESHOLD)
    state = HIGH_CURRENT;

  else if (state == HIGH_CURRENT && filtered_current < CURRENT_THRESHOLD)
  {
    state = LOW_CURRENT;
    cycle_count++;
    send_message_to_raspberry_pi(cycle_count);
  }
  
  Serial.println("Amps: " + String(filtered_current));
  delay(500);
}
