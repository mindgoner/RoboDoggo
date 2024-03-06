#include <AccelStepper.h>
#include "DoggoStepper.h"

DoggoStepper::DoggoStepper(int enPin, int stepPin, int dirPin) {
  _enPin = enPin;
  _stepPin = stepPin;
  _dirPin = dirPin;
  _position = 0;
  _stepper = new AccelStepper(AccelStepper::DRIVER, _stepPin, _dirPin);
}

void DoggoStepper::begin() {
  pinMode(_enPin, OUTPUT);
  digitalWrite(_enPin, LOW); // Wyłącz silnik na starcie
  _state = true;
  _stepper->setMaxSpeed(1000); // Domyślna maksymalna prędkość
  _stepper->setAcceleration(4000); // Domyślne przyspieszenie
}

void DoggoStepper::setMaxSpeed(float speed) {
  _stepper->setMaxSpeed(speed);
}

void DoggoStepper::setAcceleration(float acceleration) {
  _stepper->setAcceleration(acceleration);
}

void DoggoStepper::moveTo(long position) {
  _stepper->moveTo(position);
  _isRunning = true;
  _position = position;
}

void DoggoStepper::run() {
  if (_isRunning) {
    _stepper->run();
    if (!_stepper->isRunning())
      _isRunning = false;
  }
}

bool DoggoStepper::disable() {
  _state = false;
  digitalWrite(_enPin, HIGH);
  return _state;
}

bool DoggoStepper::enable() {
  _state = true;
  digitalWrite(_enPin, LOW);
  return _state;
}

bool DoggoStepper::state() {
  return _state;
}

int DoggoStepper::position() {
  return _position;
}

bool DoggoStepper::isRunning() {
  return _isRunning;
}

long DoggoStepper::distanceToGo() {
  return _stepper->distanceToGo();
}
