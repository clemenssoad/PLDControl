
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
#define MICROSTEPS 64
#define STALL_VALUE 27  // [0..255]
#define MOTORCURRENT 2000


#define TargetChangeAxisStall 27
#define Z2Stall 27