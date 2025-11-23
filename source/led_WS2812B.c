#include "led_WS2812B.h"


static uint32_t g_buff[BUFF_SIZE] = {0};

void led_ws2812B_init(void)
{

}

void led_ws2812b_low_bit(uint32_t *buff)
{
	buff[0] = GPIO_TOGGLE_MASK;
	buff[1] = GPIO_TOGGLE_MASK;
	buff[2] = GPIO_NO_TOGGLE_MASK;
}

void led_ws2812b_high_bit(uint32_t *buff)
{
	buff[0] = GPIO_TOGGLE_MASK;
	buff[1] = GPIO_NO_TOGGLE_MASK;
	buff[2] = GPIO_TOGGLE_MASK;
}

void led_ws2812b_fill_array_rainbow(	led_ws2812b_rgb_t rgb_array[N_LEDS],
										uint32_t step,
										uint8_t intensity)
{
	float led_intensity  = (float)intensity/255.0;
	float led_scale 	 = 3.0*255.0/N_LEDS;

	float first_section  = N_LEDS/3.0;
	float second_section = N_LEDS*2.0/3.0;
	float third_section  = N_LEDS;

	float red_value;
	float green_value;
	float blue_value;
	float aux_val;

	uint32_t pixel;
	uint32_t counter;

	counter = step;

	for(pixel = 0; pixel < N_LEDS; pixel ++)
	{
		if(counter <= (uint32_t)first_section)
		{
			aux_val     = (float)counter * led_scale;
			aux_val 	= (aux_val > 255)? 255:aux_val;

			red_value   = 255.0-aux_val;
			green_value = aux_val;
			blue_value  = 0.0;
		}
		else if(counter <= (uint32_t)second_section)
		{
			aux_val     = ((float)counter - first_section) * led_scale;
			aux_val 	= (aux_val > 255)? 255:aux_val;

			red_value   = 0.0;
			green_value = 255 - aux_val;
			blue_value  = aux_val;
		}
		else
		{
			aux_val     = ((float)counter - second_section) * led_scale;
			aux_val 	= (aux_val > 255)? 255:aux_val;

			red_value   = aux_val;
			green_value = 0.0;
			blue_value  = 255 - aux_val;
		}
		rgb_array[pixel].r = (uint8_t)(red_value   * led_intensity);
		rgb_array[pixel].g = (uint8_t)(green_value * led_intensity);
		rgb_array[pixel].b = (uint8_t)(blue_value  * led_intensity);
		counter = (counter >= (N_LEDS-1))? 0:(counter + 1);
	}
}


void led_ws2812b_fill_array_with_pattern(	led_ws2812b_rgb_t rgb_array[N_LEDS],
											uint32_t step,
											led_ws2812b_rgb_t *pattern_colors,
											uint32_t n_colors,
											uint32_t *repeat_each_color,
											uint8_t isCyclic,
											uint8_t leftStart,
											uint8_t intensity)
{
	float led_intensity  = (float)intensity/255.0;
	uint32_t pixel;
	uint32_t counter;
	uint32_t color_counter;
	uint32_t repeat_counter;

	step = (step > (N_LEDS-1))? 0:step;
	counter = step;
	color_counter = 0;
	repeat_counter = 0;

	for(pixel = 0; pixel < N_LEDS; pixel ++)
	{
		if(isCyclic ||
		  (leftStart 		&& (((N_LEDS-1)-counter) > step)) ||
		  ((!leftStart) 	&& (counter > step)))
		{
			rgb_array[counter].r = ((float)pattern_colors[color_counter].r*led_intensity);
			rgb_array[counter].g = ((float)pattern_colors[color_counter].g*led_intensity);
			rgb_array[counter].b = ((float)pattern_colors[color_counter].b*led_intensity);
		}
		else
		{
			rgb_array[counter].r = 0;
			rgb_array[counter].g = 0;
			rgb_array[counter].b = 0;
		}

		if(repeat_counter >= repeat_each_color[color_counter])
		{
			color_counter = (color_counter < n_colors-1)? (color_counter + 1):0;
			repeat_counter = 0;
		}
		else
		{
			repeat_counter ++;
		}
		counter = (counter < (N_LEDS-1))? (counter + 1):0;
	}
}

