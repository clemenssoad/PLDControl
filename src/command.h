#include <String>
void Command(String command, String argument) {
  
  // Serial.println("command = " + command);  
  // Serial.println("argument = " + argument);  
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
    if (abs(y) <= y_max*1.1) {
      Serial.print("STATE:" + String(TargetIndex + 1, DEC) + ",");
      Serial.print(y, 3);
      Serial.print(",");
      Serial.println(TargetChangeAxis.currentPosition, 3);

    } else {
      Serial.println("STATE:0," + String(y, 3));
    }
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

  if (command == "MOVETC") {
    Serial.flush();
    float distance = argument.toFloat();
    TargetChangeAxis.move(distance);
    Serial.println("o");
    return;
  }

   if (command == "HOMETC") {
    Serial.flush();
    TargetChangeAxis.HomeAxis();
    Serial.println("o");
    return;
  } 

  if (command == "MOVEZ2") {
    Serial.flush();
    float distance = argument.toFloat();
    Z2Axis.move(distance);
    Serial.println("o");
    return;
  }

  if (command == "HOMEZ2") {
    Serial.flush();
    Z2Axis.HomeAxis();
    Serial.println("o");
    return;
  }


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