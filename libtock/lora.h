
/* Corresponds to LMIC -> radio.c */

#pragma once

#include <stdbool.h>
#include "tock.h"

/* Lora system call interface */

#ifdef __cplusplus
extern "C" {
#endif

#define DEFAULT_FREQ 865000000
#define IMPLICIT_HEADER true
#define EXPLICIT_HEADER false
#define SYNC true
#define ASYNC false

int lora_begin(uint64_t freq);
int lora_begin_packet(bool implicit_header);
int lora_end_packet(bool asyn);

#ifdef __cplusplus
}
#endif
