
//#define OCTOPUS_BOARD_FROM_HSI 1
//#define RAMPS 1
//#define ESP 1
// Board Pins
//#ifndef OCTPOPUS_BOARD
#include "pins_BTT_OCTOPUS_V1_common.h"
//#endif
// #ifndef RAMPS
//     #include "pins_RAMPS.h"
// #endif
// #ifndef ESP
//     #include "pins_ESP32CNCShield.h"
// #endif

//
//
#define MOTORSTEPS 200
#define RPM 60
#define MICROSTEPS 32
#define STALL_VALUE 25  // [0..255]
#define MOTORCURRENT 2000


#define TargetChangeAxisStall 50
#define Z2Stall 27


// F-Chamber
// float steps_per_mm = 0.035369 * MICROSTEPS * MOTORSTEPS;
// long steps_per_targetchanger_rotation = MICROSTEPS * MOTORSTEPS * 10;
// float Target1 = 0;
// float Target2 = steps_per_targetchanger_rotation * 1 / 4;
// float Target3 = steps_per_targetchanger_rotation * 1 / 2;
// float Target4 = steps_per_targetchanger_rotation * 0.75;
// float TARGET[4] = { Target1/steps_per_mm, Target2/steps_per_mm, Target3/steps_per_mm, Target4/steps_per_mm };

//A-Chamber
float steps_per_mm = 0.020873 * MICROSTEPS * MOTORSTEPS;
float shield_steps_per_mm = MICROSTEPS * MOTORSTEPS*1/1.27;
long steps_per_targetchanger_rotation = MICROSTEPS * MOTORSTEPS * 4;
float Target1 = 0;
float Target2 = steps_per_targetchanger_rotation * (float) 1/3;
float Target3 = steps_per_targetchanger_rotation * (float) 2/3;
// float Target4 = steps_per_targetchanger_rotation * 0.75;
float TARGET[3] = { Target1/steps_per_mm, Target2/steps_per_mm, Target3/steps_per_mm};