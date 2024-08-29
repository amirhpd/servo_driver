#ifndef SERVO_DRIVE_H
#define SERVO_DRIVE_H

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <SPI.h>

#define MIN_PULSE 70
#define MAX_PULSE 520
#define OSC_FREQUENCY 27000000
#define PWM_FREQUENCY 50
#define PULSE_TIME 4  // travel time of 1 degree pulse [ms]

class ServoMotor {
public:
    ServoMotor(int angle_range, int address);
    void servo_init();
    void home();
    void free();
    void move(int angle, float rpm);
private:
    int dp(int degree);  // degree_to_pulse
    unsigned rpm_to_delay(int rpm);
    int angle_range;
    int address;
    int position;
    Adafruit_PWMServoDriver pwm;
};

#endif