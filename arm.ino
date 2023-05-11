// include the Servo library
#include <Servo.h>

Servo servoBase;  // create a servo object
Servo servoEnd;  // create a servo object
Servo servoEjector;

int posBase = 0, posEnd = 160, posEjector = 0;

void setup() {
  servoBase.attach(9);   // attaches the servo on pin 9 to the servo object
  servoEnd.attach(10);   // attaches the servo on pin 10 to the servo object
  servoEjector.attach(11);   // attaches the servo on pin 11 to the servo object
  Serial.begin(9600);  // open a serial connection to your computer
}

void loop() {
  Serial.println(0);
  servoEnd.write(160);
  servoBase.write(0);
  delay(1000);

  // base action
  for (posBase = 0; posBase <= 50; posBase += 1) {
    // pos cannot go beyond 180
    Serial.println(posBase);
    servoBase.write(posBase);
    delay(50);
  }
  // delay(1000);

  // end action
  for (posEnd = 160; posEnd >= 0; posEnd -= 1) {
    // pos cannot go beyond 180
    Serial.println(posEnd);
    servoEnd.write(posEnd);
    delay(20);
  }
 
  for (posEjector = 0; posEjector <= 180; posEjector += 1) {
    // pos cannot go beyond 180
//    Serial.println(servoEjector);
    servoEjector.write(posEjector);
    delay(20);
  }
  delay(10000);
 
  while (posEnd < 160) {
    posEnd += 1;
    servoEnd.write(posEnd);
    delay(20);
  }
  while (posBase > 0) {
    posBase -= 1;
    servoBase.write(posBase);
    delay(20);
  }
  while (posEjector > 0) {
    posEjector -= 1;
    servoEjector.write(posEjector);
    delay(20);
  }
 
  delay(2000);
}