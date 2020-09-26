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
#define F_TRIG 11
#define F_ECHO 12


//Analog power to motors: Range -255 to 255
#define fixedPower 100
#define maxPower 255
#define ticksFor360Turn 1476 //Should be 369*4=1476
#define ticksFor180Turn 738 //Should be 369*4=1476
#define ticksFor90Turn 369 //Should be 369*4=1476


//PID Controller Values
#define dutyMax 255
#define dutyMin -255
double LM_setDuty, RM_setDuty, LM_CrntSpeed, RM_CrntSpeed, LM_adjDuty, RM_adjDuty;
//Left Motor:
#define KpLM 0.0000715
#define KiLM 0.000217
#define KdLM 0
//Right Motor:
#define KpRM 0.0000715
#define KiRM 0.000217
#define KdRM 0



UltraSonicDistanceSensor F_DSENSOR(F_TRIG, F_ECHO);
motor LH_MOTOR(LH_MOTOR_A1, LH_MOTOR_A2);
motor RH_MOTOR(RH_MOTOR_B1, RH_MOTOR_B2);
Encoder LH_ENCODER(LH_ENCODER_A, LH_ENCODER_B);
Encoder RH_ENCODER(RH_ENCODER_A, RH_ENCODER_B);

// AutoPID LH_MOTOR_PID(&LM_CrntSpeed, &LM_setDuty, &LM_adjDuty, dutyMin, dutyMax, KpLM, KiLM, KdLM);
// AutoPID RH_MOTOR_PID(&RM_CrntSpeed, &RM_setDuty, &RM_adjDuty, dutyMin, dutyMax, KpLM, KiLM, KdLM);


void turnLeftDeg(int degrees, int power);
void testingDutyCycles();



double lastTime = 0;
double crntTime = 0;
// the setup function runs once when you press reset or power the board
void setup() {
    Serial.begin(9600); //Opens serial port and sets data range to 9600 
    lastTime = millis();
    crntTime = millis();
    // LH_MOTOR.driveDutyCycle(200);
    // RH_MOTOR.driveDutyCycle(-200);
}

// the loop function runs over and over again until power down or reset
int count = 0;
int count2 = 0;
int speed = 0;
int done = false;
void loop()
{
    // Every 500 miliseconds, do a measurement using the sensor and print the distance in centimeters.
    Serial.println(F_DSENSOR.measureDistanceCm());
    delay(500);
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
}

void testingDutyCycles()
{
    for (; millis() < 28000;)
    {
        LH_MOTOR.driveDutyCycle(speed);
        Serial.print(millis());
        Serial.print(", ");
        Serial.print(speed);
        Serial.print(", ");
        Serial.println(LH_MOTOR.getSpeed(LH_ENCODER));

        if (millis() - lastTime > 2000)
        {
            lastTime = millis();
            count2++;

            switch (count2)
            {
            case 1: speed = 50;
                break;
            case 2: speed = 0;
                break;
            case 3: speed = 0;
                break;
            case 4: speed = 100;
                break;
            case 5: speed = 0;
                break;
            case 6: speed = 0;
                break;
            case 7: speed = 150;
                break;
            case 8: speed = 0;
                break;
            case 10: speed = 200;
                break;
            case 11: speed = 0;
                break;
            case 12: speed = 255;
                break;
            case 13: speed = 0;
                break;
            default:
                done = true;
            }

            LM_setDuty = speed;
            RM_setDuty = speed;
        }
    }

    if (done)
    {
        LM_setDuty = 0;
        RM_setDuty = 0;
    }
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

        while (LH_ENCODER.read() < tickGoal || RH_ENCODER.read() > -tickGoal)
        {
            if (LH_ENCODER.read() > tickGoal) { LH_MOTOR.stop(); }
            if (RH_ENCODER.read() < -tickGoal) { RH_MOTOR.stop(); }
        }
    }
    else //Right turn
    {
        LH_MOTOR.driveDutyCycle(power);
        RH_MOTOR.driveDutyCycle(-1 * power);

        while (LH_ENCODER.read() > -tickGoal || RH_ENCODER.read() < tickGoal)
        {
            if (LH_ENCODER.read() < -tickGoal) { LH_MOTOR.stop(); }
            if (RH_ENCODER.read() > tickGoal) { RH_MOTOR.stop(); }
        }
    }

    //Make sure both motors stop at the end of the turn.
    LH_MOTOR.stop();
    RH_MOTOR.stop();
}