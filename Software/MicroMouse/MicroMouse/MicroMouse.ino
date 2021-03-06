/*
 Name:		MicroMouse.ino
 Created:	7/21/2020 7:25:11 PM
 Author:	noaht
*/

#include <Encoder.h>
#include <AutoPID.h>
#include "motor.h"
#include "HCSR04.h"

// Our Motor's: https://www.pololu.com/product/2215
// They are 75:1 Micro Metal Gearmotor HP 6V with Extended Motor Shaft
// PWM Pins:
// 9,10:    490Hz
// 5,6:     980Hz
//pins for motors
#define RH_MOTOR_B1 5
#define RH_MOTOR_B2 6
#define LH_MOTOR_A2 9 
#define LH_MOTOR_A1 10
//Motor PID Controller Values
#define dutyMax 255
#define dutyMin -255
#define stepTime 500
#define Kp 0.1
#define Ki 0.6
#define Kd 0.85
double LM_setSpeed, RM_setSpeed, LM_CrntSpeed, RM_CrntSpeed, LM_adjDuty, RM_adjDuty;


// Our encoder: https://www.pololu.com/product/4760
// Our encoder disk: https://www.pololu.com/product/2599
// 12 Counts per Revolution of Motor Shaft (CRP_MS)
// CPR of Output Shaft (CPR_OS) = Motor Gear Ratio * CPM_MS
// CPR_OS = 75 * 12 = 900 CPR
// Improve encoder interrupts
#define ENCODER_USE_INTERRUPTS
#define ENCODER_OPTIMIZE_INTERRUPTS
//pins for encoder inputs
#define LH_ENCODER_A 3 
#define LH_ENCODER_B 8
#define RH_ENCODER_A 2
#define RH_ENCODER_B 4


// pins for distance sensors
#define TRIG 7
#define LH_ECHO 11
#define F_ECHO 12
#define RH_ECHO 13


//Analog power to motors: Range -255 to 255
#define fixedPower 100
#define maxPower 255
#define ticksFor360Turn 1476 //Should be 369*4=1476
#define ticksFor180Turn 738 //Should be 369*2=738
#define ticksFor90Turn 369 //Should be 369


UltraSonicDistanceSensor LH_DSENSOR(TRIG, LH_ECHO);
UltraSonicDistanceSensor F_DSENSOR(TRIG, F_ECHO);
UltraSonicDistanceSensor RH_DSENSOR(TRIG, RH_ECHO);
motor LH_MOTOR(LH_MOTOR_A1, LH_MOTOR_A2);
motor RH_MOTOR(RH_MOTOR_B1, RH_MOTOR_B2);
AutoPID LH_MOTOR_PID(&LM_CrntSpeed, &LM_setSpeed, &LM_adjDuty, dutyMin, dutyMax, Kp, Ki, Kd);
AutoPID RH_MOTOR_PID(&RM_CrntSpeed, &RM_setSpeed, &RM_adjDuty, dutyMin, dutyMax, Kp, Ki, Kd);
Encoder LH_ENCODER(LH_ENCODER_A, LH_ENCODER_B);
Encoder RH_ENCODER(RH_ENCODER_A, RH_ENCODER_B);


// void turnLeftDeg(int degrees, int power);
void turnDeg(int degrees, int power);


// the setup function runs once when you press reset or power the board
void setup() {
    Serial.begin(9600); //Opens serial port and sets data range to 9600 

    LH_MOTOR_PID.setTimeStep(stepTime);
    RH_MOTOR_PID.setTimeStep(stepTime);
}


// the loop function runs over and over again until power down or reset
int count = 0;
int count2 = 0;
int speed = 0;
int done = false;
void loop()
{
    // Every 500 miliseconds, do a measurement using the sensor and print the distance in centimeters.
    // Serial.print("Left: ");
    // Serial.println(LH_DSENSOR.measureDistanceCm());
    // Serial.print("Front: ");
    // Serial.println(F_DSENSOR.measureDistanceCm());
    // Serial.print("Right: ");
    // Serial.println(RH_DSENSOR.measureDistanceCm());
    // delay(500);
    //
    // Serial.print(LH_ENCODER.read());
    // Serial.print(", ");
    // Serial.println(RH_ENCODER.read());
    //
    // while (LH_ENCODER.read() < ticksFor90Turn || RH_ENCODER.read() > -ticksFor90Turn)
    // {
    //     if (LH_ENCODER.read() > ticksFor90Turn) {LH_MOTOR.stop();}
    //     if (RH_ENCODER.read() < -ticksFor90Turn) {RH_MOTOR.stop();}
    // }
    //
    // LH_MOTOR.stop();
    // RH_MOTOR.stop();

    // Serial.println(F_DSENSOR.measureDistanceCm());
    // Serial.println(LH_ENCODER.read());
    // Serial.println(RH_ENCODER.read());
    // Serial.println("------------------");
    // if (F_DSENSOR.measureDistanceCm() > 20)
    // {
    //     LH_MOTOR.driveDutyCycle(100);
    //     RH_MOTOR.driveDutyCycle(100);
    // }
    // else
    // {
    //     turnDeg(90, 100);
    //     delay(1000);
    // }
    // delay(100);

    LM_setSpeed = RM_setSpeed = 0;

    LM_CrntSpeed = LH_MOTOR.getSpeed(LH_ENCODER);
    RM_CrntSpeed = RH_MOTOR.getSpeed(RH_ENCODER);

    LH_MOTOR_PID.run();
    RH_MOTOR_PID.run();

    LH_MOTOR.driveDutyCycle(LM_adjDuty);
    RH_MOTOR.driveDutyCycle(RM_adjDuty);
}



void turnDeg(int degrees, int power)
{
    //Reset encoders
    LH_ENCODER.write(0);
    RH_ENCODER.write(0);

    //Determine tickGoal
    int tickGoal = (41 * degrees) / 10;

    //Start the motors
    if (degrees < 0) //Left turn
    {
        LH_MOTOR.driveDutyCycle(-1 * power);
        RH_MOTOR.driveDutyCycle(power);

        while (LH_ENCODER.read() > -tickGoal || RH_ENCODER.read() < tickGoal)
        {
            if (LH_ENCODER.read() > tickGoal) { LH_MOTOR.stop(); }
            if (RH_ENCODER.read() < -tickGoal) { RH_MOTOR.stop(); }
            Serial.println(LH_ENCODER.read());
            Serial.println(RH_ENCODER.read());
        }
    }
    else //Right turn
    {
        LH_MOTOR.driveDutyCycle(power);
        RH_MOTOR.driveDutyCycle(-1 * power);

        while (LH_ENCODER.read() < tickGoal || RH_ENCODER.read() > -tickGoal)
        {
            if (LH_ENCODER.read() < -tickGoal) { LH_MOTOR.stop(); }
            if (RH_ENCODER.read() > tickGoal) { RH_MOTOR.stop(); }
            Serial.println(LH_ENCODER.read());
            Serial.println(RH_ENCODER.read());
        }
    }

    //Make sure both motors stop at the end of the turn.
    LH_MOTOR.stop();
    RH_MOTOR.stop();
}