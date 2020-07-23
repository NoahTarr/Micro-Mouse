// 
// 
// 

#include "motor.h"

motor::motor(int pinA, int pinB)
{
    this->pinA_ = pinA;
    this->pinB_ = pinB;
    pinMode(pinA, OUTPUT);
    pinMode(pinB, OUTPUT);
}

int motor::getPowerA() const
{
    return this->powerA_;
}

int motor::getPowerB() const
{
    return this->powerB_;
}

void motor::setPower(int powerA, int powerB)
{
    this->powerA_ = powerA;
    this->powerB_ = powerB;
    writePowerAndDirection();
}

void motor::writePowerAndDirection()
{
    analogWrite(pinA_, this->powerA_);
    analogWrite(pinB_, this->powerB_);
}