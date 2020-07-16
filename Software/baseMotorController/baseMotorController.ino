const int motorLeftForwardPin = 8; //Motor A - Ain1
const int motorLeftBackPin = 9; //Motor A - Ain2
const int motorRightForwardPin = 11; //Motor B - Bin1
const int motorRightBackPin = 10; //Motor B - Bin2

void setup() {
  // put your setup code here, to run once:
  pinMode(motorLeftForwardPin, OUTPUT);
  pinMode(motorLeftBackPin, OUTPUT);
  pinMode(motorRightForwardPin, OUTPUT);
  pinMode(motorRightBackPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:


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
