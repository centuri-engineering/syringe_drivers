/*
 * Code adapted from stepper_oneRevolution from the Stepper library, Tom Igoe
 */
#include <Stepper.h>

// change this to the number of steps on your motor
#define STEPS 2048

// create an instance of the stepper class, specifying
// the number of steps of the motor and the pins it's
// attached to
Stepper stepper(STEPS, 8, 10, 9, 11);
long steps;

void setup() {
  stepper.setSpeed(10);
  Serial.begin(9600);
}

void loop() {
  stepsMove();
}

void stepsMove() {
  if (Serial.available()) {
    steps = Serial.parseInt();
    Serial.println(steps);
    stepper.step(steps);
  }
}
