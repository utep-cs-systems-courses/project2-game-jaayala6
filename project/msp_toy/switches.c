#include <msp430.h>
#include "switches.h"
#include "led.h"
#include "buzzer.h"
#include "stateMachines.h"

switch_state = 0;
char switch1_state_down,switch2_state_down,switch3_state_down,switch4_state_down, switch_state_changed;

static char
switch_update_interrupt_sense(){
  char p2val = P2IN;
  P2IES |= (p2val & SWITCHES);
  P2IES &= (p2val | ~SWITCHES);
  return p2val;
}

void
switch_init(){
  P2REN |= SWITCHES;
  P2IE = SWITCHES;
  P2OUT |= SWITCHES;
  P2DIR &= ~SWITCHES;
  switch_update_interrupt_sense();
}

void
switch_interrupt_handler(){
  char p2val = switch_update_interrupt_sense();

  switch1_state_down = (p2val & SW1) ? 0 : 1; //tells which button of the 4 were pressed
  switch2_state_down = (p2val & SW2) ? 0 : 1;
  switch3_state_down = (p2val & SW3) ? 0 : 1;
  switch4_state_down = (p2val & SW4) ? 0 : 1;

  //10-switch-full-modular
  if (switch1_state_down) {
    switch_state = 1;
  }
  //7-blink-file-modular
  if (switch2_state_down)
    switch_state = 2;

  //assy
  if (switch3_state_down)
    switch_state = 3;

  //buzzer-song
  if (switch4_state_down)
    switch_state = 4;

  switch_state_changed = 1; //make sure to show a button was pressed
}
