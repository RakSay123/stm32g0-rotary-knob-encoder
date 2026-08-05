#pragma once

#include "timer/timer_encoder/timer_encoder.h"

typedef enum {
	ROTARY_ENCODER_OK,
	ROTARY_ENCODER_ERR
} ROTARY_ENCODER_Status_t;

typedef struct {
	TIM_ENCODER_Config_t *encoder_cfg;
	uint32_t count;
	TIM_ENCODER_Direction_t direction;
} ROTARY_ENCODER_t;

ROTARY_ENCODER_Status_t rotary_encoder_init(ROTARY_ENCODER_t *cfg);

ROTARY_ENCODER_Status_t rotary_encoder_update(ROTARY_ENCODER_t *encoder);
