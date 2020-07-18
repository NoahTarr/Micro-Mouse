#include <PIDController.h>
volatile long int encoder_pos = 0;
PIDController pos_pid; 
int motor_value = 255;
#define RH_MOTOR_Forward 11 //RH = A on motorController
#define RH_MOTOR_BACK 10
#define LH_MOTOR_Forward 8 //LH = B on motorController
#define LH_MOTOR_BACK 9
void setup() {

  Serial.begin(9600);
  pinMode(2, INPUT);
  pinMode(5, INPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(2), encoder, RISING);

  pos_pid.begin();    
  pos_pid.tune(20, 0, 200);    
  pos_pid.limit(-255, 255);
}

void loop() {
pos_pid.setpoint((int)(((float)analogRead(A0)/1023) * 374.0 *1));
   motor_value = pos_pid.compute(encoder_pos);
//if(motor_value > 0){
//  MotorCounterClockwise(motor_value);
//}else{
//  MotorClockwise(abs(motor_value));
//}  //FORWARD
  analogWrite(LH_MOTOR_Forward , 255);
  analogWrite(LH_MOTOR_BACK , 0);
  delay(1000);
  Serial.println(encoder_pos);

  //BREAK
  analogWrite(LH_MOTOR_Forward , 255);
  analogWrite(LH_MOTOR_BACK , 255);
  delay(1000);

  
  //REVERSE
  analogWrite(LH_MOTOR_Forward , 0);
  analogWrite(LH_MOTOR_BACK , 255);
  delay(1000);
  Serial.println(encoder_pos);
  
  //BREAK
  analogWrite(LH_MOTOR_Forward , 255);
  analogWrite(LH_MOTOR_BACK , 255);
  delay(1000);


  delay(2);
}



void encoder(){

  if(digitalRead(5) == HIGH){
    encoder_pos++;
  }else{
    encoder_pos--;
  }
}

void MotorClockwise(int power){
  if(power > 50){
  analogWrite(8, power);
  digitalWrite(9, LOW);
  }else{
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
  }
}

void MotorCounterClockwise(int power){
  if(power > 50){
  analogWrite(9, power);
  digitalWrite(8, LOW);
  }else{
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
  }
}
