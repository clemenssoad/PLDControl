
#pragma once
#include <Accelstepper.h>

#include <PLDStepper.h>
#include <TMCStepper.h>
#include <TMCStepper_UTILITY.h>
#include <Axis.h>

float steps_per_mm = 0.035369 * MICROSTEPS * MOTORSTEPS;
long steps_per_targetchanger_rotation = MICROSTEPS * MOTORSTEPS * 10;
float Target1 = 0;
float Target2 = steps_per_targetchanger_rotation * 1 / 4;
float Target3 = steps_per_targetchanger_rotation * 1 / 2;
float Target4 = steps_per_targetchanger_rotation * 0.75;
float TARGET[4] = { Target1/steps_per_mm, Target2/steps_per_mm, Target3/steps_per_mm, Target4/steps_per_mm };


int StartAngles[5] = {0,10,170,190,350};
int EndAngles[5] = {10,170,190,350,360};  
int Frequencies[5] = {0,10,0,3,0};  

int TargetIndex = 0;
bool substrate_rotation = false;
bool target_rotation = false;
bool target_wiggle = false;
bool target_ccswiggle = false;
float y_max = 0;
float t;

float target_position;
long time_step = 0;
long WigglePeriod = 11111;

//AccelStepper TargetChangeStepper(1,X_STEP_PIN,X_DIR_PIN);
//AccelStepper TargetRotationStepper(1,Y_STEP_PIN,Y_DIR_PIN);
//AccelStepper SubstrateRotationStepper(1,Z_STEP_PIN,Z_DIR_PIN);

AccelStepper XStepper(1,X_STEP_PIN,X_DIR_PIN);
Stepper YStepper(Y_STEP_PIN,Y_DIR_PIN,Y_ENABLE_PIN,MOTORSTEPS, MICROSTEPS);
Stepper ZStepper(Z_STEP_PIN,Z_DIR_PIN,Z_ENABLE_PIN,MOTORSTEPS, MICROSTEPS);
AccelStepper Z2Stepper(1,Z2_STEP_PIN,Z2_DIR_PIN);
AccelStepper E0Stepper(1,E0_STEP_PIN,E0_DIR_PIN);
AccelStepper E1Stepper(1,E1_STEP_PIN,E1_DIR_PIN);
AccelStepper E2Stepper(1,E2_STEP_PIN,E2_DIR_PIN);
AccelStepper E3Stepper(1,E3_STEP_PIN,E3_DIR_PIN);
#define DRIVER_ADDRESS 0b00
TMC2209Stepper driverX(X_SERIAL_RX_PIN, X_SERIAL_TX_PIN, .11f, DRIVER_ADDRESS ); // (RX, TX,RSENSE) Software serial X axis
TMC2209Stepper driverY(Y_SERIAL_RX_PIN, Y_SERIAL_TX_PIN, .11f, DRIVER_ADDRESS ); // (RX, TX,RSENSE) Software serial X axis
TMC2209Stepper driverZ(Z_SERIAL_RX_PIN, Z_SERIAL_TX_PIN, .11f, DRIVER_ADDRESS ); // (RX, TX,RSENSE) Software serial X axis
TMC2209Stepper driverZ2(Z2_SERIAL_RX_PIN, Z2_SERIAL_TX_PIN, .11f, DRIVER_ADDRESS ); // (RX, TX,RSENSE) Software serial X axis
TMC2209Stepper driverE0(E0_SERIAL_RX_PIN, E0_SERIAL_TX_PIN, .11f, DRIVER_ADDRESS ); // (RX, TX,RSENSE) Software serial X axis
TMC2209Stepper driverE1(E1_SERIAL_RX_PIN, E1_SERIAL_TX_PIN, .11f, DRIVER_ADDRESS ); // (RX, TX,RSENSE) Software serial X axis
TMC2209Stepper driverE2(E2_SERIAL_RX_PIN, E2_SERIAL_TX_PIN, .11f, DRIVER_ADDRESS ); // (RX, TX,RSENSE) Software serial X axis
TMC2209Stepper driverE3(E3_SERIAL_RX_PIN, E3_SERIAL_TX_PIN, .11f, DRIVER_ADDRESS ); // (RX, TX,RSENSE) Software serial X axis

// Axis SetUp
PLDStepper TargetSubstrateAxes(&YStepper,&ZStepper);

Axis Z2Axis(&Z2Stepper,&driverZ2,Z2_DIAG_PIN, 100.0,30);

Axis TargetChangeAxis(&XStepper,&driverX,X_DIAG_PIN, steps_per_mm,30);



