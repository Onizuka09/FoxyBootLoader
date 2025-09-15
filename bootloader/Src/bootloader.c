#include <stm32f407xx.h>
#include "led.h"
#define BOOTLOADER_SIZE (0x8000U)
#define APP_ADDR  (FLASH_BASE + BOOTLOADER_SIZE)
void do_somthing(int i){
	i++;
	i = i * 2;
}
static void jump_main(){
	// get the address of the reset handler, it the second item in the vetor table, hence +4 

	Led_init(); 
	uint32_t* reset_handler_entry= (uint32_t*)(APP_ADDR+4U ); 
	// get the address of the reset handler  
	uint32_t* reset_handler = (uint32_t*)(*reset_handler_entry);
	typedef void (*void_fptr)(void) ; 
	void_fptr jump_reset_handler = (void_fptr)reset_handler ; 
	
	TurOn_led(); 
	
	jump_reset_handler();

}

int main(void)
{
	 jump_main();

	while (1)
	{

		/* code */
	}
	
	return 0;
}
