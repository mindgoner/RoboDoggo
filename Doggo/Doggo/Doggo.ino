#include "DoggoStepper.h"
#include <Servo.h>

// Define servos:
Servo leftFrontServo;
Servo rightFrontServo;
Servo leftBackServo;
Servo rightBackServo;

DoggoStepper leftFrontLever = DoggoStepper(22, 23, 24);
DoggoStepper rightFrontLever = DoggoStepper(25, 26, 27);
DoggoStepper leftBackLever = DoggoStepper(28, 29, 30);
DoggoStepper rightBackLever = DoggoStepper(31, 32, 33);

DoggoStepper leftFrontJoint = DoggoStepper(34, 35, 36);
DoggoStepper rightFrontJoint = DoggoStepper(37, 38, 39);
DoggoStepper leftBackJoint = DoggoStepper(40, 41, 42);
DoggoStepper rightBackJoint = DoggoStepper(43, 44, 45);

int incomingByte = 0;

void runSteppers(){
  
  // Levers:
  if (leftFrontLever.distanceToGo()) {
    leftFrontLever.run();
  } else {
    leftFrontLever.disable();
  }
  if (rightFrontLever.distanceToGo()) {
    rightFrontLever.run();
  } else {
    rightFrontLever.disable();
  }
  if (leftBackLever.distanceToGo()) {
    leftBackLever.run();
  } else {
    leftBackLever.disable();
  }
  if (rightBackLever.distanceToGo()) {
    rightBackLever.run();
  } else {
    rightBackLever.disable();
  }
  
  // Joints:
  if (leftFrontJoint.distanceToGo()) {
    leftFrontJoint.run();
  }
  if (rightFrontJoint.distanceToGo()) {
    rightFrontJoint.run();
  }
  if (leftBackJoint.distanceToGo()) {
    leftBackJoint.run();
  }
  if (rightBackJoint.distanceToGo()) {
    rightBackJoint.run();
  }
}

void setup() {
  
  // Configure servos (attach pins):
  leftFrontServo.attach(3);
  rightFrontServo.attach(4);
  leftBackServo.attach(5);
  rightBackServo.attach(6);
  // Set servos in  home  position(90deg):
  leftFrontServo.write(90);
  rightFrontServo.write(90);
  leftBackServo.write(90);
  rightBackServo.write(90);

  delay(3000);

  
  // Configure steppers:
  leftFrontLever.begin();
  rightFrontLever.begin();
  leftBackLever.begin();
  rightBackLever.begin();
  leftFrontJoint.begin();
  rightFrontJoint.begin();
  leftBackJoint.begin();
  rightBackJoint.begin();

  Serial.begin(115200);
}

void loop(){
  runSteppers();
}



/*
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
  steppers[0].moveTo(500); // z = 5000
  steppers[0].enable();
}

void loop() {
  
  steppers[0].disable();
  steppers[1].disable();
  steppers[2].disable();
  steppers[3].disable();
  steppers[4].disable();
  steppers[5].disable();
  steppers[6].disable();
  steppers[7].disable();
  
  Serial.println("TEST");

  if(steppers[0].distanceToGo() != 0){
    steppers[0].run();
  }
  


}

*/