void DRIVER_SETUP()
{
  driverX.beginSerial(115200); // X driver Coms begin
  Serial.println("Driver X Enabled\n");
  driverX.begin();
  driverX.toff(4);
  driverX.blank_time(24);
  driverX.rms_current(MOTORCURRENT); // mA
  driverX.TCOOLTHRS(0xFFFFF); // 20bit max
  driverX.semin(5);
  driverX.semax(2);
  driverX.sedn(0b01);
  driverX.SGTHRS(TargetChangeAxisStall);
  driverX.microsteps(MICROSTEPS);

  driverY.beginSerial(115200);
  driverY.begin();
  driverY.toff(4);
  driverY.blank_time(24);
  driverY.rms_current(MOTORCURRENT); // mA
  driverY.microsteps(MICROSTEPS);
  driverY.TCOOLTHRS(0xFFFFF); // 20bit max
  driverY.semin(5);
  driverY.semax(2);
  driverY.sedn(0b01);
  driverY.SGTHRS(STALL_VALUE);

  driverZ.beginSerial(115200);
  driverZ.begin();
  driverZ.toff(4);
  driverZ.blank_time(24);
  driverZ.rms_current(MOTORCURRENT); // mA
  driverZ.microsteps(MICROSTEPS);
  driverZ.TCOOLTHRS(0xFFFFF); // 20bit max
  driverZ.semin(5);
  driverZ.semax(2);
  driverZ.sedn(0b01);
  driverZ.SGTHRS(STALL_VALUE);

  driverZ2.beginSerial(115200);
  driverZ2.begin();
  driverZ2.toff(4);
  driverZ2.blank_time(24);
  driverZ2.rms_current(MOTORCURRENT); // mA
  driverZ2.microsteps(MICROSTEPS);
  driverZ2.TCOOLTHRS(0xFFFFF); // 20bit max
  driverZ2.semin(5);
  driverZ2.semax(2);
  driverZ2.sedn(0b01);
  driverZ2.SGTHRS(Z2Stall);



  driverE0.beginSerial(115200);
  driverE0.begin();
  driverE0.toff(4);
  driverE0.blank_time(24);
  driverE0.rms_current(MOTORCURRENT); // mA
  driverE0.microsteps(MICROSTEPS);
  driverE0.TCOOLTHRS(0xFFFFF); // 20bit max
  driverE0.semin(5);
  driverE0.semax(2);
  driverE0.sedn(0b01);
  driverE0.SGTHRS(STALL_VALUE);

  driverE1.beginSerial(115200);
  driverE1.begin();
  driverE1.toff(4);
  driverE1.blank_time(24);
  driverE1.rms_current(MOTORCURRENT); // mA
  driverE1.microsteps(MICROSTEPS);
  driverE1.TCOOLTHRS(0xFFFFF); // 20bit max
  driverE1.semin(5);
  driverE1.semax(2);
  driverE1.sedn(0b01);
  driverE1.SGTHRS(STALL_VALUE);

  driverE2.beginSerial(115200);
  driverE2.begin();
  driverE2.toff(4);
  driverE2.blank_time(24);
  driverE2.rms_current(MOTORCURRENT); // mA
  driverE2.microsteps(MICROSTEPS);
  driverE2.TCOOLTHRS(0xFFFFF); // 20bit max
  driverE2.semin(5);
  driverE2.semax(2);
  driverE2.sedn(0b01);
  driverE2.SGTHRS(STALL_VALUE);

  driverE3.beginSerial(115200);
  driverE3.begin();
  driverE3.toff(4);
  driverE3.blank_time(24);
  driverE3.rms_current(MOTORCURRENT); // mA
  driverE3.microsteps(MICROSTEPS);
  driverE3.TCOOLTHRS(0xFFFFF); // 20bit max
  driverE3.semin(5);
  driverE3.semax(2);
  driverE3.sedn(0b01);
  driverE3.SGTHRS(STALL_VALUE);
}





void SetUpSteppers()
{
  XStepper.setEnablePin(X_ENABLE_PIN);
  XStepper.setPinsInverted(true,false,true);
  XStepper.setAcceleration(MICROSTEPS*MOTORSTEPS);
  XStepper.setMaxSpeed(MICROSTEPS*MOTORSTEPS*1/3);
  XStepper.enableOutputs();

  E0Stepper.setEnablePin(E0_ENABLE_PIN);
  E0Stepper.setPinsInverted(false,false,true);
  E0Stepper.setAcceleration(MICROSTEPS*MOTORSTEPS);
  E0Stepper.setMaxSpeed(MICROSTEPS*MOTORSTEPS*1/2);
  E0Stepper.enableOutputs();

  Z2Stepper.setEnablePin(Z2_ENABLE_PIN);
  Z2Stepper.setPinsInverted(false,false,true);
  Z2Stepper.setAcceleration(MICROSTEPS*MOTORSTEPS*2);
  Z2Stepper.setMaxSpeed(MICROSTEPS*MOTORSTEPS*1/2);
  Z2Stepper.enableOutputs();

  int AngleCount = sizeof(StartAngles);
  TargetSubstrateAxes.SetAzimuthalBurst(Frequencies,StartAngles,EndAngles,AngleCount);
 
}


