// LED.h
#ifndef LED_h
#define LED_h

#include <Arduino.h>
#include <Servo.h>

#define SERVO_NUM 4
#define STATIONARY 90

class ServoManager {
  private:
    int speed;
    Servo servoArray[SERVO_NUM];

  public:
    ServoManager();
    void addServo(int, int);
    void incrementServo(int );
};

#endif