// Include HardPilot required classes:
#include "HardPilot.h"
#include <ArduinoJson.h>

// Include NRF24l01 module required classes:
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

HardPilot::HardPilot() {
  
  // Debug is disabled by default
  this->debug = false;
  
  // Readings and JSON variables 
  StaticJsonDocument<200> readingsTable;
  this->readingsTable = readingsTable;
  String readingsJSON = "";

  // Transmitter module variables
  RF24 transmitter(9,10);
  this->transmitter = transmitter;
  const uint64_t transmitterPipe=0xDEADBEEF01;
}

void HardPilot::initialize(bool debug = false) {
  // Set debug to false by default
  this->debug = debug;

  // Define pin modes:
  pinMode(2, INPUT_PULLUP); // Left Joystick Button
  pinMode(3, INPUT_PULLUP); // Right Joystick Button
  pinMode(4, INPUT_PULLUP); // Button 1
  pinMode(5, INPUT_PULLUP); // Button 2
  pinMode(6, INPUT_PULLUP); // Button 3
  pinMode(7, INPUT_PULLUP); // Button 4
  pinMode(8, INPUT_PULLUP); // Switch 1 

  // Initialize transmitter (loop until connected successfully)
  while(!this->transmitter.begin()){ 
    if(this->debug){   
      Serial.println("Transmitter hardware is not responding!");
    }
    delay(1000); // Try again after 1 second
  }

  this->configureTransmitterDefaultValues();

}


int HardPilot::digitalizeAnalogInput(int analogInput){
  if(analogInput < 400){
    return -1;
  }else if(analogInput > 600){
    return 1;
  }else{
    return 0;  
  }
}


void HardPilot::configureTransmitterDefaultValues() {
  this->transmitter.setPALevel(RF24_PA_LOW);  // RF24_PA_MAX is default.
  this->transmitter.openWritingPipe(this->transmitterPipe);
  this->transmitter.setPayloadSize(sizeof(String));
  this->transmitter.setAutoAck(false);
  this->transmitter.setDataRate(RF24_250KBPS);
  //this->transmitter.printDetails();
  this->transmitter.stopListening();
}

void HardPilot::readInput() {

  this->readingsJSON = "";
  
  this->readingsTable["leftJoystick"]["button"] = !digitalRead(2);
  this->readingsTable["rightJoystick"]["button"] = !digitalRead(3);
  this->readingsTable["button"]["1"] = !digitalRead(4);
  this->readingsTable["button"]["2"] = !digitalRead(5);
  this->readingsTable["button"]["3"] = !digitalRead(6);
  this->readingsTable["button"]["4"] = !digitalRead(7);
  this->readingsTable["switch"]["1"] = !digitalRead(8);

  this->readingsTable["leftJoystick"]["axisX"] = this->digitalizeAnalogInput(analogRead(A0));
  this->readingsTable["leftJoystick"]["axisY"] = this->digitalizeAnalogInput(analogRead(A1));
  this->readingsTable["rightJoystick"]["axisX"] = this->digitalizeAnalogInput(analogRead(A2));
  this->readingsTable["rightJoystick"]["axisY"]  = this->digitalizeAnalogInput(analogRead(A3));
  this->readingsTable["potentiometer"]["1"]  = (int) analogRead(A6)/100;
  this->readingsTable["potentiometer"]["2"] = (int) analogRead(A7)/100;

  // Serialize data to String
  serializeJson(this->readingsTable, this->readingsJSON);

  if(this->debug){
    //Serial.println(this->readingsJSON);  
  }
  
}


void HardPilot::broadcast() {
  
  this->configureTransmitterDefaultValues();

  // Write data and track the time:
  unsigned long start_timer = micros();
  bool report = this->transmitter.write(this->readingsJSON.c_str(), (this->readingsJSON.length() + 1) );  // +1 na znak null
  unsigned long end_timer = micros();

 if(this->debug){
    if (report) {
      //Serial.print("Transmission successful! Transmission time = ");
      //Serial.print(end_timer - start_timer);  // Print transmitions time
      //Serial.println(" us.");
      Serial.println(this->readingsJSON);
    } else {
      Serial.println("Transmission failed or timed out"); // Error while broadcasting.
    }
 }
}


void HardPilot::transmit(int transmissionDelay = 250) {
  if(this->debug){
    if(!this->transmitter.isChipConnected()){ // Check whether transmitter is connected
      Serial.println("Transmitter is not connected!");
    }
    this->broadcast();
  delay(transmissionDelay);
}

void HardPilot::transmitOnChange(int postTransmissionDelay = 100) {
  this->previousReadingsJSON = this->readingsJSON;
  this->readInput();
  if(this->previousReadingsJSON != this->readingsJSON){
    
    if(this->debug && !this->transmitter.isChipConnected()){
        Serial.println("Transmitter is not connected!");
    }

    // Broadcast values.
    this->broadcast();
    delay(postTransmissionDelay);
  }
}

