void moveChassis(int leftSpeed, int rightSpeed) {
  // Set the speed of the left and right motors
  analogWrite(leftMotorPin, leftSpeed);
  analogWrite(rightMotorPin, rightSpeed);
}


/////////////////

// Define the motor pins
int motor1Pin1 = 2;
int motor1Pin2 = 3;
int motor2Pin1 = 4;
int motor2Pin2 = 5;

// Define the speed and direction variables
int motorSpeed = 255;
int motorDirection = 0;

// Define the function to rotate the chassis towards the pixel with the highest heat value
void rotateTowardsFire(int highestPixel) {
  // Check which side the highest pixel is on
  if (highestPixel < 4) {
    // Set the motor direction to rotate left
    motorDirection = -1;
  } else if (highestPixel > 4) {
    // Set the motor direction to rotate right
    motorDirection = 1;
  } else {
    // Stop the motors if the highest pixel is in the center
    motorDirection = 0;
  }
  
  // Set the motor speed and direction
  analogWrite(motor1Pin1, motorSpeed * motorDirection);
  analogWrite(motor1Pin2, 0);
  analogWrite(motor2Pin1, motorSpeed * motorDirection);
  analogWrite(motor2Pin2, 0);
}