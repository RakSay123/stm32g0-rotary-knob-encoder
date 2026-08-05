#include "rotary_encoder.h"
#include <stddef.h>

ROTARY_ENCODER_Status_t rotary_encoder_init(ROTARY_ENCODER_t *cfg)
{
	if (cfg == NULL || cfg->encoder_cfg == NULL) return ROTARY_ENCODER_ERR;

	if (timer_encoder_init(cfg->encoder_cfg) != TIM_OK) return ROTARY_ENCODER_ERR;

	if (timer_encoder_get_count(cfg->encoder_cfg, &cfg->count) != TIM_OK) return ROTARY_ENCODER_ERR;

	if (timer_encoder_get_direction(cfg->encoder_cfg, &cfg->direction) != TIM_OK) return ROTARY_ENCODER_ERR;

	return ROTARY_ENCODER_OK;
}

ROTARY_ENCODER_Status_t rotary_encoder_update(ROTARY_ENCODER_t *encoder)
{
	if (encoder == NULL || encoder->encoder_cfg == NULL) return ROTARY_ENCODER_ERR;

	if (timer_encoder_get_count(encoder->encoder_cfg, &encoder->count) != TIM_OK) return ROTARY_ENCODER_ERR;

	if (timer_encoder_get_direction(encoder->encoder_cfg, &encoder->direction) != TIM_OK) return ROTARY_ENCODER_ERR;

	return ROTARY_ENCODER_OK;
}

