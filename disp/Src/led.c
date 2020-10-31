#include "led.h"
#include "main.h"

#undef FORMAT_BCD
#undef FORMAT_BIN

uint32_t LEDs[LED_CNT];

#define SETP() do{HAL_GPIO_WritePin(LED_G,LED_P,GPIO_PIN_SET);}while(0)
#define RSTP() do{HAL_GPIO_WritePin(LED_G,LED_P,GPIO_PIN_RESET);}while(0)


inline void send0(void);
inline void send1(void);

volatile double sysclock = 0;  

int h0=0;
int h1=0;
int l0=0;
int l1=0;

void led_init(void){
	RSTP();
	HAL_Delay(1);
	
	sysclock = HAL_RCC_GetSysClockFreq();
	
	h0=sysclock*100/4000000000.0;
	l0=sysclock*450/4000000000.0;
	
	h1=sysclock*550/4000000000.0;
	l1=sysclock*0/4000000000.0;
	
	for(int i=0;i<LED_CNT;i++)LEDs[i]=0;
	
	leds_set(LEDs,LED_CNT);
}

void send0(void){
	SETP();
	for(register int i=0;i<h0;i++);
	RSTP();
	for(register int i=0;i<l0;i++);
}

void send1(void){
	SETP();
	for(register int i=0;i<h1;i++);
	RSTP();
	for(register int i=0;i<l1;i++);
}

void reset(void){
	HAL_Delay(1);
}

void led_set(uint32_t rgb){
	for(int i=15;i>7;i--){
		if(rgb&(1<<i))send1();
		else send0();
	}
	for(int i=23;i>15;i--){
		if(rgb&(1<<i))send1();
		else send0();
	}
	for(int i=7;i>-1;i--){
		if(rgb&(1<<i))send1();
		else send0();
	}
}

void leds_set(uint32_t* rgb,int cnt){
	for(int i=0;i<cnt;i++)
		led_set(rgb[i]);
	reset();
}

