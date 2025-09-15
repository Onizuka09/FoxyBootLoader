#include "led.h"
#define BOOTLOADER_SIZE (0x8000U)
#define APP_START_ADDRESS (0x08000000U + 0x8000U) // Bootloader origin + bootloader size
void do_somthing(int i) ;

static void setup_vectable(){
	SCB->VTOR = BOOTLOADER_SIZE ; 
}
int main(void)
{
	setup_vectable();
    Led_init();
    TurOn_led();
	while (1)
		{
			Toggle_led();
			for (int i = 0; i < 100000; i++)
			{
				do_somthing(i);		
			}
		}
return 0;
}
void do_somthing(int i){
	i++;
	i = i * 2;
}