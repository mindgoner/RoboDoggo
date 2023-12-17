#include <Arduino.h>
#include "HardPilot.h" // Include HardPilot library (by Mindgoner)

HardPilot Pilot; // Create "Pilot" variable.

void setup() {
  Serial.begin(115200);
  Pilot.initialize(true); // Initialize Pilot
}

void loop() {
  Pilot.transmitOnChange();
}
