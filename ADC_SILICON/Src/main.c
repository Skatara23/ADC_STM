#include "stm32f4xx.h" // Include the appropriate STM32F4 header file

// Define the GPIO ports for the seven-segment display
#define GPIO_PORT_A (1 << 0)
#define GPIO_PORT_B (1 << 1)
#define GPIO_PORT_C (1 << 2)
#define GPIO_PORT_D (1 << 3)
#define GPIO_PORT_E (1 << 4)
#define GPIO_PORT_F (1 << 5)
#define GPIO_PORT_G (1 << 6)

// Function to display a digit on the seven-segment display
void displayDigit(uint8_t digit) {
  // Lookup table for common cathode seven-segment display
  uint8_t segments[10] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
  // Set the GPIO output data register
  GPIOA->ODR |= segments[digit];
}

int main(void) {
  // Enable the GPIOA peripheral clock
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

  // Configure the GPIO pins for the seven-segment display as outputs
  GPIOA->MODER |= GPIO_MODER_MODER0_0 | GPIO_MODER_MODER1_0 | GPIO_MODER_MODER2_0 | GPIO_MODER_MODER3_0 |
                  GPIO_MODER_MODER4_0 | GPIO_MODER_MODER5_0 | GPIO_MODER_MODER6_0;

  // Loop to display digits from 0 to 9 continuously
  while (1) {
    for (int i = 0; i < 10; i++) {
      displayDigit(i);

      // Delay for a certain period
      for (int delay = 0; delay < 1000000; delay++) {
        __asm__("nop"); // A simple delay loop
      }

      // Clear the GPIO output data register
      GPIOA->ODR &= ~(GPIO_PORT_A | GPIO_PORT_B | GPIO_PORT_C | GPIO_PORT_D | GPIO_PORT_E | GPIO_PORT_F | GPIO_PORT_G);
    }
  }
}
