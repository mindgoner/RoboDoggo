#include "HardPilot.h"

HardPilot::HardPilot() {
  this->debug = false;
}

void HardPilot::initialize(bool debug = false) {
  this->debug = debug;
  this->readings[0] = '\0';
  this->previousReadings[0] = '\0';
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  if(this->debug){
    Serial.begin(115200);
  }
}


int HardPilot::digitalizeAnalogInput(int analogInput){
  if(analogInput < 400){
    return 4;
  }else if(analogInput > 600){
    return 6;
  }else{
    return 5;  
  }
}


void HardPilot::readInput() {
  char concatenatedData[16];
  concatenatedData[0] = '\0';
  char temp[5];
  itoa(!digitalRead(2), temp, 10);
  strcat(concatenatedData, temp);
  itoa(!digitalRead(3), temp, 10);
  strcat(concatenatedData, temp);
  itoa(!digitalRead(4), temp, 10);
  strcat(concatenatedData, temp);
  itoa(!digitalRead(5), temp, 10);
  strcat(concatenatedData, temp);
  itoa(!digitalRead(6), temp, 10);
  strcat(concatenatedData, temp);
  itoa(!digitalRead(7), temp, 10);
  strcat(concatenatedData, temp);
  itoa(!digitalRead(8), temp, 10);
  strcat(concatenatedData, temp);
  itoa(this->digitalizeAnalogInput(analogRead(A0)), temp, 10);
  strcat(concatenatedData, temp);
  itoa(this->digitalizeAnalogInput(analogRead(A1)), temp, 10);
  strcat(concatenatedData, temp);
  itoa(this->digitalizeAnalogInput(analogRead(A2)), temp, 10);
  strcat(concatenatedData, temp);
  itoa(this->digitalizeAnalogInput(analogRead(A3)), temp, 10);
  strcat(concatenatedData, temp);
  strcpy(this->readings, concatenatedData);
}


bool HardPilot::reactOnChange() {
  strcpy(this->previousReadings, this->readings);
  this->readInput();
  if(strcmp(this->readings, this->previousReadings) != 0){
    if(this->debug){
      Serial.print("Difference: [");
      Serial.print(this->previousReadings);
      Serial.print("] ===> [");
      Serial.print(this->readings);
      Serial.println("]");
    }
    return true;
  }else{
    return false;
  }
}
