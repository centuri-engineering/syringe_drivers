/*
   Code adapted from BasicStepperDriver example from the StepperDriver library. Copyright (C)2015-2017 Laurentiu Badea
   Simple demo, should work with any driver board
   Connect STEP, DIR as indicated
   This file may be redistributed under the terms of the MIT license.
   A copy of this license has been included with this distribution in the file LICENSE.

*/
#include <Arduino.h>
#include "BasicStepperDriver.h"

// Motor steps per revolution. Most steppers are 200 steps or 1.8 degrees/step
#define MOTOR_STEPS 200
#define RPM 10
// Since microstepping is set externally, make sure this matches the selected mode
// If it doesn't, the motor will move at a different RPM than chosen
// 1=full step, 2=half step etc.
#define MICROSTEPS 16

// All the wires needed for full functionality
#define DIR 8
#define STEP 9
//Uncomment line to use enable/disable functionality
//#define SLEEP 13

// 2-wire basic config, microstepping is hardwired on the driver
BasicStepperDriver stepper(MOTOR_STEPS, DIR, STEP);

//Uncomment line to use enable/disable functionality
//BasicStepperDriver stepper(MOTOR_STEPS, DIR, STEP, SLEEP);

long steps;
bool fullRotation;

void setup() {
  Serial.begin(9600);
  stepper.begin(RPM, MICROSTEPS);
  // if using enable/disable on ENABLE pin (active LOW) instead of SLEEP uncomment next line
  // stepper.setEnableActiveState(LOW);
}

void loop() {

  // energize coils - the motor will hold position
  // stepper.enable();
  stepsMove(fullRotation=false);
}

void stepsMove(bool fullRotation) {
  if (Serial.available()) {
    steps = Serial.parseInt();
    if (fullRotation == true) {
      steps = steps * MICROSTEPS * MOTOR_STEPS;
    }
    Serial.println(steps);
    stepper.move(steps);
  }
}
