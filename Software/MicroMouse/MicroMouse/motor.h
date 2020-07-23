// motor.h

#ifndef _MOTOR_h
#define _MOTOR_h

#include <Arduino.h>

class motor
{
public:
    motor(int pinA, int pinB);
    int getPowerA() const; // 0 to 255
    int getPowerB() const;
    void setPower(int powerA, int powerB);

private:
    int pinA_;
    int pinB_;
    int powerA_;
    int powerB_;

    void writePowerAndDirection();
};


#endif

