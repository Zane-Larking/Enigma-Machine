#include "ServoManager.h"

// not comfirmed
#define ROTOR_SENSE 0
#define ROTOR_ORIENTATION_SENSE 1

ServoManager sm;

void setup()
{
  // add servos
  sm.addServo(0,11);
  // pins not confirmed
  sm.addServo(1,9);
  sm.addServo(2,7);
  sm.addServo(3,6);
  delay(100);

}

void loop() {
  // put your main code here, to run repeatedly:
  // delay(1000);
  // myservo.write(0);

  if (rotorsInserted()) {
    if (rotorsInCorrectOrientation)

  }

  sm.incrementServo(0);
  delay(1000);
}

bool rotorsInserted() {
  return digitialRead(ROTOR_SENSE) != 0;
}

bool rotorsInCorrectOrientation() {
  return digitalRead(ROTOR_ORIENTATION_SENSE)
}
