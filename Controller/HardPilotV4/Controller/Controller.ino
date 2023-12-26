#include <Arduino.h>
#include "HardPilot.h" // Include HardPilot library (by Mindgoner)

HardPilot Controller; // Create "Controller" variable.

void setup() {
  Serial.begin(115200);
  Controller.initialize(true); // Initialize Controller
}

void loop() {
  Controller.transmitOnChange();
}



