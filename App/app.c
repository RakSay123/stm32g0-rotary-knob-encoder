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

static uint32_t previous_toggle_ms;
static uint32_t previous_print_ms;

static bool rotary_encoder_update_success;


void app_init(void)
{
	rotary_encoder_update_success = rotary_encoder_set_count_zero(board_get_rotary_encoder()) == ROTARY_ENCODER_OK;

	uart_write_line(USART2, "SUCCESSFUL BOOT");
	systick_delay_s(2);

	previous_toggle_ms = millis();
	previous_print_ms = millis();
}

void app_update(void)
{
	uint32_t current_ms = millis();

	rotary_encoder_update_success = rotary_encoder_update(board_get_rotary_encoder()) == ROTARY_ENCODER_OK;

	if (current_ms - previous_toggle_ms >= APP_STATUS_LED_PERIOD_MS)
	{
		previous_toggle_ms = current_ms;
		led_toggle(board_get_status_led());
	}

	if (current_ms - previous_print_ms >= APP_ROTARY_ENCODER_PRINT_PERIOD_MS)
	{
		previous_print_ms = current_ms;

		if (rotary_encoder_update_success)
		{
			uart_write_str(USART2, "[ROTARY_ENCODER] Dir: ");
			if (board_get_rotary_encoder()->direction == TIM_ENCODER_DIRECTION_UP) uart_write_str(USART2, "UP | ");
			else uart_write_str(USART2, "DOWN | ");

			uart_write_str(USART2, "Cnt: ");
			uart_write_int(USART2, board_get_rotary_encoder()->total_count);
			uart_write_str(USART2, " | ");

			uart_write_str(USART2, "Revs: ");
			uart_write_float(USART2, board_get_rotary_encoder()->revolutions);
			uart_write_str(USART2, " | ");

			uart_write_str(USART2, "Cumulative: ");
			uart_write_float(USART2, board_get_rotary_encoder()->cumulative_angle_degrees);
			uart_write_str(USART2, " deg | ");

			uart_write_str(USART2, "Normalized: ");
			uart_write_float(USART2, board_get_rotary_encoder()->normalized_angle_degrees);
			uart_write_str(USART2, " deg | ");

			uart_write_str(USART2, "Displacement: ");
			uart_write_float(USART2, board_get_rotary_encoder()->displacement_mm);
			uart_write_str(USART2, " mm | ");

			uart_write_str(USART2, "Distance: ");
			uart_write_float(USART2, board_get_rotary_encoder()->total_distance_mm);
			uart_write_line(USART2, " mm");
		}
		else
		{
			uart_write_line(USART2, "[ROTARY_ENCODER] Update failed");
		}

		uart_write_line(USART2, "");
	}
}
