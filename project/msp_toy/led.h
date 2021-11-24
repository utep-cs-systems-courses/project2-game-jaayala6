#ifndef led_included
#define led_included

#define LED_RED BIT6               // P1.6 0000 0001
#define LED_GREEN BIT0             // P1.0 0100 0001
#define LEDS (BIT0 | BIT6)

// these are boolean flags
extern unsigned char led_changed, green_on, red_on;
void led_init();
void led_update();

#endif // included
