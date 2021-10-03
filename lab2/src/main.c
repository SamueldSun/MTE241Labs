#include <LPC17xx.h>
#include "stdio.h"
#include "uart.h"

/* Pins 
Pushbutton: P2.10
Leftmost LED: P1.28
Rightmost LED: P2.6
Joystick button: P1.20
Joystick N: P1.23
Joystick W: P1.26
Joystick S: P1.25
Joystick E: P1.24
*/

//section selection
#define section 2

void set_LED (int LED_num, int val) {
	LPC_GPIO1->FIODIR |= ((1u << 28) | (1u << 29) | (1u << 31));
	LPC_GPIO2->FIODIR |= ((1u << 2) | (1u << 3) | (1u << 4) | (1u << 5) | (1u << 6));
	LPC_GPIO1->FIOCLR |= ((1u << 28) | (1u << 29) | (1u << 31));
	LPC_GPIO2->FIOCLR |= ((1u << 2) | (1u << 3) | (1u << 4) | (1u << 5) | (1u << 6));
	
	if (val==1) { //LED on
		LPC_GPIO1->FIOCLR |= (1u << LED_num);
		LPC_GPIO1->FIOSET |= (1u << LED_num);
	}
	else { //LED off
		LPC_GPIO1->FIOCLR = (1u << LED_num);
	}
}

#if section == 1
int main(void) //1. push button LED
{
SystemInit();
while(1){
if((LPC_GPIO2->FIOPIN & (1u << 10))) {//set LED off
	set_LED(28,0);
}
else { //set LED on
	set_LED(28,1);
}
}
}
#elif section == 2
int main(void) //1. push button LED
{
SystemInit();
while(1){
if((LPC_GPIO2->FIOPIN & (1u << 10))) {//set LED off
	set_LED(28,0);
}
else { //set LED on
	set_LED(28,1);
}
}
}
#endif
