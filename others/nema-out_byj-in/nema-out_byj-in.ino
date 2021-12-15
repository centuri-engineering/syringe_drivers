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
BasicStepperDriver stepper2(MOTOR_STEPS, DIR, STEP);

//Uncomment line to use enable/disable functionality
//BasicStepperDriver stepper(MOTOR_STEPS, DIR, STEP, SLEEP);

bool fullRotation;

/*
 * Code adapted from stepper_oneRevolution from the Stepper library, Tom Igoe
 */
#include <Stepper.h>

// change this to the number of steps on your motor
#define STEPS 2048

// create an instance of the stepper class, specifying
// the number of steps of the motor and the pins it's
// attached to
Stepper stepper(STEPS, 4, 6, 5, 7);
long steps;
String letter;

void setup() {
  stepper.setSpeed(10);
  stepper2.begin(RPM, MICROSTEPS);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    letter = Serial.read();
    steps = Serial.parseInt();
    Serial.print("Letter is :");
    Serial.println(letter);
    Serial.print("Step is : ");
    Serial.println(steps);
    serialFlush();
        if (fullRotation == true) {
      steps = steps * MICROSTEPS * MOTOR_STEPS;
    }
    if (letter == "122"){//type "z"
      stepper.step(steps);
    }
    else if (letter == "97"){ //type "a"
      stepper2.move(-steps);
    }
  }
}

void serialFlush(){
  while(Serial.available() > 0) {
    char t = Serial.read();
  }
}
