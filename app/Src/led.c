#include "led.h"
#include <stdint.h>

#define PIN12 (1U << 12)
#define LED_pin PIN12
void Led_init(){
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN ; 
    GPIOD->MODER |= (1U << 24);
    GPIOD->MODER &= ~(1U << 25);
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