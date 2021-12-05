#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"
#include "greenControlc.h"


char toggle_red(){ //toggle methods for the state machine, alwayys toggle
  static char state = 0;

  switch (state){
  case 0:
    red_on = 1;
    state = 1;
    break;
  case 1:
    red_on = 0;
    state = 0;
    break;
  }
  return 1;  //led always changes
}

char toggle_green(){ //green toggle is based on the red, only if red is on
  char changed = 0;
  if (red_on){
    green_on ^= 1;
    changed = 1;
  }
  return changed;
}

void led_state_advance(){
  char changed = 0;
  
  static enum {R=0,G=1} color = G;
  switch (color){      //state machine for led to blink back and forth
  case R: changed = toggle_red(); color = G; break;
  case G: changed = toggle_green(); color = R; break;
  }
  
  led_changed = changed;
  led_update();
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void switch_state_Machine(){
  switch (switch_state){
  case 1:
    buzzer_set_period(1300); //buzzer is set to a input when a certain button is pressed
    break;
  case 2:
    buzzer_set_period(200);
    break;
  case 3:
    no_buzzer();
    break;
  case 4:
    song();
    break;
  }

  led_update(); //after the state is set it will update the leds accordingly
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    // blink state machine
static int blinkLimit = 5;   //  state var representing reciprocal of duty cycle 
void blinkUpdate() // called every 1/250s to blink with duty cycle 1/blinkLimit
{
  static int blinkCount = 0; // state var representing blink state
  blinkCount ++;
  if (blinkCount >= blinkLimit) {
    blinkCount = 0;
    greenControl(1);
  } else
    greenControl(0);
  
}

void oncePerSecond() // repeatedly start bright and gradually lower duty cycle, one step/sec
{
  blinkLimit ++;  // reduce duty cycle
  if (blinkLimit >= 8)  // but don't let duty cycle go below 1/7.
    blinkLimit = 0;
}

void secondUpdate()  // called every 1/250 sec to call oncePerSecond once per second
{
  static int secondCount = 0; // state variable representing repeating time 0…1s
  secondCount ++;
  if (secondCount >= 250) { // once each second
    secondCount = 0;
    oncePerSecond();
  }
}

void timeAdvStateMachines() // called every 1/250 sec
{
  blinkUpdate();
  secondUpdate();
}
