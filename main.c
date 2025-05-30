#include <stdint.h>

// RCC base address (Reset and Clock Control)
#define RCC_BASE        0x40021000
#define RCC_APB2ENR     (*(volatile uint32_t *)(RCC_BASE + 0x18))

// GPIOC base address
#define GPIOC_BASE      0x40011000
#define GPIOC_CRH       (*(volatile uint32_t *)(GPIOC_BASE + 0x04))
#define GPIOC_ODR       (*(volatile uint32_t *)(GPIOC_BASE + 0x0C))

extern uint32_t _estack;
void Reset_Handler(void);

__attribute__((section(".isr_vector")))
const void *vector_table[] = {
    &_estack,
    Reset_Handler,
};

// Simple delay loop
void delay(volatile uint32_t count) {
  while (count--) {
    __asm__("nop");
  }
}

int main(void) {
  // Enable GPIOC clock (IOPCEN bit in RCC_APB2ENR)
  RCC_APB2ENR |= (1 << 4);

  // Configure PC13 as push-pull output (50 MHz)
  // CRH controls pins 8–15; PC13 is bits 20–23
  GPIOC_CRH &= ~(0xF << 20);        // Clear CNF13[1:0] + MODE13[1:0]
  GPIOC_CRH |=  (0x3 << 20);        // Set MODE13 = 0b11 (output 50 MHz), CNF13 = 0b00 (push-pull)

  while (1) {
    GPIOC_ODR ^= (1 << 13);       // Toggle PC13
    delay(500000);                // Rough delay
  }

  return 0;
}

void Reset_Handler(void) {
    main();
    while (1);
}
