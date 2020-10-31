#ifndef __LED_H__
#define __LED_H__

#define LED_G GPIOB
#define LED_P GPIO_PIN_9

#define LED_CNT 60

#include "stdint.h"

extern uint32_t LEDs[];

inline void led_set(uint32_t rgb);
void leds_set(uint32_t* rgb,int cnt);
void led_init(void);
#endif
