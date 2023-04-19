#include <Servo.h>

// Define the servo pins
#define servo1Pin 9
#define servo2Pin 10

// Create servo objects
Servo servo1;
Servo servo2;

// Define the servo angles for the arm
#define baseAngle 90
#define link1Angle 90
#define link2Angle 90

void moveArm(int fireX, int fireY) {
  // Calculate the angle of the base servo
  int baseAngle = map(fireX, 0, 8, 0, 180);

  // Calculate the angle of the first link servo
  int link1Angle = map(fireY, 0, 8, 0, 180);

  // Calculate the angle of the second link servo
  int link2Angle = 180 - baseAngle - link1Angle;

  // Move the servos to the calculated angles
  servo1.write(baseAngle);
  servo2.write(link1Angle);
}

void setup() {
  // Attach the servos to their pins
  servo1.attach(servo1Pin);
  servo2.attach(servo2Pin);
}

void loop() {
  // Move the arm towards the source of fire
  moveArm(fireX, fireY);
}


///////////////////////////

#include <Servo.h>
Servo base_motor;
Servo link_motor;
// Define the Servo Motor Pins:
base_motor.attach(base_motor_pin);
link_motor.attach(link_motor_pin);
// Move the Arm to Point to the Fire:
void move_arm_to_fire() {
  int base_angle = calculate_base_angle(); // Calculate the angle for the base motor
  int link_angle = calculate_link_angle(); // Calculate the angle for the link motor
  base_motor.write(base_angle); // Move the base motor to the calculated angle
  link_motor.write(link_angle); // Move the link motor to the calculated angle
}
// Calculate the Angle for the Base Motor:
int calculate_base_angle() {
  // Calculate the angle based on the position of the fire on the AMG8833 sensor
  // You can use the pixel value and the resolution of the sensor to calculate the angle
  int angle = 0; // Replace with your calculation
  return angle;
}
// Calculate the Angle for the Link Motor:
int calculate_link_angle() {
  // Calculate the angle based on the position of the fire on the AMG8833 sensor
  // You can use the pixel value and the resolution of the sensor to calculate the angle
  int angle = 0; // Replace with your calculation
  return angle;
}
// Stop the Robot at a Certain Threshold:
void stop_robot_at_threshold() {
  // Calculate the distance between the robot and the fire
  // You can use the sensor data and the position of the robot to calculate the distance
  int distance = 0; // Replace with your calculation
  if (distance < threshold_distance) {
    // Stop the robot
    // You can use the DC motors to stop the robot
  }
}