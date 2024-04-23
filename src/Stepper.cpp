#include <Stepper.h>
#include <Arduino.h>

Stepper::Stepper(int STEP_PIN, int DIR_PIN, int EN_PIN,int MICRO_STEPS,int MOTOR_STEPS)
{
  pinMode(STEP_PIN,OUTPUT);
  pinMode(EN_PIN,OUTPUT);
  pinMode(DIR_PIN,OUTPUT); 
  this->STEP_PIN = STEP_PIN;
  this->DIR_PIN = DIR_PIN;
  this->EN_PIN = EN_PIN; 
  this->MICRO_STEPS = MICRO_STEPS;
  this->MOTOR_STEPS = MOTOR_STEPS; 
}

void Stepper::step()
{
    digitalWrite(this->STEP_PIN,HIGH);
	delayMicroseconds(this->StepPulseLength);
	digitalWrite(this->STEP_PIN,LOW);
    if (this->fwd == true)
    {
        this->current_step++;
    }
    else
    {
        this->current_step--;
    }
    this->last_step_time = micros();
}


void Stepper::setDir(bool dir)
{
    this->fwd = dir;
    if (this->invert_dir == true)
    {
        dir = !dir;
    }
    if (dir == true)
    {
    digitalWrite(this->DIR_PIN,HIGH);    
    }
    else
    {
    digitalWrite(this->DIR_PIN,LOW);    
    }

}

void Stepper::toggle(bool power)
{
    if (this->EN_PIN == -1) // in case no en pin is defined
    {
        return;
    }
    if (this->invert_en == true)
    {
        power = !power;
    }
    if (power == true)
    {
    digitalWrite(this->EN_PIN,HIGH);    
    }
    else
    {
    digitalWrite(this->EN_PIN,LOW);    
    }
}


Stepper::~Stepper()
{
}
