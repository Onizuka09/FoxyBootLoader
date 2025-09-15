#include "led.h"
#include <stdint.h>

#define PIN13 (1U << 13)
#define LED_pin PIN13
void Led_init(){
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN ; 
    GPIOD->MODER |= (1U << 26);
    GPIOD->MODER &= ~(1U << 27);
}
void Toggle_led(){

    GPIOD->ODR ^= LED_pin;
}
void TurOn_led(){
    GPIOD->ODR |= LED_pin;
}
void TurOff_led(){
    GPIOD->ODR &= ~LED_pin;
}