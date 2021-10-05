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
#define section 3

void set_LED (int LED_num, int val) { //val = 0 is off, val = 1 is on, val = 2 is all LEDs off
	int port = 0;
	switch(LED_num) {
		case 1:
			LED_num = 28;
			port = 1;
			break;
		case 2:
			LED_num = 29;
			port = 1;
			break;
		case 3:
			LED_num = 31;
			port = 1;
			break;
		case 4:
			LED_num = 2;
			port = 2;
			break;
		case 5:
			LED_num = 3;
			port = 2;
			break;
		case 6:
			LED_num = 4;
			port = 2;
			break;
		case 7:
			LED_num = 5;
			port = 2;
			break;
		case 8:
			LED_num = 6;
			port = 2;
			break; 
	}
	LPC_GPIO1->FIODIR |= ((1u << 28) | (1u << 29) | (1u << 31));
	LPC_GPIO2->FIODIR |= ((1u << 2) | (1u << 3) | (1u << 4) | (1u << 5) | (1u << 6));

	if(val==2 )	{//all LEDs off
		LPC_GPIO1->FIOCLR |= ((1u << 28) | (1u << 29) | (1u << 31));
		LPC_GPIO2->FIOCLR |= ((1u << 2) | (1u << 3) | (1u << 4) | (1u << 5) | (1u << 6));
		return;
	}
	else if (val==1 && port==1) {	//LED on
		LPC_GPIO1->FIOCLR |= (1u << LED_num);
		LPC_GPIO1->FIOSET |= (1u << LED_num);
	}
	else if(val==1 && port==2) {	//LED on
		LPC_GPIO2->FIOCLR |= (1u << LED_num);
		LPC_GPIO2->FIOSET |= (1u << LED_num);
	}
	else if(val==0 && port==1)	//LED off
		LPC_GPIO1->FIOCLR = (1u << LED_num);
	else	//LED off
		LPC_GPIO2->FIOCLR = (1u << LED_num);
}

#if section == 1
int main(void) //1. push button LED
{
SystemInit();
set_LED(0,2); //set all LEDs off
while(1){
if((LPC_GPIO2->FIOPIN & (1u << 10))) {//set LED off
	set_LED(1,0);
}
else { //set LED on
	set_LED(1,1);
}
}
}
#elif section == 2
int main(void) //2. joystick
{
SystemInit();
while(1){
//Joystick direction
if(!(LPC_GPIO1->FIOPIN & (1u << 23))) { //checks if joystick north
	printf("North");
}
else if(!(LPC_GPIO1->FIOPIN & (1u << 26))) { //checks if joystick west
	printf("West");
}
else if(!(LPC_GPIO1->FIOPIN & (1u << 25))) { //checks if joystick south
	printf("South");
}
else if(!(LPC_GPIO1->FIOPIN & (1u << 24))) { //checks if joystick east
	printf("East");
}
else {
	printf("Centered");
}
//Joystick button
if(!(LPC_GPIO1->FIOPIN & (1u << 20))) {//checks if joystick pressed
	printf(" and joystick is pressed\n");
}
else {
	printf(" and joystick is not pressed\n");
}
}
}
#elif section == 3
int main(void) //3. uart LED
{
SystemInit();
UARTInit(1, 115200);
set_LED(0,2); //set all LEDs off
while(1){
	int curr_input = 0;
	int input_sum = 0;
	while(curr_input != 10) {
		curr_input = UARTReceiveChar(1);
		if(curr_input != 10)
			input_sum = 10*input_sum+(curr_input-48);
	}
	set_LED(0,2);
	for(int i=0; i<8; i++) {
		int bitmask = (1u << i);
		if((input_sum & (1u << i))) {
			set_LED(8-i,1);
		}
	}
}
}
#endif
