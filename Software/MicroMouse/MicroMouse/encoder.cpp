//
// Our encoder: https://www.pololu.com/product/4760
// Our encoder disk: https://www.pololu.com/product/2599
// 12 Counts per Revolution of Motor Shaft (CRP_MS)
// CPR of Output Shaft (CPR_OS) = Motor Gear Ratio * CPM_MS
// CPR_OS = 75 * 12 = 900 CPR
//
// This position of the axle is altered based on RISING pulse of encoder pinA.
// The CPR counts 4 times each cycle/period.
// So 1 full rotation will occur at CPR/4 or 225 counts/rotation.

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
    digitalRead(pinB_) == LOW ? ++position_ : --position_;
}
