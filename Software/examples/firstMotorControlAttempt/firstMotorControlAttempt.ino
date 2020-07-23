//RH = Motor B
//LH = Motor A

//pins for motors
#define RH_MOTOR_Forward 5
#define RH_MOTOR_BACK 6
#define LH_MOTOR_Forward 9
#define LH_MOTOR_BACK 10

//pins for encoder inputs
#define RH_ENCODER_A 2
#define RH_ENCODER_B 4
#define LH_ENCODER_A 3
#define LH_ENCODER_B 7

#define power 150
#define maxPower 255

// variables for rotation count
// Declared volatile because they are altered in ISR (Interrupt Service Routine)
volatile int rightCount = 0;
volatile int leftCount = 0;

//Function Declarations
//void rightEncoderEvent();
//void leftEncoderEvent();

void setup() {
  Serial.begin(9600); //Opens serial port and sets data range to 9600 bps

  pinMode(RH_MOTOR_Forward, OUTPUT);
  pinMode(RH_MOTOR_BACK, OUTPUT);
  pinMode(LH_MOTOR_Forward, OUTPUT);
  pinMode(LH_MOTOR_BACK, OUTPUT);

  pinMode(RH_ENCODER_A, INPUT);
  pinMode(RH_ENCODER_B, INPUT);
  pinMode(LH_ENCODER_A, INPUT);
  pinMode(LH_ENCODER_B, INPUT);

  //INTERRUPTS
  attachInterrupt(digitalPinToInterrupt(LH_ENCODER_A), leftEncoderEvent, RISING);
  attachInterrupt(digitalPinToInterrupt(RH_ENCODER_A), rightEncoderEvent, RISING);
}

void loop() {

  //Encoder looping code
    Serial.print("Right Count: ");
    Serial.println(rightCount);
    Serial.print("Left Count: ");
    Serial.println(leftCount);
    Serial.println();

//  //BREAK
//  analogWrite(LH_MOTOR_Forward , maxPower);
//  analogWrite(LH_MOTOR_BACK , maxPower);
//  analogWrite(RH_MOTOR_Forward , maxPower);
//  analogWrite(RH_MOTOR_BACK , maxPower);
//  delay(1000);
//
//  //FORWARD
//  analogWrite(LH_MOTOR_Forward , power);
//  analogWrite(LH_MOTOR_BACK , 0);
//  analogWrite(RH_MOTOR_Forward , power);
//  analogWrite(RH_MOTOR_BACK , 0);
//  delay(1000);
//
//  //BREAK
//  analogWrite(LH_MOTOR_Forward , maxPower);
//  analogWrite(LH_MOTOR_BACK , maxPower);
//  analogWrite(RH_MOTOR_Forward , maxPower);
//  analogWrite(RH_MOTOR_BACK , maxPower);
//  delay(1000);

  //REVERSE
//  analogWrite(LH_MOTOR_Forward , 0);
//  analogWrite(LH_MOTOR_BACK , power);
//  analogWrite(RH_MOTOR_Forward , 0);
//  analogWrite(RH_MOTOR_BACK , power);
//  delay(1000);
//
//  //BREAK
//  analogWrite(LH_MOTOR_Forward , maxPower);
//  analogWrite(LH_MOTOR_BACK , maxPower);
//  analogWrite(RH_MOTOR_Forward , maxPower);
//  analogWrite(RH_MOTOR_BACK , maxPower);
//  delay(1000);
//
//
//  //RIGHT TURN
//  analogWrite(LH_MOTOR_Forward , power);
//  analogWrite(LH_MOTOR_BACK , 0);
//  analogWrite(RH_MOTOR_Forward , 0);
//  analogWrite(RH_MOTOR_BACK , power);
//
//
//  //BREAK
//  analogWrite(LH_MOTOR_Forward , maxPower);
//  analogWrite(LH_MOTOR_BACK , maxPower);
//  analogWrite(RH_MOTOR_Forward , maxPower);
//  analogWrite(RH_MOTOR_BACK , maxPower);
//  delay(1000);

}


void leftEncoderEvent() {
    if(digitalRead(LH_ENCODER_B) == LOW) { //Encoder moving Clockwise
      leftCount++;
    } else { //Encoder moving Counter Clockwise
      leftCount--;
    }
}

void rightEncoderEvent() {
    if(digitalRead(RH_ENCODER_B) == LOW) { //Encoder moving Clockwise
      rightCount++;
    } else { //Encoder moving Counter Clockwise
      rightCount--;
    }
}
