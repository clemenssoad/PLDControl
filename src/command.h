#include <String>
void Command(String command, String argument, String argument2) {
  
  //  Serial.println("command = " + command);  
  //  Serial.println("argument1 = " + argument);  
  //   Serial.println("argument2 = " + argument2);    
  if (command == "SETTARGET") {
    TargetIndex = argument.toInt() - 1;
    TargetChangeAxis.moveTo(TARGET[TargetIndex] + y_max);
    Serial.println("o");
    return;
  }


  if (command == "SETPOS") {
    TargetChangeAxis.setCurrentPosition(argument.toInt());
    return;
  }
  if (command == "SETCURRENTTARGET") {
    TargetIndex = argument.toInt() - 1;
    TargetChangeAxis.setCurrentPosition(TARGET[TargetIndex]);
    Serial.println("o");
    return;
  }

  if (command == "FULLROTATION")
  {
    TargetChangeAxis.moveTo(steps_per_targetchanger_rotation/steps_per_mm);
    Serial.println("o");
  }

  if (command == "GETSTATE") {
    float y = float(TargetChangeAxis.currentPosition - TARGET[TargetIndex]);
    int target = 0;
    if (abs(y) <= y_max*1.1) 
    {
      target = TargetIndex + 1;
    }
    Serial.print("STATE:" + String(target, DEC) + ",");
    Serial.print(y, 3);
    Serial.print(",");
    Serial.print(M1Axis.currentPosition, 3);
    Serial.print(",");
    Serial.print(M2Axis.currentPosition, 3);
    Serial.print(",");
    Serial.println(M3Axis.currentPosition, 3);
    return;
  }

  if (command == "INIT") {
    Serial.println("o");
    return;
  }

  if (command == "SETYMAX") {
    Serial.flush();
    y_max = argument.toFloat();
    Serial.println("o");
    TargetChangeAxis.moveTo(round(TARGET[TargetIndex] + y_max ));
    return;
  }

  if (command == "SETPWM") {
    Serial.flush();
    int pwm = round(argument.toFloat() * 255);
    Serial.println("o");
   // analogWrite(PWMPIN, pwm);


    return;
  }

  if (command == "SETTCSTALL")
  {
    Serial.flush();
    float stall = argument.toInt();
    driverX.SGTHRS(stall);
    Serial.println("o");   
  }

  if (command == "MOVETO") {
    Serial.flush();
    float distance = argument.toFloat();
    if (argument2.toInt() == 0)
    {
      TargetChangeAxis.moveTo(distance);
    }
    if (argument2.toInt() == 1)
    {
      M1Axis.moveTo(distance);
    }
    if (argument2.toInt() == 2)
    {
      M2Axis.moveTo(distance);
    }
    if (argument2.toInt() == 3)
    {
      M3Axis.moveTo(distance);
    }
    Serial.println("o");
    return;
  }

  if (command == "MOVE") {
    Serial.flush();
    float distance = argument.toFloat();
    if (argument2.toInt() == 0)
    {
      TargetChangeAxis.move(distance);
    }
    if (argument2.toInt() == 1)
    {
      M1Axis.move(distance);
    }
    if (argument2.toInt() == 2)
    {
      M2Axis.move(distance);
    }
    if (argument2.toInt() == 3)
    {
      M3Axis.move(distance);
    }
    Serial.println("o");
    return;
  }

  if (command == "SETACCELERATION") {
    Serial.flush();
    float a = argument.toFloat();
    if (argument2.toInt() == 0)
    {
      TargetChangeAxis.setAcceleration(a);
    }
    if (argument2.toInt() == 1)
    {
      M1Axis.setAcceleration(a);
    }
    if (argument2.toInt() == 2)
    {
      M2Axis.setAcceleration(a);
    }
    if (argument2.toInt() == 3)
    {
      M3Axis.setAcceleration(a);
    }
    Serial.println("o");
    return;
  }  
  if (command == "SETMAXSPEED") {
    Serial.flush();
    float v = argument.toFloat();
    if (argument2.toInt() == 0)
    {
      TargetChangeAxis.setMaxSpeed(v);
    }
    if (argument2.toInt() == 1)
    {
      M1Axis.setMaxSpeed(v);
    }
    if (argument2.toInt() == 2)
    {
      M2Axis.setMaxSpeed(v);
    }
    if (argument2.toInt() == 3)
    {
      M3Axis.setMaxSpeed(v);
    }
    Serial.println("o");
    return;
  }  

   if (command == "HOMETC") {
    Serial.flush();
    TargetChangeAxis.HomeAxis();
    Serial.println("o");
    return;
  } 

  // if (command == "MOVEZ2") {
  //   Serial.flush();
  //   float distance = argument.toFloat();
  //   Z2Axis.move(distance);
  //   Serial.println("o");
  //   return;
  // }

  // if (command == "HOMEZ2") {
  //   Serial.flush();
  //   Z2Axis.HomeAxis();
  //   Serial.println("o");
  //   return;
  // }


  if (command == "SETWIGGLEPERIOD") {
    Serial.flush();
    WigglePeriod = argument.toInt();
    Serial.println("o");
    //  Serial.println("acceleration = " + String(accel,DEC) + " steps/s^2");
    return;
  }

  if (command == "WIGGLE") {
    Serial.flush();
    // Serial.println(argument);
    if (argument.toInt() == 1) {
      target_wiggle = true;
      target_ccswiggle = false;
      //   Serial.println("Target Wiggle on");
      Serial.println("o");
      TargetChangeAxis.moveTo(TARGET[TargetIndex] + y_max);
    }

    if (argument.toInt() == 0) {

      target_wiggle = false;
      target_ccswiggle = false;
      Serial.println("o");
      //Serial.println("Target Wiggle off");
      TargetChangeAxis.moveTo(TARGET[TargetIndex] + y_max);
    }
  }

  if (command == "CCS-WIGGLE") {
    Serial.flush();
    Serial.println(argument);
    if (argument.toInt() == 1) {
      target_ccswiggle = true;
      target_wiggle = false;
      Serial.println("o");
      TargetChangeAxis.moveTo(TARGET[TargetIndex] + y_max);
    }

    if (argument.toInt() == 0) {

      target_ccswiggle = false;
      target_wiggle = false;
      Serial.println("o");
      //Serial.println("Target Wiggle off");
      TargetChangeAxis.moveTo(TARGET[TargetIndex] + y_max);
    }
  }

  if (command == "SUBSTRATEROTATION") {
    TargetSubstrateAxes.SetSubstrateSpeed(argument.toFloat());
    TargetSubstrateAxes.SyncRotation(false);
   // Serial.println("v s = " + String(v_substrate_rotation, DEC));
    return;
  }
  if (command == "TARGETROTATION") {
    TargetSubstrateAxes.SetTargetSpeed(argument.toFloat());
   // Serial.println("v s = " + String(v_substrate_rotation, DEC));
    return;
  }

  if (command == "STARTPULSING") {
    TargetSubstrateAxes.StartPulsing(argument.toInt());
    return;
  }

  if (command == "SYNCROTATION") {
    TargetSubstrateAxes.SetSubstrateSpeed(argument.toFloat());
    TargetSubstrateAxes.SetTargetSpeed(argument.toFloat());
    TargetSubstrateAxes.SyncRotation(true);
    Serial.println("o");
    return;
  }

  if (command == "STOP")
  {
    TargetSubstrateAxes.SetTargetSpeed(0);  
    TargetSubstrateAxes.SetSubstrateSpeed(0);  
    TargetSubstrateAxes.StartPulsing(0);      
  }



}