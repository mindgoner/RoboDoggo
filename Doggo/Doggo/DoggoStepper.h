#ifndef DoggoStepper_h
#define DoggoStepper_h

#include <Arduino.h>
#include <AccelStepper.h>

class DoggoStepper {
  public:
    DoggoStepper(int stepPin, int dirPin, int enPin);
    void begin();
    void setMaxSpeed(float speed);
    void setAcceleration(float acceleration);
    void moveTo(long position);
    void run();
    bool disable();
    bool enable();
    bool state();
    int position();
    bool isRunning();
    long distanceToGo();

  private:
    int _stepPin;
    int _dirPin;
    int _enPin;
    int _position;
    bool _state;
    AccelStepper* _stepper;
    bool _isRunning = false;
};

#endif
