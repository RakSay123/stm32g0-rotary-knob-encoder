/*
 * Physical hardware descriptions.
 *
 * This file maps peripherals, GPIOs, timers, and devices
 * to the current board.
 */

#include "device_instances.h"

static LED_t status_led = {
	.port = GPIOA,
	.pin = 5,
	.mode = LED_MODE_GPIO,
};

static TIM_ENCODER_Config_t tim3_encoder_cfg = {
	.TIMx = TIM3,

	.channel_a_port = GPIOA,
	.channel_a_pin = 6,
	.channel_a_AF = GPIO_AF1,

	.channel_b_port = GPIOA,
	.channel_b_pin = 7,
	.channel_b_AF = GPIO_AF1,

	.mode = TIM_ENCODER_MODE_TI1_TI2_EDGES,

	.channel_a_filter = TIM_ENCODER_FILTER_NONE,
	.channel_b_filter = TIM_ENCODER_FILTER_NONE,

	.channel_a_psc = TIM_ENCODER_IC_PSC_NONE,
	.channel_b_psc = TIM_ENCODER_IC_PSC_NONE,

	.channel_a_polarity = TIM_ENCODER_POLARITY_NORMAL,
	.channel_b_polarity = TIM_ENCODER_POLARITY_NORMAL,
};

static ROTARY_ENCODER_t rotary_encoder_cfg = {
	.encoder_cfg = &tim3_encoder_cfg,
	.count = 0U,
	.direction = TIM_ENCODER_DIRECTION_UP
};


LED_t* board_get_status_led(void)
{
	return &status_led;
}

ROTARY_ENCODER_t* board_get_rotary_encoder(void)
{
	return &rotary_encoder_cfg;
}
