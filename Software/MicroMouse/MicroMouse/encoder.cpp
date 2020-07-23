// 
// 
// 

#include "encoder.h"

encoder::encoder (int pinA, int pinB) 
{
    this->pinA_ = pinA;
    this->pinB_ = pinB;
    this->position_ = 0;
    pinMode(pinA, INPUT);
    pinMode(pinB, INPUT);
    //Turn on pullup encoder pullup resistors
    digitalWrite(pinA, HIGH);
    digitalWrite(pinB, HIGH);
    if (interruptObject0_ == nullptr)
    {
        attachInterrupt(digitalPinToInterrupt(pinA), glueFunction0, RISING);
        interruptObject0_ = this;
    }
    else
    {
        attachInterrupt(digitalPinToInterrupt(pinA), glueFunction1, RISING);
        interruptObject1_ = this;
    }
}


int encoder::getPosition() const
{
    return this->position_;
}


void encoder::setPosition(int position)
{
    this->position_ = position;
}


encoder* encoder::interruptObject0_ = nullptr;
encoder* encoder::interruptObject1_ = nullptr;

void encoder::glueFunction0()
{
    interruptObject0_->encoderEvent();
}

void encoder::glueFunction1()
{
    interruptObject1_->encoderEvent();
}


void encoder::encoderEvent() {
    if (digitalRead(pinB_) == LOW) { //Encoder moving Clockwise
        position_++;
    }
    else { //Encoder moving Counter Clockwise
        position_--;
    }
}
