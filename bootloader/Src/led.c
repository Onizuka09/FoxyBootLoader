#include "led.h"
#include <stdint.h>
#define GPIOA_en (1U << 0) // enable the clock source (set 1 at pos 0)

#define PIN5 (1U << 5)
#define LED_pin PIN5
void Led_init(){
    RCC->AHB1ENR |= GPIOA_en;
    GPIOA->MODER |= (1U << 10);
    GPIOA->MODER &= ~(1U << 11);
}
void Toggle_led(){

    GPIOA->ODR ^= LED_pin;
}
void TurOn_led(){
    GPIOA->ODR |= LED_pin;
}
void TurOff_led(){
    GPIOA->ODR &= ~LED_pin;
}