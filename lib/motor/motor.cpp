#include <Arduino.h>
#include "motor.h"

motor::Motor::Motor(int spr, int p, int dp) {
  stepsPerRev = spr;
  pin = p;
  dirPin = dp;
  curLevel = LOW;
  stepDelay = 100L * 1000L;
  lastStep = micros();

  pinMode(pin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  digitalWrite(pin, LOW);
  digitalWrite(dirPin, LOW);
}

void motor::Motor::toggle() {
  digitalWrite(pin, !curLevel);
  curLevel = !curLevel;
}

void motor::Motor::step(unsigned long now) {
  if (now - lastStep >= stepDelay) {
    lastStep = now;
    toggle();
  }
}

void motor::Motor::setRPM(int rpm) {
  int abs_rpm = abs(rpm);
  stepDelay = 60L * 1000L * 1000L / stepsPerRev / abs_rpm / 2;
}

void motor::Motor::setDirection(bool dir) {
  if (dir) {
    digitalWrite(dirPin, HIGH); // reverse I guess
  } else {
    digitalWrite(dirPin, LOW); // why not, this is forward
  }
  return;
}
