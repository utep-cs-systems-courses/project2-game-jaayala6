#ifndef led_included
#define led_included

#define LED_RED BIT6
#define LED_GREEN BIT0
#define LEDS (BIT6 | BIT0)

extern unsigned char red_on,green_on;
extern unsigned char led_changed;

void led_init();
void led_update();
void greenControl(int on);

#endif
