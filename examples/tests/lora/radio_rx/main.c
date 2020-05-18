#include <stdio.h>
#include <stdbool.h>

#include "tock.h"
#include "lora.h"
#include "timer.h"
//#include "led.h"

// Lora sample packet transmission app.

//#define BUF_SIZE 256
//char packet[BUF_SIZE];

# define EXIT_ON_FAIL(stmt,msg) if (!stmt) { printf(msg); return 0; }

int main(void) {
  EXIT_ON_FAIL(lora_begin(DEFAULT_FREQ), "Can't begin!\n");
  while (1) {
    EXIT_ON_FAIL(lora_begin_packet(IMPLICIT_HEADER), "Can't begin packet!\n");
    printf("Sending packet...\n");
    delay_ms(1);
    EXIT_ON_FAIL(lora_end_packet(SYNC), "Can't end packet!\n"); ;
    printf("Transmitted successfully.\n");
    delay_ms(1);
  }
  return 0;
}
