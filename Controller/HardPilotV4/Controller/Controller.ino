#include <Arduino.h>
#include "HardPilot.h"
#include <RF24.h>

// Controller
HardPilot Controller;

RF24 Transmitter(9, 10);
const byte address[6] = "00001";

void setup() {
  Serial.begin(115200);

  // Initialize controller
  Controller.initialize(true);

  // Initialize transmitter
  Transmitter.begin();
  Transmitter.openWritingPipe(address);
  Transmitter.setPALevel(RF24_PA_LOW);
  Transmitter.stopListening();
}

void loop() {
  if (Controller.reactOnChange()) {
    Transmitter.write(Controller.readings, strlen(Controller.readings));
    Serial.print("Nadawanie: ");
    Serial.print(Controller.readings);
    Serial.println();  // Dodaj nową linię dla czytelności w monitorze szeregowym
    delay(100);        // Post transmission delay
  }
}
