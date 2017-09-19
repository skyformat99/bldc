#include "pwm.h"

void set_duty_cycle(byte dc) {
  OCR0A = dc;
  OCR0B = dc;
  OCR2A = dc;
}


/* Set up Timer0 and Timer2 as phase correct PWM outputs
 * Maximum frequency (~32KHz)
 * All PWM outputs initially disabled
 */
void setup_pwm() {
  TCCR0A = _BV(WGM00);              //phase correct pwm. Initially both pwm outputs disabled
  TCCR2A = _BV(WGM20);
  TCCR0B = _BV(CS00);               //clock prescaler = 1 -> 16MHz/(2**8)/2 = 32KHz
  TCCR2B = _BV(CS20);
  TCNT0 = 0;                        //reset the timers
  TCNT2 = 0;                        //reset the timers
}


/* Start PWM output on a given pin (EN1, EN2 or EN3)
 * must be called once for each pin you want to start
 * setup_pwm() must be called first
 */
void start_pwm(byte pin){
  if(pin == EN1){
    TCCR2A |= _BV(COM2A1);
  }else if(pin == EN2){
    TCCR0A |= _BV(COM0A1);
  }else if(pin == EN3){
    TCCR0A |= _BV(COM0B1);
  }
}


/* Stop PWM output on a given pin (EN1, EN2 or EN3) and set it to LOW
 * must be called once for each pin you want to start
 * setup_pwm() must be called first
 */
void stop_pwm(byte pin){
  if(pin == EN1){
    TCCR2A &= ~(_BV(COM2A1));
    digitalWrite(EN1, LOW);
  }else if(pin == EN2){
    TCCR0A &= ~(_BV(COM0A1));
    digitalWrite(EN2, LOW);
  }else if(pin == EN3){
    TCCR0A &= ~(_BV(COM0B1));
    digitalWrite(EN3, LOW);
  }
}