void led_ws2812b_fill_array_with_mirror_pattern(led_ws2812b_rgb_t rgb_array[N_LEDS],
												uint32_t step,
												led_ws2812b_rgb_t *pattern_colors,
												uint32_t n_colors,
												uint32_t *repeat_each_color,
												uint8_t isCyclic,
												uint8_t centerStart,
												uint8_t intensity)
{
	float led_intensity  = (float)intensity/255.0;
	uint32_t pixel;
	uint32_t up_counter;
	uint32_t down_counter;
	uint32_t color_counter;
	uint32_t repeat_counter;

	step = (step > ((N_LEDS/2)-1))? 0:step;

	up_counter   = ((N_LEDS/2)-1)+step;
	down_counter = ((N_LEDS/2)-1)-step;
	color_counter = 0;
	repeat_counter = 0;

	for(pixel = 0; pixel < (N_LEDS/2); pixel ++)
	{
		if(isCyclic ||
		  (centerStart 		&& ((((N_LEDS/2)-1)-down_counter) > step)) ||
		  ((!centerStart) 	&& (down_counter > step)))
		{
			rgb_array[up_counter].r 	= ((float)pattern_colors[color_counter].r*led_intensity);
			rgb_array[up_counter].g 	= ((float)pattern_colors[color_counter].g*led_intensity);
			rgb_array[up_counter].b 	= ((float)pattern_colors[color_counter].b*led_intensity);
			rgb_array[down_counter].r 	= ((float)pattern_colors[color_counter].r*led_intensity);
			rgb_array[down_counter].g 	= ((float)pattern_colors[color_counter].g*led_intensity);
			rgb_array[down_counter].b 	= ((float)pattern_colors[color_counter].b*led_intensity);
		}
		else
		{
			rgb_array[up_counter].r 	= 0;
			rgb_array[up_counter].g 	= 0;
			rgb_array[up_counter].b 	= 0;
			rgb_array[down_counter].r 	= 0;
			rgb_array[down_counter].g 	= 0;
			rgb_array[down_counter].b 	= 0;
		}

		if(repeat_counter >= repeat_each_color[color_counter])
		{
			color_counter = (color_counter < n_colors-1)? (color_counter + 1):0;
			repeat_counter = 0;
		}
		else
		{
			repeat_counter ++;
		}
		up_counter   = (up_counter < (N_LEDS-1))? 	(up_counter + 1):	((N_LEDS/2)-1);
		down_counter = (down_counter > 0)? 	     	(down_counter - 1):	((N_LEDS/2)-1);
	}
}


void led_ws2812b_fill_array_colors(	led_ws2812b_rgb_t rgb_array[N_LEDS],
									led_ws2812b_rgb_t color,
									uint8_t intensity)
{
	float led_intensity  = (float)intensity/255.0;
	uint32_t pixel;

	for(pixel = 0; pixel < N_LEDS; pixel ++)
	{
		rgb_array[pixel].r = (uint8_t)((float)color.r * led_intensity);
		rgb_array[pixel].g = (uint8_t)((float)color.g * led_intensity);
		rgb_array[pixel].b = (uint8_t)((float)color.b * led_intensity);
	}
}

void led_ws2812b_prepare_buff(led_ws2812b_rgb_t rgb_array[N_LEDS])
{
	uint32_t pixel_index;
	uint32_t bit_index;
	uint32_t color_index;
	uint32_t buff_index;
	uint8_t bits;

	buff_index = 1;
	g_buff[buff_index] = 0;
	for(pixel_index = 0; pixel_index < N_LEDS; pixel_index ++)
	{
		for(color_index = 0; color_index < COLORS; color_index ++)
		{
			bits = ((uint8_t*)(rgb_array+pixel_index))[color_index];
			for(bit_index = 0; bit_index < COLOR_BITS; bit_index ++)
			{
				if(bits & 0x80) led_ws2812b_high_bit(g_buff+buff_index);
				else			led_ws2812b_low_bit(g_buff+buff_index);
				buff_index += BYTES_PER_BIT;
				bits = bits << 1;
			}
		}
	}
}

uint32_t *led_ws2812b_get_buff_ptr(void)
{
	return g_buff;
}
