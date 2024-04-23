

#include <configuration.h>
#include <SetUpSteppers.h>
#include <command.h>
//#include <string>  
//#include <iostream>   
//#define LED_PIN PA_13





#define sign(x) ({ decltype(x) _x = (x); _x < 0 ? -1 : _x ? 1 : 0; })


int address = 0;
int UpdateInterval = 100;


unsigned long lastmillis1 = 0;
unsigned long lastmillis2 = 0;
unsigned long lastmillis3 = 0;

long v_substrate_rotation = 0;
long v_target_rotation = 0;


int StepArray[100];
int array_index = 0;





bool cmd_done = false;
bool arg_done = false;
bool record_serial_array = false;




bool last_dir_fwd = false;

float last_saved_position;

String cmd = "";
String cmd_temp = "";
String arg = "";
String arg_temp = "";
char in_char;
int l = 0;







void setup() {
  // put your setup code here, to run once:
  //int result = myFunction(2, 3);
  
  Serial.begin(115200);
  Serial.println("Initializing");
  //Serial.println("Substrate Transmission:" + String(substrate_transmission, DEC));
  //Serial.println("Target Transmission:" + String(target_transmission, DEC));
  Serial.println("Motorsteps:" + String(MOTORSTEPS, DEC));
  Serial.println("Microsteps:" + String(MICROSTEPS, DEC));

  SetUpSteppers();

  TargetSubstrateAxes.SetTrigPin(SERVO0_PIN);
 // E0Axis.moveTo(10);

 // TargetSubstrateAxes.SetSubstrateSpeed((float)2);
 // TargetSubstrateAxes.SetTargetSpeed((float)2);  
 // TargetSubstrateAxes.SyncRotation(true);
//  Stepper.CorrectPulseAngles(100000);
  pinMode(LED_PIN,OUTPUT);
  pinMode(POWER_LOSS_PIN,OUTPUT);
 // digitalWrite(SERVO0_PIN,HIGH);
 // Serial.println("Frequencies: " + String(*(TargetSubstrateAxes.frequencies),DEC) + " " + String(*(TargetSubstrateAxes.frequencies+1),DEC) );  
//  Serial.println("AngleSet1: " + String(*(TargetSubstrateAxes.pulse_start_angles),DEC) + " " + String(*(TargetSubstrateAxes.pulse_end_angles),DEC) + " AngleSet2: " +String(*(TargetSubstrateAxes.pulse_start_angles+1),DEC) +" " +  (String(*(TargetSubstrateAxes.pulse_end_angles+1),DEC)));  
  #ifndef NODRIVERS
    DRIVER_SETUP();
  #endif
  delay(1000);

}

void loop() {

 while (Serial.available()) {
    in_char = Serial.read();
    // if (record_serial_array != true)
    // {
   // if (int(in_char) != '-') {
          if (!cmd_done) {
            cmd_temp += in_char;
            l = l + 1;
            if (in_char == ' ') {
              //    Serial.println("Command entered: ");
              cmd = cmd_temp.substring(0, l - 1);
              //     Serial.println(cmd);
              cmd_done = true;
              cmd_temp = "";
              l = 0;
            }
          } 
          else {
            arg_temp += in_char;
            l = l + 1;
            if (in_char == '\n') {
              //      Serial.println("Argument entered: ");
              //    Serial.println(arg_temp);
              arg = arg_temp;
              arg_temp = "";
              l = 0;
              Command(cmd, arg);
              cmd_done = false;
            }
          }
        }
   
  
   in_char = 'X';
   TargetSubstrateAxes.run();
   Z2Axis.run();
   TargetChangeAxis.run();
   if (millis() - lastmillis1 > 100) {
    lastmillis1 = millis();
    Serial.println("Z2:" + String(Z2Axis.currentPosition,DEC) + " X: " + String(TargetChangeAxis.currentPosition,DEC));
   }


}
// }

extern "C" void SystemClock_Config(void)
{
#ifdef OCTOPUS_BOARD
#ifdef OCTOPUS_BOARD_FROM_HSI
  /* boot from HSI, internal 16MHz RC, to 168MHz. **NO USB POSSIBLE**, needs HSE! */
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  RCC_OscInitStruct.PLL.PLLR = 3;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
#else
  /* boot from HSE, crystal oscillator (12MHz) */
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 6;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  RCC_OscInitStruct.PLL.PLLR = 3;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_CLK48;
  PeriphClkInitStruct.Clk48ClockSelection = RCC_CLK48CLKSOURCE_PLLQ;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
#endif
#else
  /* nucleo board, 8MHz external clock input, HSE in bypass mode */
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_CLK48;
  PeriphClkInitStruct.Clk48ClockSelection = RCC_CLK48CLKSOURCE_PLLQ;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
#endif
}
