#include "DoggoStepper.h"

DoggoStepper steppers[] = {
  DoggoStepper(22, 23, 24),
  DoggoStepper(25, 26, 27),
  DoggoStepper(28, 29, 30),
  DoggoStepper(31, 32, 33),
  DoggoStepper(34, 35, 36),
  DoggoStepper(37, 38, 39),
  DoggoStepper(40, 41, 42),
  DoggoStepper(43, 44, 45)
};

void setup() {
  Serial.begin(115200);
  steppers[0].disable();
  steppers[1].disable();
  steppers[2].disable();
  steppers[3].disable();
  steppers[4].disable();
  steppers[5].disable();
  steppers[6].disable();
  steppers[7].disable();

  
  steppers[0].setMaxSpeed(1000); // x = 1000
  steppers[0].setAcceleration(4000); // y = 4000
  steppers[0].moveTo(5000); // z = 5000
  steppers[0].enable();
}

void loop() {
  Serial.println("TEST");
  steppers[0].disable();
  steppers[1].disable();
  steppers[2].disable();
  steppers[3].disable();
  steppers[4].disable();
  steppers[5].disable();
  steppers[6].disable();
  steppers[7].disable();

  if(steppers[0].distanceToGo() != 0){
    steppers[0].run();
  }

}
