#include <Arduino.h>
#include "servo_drive.hpp"

ServoMotor servo_1(215, 0);

void setup() 
{
  servo_1.servo_init();
  delay(10);
}

void loop() 
{
  servo_1.home();
  delay(1000);
  servo_1.move(90, 20);
  delay(1000);
  servo_1.free();
  delay(10000);
}