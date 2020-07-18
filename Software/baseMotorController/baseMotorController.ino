//pins for motors
#define RH_MOTOR_Forward 11 //RH = A on motorController
#define RH_MOTOR_BACK 10
#define LH_MOTOR_Forward 8 //LH = B on motorController
#define LH_MOTOR_BACK 9

//pins for encoder inputs
#define RH_ENCODER_A 2
#define RH_ENCODER_B 4
#define LH_ENCODER_A 3
#define LH_ENCODER_B 5

#define power 255
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
//  attachInterrupt(digitalPinToInterrupt(RH_ENCODER_A), rightEncoderEvent, CHANGE);
  attachInterrupt(digitalPinToInterrupt(LH_ENCODER_A), leftEncoderEvent, CHANGE);
}

void loop() {
  
  //Encoder looping code
//  Serial.print("Right Count: ");
//  Serial.println(rightCount);
//  Serial.print("Left Count: ");
//  Serial.println(leftCount);
//  Serial.println();
  

  //BREAK
  analogWrite(LH_MOTOR_Forward , maxPower);
  analogWrite(LH_MOTOR_BACK , maxPower);
  delay(1000);
  
  //FORWARD
  analogWrite(LH_MOTOR_Forward , power);
  analogWrite(LH_MOTOR_BACK , 0);
  delay(1000);

  Serial.println(leftCount);
  //BREAK
  analogWrite(LH_MOTOR_Forward , maxPower);
  analogWrite(LH_MOTOR_BACK , maxPower);
  delay(1000);
  
  //REVERSE
  analogWrite(LH_MOTOR_Forward , 0);
  analogWrite(LH_MOTOR_BACK , power);
  delay(1000);
  
  Serial.println(leftCount);
  
  //BREAK
  analogWrite(LH_MOTOR_Forward , maxPower);
  analogWrite(LH_MOTOR_BACK , maxPower);
  delay(1000);
  
}


//void leftEncoderEvent() {
//    if(digitalRead(LH_ENCODER_B) == LOW) { //Encoder moving Clockwise 
//      leftCount++;
//    } else { //Encoder moving Counter Clockwise 
//      leftCount--;
//    } 
//}


void leftEncoderEvent() {
  if (digitalRead(LH_ENCODER_A) == HIGH) {
    if(digitalRead(LH_ENCODER_B) == LOW) { //Encoder moving Clockwise 
      leftCount++;
    } else { //Encoder moving Counter Clockwise 
      leftCount--;
    } 
  } else {
      if (digitalRead(LH_ENCODER_B) == LOW) { //Encoder moving Clockwise 
        leftCount--;
      } else { //Encoder moving Counter Clockwise 
        leftCount++;
      }
  }
}

//void rightEncoderEvent() {
//  if (digitalRead(RH_ENCODER_A) == HIGH) {
//    if (digitalRead(RH_ENCODER_B) == LOW) { 
//      rightCount++;
//    } else {
//      rightCount--;
//    }
//  } else {
//    if (digitalRead(RH_ENCODER_B) == LOW) {
//      rightCount--;
//    } else {
//      rightCount++;
//    }
//  }
//}
