#include "DoggoStepper.h"
#include <Servo.h>
#include <SPI.h>
#include <RF24.h>

RF24 Receiver(11, 12);  // Inicjalizacja obiektu radio na pinach 9 (CE) i 10 (CSN)
const byte address[6] = "00001";  // Adres odbiornika

// Serial only
int incomingByte = 0;

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

DoggoStepper* currentStepper;
int currentStepperInt = 1;


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

void switchStepperFunc(char znak){
  if(znak == '-'){
    currentStepperInt -= 1;
    if(currentStepperInt < 0){
      currentStepperInt = 7;
    }
  }else if(znak == '+'){
      currentStepperInt += 1;
      if(currentStepperInt > 7){
        currentStepperInt = 0;
      }
  }

  switch(currentStepperInt){
    case(0):
        Serial.println("Wybrales silnik lewy przedni dzwignia");
        currentStepper = &leftFrontLever;
        break;
    case(1):
        Serial.println("Wybrales silnik prawy przedni dzwignia");
        currentStepper = &rightFrontLever;
        break;
    case(2):
        Serial.println("Wybrales silnik lewy tylny dzwignia");
        currentStepper = &leftBackLever;
        break;
    case(3):
        Serial.println("Wybrales silnik prawy tylny dzwignia");
        currentStepper = &rightBackLever;
        break;
    case(4):
        Serial.println("Wybrales silnik lewy przedni joint");
        currentStepper = &leftFrontJoint;
        break;
    case(5):
        Serial.println("Wybrales silnik prawy przedni joint");
        currentStepper = &rightFrontJoint;
        break;
    case(6):
        Serial.println("Wybrales silnik lewy tylny joint");
        currentStepper = &leftBackJoint;
        break;
    case(7):
        Serial.println("Wybrales silnik prawy tylny joint");
        currentStepper = &rightBackJoint;
        break;
  }
}

void setup() {
  Serial.begin(115200);
  
  // Configure steppers:
  leftFrontLever.begin();
  rightFrontLever.begin();
  leftBackLever.begin();
  rightBackLever.begin();
  leftFrontJoint.begin();
  rightFrontJoint.begin();
  leftBackJoint.begin();
  rightBackJoint.begin();
  
  Receiver.begin();
  Receiver.openReadingPipe(1, address);
  Receiver.startListening();
  switchStepperFunc('-');
}

void loop(){
  runSteppers();

   if (Receiver.available()) {
    char receivedMessage[12] = {0}; // Przyjmij ciąg o długości 11 + znak końca null
    Receiver.read(receivedMessage, sizeof(receivedMessage));
    Serial.print("Odebrano: ");
    Serial.println(receivedMessage);
  }

  // Wait for serial
   if (Serial.available() > 0) {
    incomingByte = Serial.read();

    if(incomingByte == 49){
      // Jeżeli serial  monitor odebrał 1:
    
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

      leftFrontJoint.enable();
      rightFrontJoint.enable();
      leftBackJoint.enable();
      rightBackJoint.enable();
      
      rightFrontLever.moveTo(rightFrontLever.position()-300);
      leftFrontLever.moveTo(leftFrontLever.position()-300);
      rightBackLever.moveTo(rightBackLever.position()-300);
      leftBackLever.moveTo(leftBackLever.position()-300);

      Serial.println(rightFrontLever.position());
      
    }else if(incomingByte == 50){  
      // Jeżeli serial  monitor odebrał 2:
      leftFrontServo.detach();
      rightFrontServo.detach();
      leftBackServo.detach();
      rightBackServo.detach();
      rightFrontLever.disable();
      leftFrontLever.disable();
      rightBackLever.disable();
      leftBackLever.disable();
      
      leftFrontJoint.disable();
      rightFrontJoint.disable();
      leftBackJoint.disable();
      rightBackJoint.disable();
    }else if(incomingByte == 51){
      // Jeżeli serial  monitor odebrał 3:
    
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

      leftFrontJoint.enable();
      rightFrontJoint.enable();
      leftBackJoint.enable();
      rightBackJoint.enable();
      
      rightFrontLever.moveTo(rightFrontLever.position()+300);
      leftFrontLever.moveTo(leftFrontLever.position()+300);
      rightBackLever.moveTo(rightBackLever.position()+300);
      leftBackLever.moveTo(leftBackLever.position()+300);

      Serial.println(rightFrontLever.position());
    }else if(incomingByte == 52){
      // Wciśnięto 4'ke
      switchStepperFunc('+');
    }else if(incomingByte == 53){
      // Wciśnięto 5'ke
      switchStepperFunc('-');
    }else if(incomingByte == 54){
      // Wciśnięto 6'ke
      currentStepper->moveTo(currentStepper->position()+50);
    }else if(incomingByte == 55){
      // Wciśnięto 7'ke
      currentStepper->moveTo(currentStepper->position()+200);
    }else if(incomingByte == 56){
      // Wciśnięto 8'ke
      currentStepper->moveTo(currentStepper->position()-50);
    }else if(incomingByte == 57){
      // Wciśnięto 9'ke
      currentStepper->moveTo(currentStepper->position()-200);
    }else if(incomingByte == 48){
      // Wciśnięto 0'ro
        leftFrontServo.attach(3);
      rightFrontServo.attach(4);
      leftBackServo.attach(5);
      rightBackServo.attach(6);
      
      leftFrontServo.write(70);
      leftBackServo.write(110);
      rightFrontServo.write(110);
      rightBackServo.write(70);
    }
  }

  
}
