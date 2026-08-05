/*
 * Accessors for board-specific hardware instances.
 *
 * Applications should retrieve devices through these functions
 * rather than referencing global objects directly.
 */

#pragma once

#include "led/led.h"
#include "rotary_encoder/rotary_encoder.h"

LED_t* board_get_status_led(void);

ROTARY_ENCODER_t* board_get_rotary_encoder(void);
