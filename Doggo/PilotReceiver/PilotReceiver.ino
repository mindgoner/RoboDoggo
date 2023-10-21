#include <SPI.h>
#include <RF24.h>

RF24 radio(9, 10);  // Inicjalizacja obiektu radio na pinach 9 (CE) i 10 (CSN)
const byte address[6] = "Node2";  // Adres odbiornika

void setup() {
  Serial.begin(115200);
  radio.begin();
  radio.openReadingPipe(1, address);
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    String receivedData = "";
    while (radio.available()) {
      char c;
      radio.read(&c, sizeof(c));
      receivedData += c;
    }
    Serial.println("Odebrano: " + receivedData);
  }
}
