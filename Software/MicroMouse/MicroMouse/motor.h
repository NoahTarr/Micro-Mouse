// motor.h

#ifndef _MOTOR_h
#define _MOTOR_h

#include <Arduino.h>
#include <Encoder.h>


//Motor Controller (drv8833): H-Bridge Logic
//  xIN1    |   xIN2    |   xOUT1   |   xOUT2   |   FUNCTION
//      0   |       0   |       Z   |       Z   |   Coast/Fast Decay
//      0   |       1   |       L   |       H   |   Reverse
//      1   |       0   |       H   |       L   |   Forward
//      1   |       1   |       L   |       L   |   Brake/Slow Decay

//PWM means use analogWrite(...).
//0\1 means use digitalWrite(...) either LOW\HIGH respectively.
//Only certain pins support PWM so make sure the motors are connected to pins that support it.
//Motor Controller (drv8833): PWM Control of Motor Speed
//  xIN1    |   xIN2    |   FUNCTION
//   PWM    |      0    |   Forward PWM, fast decay
//     1    |    PWM    |   Forward PWM, slow decay
//     0    |    PWM    |   Reverse PWM, fast decay
//   PWM    |      1    |   Reverse PWM, slow decay


class motor
{
public:
    motor(int pinA, int pinB);
    int getDutyCycle() const; // Returns previous duty cycle: 0 to 255
    void driveDutyCycle(int dutyCycle);
    void turnLeftDeg(int degress, int power);
    void turnRightDeg(int degress, int power);
    double getSpeed(Encoder enc);
    void coast(); //Cuts all voltage to the motor
    void stop(); //Locks the motor in place

private:
    int pinA_;
    int pinB_;
    int dutyCycle_;
    double lastTime_;
    int lastCount_;
    int crntCount_; 
};


#endif

