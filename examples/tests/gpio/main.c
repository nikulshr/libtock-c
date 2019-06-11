/* vim: set sw=2 expandtab tw=80: */

/* This application can operate in three modes: input, output
 * or interrupt. The mode is set as a constant in main().
 *   - Output mode uses the pin connected to LED 0 (through the led()
 *   system call interface.
 *   - Input mode uses userspace GPIO pin 0 (the 0th pin made available
 *   to userspace programs. Consult the boot sequence of your board or
 *   its documentation to determine which hardware pin this is.
 *   - Interrupt mode uses userspace GPIO pin 0 (see input mode above).
 *   It executes a callback when the pin goes from low to high. To test
 *   this, connect the pin to Vdd.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <console.h>
#include <gpio.h>
#include <led.h>
#include <timer.h>
#include <tock.h>

// callback for timers
static void timer_cb (__attribute__ ((unused)) int arg0,
                      __attribute__ ((unused)) int arg1,
                      __attribute__ ((unused)) int arg2,
                      __attribute__ ((unused)) void* userdata) {}

// **************************************************
// GPIO output example: toggles LED.
// **************************************************
static void gpio_output(void) {
  printf("Periodically blinking LED\n");

  // Start repeating timer
  tock_timer_t timer;
  timer_every(500, timer_cb, NULL, &timer);

  while (1) {
    led_toggle(0);
    yield();
  }
}

// **************************************************
// GPIO input example: reads userspace pin 0.
// **************************************************
static void gpio_input(void) {
  printf("Periodically reading value of the GPIO 0 pin\n");
  printf("Jump pin high to test (defaults to low)\n");

  // set userspace pin 0 as input and start repeating timer
  // pin is configured with a pull-down resistor, so it should read 0 as default
  gpio_enable_input(0, PullDown);
  tock_timer_t timer;
  timer_every(500, timer_cb, NULL, &timer);

  while (1) {
    // print pin value
    int pin_val = gpio_read(0);
    printf("\tValue(%d)\n", pin_val);
    yield();
  }
}

// **************************************************
// GPIO interrupt example
// **************************************************
static void gpio_cb (__attribute__ ((unused)) int pin_num,
                     __attribute__ ((unused)) int arg2,
                     __attribute__ ((unused)) int arg3,
                     __attribute__ ((unused)) void* userdata) {}

static void gpio_interrupt(void) {
  printf("Print userspace GPIO 0 pin reading whenever its value changes\n");
  printf("Jump pin high to test\n");

  // set callback for GPIO interrupts
  gpio_interrupt_callback(gpio_cb, NULL);

  // set userspace pin 0 as input and enable interrupts on it
  gpio_enable_input(0, PullDown);
  gpio_enable_interrupt(0, Change);

  while (1) {
    yield();
    printf("\tGPIO Interrupt!\n");
  }
}


int main(void) {
  printf("*********************\n");
  printf("GPIO Test Application\n");

  // Set mode to which test you want
  uint8_t mode = 0;

  switch (mode) {
    case 0: gpio_interrupt(); break;
    case 1: gpio_output(); break;
    case 2: gpio_input(); break;
  }

  return 0;
}
