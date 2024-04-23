#pragma once
#include <Arduino.h>
#include <Stepper.h>
#ifndef SYNCHRO_H
#define SYNCHRO_H

class PLDStepper {
  
  private:

	int TRIG_PIN;
	long temp_step = 0;
    
  public:
  

	Stepper *TargetRotationStepper;
	Stepper *SubstrateRotationStepper;

	PLDStepper(Stepper *SubstrateRotationStepper, Stepper *TargetRotationStepper);	


	// SyncBurstMode
	long pulse_delay = 17816;//17816; // microseconds
	int AngleCount = 5;
	// int *frequencies;	
	// int *pulse_start_angles;
	// int *pulse_end_angles;
	int TriggerPulseLength = 50; // Pulse length in microseconds
	long last_pulse_time;
	long current_pulse_count = 0;
	long target_pulse_count = 0;
	float current_target_angle = 0;
	float current_substrate_angle = 0;
	int current_pulse_frequency;

	int StartAngles[5] = {0,10,170,190,350};
	int EndAngles[5] = {10,170,190,350,350};  
	int Frequencies[5] = {0,10,0,5,0};  

	//
	bool sync_rotation = false;
    int targetRotationSpeed = 0; // steps/s
	int target_transmission[2] = {1,2}; // {1,2}

    int substrateRotationSpeed = 0;	 // steps/s
	int substrate_transmission[2] = {29,4}; // {29,4}
	//
	void SetTrigPin(int pin);
	void StartPulsing(long pulses);
	void TriggerPulse();	
	void run();
	void SyncRotation(bool sync);

	void Enable();
	void Disable();

	void SetTargetSpeed(float rpm);
	void SetTargetDir(bool fwd);	
	void SetTargetTransmission(int transmission1, int transmission2);

	void SetSubstrateSpeed(float rpm);	
	void SetSubstrateDir(bool fwd);
	void SetSubstrateTransmission(int transmission1, int transmission2);	

	void SetAzimuthalBurst(int *PulseFrequencies,int *StartAngles, int *EndAngles,int AngleCount);

};
#endif