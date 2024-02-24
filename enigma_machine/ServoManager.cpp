// ServoManager.cpp
#include "ServoManager.h"

ServoManager::ServoManager() {
  speed = 10;
}

void ServoManager::addServo(int servo, int pin) {
  servoArray[servo].attach(pin);
}
void ServoManager::incrementServo(int servo) {
  servoArray[servo].write(STATIONARY + this->speed);
  delay(100);
}