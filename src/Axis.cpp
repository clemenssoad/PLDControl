#include <Axis.h>


Axis::Axis(AccelStepper *stepper, TMC2209Stepper *driver,int EndStopPin,float steps_per_unit,int StallValue)
{
    this->stepper = stepper;
    this->driver = driver;
    this->EndStopPin = EndStopPin;
    this->steps_per_mm = steps_per_mm;
    pinMode(EndStopPin,INPUT_PULLDOWN);
}

void Axis::run()
{
    this->stepper->run();
    this->currentPosition = (float) this->stepper->currentPosition()*1/this->steps_per_mm;
    if (this->isHoming == true)
    {
        this->stepper->move(-100);
        if (digitalRead(this->EndStopPin) == true)
        {
            this->isHoming = false;
            this->stepper->stop();
            this->stepper->setCurrentPosition(0);
            Serial.println("Homed");
        }
    }

}

void Axis::moveTo(float position)
{
    long target_step = round(position * this->steps_per_mm);
    this->stepper->moveTo(target_step);
}

void Axis::move(float distance)
{
    long steps = round(distance*this->steps_per_mm);
    this->stepper->move(steps);
}

void Axis::setCurrentPosition(float position)
{
    long steps = round(position*this->steps_per_mm);
    this->stepper->setCurrentPosition(steps);
}

void Axis::HomeAxis()
{
    this->isHoming = true;
}






