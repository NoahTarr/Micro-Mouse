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
    pinA_ = pinA;
    pinB_ = pinB;
    lastCount_ = 0;
    crntCount_ = 0;
    lastTime_ = 0;

    //Initialize motor control pins
    pinMode(pinA_, OUTPUT);
    pinMode(pinB_, OUTPUT);

    //Start with motor breaking
    stop();
}

int motor::getDutyCycle() const
{
    return dutyCycle_;
}

void motor::driveDutyCycle(int dutyCycle)
{
    dutyCycle_ = dutyCycle;

    if (dutyCycle_ > 255)
        dutyCycle_ = 255;
    else if (dutyCycle_ < -255)
        dutyCycle_ = -255;

    if (dutyCycle_ > 0)
    {
        analogWrite(pinA_, dutyCycle_);
        digitalWrite(pinB_, LOW);
    }
    else if (dutyCycle_ < 0)
    {
        analogWrite(pinB_, -1 * dutyCycle_);
        digitalWrite(pinA_, LOW);
    }
    else //Break
    {
        digitalWrite(pinA_, HIGH);
        digitalWrite(pinB_, HIGH);
    }
}

//Get speed in RPM's
double motor::getSpeed(Encoder enc) {
    lastCount_ = crntCount_;
    crntCount_ = enc.read();
    const double deltaCount = crntCount_ - lastCount_;
    const double crntTime = millis();
    const double deltaTime = crntTime - lastTime_;
    lastTime_ = crntTime;

    //speedInnerShaft RPM = (change counts)/(change time) * (1 Rotation)/(12 counts) * (60000 ms)/(1 min)
    //speedOutShaft RPM = (speedInnerShaft RPM)/(75 gear ration)
    // return pow(2.71828, (((deltaCount * 60000) / (deltaTime * 900)) + 167) / 111);
    // return (((deltaCount * 60000) / (deltaTime * 900)) - 350) / 0.3;
    return (deltaCount * 60000) / (deltaTime * 900);
}

void motor::coast()
{
    digitalWrite(pinA_, LOW);
    digitalWrite(pinB_, LOW);
}

void motor::stop()
{
    digitalWrite(pinA_, HIGH);
    digitalWrite(pinB_, HIGH);
}
