#include "sweater.h"

void effect_color_tree(led_ws2812b_rgb_t led_array[N_LEDS])
{
	const led_ws2812b_rgb_t color[] =
	{
			{.r = 255, .g = 0, .b = 0},
			{.r = 0, .g = 255, .b = 0},
			{.r = 0, .g = 0, .b = 255}
	};
	const uint32_t color_repeat[] =
	{
			0,
			0,
			0
	};
	static uint32_t step = 0;

	led_ws2812b_fill_array_with_pattern(led_array,
										step,
										(led_ws2812b_rgb_t*)color,
										3,
										(uint32_t*)color_repeat,
										1,
										1,
										255);
	step = (step >= (N_LEDS))? 0:(step + 1);
}

void effect_wy_tree_1(led_ws2812b_rgb_t led_array[N_LEDS])
{
	const led_ws2812b_rgb_t color[] =
	{
			{.r = 255, .g = 100, .b = 0},
			{.r = 200, .g = 200, .b = 200}
	};
	const uint32_t color_repeat[] =
	{
			0,
			0,
	};
	static uint32_t step = 0;

	led_ws2812b_fill_array_with_pattern(led_array,
										step,
										(led_ws2812b_rgb_t*)color,
										2,
										(uint32_t*)color_repeat,
										1,
										1,
										255);
	step = !step;
}

void effect_wy_tree_2(led_ws2812b_rgb_t led_array[N_LEDS])
{
	static led_ws2812b_rgb_t color_1[] =
	{
			{.r = 200, .g = 200, .b = 200},
	};
	static led_ws2812b_rgb_t color_2[] =
	{
			{.r = 255, .g = 100, .b = 0},
			{.r = 200, .g = 200, .b = 200}
	};
	static led_ws2812b_rgb_t color_3[] =
	{
			{.r = 255, .g = 100, .b = 0},
	};
	static uint32_t color_repeat[] =
	{
			N_LEDS,
			N_LEDS,
	};
	static uint32_t step = 0;
	static uint32_t state = 0;
	static led_ws2812b_rgb_t *color_ptr = color_1;

	static uint32_t aux_step = 0;
	static uint32_t n_colors = 1;

	uint8_t left;


	switch(state)
	{
		case 0:
			color_ptr = color_1;
			n_colors = 1;
			aux_step = step;
			left = 1;
		break;
		case 1:
			color_ptr = color_2;
			color_repeat[0] = N_LEDS-step;
			color_repeat[1] = step;
			n_colors = 2;
			aux_step = 0;
			left = 1;
		break;
		case 2:
			color_ptr = color_3;
			n_colors = 1;
			aux_step = N_LEDS-step;
			left = 0;
		break;
	}

	led_ws2812b_fill_array_with_pattern(led_array,
										aux_step,
										(led_ws2812b_rgb_t*)color_ptr,
										n_colors,
										(uint32_t*)color_repeat,
										0,
										left,
										255);

	if(step <= 1)
	{
		step = N_LEDS-1;
		switch(state)
		{
			case 0:
				state = 1;
			break;
			case 1:
				state = 2;
			break;
			case 2:
				state = 0;
			break;
		}
	}
	else
	{
		step -= 2;
	}
}

void effect_epilepsia(led_ws2812b_rgb_t led_array[N_LEDS])
{
	const led_ws2812b_rgb_t color[] =
	{
			{.r = 255, .g = 0, .b = 0},
			{.r = 0, .g = 255, .b = 0},
			{.r = 0, .g = 0, .b = 255}
	};
	const uint32_t color_repeat[] =
	{
			0,
			0,
			0
	};
	static uint32_t step = 0;

	led_ws2812b_fill_array_with_pattern(led_array,
										step,
										(led_ws2812b_rgb_t*)color,
										3,
										(uint32_t*)color_repeat,
										1,
										1,
										255);
	step = (step >= (5))? 0:(step + 1);
}

void effect_white(led_ws2812b_rgb_t led_array[N_LEDS])
{
	const led_ws2812b_rgb_t color[] =
	{
			{.r = 255, .g = 255, .b = 255},
	};
	const uint32_t color_repeat[] =
	{
			N_LEDS,
	};
	static uint32_t step = 0;

	led_ws2812b_fill_array_with_pattern(led_array,
										step,
										(led_ws2812b_rgb_t*)color,
										1,
										(uint32_t*)color_repeat,
										1,
										1,
										150);
}

void effect_spiral(led_ws2812b_rgb_t led_array[N_LEDS])
{
	const led_ws2812b_rgb_t color[] =
	{
			{.r = 255, .g = 0, .b = 0},
			{.r = 0, .g = 255, .b = 0},
			{.r = 0, .g = 0, .b = 255},
	};
	const uint32_t color_repeat[] =
	{
			N_LEDS/2-1,
	};
	static uint32_t step = 0;
	static uint32_t state = 0;
	static uint32_t n_color = 0;

	led_ws2812b_fill_array_with_mirror_pattern(led_array,
										step,
										(led_ws2812b_rgb_t*)color+n_color,
										1,
										(uint32_t*)color_repeat,
										0,
										1,
										150);

	if(state)
	{
		if(step >= (N_LEDS/2-1))
		{
			state = !state;
		}
		else
		{
			step ++;
		}
	}
	else
	{
		if(step <= 0)
		{
			state = !state;
			n_color = (n_color < 2)? n_color+1:0;
		}
		else
		{
			step --;
		}
	}
}

void effect_rainbow(led_ws2812b_rgb_t led_array[N_LEDS])
{
	static uint32_t step = 0;

	led_ws2812b_fill_array_rainbow(led_array, step, 255);

	step = (step >= (N_LEDS))? 0:(step + 1);
}

void effect_celebration(led_ws2812b_rgb_t led_array[N_LEDS])
{

	const led_ws2812b_rgb_t color[] =
	{
			{.r = 255, .g = 100, .b = 0},
			{.r = 200, .g = 200, .b = 200},
			{.r = 255, .g = 100, .b = 0},
			{.r = 200, .g = 200, .b = 200},
			{.r = 255, .g = 100, .b = 0},
			{.r = 200, .g = 200, .b = 200},
	};
	const uint32_t color_repeat[] =
	{
			25,
			32,
			34,
			37,
			22
	};
	static uint32_t step = 0;
	led_ws2812b_fill_array_with_pattern(led_array,
										0,
										(led_ws2812b_rgb_t*)color+step,
										5,
										(uint32_t*)color_repeat,
										1,
										1,
										150);

	step = !step;
}
