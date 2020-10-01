// encoder.h

#ifndef _ENCODER_h
#define _ENCODER_h

#include <Arduino.h>

class encoder
{
public:
    encoder(int pinA, int pinB);
    int getPosition() const;
    void setPosition(int position);

private:
    int pinA_;
    int pinB_;
    volatile int position_;

    //The 2 interrupt objects and glue functions are used to attach interrupts to both encoders.
    //If more interrupts are needed simply duplicate the objects and glue functions and rename them. Then edit the constructor to account for the new ones.
    static encoder* interruptObject0_;
    static encoder* interruptObject1_;
    static void glueFunction0();
    static void glueFunction1();
    void encoderEvent();
};

extern encoder Encoder;

#endif

