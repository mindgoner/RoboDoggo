#ifndef HardPilot_h
#define HardPilot_h


// Include HardPilot required classes:
#include <Arduino.h>
#include <ArduinoJson.h>
// Include NRF24l01 module required classes:
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


class HardPilot {
  
  public:
    HardPilot();
    void initialize(bool enableDebug = false);
    void transmit();
  
  private:
    bool debug;
    StaticJsonDocument<200> readingsTable;
    String readingsJSON;
    RF24 transmitter;
    byte receiverAddress[];
  
    void readInput();
    void broadcast();

};

#endif
