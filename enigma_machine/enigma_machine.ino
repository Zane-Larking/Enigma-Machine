#include "ServoManager.h"

// Comment or uncomment according to the position of the LD jumper KEY_BOARD_LD (Line 13) will also need to be commented
#define KEY_BOARD_MANUAL_LOAD
#define KEY_BOARD_INT_FLAG
// continuous polling is required without interupt flags
// #define KEY_BOARD_CONTINUOUS_POLLING


#define TRUE 1
#define FALSE 0
#define ON 1
#define OFF 0

// Pins are not comfirmed
#define KEY_BOARD_CLK 2
#define KEY_BOARD_DATA 3 
#define DEBUG_LED 7

// optional Key Board pins
// using all functional pins improve reliability.
// Not using them can cause race condition issues and require more computation
#ifdef KEY_BOARD_INT_FLAG
#define KEY_BOARD_INT 4
#endif
#ifdef KEY_BOARD_MANUAL_LOAD
#define KEY_BOARD_LD 13
#endif

#define ROTOR_SENSE 5
#define ROTOR_ORIENTATION_SENSE 6


int _key_down = 0;
int key;
char charKey;
ServoManager sm;

void setup()
{
  Serial.begin(9600);
  // add servos
  sm.addServo(0,11);
  // pins not confirmed
  sm.addServo(1,9);
  sm.addServo(2,7);
  sm.addServo(3,6);
  delay(100);

  #ifdef KEY_BOARD_MANUAL_LOAD
  pinMode(KEY_BOARD_LD, OUTPUT);
  #endif
  pinMode(KEY_BOARD_CLK, OUTPUT);
  pinMode(KEY_BOARD_DATA, INPUT);
  pinMode(ROTOR_SENSE, INPUT);
  pinMode(DEBUG_LED, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

  if (rotorsInserted()) {
    Serial.println("ROTOR INSERTED");

    if (rotorsInCorrectOrientation()){
      sm.incrementServo(0);
      delay(1000);
    }

  }
  #ifdef KEY_BOARD_CONTINUOUS_POLLING
  if (keyPressed()) {
    key = getKeyNow();
    charKey = key;
    Serial.println(charKey); 
  }
  #else 
  if (keyDown()) {
    key = getKey();
    charKey = key;
    Serial.println(charKey);  
  }
  #endif
  keyUp();
  

}

char getKey() {
  int keyCode = getKeyCode();
  char charCode = 'A' + keyCode;
  return charCode;
}

char getKeyNow() {
  if (KEY_BOARD_INT) {
    return getKey();
  }
  else {
    return '\0';
  }
}

bool keyDown() {
  if (keyPressed() && (_key_down == 0)) {
    _key_down = 1;
    return TRUE;
  }
  return FALSE;
}
bool keyUp() {
  if (keyPressed()==0 && (_key_down == 1)) {
    _key_down = 0;
    return TRUE;
  }
  return FALSE;
}
bool keyPressed() {
  return digitalRead(KEY_BOARD_INT) == 1;
}

int getKeyCode() {
  int KB_data = 0;
  // for wire debugging (without wired up buttons)
  // delay(1000);
  #ifdef KEY_BOARD_MANUAL_LOAD
    digitalWrite(KEY_BOARD_LD, 0);
    digitalWrite(KEY_BOARD_LD, 1);
  #endif
  Serial.println("");
  
  for (int i = 4; i >= 0; i--) {
    int data = digitalRead(KEY_BOARD_DATA);
    
    // most significant digit first
    int temp = myPow(2, i) * data;
    KB_data += temp;
    
    digitalWrite(KEY_BOARD_CLK, 1);
    digitalWrite(KEY_BOARD_CLK, 0);
  }
  return KB_data;
}

int myPow(int base, int exp) {
  int num = 1;
  for (int i = 0; i < exp; i ++) {
    num = num * base;
  }
  return num;
}
bool rotorsInserted() {
  return digitalRead(ROTOR_SENSE) == 1;
}

bool rotorsInCorrectOrientation() {
  return digitalRead(ROTOR_ORIENTATION_SENSE);
}
