
#ifndef LED_WS2812B_H_
#define LED_WS2812B_H_

#include <stdint.h>

#define N_LEDS 			150
#define	COLOR_BITS 		8
#define COLORS 			3

#define BYTES_PER_BIT 	3
#define BUFF_TYPE_SIZE 	4

#define BUFF_SIZE (TRANSFER_BITS*BUFF_TYPE_SIZE*BYTES_PER_BIT+4)

#define TRANSFER_BITS (COLOR_BITS*COLORS*N_LEDS)

#define GPIO_TOGGLE_MASK 	0x04
#define GPIO_NO_TOGGLE_MASK 0x00

typedef struct _led_ws2812b_rgb_t
{
	uint8_t g;
	uint8_t r;
	uint8_t b;
	uint8_t reserved;
} led_ws2812b_rgb_t;


void led_ws2812b_prepare_buff(led_ws2812b_rgb_t rgb_array[N_LEDS]);

uint32_t *led_ws2812b_get_buff_ptr(void);

void led_ws2812b_fill_array_rainbow(			led_ws2812b_rgb_t rgb_array[N_LEDS],
												uint32_t step,
												uint8_t intensity);


void led_ws2812b_fill_array_with_pattern(		led_ws2812b_rgb_t rgb_array[N_LEDS],
												uint32_t step,
												led_ws2812b_rgb_t *pattern_colors,
												uint32_t n_colors,
												uint32_t *repeat_each_color,
												uint8_t isCyclic,
												uint8_t leftStart,
												uint8_t intensity);

void led_ws2812b_fill_array_with_mirror_pattern(led_ws2812b_rgb_t rgb_array[N_LEDS],
												uint32_t step,
												led_ws2812b_rgb_t *pattern_colors,
												uint32_t n_colors,
												uint32_t *repeat_each_color,
												uint8_t isCyclic,
												uint8_t centerStart,
												uint8_t intensity);


void led_ws2812b_fill_array_colors(				led_ws2812b_rgb_t rgb_array[N_LEDS],
												led_ws2812b_rgb_t color,
												uint8_t intensity);

#endif /* LED_WS2812B_H_ */
