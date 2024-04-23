#pragma once
class Stepper
{
private:
    /* data */
    int StepPulseLength = 1; //microseconds
public:
    Stepper(int STEP_PIN, int DIR_PIN, int EN_PIN, int MICRO_STEPS, int MOTOR_STEPS);
    ~Stepper();
    void step();
    void toggle(bool power);
    void setDir(bool dir);
    int STEP_PIN;
    int DIR_PIN;
    int EN_PIN = -1;
    int MOTOR_STEPS;
    int MICRO_STEPS; 
    bool invert_dir = false;
    bool invert_en = false;      
    bool fwd = true;
    long last_step_time;
    long current_step;
};
