/*
 Name:		MicroMouse.ino
 Created:	7/21/2020 7:25:11 PM
 Author:	noaht
*/


#include <PIDController.h>
#include "motor.h"
#include "encoder.h"

//pins for motors
#define LH_MOTOR_A 6 //PWM of 980Hz
#define LH_MOTOR_B 9 //PWM of 490Hz
#define RH_MOTOR_A 5 //PWM of 980Hz
#define RH_MOTOR_B 10 //PWM of 490Hz

//pins for encoder inputs
#define LH_ENCODER_A 3 
#define LH_ENCODER_B 7
#define RH_ENCODER_A 2
#define RH_ENCODER_B 4

//Analog power to motors: Range -255 to 255
#define fixedPower 150
#define maxPower 255

//PID Controller Values
//These are values I got from an online example. Could be wrong.
#define Kp 15
#define Ki 0
#define Kd 2000
#define pidMax 255
#define pidMin -255


motor LH_MOTOR(LH_MOTOR_A, LH_MOTOR_B);
motor RH_MOTOR(RH_MOTOR_A, RH_MOTOR_B);
encoder LH_ENCODER(LH_ENCODER_A, LH_ENCODER_B);
encoder RH_ENCODER(RH_ENCODER_A, RH_ENCODER_B);
PIDController MOTOR_POS_PID;

// the setup function runs once when you press reset or power the board
void setup() {
    Serial.begin(9600); //Opens serial port and sets data range to 9600 bps

    MOTOR_POS_PID.begin();
    MOTOR_POS_PID.tune(Kp, Ki, Kd); 
    MOTOR_POS_PID.limit(pidMin, pidMax);
}

// the loop function runs over and over again until power down or reset
int count = 0;
void loop() {
    //Encoder looping code
    // Serial.print("Left Count: ");
    // Serial.println(LH_ENCODER.getPosition());
    // Serial.print("Right Count: ");
    // Serial.println(RH_ENCODER.getPosition());
    // Serial.println();
    // delay(1000);
    // RH_MOTOR.stop();
    // delay(10);
    // if (count < 3)
    // {
    //     RH_MOTOR.driveClockwise(225);
    //     delay(1000);
    //     RH_ENCODER.setPosition(0);
    //     delay(1000);
    //     RH_MOTOR.stop();
    //     delay(100);
    //     Serial.print("Counts/Sec: ");
    //     Serial.println(RH_ENCODER.getPosition());
    //     Serial.print("Revolutions/Sec: ");
    //     Serial.println(static_cast<double>(RH_ENCODER.getPosition())/225);
    //     count++;
    // }
    LH_MOTOR.driveClockwise(255);
    RH_MOTOR.driveClockwise(255);
}

