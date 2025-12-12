/*
 * sweater.h
 *
 *  Created on: 11 dic. 2025
 *      Author: Luis
 */

#ifndef SWEATER_H_
#define SWEATER_H_

#include "led_WS2812B.h"

typedef enum _state_machine_sweater_t
{
	k_state_machine_efect_color_tree,
	k_state_machine_efect_wy_tree_1,
	k_state_machine_efect_wy_tree_2,
	k_state_machine_efect_epilepsia,
	k_state_machine_efect_white,
	k_state_machine_efect_spiral,
	k_state_machine_efect_rainbow,
	k_state_machine_efect_celebration,
} state_machine_sweater_t;


void effect_color_tree(led_ws2812b_rgb_t led_array[N_LEDS]);
void effect_wy_tree_1(led_ws2812b_rgb_t led_array[N_LEDS]);
void effect_wy_tree_2(led_ws2812b_rgb_t led_array[N_LEDS]);
void effect_epilepsia(led_ws2812b_rgb_t led_array[N_LEDS]);
void effect_white(led_ws2812b_rgb_t led_array[N_LEDS]);
void effect_spiral(led_ws2812b_rgb_t led_array[N_LEDS]);
void effect_rainbow(led_ws2812b_rgb_t led_array[N_LEDS]);
void effect_celebration(led_ws2812b_rgb_t led_array[N_LEDS]);


#endif /* SWEATER_H_ */
