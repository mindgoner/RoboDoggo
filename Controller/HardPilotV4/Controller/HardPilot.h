#ifndef HardPilot_h
#define HardPilot_h
#include <Arduino.h>

class HardPilot {
  
  public:
    bool debug;
    char readings[16], previousReadings[16];
    
    HardPilot();
    void initialize(bool enableDebug = false);
    bool reactOnChange();
    void readInput();

    int digitalizeAnalogInput(int analogInput);

};

#endif
