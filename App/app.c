/*
 * Application behavior belongs here.
 *
 * This file should describe what the firmware does,
 * not how peripherals are configured.
 */

#include "app.h"

#include <stdbool.h>

#include "app_config.h"
#include "device_instances.h"

#include "gpio/gpio.h"
#include "systick/systick.h"
#include "uart/uart.h"

#include "led/led.h"

static uint32_t previous_toggle_ms;
static uint32_t previous_print_ms;

static uint32_t a;
static uint32_t b;

uint32_t sms;

static bool rotary_encoder_update_success;


void app_init(void)
{
	uart_write_line(USART2, "SUCCESSFUL BOOT");
	systick_delay_s(2);

	a = 0xFFFFFFFF;
	b = 0xFFFFFFFF;

	rotary_encoder_update_success = false;

	previous_toggle_ms = millis();
	previous_print_ms = millis();
}

void app_update(void)
{
	uint32_t current_ms = millis();

	rotary_encoder_update_success = rotary_encoder_update(board_get_rotary_encoder()) == ROTARY_ENCODER_OK;

	a = (uint32_t)gpio_read(GPIOA, 6);
	b = (uint32_t)gpio_read(GPIOA, 7);

	if (current_ms - previous_toggle_ms >= APP_STATUS_LED_PERIOD_MS)
	{
		previous_toggle_ms = current_ms;
		led_toggle(board_get_status_led());
	}

	if (current_ms - previous_print_ms >= APP_ROTARY_ENCODER_PRINT_PERIOD_MS)
	{
		previous_print_ms = current_ms;

		uart_write_str(USART2, "[DEBUG] A: ");
		uart_write_int(USART2, a);
		uart_write_str(USART2, " | B: ");
		uart_write_int(USART2, b);
		uart_write_line(USART2, "");

		if (rotary_encoder_update_success)
		{
			uart_write_str(USART2, "[ROTARY_ENCODER] Count: ");
			uart_write_int(USART2, board_get_rotary_encoder()->count);
			uart_write_line(USART2, "");
			uart_write_str(USART2, "[ROTARY_ENCODER] Direction: ");

			if (board_get_rotary_encoder()->direction == TIM_ENCODER_DIRECTION_UP) uart_write_line(USART2, "UP");
			else uart_write_line(USART2, "DOWN");
		}
		else
		{
			uart_write_line(USART2, "[ROTARY_ENCODER] Update failed");
		}

		uart_write_line(USART2, "");
	}
}
