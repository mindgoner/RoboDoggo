#include "DoggoStepper.h"

DoggoStepper silnikA = DoggoStepper(28, 29, 30);
DoggoStepper silnikB = DoggoStepper(25, 26, 27);
DoggoStepper silnikC = DoggoStepper(22, 23, 24);
DoggoStepper silnikD = DoggoStepper(31, 32, 33);
DoggoStepper silnikE = DoggoStepper(34, 35, 36);
DoggoStepper silnikF = DoggoStepper(37, 38, 39);
DoggoStepper silnikG = DoggoStepper(40, 41, 42);
DoggoStepper silnikH = DoggoStepper(43, 44, 45);

int incomingByte = 0;

void setup() {
  silnikA.begin();
  silnikA.disable();
  silnikB.begin();
  silnikB.disable();
  silnikC.begin();
  silnikC.disable();
  silnikD.begin();
  silnikD.disable();
  silnikE.begin();
  silnikE.disable();
  silnikF.begin();
  silnikF.disable();
  silnikG.begin();
  silnikG.disable();
  silnikH.begin();
  silnikH.disable();

  silnikA.enable();
  silnikA.setMaxSpeed(800);
  silnikA.setAcceleration(4000);

  Serial.begin(115200);
}

void loop() {
   if (Serial.available() > 0) {
    incomingByte = Serial.read();

    if(incomingByte == 49){
      Serial.print("Moving from ");
      Serial.print(silnikA.position());
      Serial.print(" adding 400 to position ");
      Serial.print(silnikA.position()+400);
      Serial.print(" distanceToGo: ");
      
      silnikA.moveTo(silnikA.position()+400);
      Serial.println(silnikA.distanceToGo());
      silnikA.enable();
    }else if(incomingByte == 50){  
      Serial.print("Moving from ");
      Serial.print(silnikA.position());
      Serial.print(" deduct 400 to position ");
      Serial.print(silnikA.position()-400);
      Serial.print(" distanceToGo: ");
      
      silnikA.moveTo(silnikA.position()-400);
      Serial.println(silnikA.distanceToGo());
      silnikA.enable();
    }
  }

  // Sprawdź czy silnik A jest w ruchu
  if (silnikA.distanceToGo()) {
    silnikA.run();
  } else {
    silnikA.disable(); // Wyłącz silnik A gdy osiągnie cel
  }
}
