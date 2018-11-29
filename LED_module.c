#include "LPC17xx.H" // LPC17xx definitions

void delay(int count) {
	int i;
	for (i = 0; i < count; i++); //Just count for delay
}
int led_button(int value){
	int val = 1;
	int i;
	for(i=0;i<value;i++)val *= 2;
	return val;
}
int main (void) {
	int mask_val = 0x800;
	int mask_val2 = 0x1000;
	int delayer;
	int on_val = 0;
	int val;
	int count =0;
	int count2 = 8;
	int count3 =8;
	int mode =0;
	int speed_mode =0;
	LPC_GPIO2->FIODIR = 0x000000FF; // P2.0, P2.1,...P2.7 pins/LEDs on port2 set as output
	//turn on/off the LED driven by P2.0;
	while (1) { //infinite loop
		int led;
		if((LPC_GPIO2->FIOPIN & mask_val) == on_val) mode++; //change state based on which button is pushed on the board
		if((LPC_GPIO2->FIOPIN & mask_val2) == on_val)speed_mode++; //change speed based on which button is pushed on the board
		switch(speed_mode){
			case 0:
				delayer = 12000000;
				break;
			case 1:
				delayer = 900000;
				break;
			case 2:
				delayer = 700000;
				break;
			case 3:
				delayer = 600000;
				speed_mode = 0;
				break;
		}
		switch(mode){
			case 0:
				led = led_button(count);
				LPC_GPIO2->FIOPIN |= led;
				delay(delayer); // delay of about 1 s implemented in software;
				LPC_GPIO2->FIOPIN &= ~led;
				delay(delayer);
				count++;
				if(count == 8)count =0;
				break;
			case 1:
				led =led_button(count2);
				LPC_GPIO2->FIOPIN |= led;
				delay(12000000); // delay of about 1 s implemented in software;
				LPC_GPIO2->FIOPIN &= ~led;
				delay(12000000);
				count2--;
				if(count2 <0)count2 = 8;
				break;

			case 2:
				if(count3<0){
					val=count3 * -1;
					led =led_button(val);
					LPC_GPIO2->FIOPIN |= led;
					delay(delayer); // delay of about 1 s implemented in software;
					LPC_GPIO2->FIOPIN &= ~led;
					delay(delayer);
					count3--;
					if(count3 == -8)count3 =8;
				}else{
				 	led =led_button(count3);
				 	LPC_GPIO2->FIOPIN |= led;
					delay(delayer); // delay of about 1 s implemented in software;
					LPC_GPIO2->FIOPIN &= ~led;
					delay(delayer);
					count3--;
					if(count3 <0)count3 = -1;
					
				}
				break;
			case 3:
				LPC_GPIO2->FIOPIN |= 0x1ff;
				delay(delayer); // delay of about 1 s implemented in software;
				LPC_GPIO2->FIOPIN &= ~0x1ff;
				delay(delayer);
				break;
		}


  }
}
