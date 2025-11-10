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

void led_ws2812b_fill_array_rainbow(led_ws2812b_rgb_t rgb_array[N_LEDS])
{
	uint32_t pixel, val;

	for(pixel = 0; pixel < N_LEDS; pixel ++)
	{
		if(pixel <= 75)
		{
			val = pixel * 3;
			rgb_array[pixel].r = (uint8_t)225-val;
			rgb_array[pixel].g = (uint8_t)val;
			rgb_array[pixel].b = 0;
		}
		else
		{
			val = (pixel-75) * 3;
			rgb_array[pixel].r = 0;
			rgb_array[pixel].g = (uint8_t)225-val;
			rgb_array[pixel].b = (uint8_t)val;
		}
	}
}

void led_ws2812b_fill_array_colors(led_ws2812b_rgb_t rgb_array[N_LEDS])
{
	uint32_t pixel;

	for(pixel = 0; pixel < N_LEDS; pixel ++)
	{
		if(pixel%2 == 0)
		{
			rgb_array[pixel].r = 225;
			rgb_array[pixel].g = 0;
			rgb_array[pixel].b = 0;
		}
		else if(pixel%3 == 0)
		{
			rgb_array[pixel].r = 0;
			rgb_array[pixel].g = 225;
			rgb_array[pixel].b = 0;
		}
		else
		{
			rgb_array[pixel].r = 0;
			rgb_array[pixel].g = 0;
			rgb_array[pixel].b = 225;
		}
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
