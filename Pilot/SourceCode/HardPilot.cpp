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
  RF24 transmitter(9, 10);
  this->transmitter = transmitter;
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
      Serial.println(F("Transmitter hardware is not responding!"));
    }
    delay(1000); // Try again after 1 second
  }

  // Set receiver address:
  byte receiverAddress[] = "Node";
  this->receiverAddress[sizeof(receiverAddress)] = receiverAddress;
  this->transmitter.setPALevel(RF24_PA_LOW); // RF24_PA_MAX is default.
  this->transmitter.setPayloadSize(sizeof(String));
  this->transmitter.openWritingPipe(this->receiverAddress); // Open connection with transmitter

}

void HardPilot::readInput() {
  this->readingsTable["leftJoystick"]["button"] = !digitalRead(2);
  this->readingsTable["rightJoystick"]["button"] = !digitalRead(3);
  this->readingsTable["button"]["1"] = !digitalRead(4);
  this->readingsTable["button"]["2"] = !digitalRead(5);
  this->readingsTable["button"]["3"] = !digitalRead(6);
  this->readingsTable["button"]["4"] = !digitalRead(7);
  this->readingsTable["switch"]["1"] = !digitalRead(8);

  this->readingsTable["leftJoystick"]["axisX"] = analogRead(A0);
  this->readingsTable["leftJoystick"]["axisY"] = analogRead(A1);
  this->readingsTable["rightJoystick"]["axisX"] = analogRead(A2);
  this->readingsTable["rightJoystick"]["axisY"]  = analogRead(A3);
  this->readingsTable["potentiometer"]["1"]  = analogRead(A6);
  this->readingsTable["potentiometer"]["2"] = analogRead(A7);

  // Serialize data to String
  serializeJson(this->readingsTable, this->readingsJSON);

  if(this->debug){
    //Serial.println(this->readingsJSON);  
  }
  
}


void HardPilot::broadcast() {

  // Prepare data to be transmitted
  uint8_t data[this->readingsJSON.length() + 1];
  this->readingsJSON.getBytes(data, this->readingsJSON.length() + 1);

  // Write data and track the time:
  unsigned long start_timer = micros();
  bool report = this->transmitter.write(&data, sizeof(data));  // transmit & save the report
  unsigned long end_timer = micros();

 if(this->debug){
    if (report) {
      Serial.print(F("Transmission successful! "));
      Serial.print(F("Transmission time = "));
      Serial.print(end_timer - start_timer);  // Print transmitions time
      Serial.println(F(" us."));
    } else {
      Serial.println(F("Transmission failed or timed out")); // Error while broadcasting.
    }
 }
}


void HardPilot::transmit() {
  this->readInput();
  this->broadcast();
}
