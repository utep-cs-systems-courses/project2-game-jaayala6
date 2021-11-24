#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "buzzer.h"
#include "switches.h"
#include "stateMachines.h"

int main(void){
  configureClocks();
  switch_init();
  led_init();
  buzzer_init();
  enableWDTInterrupts();

  or_sr(0x18);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*
  configureClocks();		// setup master oscillator, CPU & peripheral clocks
  enableWDTInterrupts();	// enable periodic interrupt 
  switch_init();
  led_init();  
  buzzer_init();
  //buzzer_set_period(1000);	// start buzzing!!!  
  or_sr(0x18);			// CPU off, GIE on 
}



//led-blink:
// global state var to count time
int secondCount = 0;

void
__interrupt_vec(WDT_VECTOR) WDT()	// 250 interrupts/sec 
{
  secondCount ++;
  if (secondCount >= 250) { 	// once each sec...
    secondCount = 0;		// reset count
    P1OUT ^= LED_GREEN;		// toggle green LED
  }
}
*/
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*
//blink-pattern:
// global state vars that control blinking
int blinkLimit = 5;  // duty cycle = 1/blinkLimit
int blinkCount = 0;  // cycles 0...blinkLimit-1
int secondCount = 0; // state var representing repeating time 0…1s

void
__interrupt_vec(WDT_VECTOR) WDT()	// 250 interrupts/sec
{
  // handle blinking 
  blinkCount ++;
  if (blinkCount >= blinkLimit) { // on for 1 interrupt period
    blinkCount = 0;
    P1OUT |= LED_GREEN;
  } else		          // off for blinkLimit - 1 interrupt periods
    P1OUT &= ~LED_GREEN;

  // measure a second
  secondCount ++;
  if (secondCount >= 250) {  // once each second
    secondCount = 0;
    blinkLimit ++;	     // reduce duty cycle
    if (blinkLimit >= 8)     // but don't let duty cycle go below 1/7.
      blinkLimit = 0;
  }
} 
*/
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


