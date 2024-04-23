#include "PLDStepper.h"

PLDStepper::PLDStepper(Stepper *SubstrateRotationStepper, Stepper *TargetRotationStepper)
{
  this->SubstrateRotationStepper = SubstrateRotationStepper;
  this->TargetRotationStepper = TargetRotationStepper;
}


void PLDStepper::SetTrigPin(int pin)
{
	pinMode(this->TRIG_PIN,OUTPUT);
	this->TRIG_PIN = pin;
}

void PLDStepper::SetAzimuthalBurst(int *Frequencies, int *StartAngles, int *EndAngles,  int AngleCount)
{
	// this->AngleCount = AngleCount;
	// for (int i = 0; i < this->AngleCount; i++) 
	// {
	// 	this->Frequencies[i] = *(Frequencies+i);		
	// 	this->StartAngles[i] = *(StartAngles+i);
	// 	this->EndAngles[i] = *(EndAngles+i);
	// }
	// Serial.println("Set azimuthal Burst");

}


void PLDStepper::TriggerPulse()
{
   digitalWrite(this->TRIG_PIN,HIGH);
   delayMicroseconds(this->TriggerPulseLength);
   digitalWrite(this->TRIG_PIN,LOW);
   this->current_pulse_count++;
}




void PLDStepper::run()
{	
		long time = micros();
	// Calculate Target Stepping
	if ((time - this->TargetRotationStepper->last_step_time)*this->targetRotationSpeed > 1000000)
	{
			this->TargetRotationStepper->step();
	}
	// Calculate Substrate Stepping
	if (this->sync_rotation == false)
	{
		if ((time - this->SubstrateRotationStepper->last_step_time)*this->substrateRotationSpeed > 1000000)
		{
			this->SubstrateRotationStepper->step();
		}
	}
	else  // Calculate Substrate Stepping Sync Case
	{
		if ((time - this->SubstrateRotationStepper->last_step_time)*this->substrateRotationSpeed*2 > 1000000) // Define max speed for sync stepping
		{
		if (this->current_substrate_angle < this->current_target_angle  || (this->current_substrate_angle - this->current_target_angle) > 350 )
			{
			this->SubstrateRotationStepper->step();
			}
		}

	}
	// Burst Pulsing Calculation -> Calculate frequency target
	long steps_per_target_round = this->TargetRotationStepper->MICRO_STEPS * TargetRotationStepper->MOTOR_STEPS * this->target_transmission[0] / this->target_transmission[1];
	this->current_target_angle = (float)(this->TargetRotationStepper->current_step % steps_per_target_round)/steps_per_target_round * 360;

	long steps_per_substrate_round = this->SubstrateRotationStepper->MICRO_STEPS * SubstrateRotationStepper->MOTOR_STEPS * this->substrate_transmission[0] / this->substrate_transmission[1];
	this->current_substrate_angle = (float)(this->SubstrateRotationStepper->current_step % steps_per_substrate_round)/steps_per_substrate_round * 360;
	this->current_pulse_frequency = 0;
	float angle_shift = (float) this->pulse_delay/(1000000) * this->targetRotationSpeed/steps_per_target_round*360;
    int j = 0;
	for (int i = 0; i < this->AngleCount; i++) 
	{
		if (round(this->current_target_angle-angle_shift) > (this->StartAngles[i])  &&  round(this->current_target_angle-angle_shift) < this->EndAngles[i])
		{
			j = i;
		}
    }
	this->current_pulse_frequency = this->Frequencies[j];
	// Trigger laser pulse if due
	if (current_pulse_count < target_pulse_count)
	{
		if ((time - this->last_pulse_time) * this->current_pulse_frequency > 1000000)
		{
			this->TriggerPulse();
			last_pulse_time = time;
		}
	}
}


void PLDStepper::SetSubstrateTransmission(int transmission1, int transmission2)
{
	this->substrate_transmission[0] = transmission1;
	this->substrate_transmission[1] = transmission2;
}

void PLDStepper::SetTargetTransmission(int transmission1, int transmission2)
{
	this->target_transmission[0] = transmission1;
	this->target_transmission[1] = transmission2;
}

void PLDStepper::SetTargetSpeed(float rpm)
{
	long steps_per_round = this->TargetRotationStepper->MICRO_STEPS * TargetRotationStepper->MOTOR_STEPS * this->target_transmission[0] / this->target_transmission[1];
	this->targetRotationSpeed = round(rpm/60*steps_per_round);
}

void PLDStepper::SetSubstrateSpeed(float rpm)
{
	long steps_per_round = this->SubstrateRotationStepper->MICRO_STEPS * SubstrateRotationStepper->MOTOR_STEPS * this->substrate_transmission[0] / this->substrate_transmission[1];

	this->substrateRotationSpeed = round(rpm/60*steps_per_round);
}

void PLDStepper::SetSubstrateDir(bool fwd)
{
	this->SubstrateRotationStepper->fwd = fwd;
}

void PLDStepper::SetTargetDir(bool fwd)
{
	this->TargetRotationStepper->fwd = fwd;
}

void PLDStepper::StartPulsing(long pulse_target)
{
	this->current_pulse_count = 0;
	this->target_pulse_count = pulse_target;
}

void PLDStepper::SyncRotation(bool sync)
{
	this->sync_rotation = sync;
}