#pragma once

#include "timer/timer_encoder/timer_encoder.h"
#include <stdbool.h>

typedef enum {
	ROTARY_ENCODER_OK,
	ROTARY_ENCODER_ERR
} ROTARY_ENCODER_Status_t;

typedef struct {
	TIM_ENCODER_Config_t *encoder_cfg;

	float radius_mm;

	uint32_t pulses_per_revolution;
	uint32_t counts_per_revolution;

	uint16_t raw_count;
	uint16_t previous_raw_count;
	int16_t delta_count;
	int32_t total_count;

	float revolutions;
	float cumulative_angle_degrees;
	float normalized_angle_degrees;

	float displacement_mm;
	float total_distance_mm;

	TIM_ENCODER_Direction_t direction;
} ROTARY_ENCODER_t;

ROTARY_ENCODER_Status_t rotary_encoder_init(ROTARY_ENCODER_t *cfg);

ROTARY_ENCODER_Status_t rotary_encoder_update(ROTARY_ENCODER_t *encoder);

ROTARY_ENCODER_Status_t rotary_encoder_set_count(ROTARY_ENCODER_t *encoder, uint32_t cnt);

ROTARY_ENCODER_Status_t rotary_encoder_set_count_median(ROTARY_ENCODER_t *encoder);

ROTARY_ENCODER_Status_t rotary_encoder_set_count_zero(ROTARY_ENCODER_t *encoder);
