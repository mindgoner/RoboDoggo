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
    bool debug;
    StaticJsonDocument<200> readingsTable;
    String readingsJSON;
    String previousReadingsJSON;
    RF24 transmitter;
    const uint64_t transmitterPipe;
    
    HardPilot();
    void initialize(bool enableDebug = false);
    void transmit(int transmissionDelay = 250);
    void transmitOnChange(int postTransmissionDelay = 100);
    void readInput();
    void broadcast();
    void configureTransmitterDefaultValues();

    int digitalizeAnalogInput(int analogInput);

};

#endif
