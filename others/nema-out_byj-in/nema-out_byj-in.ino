/*
   Code adapted from BasicStepperDriver example from the StepperDriver library.
   Copyright (C)2015-2017 Laurentiu Badea Simple demo, should work with any
   driver board Connect STEP, DIR as indicated

   Code adapted from stepper_oneRevolution from the Stepper library, Tom Igoe

   This file may be redistributed
   under the terms of the MIT license. A copy of this license has been included
   with this distribution in the file LICENSE.

*/
#include <Arduino.h>
#include <Stepper.h>

#include "BasicStepperDriver.h"

// Initialization of the Nema driver (reward delivery)
// Motor steps per revolution. Most steppers are 200 steps or 1.8 degrees/step
#define MOTOR_STEPS 200
#define RPM 10
// Since microstepping is set externally, make sure this matches the selected
// mode If it doesn't, the motor will move at a different RPM than chosen 1=full
// step, 2=half step etc.
#define MICROSTEPS 16

// All the wires needed for full functionality
#define DIR 8
#define STEP 9
// Uncomment line to use enable/disable functionality
//#define SLEEP 13

// 2-wire basic config, microstepping is hardwired on the driver
BasicStepperDriver stepper_out(MOTOR_STEPS, DIR, STEP);

// Initialization of the byj driver (reward sucking)
// change this to the number of steps on your motor
#define STEPS_IN 2048

// create an instance of the stepper class, specifying
// the number of steps of the motor and the pins it's
// attached to
Stepper stepper_in(STEPS_IN, 4, 6, 5, 7);

void setup() {
  stepper_in.setSpeed(10);
  stepper_out.begin(RPM, MICROSTEPS);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    int letter = Serial.read();
    if (letter == 'z') { // Sucking reward
      long steps = Serial.parseInt();
      Serial.print("Sucking reward with ");
      Serial.print(steps);
      Serial.println(" steps");
      stepper_in.step(steps);
    } else if (letter == 'a') {
      long steps = Serial.parseInt();
      Serial.print("Delivering reward with ");
      Serial.print(steps);
      Serial.println(" steps");
      stepper_out.move(-steps);
    } else {
      Serial.print("Command not recognized: ");
      Serial.println(letter);
    }
  }
