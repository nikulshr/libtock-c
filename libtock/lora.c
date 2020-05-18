
/* Corresponds to LMIC -> radio.c */

#include "lora.h"
#include "timer.h"

const int RADIO_DRIVER = 0x30003;

//const int ALLOW_RX  = 0;
//const int ALLOW_TX  = 1;
//const int ALLOW_CFG = 2;
//
//const int SUBSCRIBE_RX = 0;
//const int SUBSCRIBE_TX = 1;

const int COMMAND_BEGIN        = 1;
const int COMMAND_BEGIN_PKT    = 2;
const int COMMAND_END_PKT      = 3;

// Temporary buffer used for some commands where the system call interface
// parameters / return codes are not enough te contain the required data.
// unsigned char BUF_CFG[27];

int lora_begin(uint64_t freq) {
  return command(RADIO_DRIVER, COMMAND_BEGIN, freq, 0) == TOCK_SUCCESS;
}

int lora_begin_packet(bool implicit_header) {
  return command(RADIO_DRIVER, COMMAND_BEGIN_PKT, implicit_header, 0) == TOCK_SUCCESS;
}

int lora_end_packet(bool asyn) {
  return command(RADIO_DRIVER, COMMAND_END_PKT, asyn, 0) == TOCK_SUCCESS;
}

