#include "fsm.h"
#include "sma_filter.h"
#include "current_sensor_driver.h"

const float THRESHOLD = 2.5; // in volts (this is the threshold for the cycle detection)
int cycle_count = 0;
SMA_Filter sma_filter(5); // The argument is the lookback_period
FSM fsm(0, THRESHOLD);

void send_message_to_raspberry_pi(const int n) {
  Serial.print("Cycle completed: ");
  Serial.println(n);
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  float raw_signal = get_voltage();
  float filtered_signal = sma_filter(raw_signal);

  if (fsm(filtered_signal)) {
    cycle_count++;
    send_message_to_raspberry_pi(cycle_count);
  }
}
