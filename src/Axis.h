#pragma once

#include <Arduino.h>
#include <AccelStepper.h>
#include <TMCStepper.h>

class Axis
{
private:
    bool isHoming = false;

public:
//Properties
    AccelStepper *stepper;
    TMC2209Stepper *driver;
// Methods
    Axis(AccelStepper *stepper, TMC2209Stepper *driver,int EndStopPin,float steps_per_unit,int StallValue);
    void run();
    void moveTo(float position);
    void move(float distance);
    void HomeAxis();
    void ISR();
    void attachInterrupt();
    void detachInterrupt();
    void setCurrentPosition(float position);
    int EndStopPin;

//  
    float steps_per_mm = 100;
    float currentPosition = 0;
};


