// 
// 
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

#include "motor.h"

motor::motor(int pinA, int pinB)
{
    dutyCycle_ = 0;
    movingClockwise_ = true; //Assuming first direction is forward
    this->pinA_ = pinA;
    this->pinB_ = pinB;
    pinMode(pinA, OUTPUT);
    pinMode(pinB, OUTPUT);
}

int motor::getDutyCycle() const
{
    return dutyCycle_;
}

bool motor::isMovingClockwise() const
{
    return movingClockwise_;
}

void motor::driveClockwise(int dutyCycle)
{
    dutyCycle_ = dutyCycle;
    movingClockwise_ = true;
    analogWrite(pinA_, dutyCycle);
    digitalWrite(pinB_, LOW);
}

void motor::driveCounterClockwise(int dutyCycle)
{
    dutyCycle_ = dutyCycle;
    movingClockwise_ = false;
    digitalWrite(pinA_, LOW);
    analogWrite(pinB_, dutyCycle);
}

void motor::coast()
{
    digitalWrite(pinA_, LOW);
    digitalWrite(pinB_, LOW);
}

void motor::stop()
{
    analogWrite(pinA_, HIGH);
    analogWrite(pinB_, HIGH);
}

void motor::resume()
{
    if (movingClockwise_)
    {
        analogWrite(pinA_, dutyCycle_);
        digitalWrite(pinB_, LOW);
    }
    else
    {
        digitalWrite(pinA_, LOW);
        analogWrite(pinB_, dutyCycle_);
    }
}
