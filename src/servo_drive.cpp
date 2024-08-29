#include "servo_drive.hpp"

ServoMotor::ServoMotor(int angle_range, int address)
    : angle_range(angle_range), address(address)
{
    pwm = Adafruit_PWMServoDriver();
}

void ServoMotor::servo_init()
{
    pwm.begin();
    pwm.setOscillatorFrequency(OSC_FREQUENCY);
    pwm.setPWMFreq(PWM_FREQUENCY); 
}

int ServoMotor::dp(int degree)
{
    return map(degree, 0, angle_range, MIN_PULSE, MAX_PULSE);
}

unsigned ServoMotor::rpm_to_delay(int rpm)
{
    if (rpm < 1){return 100;}
    else if (rpm > 40){return 0;}
    else
    {
        return (60000 / (rpm * 360)) - PULSE_TIME;
    }
}

void ServoMotor::home()
{
    pwm.setPWM(address, 0, dp(0));
    position = 0;
    delay(100);
}

void ServoMotor::free()
{
    pwm.setPWM(address, 4096, 0);
}

void ServoMotor::move(int angle, float rpm)
{
    if (angle > position)
    {
        for (int pulse = dp(position); pulse < dp(angle); pulse++) 
        {
            pwm.setPWM(address, 0, pulse);
            delay(rpm_to_delay(rpm));
        }   
    }
    else if (angle < position)
    {
        for (int pulse = dp(position); pulse > dp(angle); pulse--) 
        {
            pwm.setPWM(address, 0, pulse);
            delay(rpm_to_delay(rpm));
        }
    }
    else {}
    position = angle;
    
}
