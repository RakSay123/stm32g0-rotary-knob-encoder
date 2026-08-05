/*
 * Hardware initialization.
 *
 * Initializes board resources in dependency order and reports
 * failures through BOARD_Status_t.
 */

#include "board_init.h"

#include <stdint.h>
#include <stddef.h>

#include "board_config.h"
#include "device_instances.h"

#include "gpio/gpio.h"
#include "systick/systick.h"
#include "timer/timer.h"
#include "timer/timer_encoder/timer_encoder.h"
#include "uart/uart.h"

#include "led/led.h"
#include "rotary_encoder/rotary_encoder.h"

GPIO_Config_t usart2_tx = {
	.port = GPIOA,
	.pin = 2,
	.mode = GPIO_MODE_AF,
	.otype = GPIO_PUSH_PULL,
	.speed = GPIO_SPEED_HIGH,
	.pull = GPIO_NO_PULL,
	.alternate = GPIO_AF1
};

GPIO_Config_t usart2_rx = {
	.port = GPIOA,
	.pin = 3,
	.mode = GPIO_MODE_AF,
	.otype = GPIO_PUSH_PULL,
	.speed = GPIO_SPEED_HIGH,
	.pull = GPIO_NO_PULL,
	.alternate = GPIO_AF1
};

TIM_Config_t tim3_cfg = {
	.TIMx = TIM3,
	.psc = BOARD_TIM3_PSC,
	.arr = BOARD_TIM3_ARR,
	.cnt = BOARD_TIM3_CNT,
	.interrupt_status = TIM_INTERRUPTS_DISABLED
};

UART_Config_t usart2_cfg = {
	.USARTx = USART2,
	.fclk = BOARD_FCLK_HZ,
	.baud_rate = BOARD_DEBUG_UART_BAUD,
};

BOARD_Status_t board_init(void)
{
	LED_t *status_led = board_get_status_led();
	if (status_led == NULL) return BOARD_STATUS_LED_ERROR;

	ROTARY_ENCODER_t *rotary_encoder = board_get_rotary_encoder();
	if (rotary_encoder == NULL) return BOARD_STATUS_ROTARY_ENCODER_ERROR;

	gpio_init(&usart2_tx);
	gpio_init(&usart2_rx);

	systick_init(BOARD_FCLK_HZ / BOARD_SYSTICK_HZ);

	if (timer_init(&tim3_cfg) != TIM_OK) return BOARD_STATUS_TIM3_ERROR;

	uart_init(&usart2_cfg);

	led_init(status_led); // void return type at the moment

	if (rotary_encoder_init(rotary_encoder) != ROTARY_ENCODER_OK) return BOARD_STATUS_ROTARY_ENCODER_ERROR;

	return BOARD_STATUS_OK;
}
