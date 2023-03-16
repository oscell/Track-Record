#include <iostream>
#include <bcm2835.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

using namespace std;

void move(int angle,int prev_angle, int hold, int align)
{
	int pulse;
	int i;
	float Angle;
	float on_time = 10.3*angle+340; // default original: 10.3*angle+546
	char c;
	
	if (hold==1)
	{
		std::cout << ("Holding motor") << std::endl;
		while(1)
		{
			bcm2835_gpio_set(18); // setting pin 18 to high
			bcm2835_delayMicroseconds(on_time); // leaving it on high for time specified
			bcm2835_gpio_clr(18); // setting pin 18 to low
			bcm2835_delayMicroseconds(20000 - on_time); // 20000 = 20ms
		}
	}
	if (hold==0)
	{
		if (align==1)
		{
			pulse = 40; // pulse width ~ 33 gives 180 deg rotation (needs tuning)
		}
		else
		{
			pulse = (int)abs(((angle-prev_angle)*40)/180) + 5;
		}
		for(i=0;i<pulse;i++)
		{
			bcm2835_gpio_set(18); // setting pin 18 to high
			bcm2835_delayMicroseconds((int)on_time); // leaving it on high for time specified
			bcm2835_gpio_clr(18); // setting pin 18 to low
			bcm2835_delayMicroseconds(20000 - (int)on_time); // 20000 = 20ms
		}
	}
}

int main(int argc, char** argv)
{
	if(!bcm2835_init())
	{
		cout << ("motor not initialised") << endl;
	}
	
	int angle;
	int prev_angle;
	int pulse;
	//int j;
	char input[5];
	
	bcm2835_gpio_fsel(18, BCM2835_GPIO_FSEL_OUTP); // setting pin 18 as output in main function
	
	int user_angle = 0; // defining user angle
	move(0,0,0,1); // initially moving to 0 degrees (default)
	prev_angle = 0;
	while(1)
	{
		cout << ("Enter integer for angle rotation") << endl; // asking user to input
		cin >> user_angle;
		
		angle = user_angle;
		move(angle, prev_angle, 0, 0);
		prev_angle = angle;
	}
return 0;
}

