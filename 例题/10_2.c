#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h> 
#include <avr/interrupt.h>
#include <util/delay.h>

#define SET_BIT(reg, pin)           (reg) |= (1 << (pin))
#define CLEAR_BIT(reg, pin)         (reg) &= ~(1 << (pin))
#define WRITE_BIT(reg, pin, value)  (reg) = (((reg) & ~(1 << (pin))) | ((value) << (pin)))
#define BIT_VALUE(reg, pin)         (((reg) >> (pin)) & 1)
#define BIT_IS_SET(reg, pin)        (BIT_VALUE((reg),(pin))==1)

/*
||  Define function pwm_init which sets up the registers required to perform simple
||  analogue output using Timer 0 to generate a PWM signal on an ATmega328P
||  microcontroller. 
||  
||  Parameter:
||      division_factor - a 16-bit unsigned integer by which the clock is
||          pre-scaled. Your function should carry out the appropriate initialisation
||          action for any value of division_factor in {1, 8, 64, 256, 1024}.
||  
||  Return: Nothing.
||  
||  Do this by adapting code from the lecture notes to complete the following
||  skeleton.
||  
||      ***************************************************************************
||  *** DO NOT ASSUME that the previous contents of timer control registers are 0   ***
||  *** when the function is called. If a particular bit is supposed to be zero, or ***
||  *** is listed in the datasheet as being reserved, make sure you clear it        ***
||  **  explicitly.                                                                 ***
||      ***************************************************************************
*/
void pwm_init( uint16_t division_factor ) {
    //  Configure the digital I/O pin corresponding to OCR0A for output. 
    //  Modify at most one pin in the DDR.
TCCR0A=0;
DDRD |= (1 << PD6);
TCCR0A|=(1<<COM0A1);    
    //  Update the value of TCCR0A so that register OC0A will clear on compare 
    //  match. 

    //  Update TCCR0B to disable Force Output Compare functionality.
if (division_factor==1)
{
TCCR0B=1;
}
else if (division_factor==8)
{
 TCCR0B=2;
}
else if (division_factor==64)
{
 TCCR0B=3;
}
else if (division_factor==256)
{
 TCCR0B=4;
}
else if (division_factor==1024)
{
TCCR0B=5;
}

    //  Update TCCR0B to ensure that the clock pre-scaler matches the 
    //  designated division factor.

    //  Update the values of TCCR0A and TCCR0B so that the Waveform Generation 
    //  Mode corresponds to Fast PWM with a Top value equal to 255.
    //
    //  Note from Lawrence: In TinkerCad I found it necessary to do this step 
    //  last to obtain the desired results. You may also get better results by 
    //  updating WGM01:0 in a single write instead of calling SET_BIT twice.
    TCCR0A |=(1<<WGM00)|(1<<WGM01);
}

/*
||  Complete function pwm_write which assigns a value to Output Compare Register 0A.
||  
||  Parameter: duration - an 8-bit unsigned integer which specifies the number of 
||      timer ticks in the duty cycle.
||  
||  Return: Nothing.
*/
void pwm_write( uint8_t duration ) {
    OCR0A = duration;
}

int main() {
    //  Desired clock scale factor for timer: .
    uint16_t divider = 256;

    //  Duration: number of timer ticks required for 25% duty cycle.
    uint16_t duration = 64; 

    pwm_init(divider);
    pwm_write(duration);

    for (;;) {
        //  Add code to interact with device here.
    }
}