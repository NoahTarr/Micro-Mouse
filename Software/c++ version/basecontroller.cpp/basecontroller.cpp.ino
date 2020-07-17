#include <Arduino.h>

const int motorLeftForwardPin = 8; //Motor A - Ain1
const int motorLeftBackPin = 9; //Motor A - Ain2
const int motorRightForwardPin = 11; //Motor B - Bin1
const int motorRightBackPin = 10; //Motor B - Bin2

//pins for encoder inputs
#define RH_ENCODER_A 7
#define RH_ENCODER_B 6
#define LH_ENCODER_A 4
#define LH_ENCODER_B 3

// variables for rotation count
volatile unsigned long LeftCount = 0;
volatile unsigned long RightCount = 0;



void setup() {
  
  // put your setup code here, to run once:
  pinMode(motorLeftForwardPin, OUTPUT);
  pinMode(motorLeftBackPin, OUTPUT);
  pinMode(motorRightForwardPin, OUTPUT);
  pinMode(motorRightBackPin, OUTPUT);

 //Following is setup for the encoder

 pinMode(RH_ENCODER_A, INPUT);
 pinMode(RH_ENCODER_B, INPUT);
 pinMode(LH_ENCODER_A, INPUT);
 pinMode(LH_ENCODER_B, INPUT);

//INTERRUPTS

attachInterrupt(digitalPinToInterrupt(0), &leftEncoderEvent, CHANGE);
attachInterrupt(digitalPinToInterrupt(1), &rightEncoderEvent, CHANGE);

Serial.begin(9600); //Opens serial port and sets data range to 9600 bps

}

void loop() {
  // put your main code here, to run repeatedly:

//Encoder looping code

 Serial.print("Right Count: ");
  Serial.println(rightCount);
  Serial.print("Left Count: ");
  Serial.println(leftCount);
  Serial.println();
  delay(500);

//Interupt Call

void LeftEncoderEvent() {
if (digitalRead(LH_ENCODER_A) == HIGH) {
  if(digitalRead(LH_ENCODER_B) == LOW) {
    leftCount++;
  } else {
    LeftCount--;
  }
} else {
    if (digitalRead(LH_ENCODER_B) == LOW) {
      leftCount--;
    } else {
      leftCount++;
    }
  }
}

void rightEncoderEvent() {
  if (digitalRead(RH_ENCODER_A) == HIGH) {
    if (digitalRead(RH_ENCODER_B) == LOW) {
      rightCount++;
    } else {
      rightCount--;
    }
  } else {
    if (digitalRead(RH_ENCODER_B) == LOW) {
      rightCount--;
    } else {
      rightCount++;
    }
  }
}



  //Code to start , slow down , brake, then reverse.
delay(2000);

//FORWARD
analogWrite(motorLeftForwardPin , 255);
analogWrite(motorLeftBackPin , 0);
analogWrite(motorRightForwardPin , 255);
analogWrite(motorRightBackPin , 0);

delay(1000);

//SLOW DOWN
analogWrite(motorLeftForwardPin , 0);
analogWrite(motorLeftBackPin , 0);
analogWrite(motorRightForwardPin , 0);
analogWrite(motorRightBackPin , 0);

delay(8000);

//REVERSE
analogWrite(motorLeftForwardPin , 0);
analogWrite(motorLeftBackPin , 255);
analogWrite(motorRightForwardPin , 0);
analogWrite(motorRightBackPin , 255);

delay(2500);

  
  
}
