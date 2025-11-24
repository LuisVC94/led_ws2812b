#include "board.h"
#include "app.h"
#include "fsl_debug_console.h"
#include "fsl_edma.h"
#include <stdlib.h>
#include "led_WS2812B.h"
#include "fsl_ctimer.h"
#include "fsl_lptmr.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define TCD_QUEUE_SIZE   1U
#define EFFECT_DIV		 5
/*******************************************************************************
 * Prototypes
 ******************************************************************************/

typedef enum _state_machine_efects_t
{
	k_state_machine_efect_breathing,
	k_state_machine_efect_rainbow,
	k_state_machine_efect_pattern,
	k_state_machine_efect_mirror_pattern,
	k_state_machine_efect_run,
	k_state_machine_efect_kitt,
} state_machine_efects_t;

/*******************************************************************************
 * Variables
 ******************************************************************************/
static edma_handle_t g_EDMA_Handle;

AT_QUICKACCESS_SECTION_DATA_ALIGN(edma_tcd_t tcdMemoryPoolPtr[TCD_QUEUE_SIZE], sizeof(edma_tcd_t));

// For led array --------------------------------------------------------------
static led_ws2812b_rgb_t g_led_array[N_LEDS] = {0};
// ----------------------------------------------------------------------------

static uint8_t g_task_flag = 0;

/*******************************************************************************
 * Code
 ******************************************************************************/


void EDMA_Callback(edma_handle_t *handle, void *param, bool transferDone, uint32_t tcds)
{
     if (transferDone)
    {
    	CTIMER_StopTimer(CTIMER0);
    }
}

void DMA_init(void);

void lptmr_init(void);

void ctimer_init(void);

void DMA_set_transfer(void);


void rainbow_effect(void)
{
	static uint32_t step = 0;

    led_ws2812b_fill_array_rainbow(g_led_array, step, 255);
	step = (step < N_LEDS-1)? (step + 1):0;
}

void go_back_read_white_effect(void)
{
	const led_ws2812b_rgb_t color[] =
	{
			{.r = 255, .g = 255, .b = 255},
			{.r = 255, .g = 0, .b = 0}
	};
	const uint32_t color_repeat[] =
	{
			20,
			55
	};
	static uint32_t step = 0;
	static uint8_t state = 1;

	led_ws2812b_fill_array_with_mirror_pattern( g_led_array,
												step,
												(led_ws2812b_rgb_t*)color,
												2,
												(uint32_t*)color_repeat,
												0,
												1,
												255);
	if(state)
	{
		step ++;
		state = (step >= (N_LEDS/2-1))? (!state):state;
	}
	else
	{
		step --;
		state = (step <= 0)? (!state):state;
	}
}

void cyclic_read_withe_effect(void)
{
	const led_ws2812b_rgb_t color[] =
	{
			{.r = 255, .g = 255, .b = 255},
			{.r = 255, .g = 0, .b = 0}
	};
	const uint32_t color_repeat[] =
	{
			20,
			55
	};
	static uint32_t step = 0;

	led_ws2812b_fill_array_with_mirror_pattern( g_led_array,
												step,
												(led_ws2812b_rgb_t*)color,
												2,
												(uint32_t*)color_repeat,
												1,
												1,
												255);
	step = (step >= (N_LEDS/2-1))? 0:(step + 1);
}

void cyclic_red_green_blue_withe_effect(void)
{
	const led_ws2812b_rgb_t color[] =
	{
			{.r = 255, .g = 0, .b = 0},
			{.r = 0, .g = 255, .b = 0},
			{.r = 0, .g = 0, .b = 255}
	};
	const uint32_t color_repeat[] =
	{
			2,
			2,
			2
	};
	static uint32_t step = 0;

	led_ws2812b_fill_array_with_mirror_pattern( g_led_array,
												step,
												(led_ws2812b_rgb_t*)color,
												3,
												(uint32_t*)color_repeat,
												1,
												1,
												255);
	step = (step >= (N_LEDS/2-1))? 0:(step + 1);
}



int main(void)
{
	state_machine_efects_t state = k_state_machine_efect_breathing;
	uint32_t counter = 0;
	uint32_t div = 0;
	led_ws2812b_rgb_t color;
    BOARD_InitHardware();

    GPIO_EnablePinControlNonSecure(GPIO1_ALIAS1, 0x04);
    GPIO_EnablePinControlNonPrivilege(GPIO1_ALIAS1, 0x04);

    DMA_init();
    ctimer_init();
    lptmr_init();

    color.b = 0;
    color.g = 0;
    color.r = 0;

    led_ws2812b_fill_array_colors(g_led_array, color, 0);

    while(1)
    {
    	if(g_task_flag)
    	{
    	    if(div >= EFFECT_DIV)
    	    {
        	    led_ws2812b_prepare_buff(g_led_array);
        		DMA_set_transfer();
        	    CTIMER_StartTimer(CTIMER0);
        	    //rainbow_effect();
        	    go_back_read_white_effect();
        	    //cyclic_read_withe_effect();
       	        //cyclic_red_green_blue_withe_effect();
        	    div = 0;
    	    }
    	    else
    	    {
    	    	div ++;
    	    }
    	    g_task_flag = 0;
    	}
    }
}


void DMA_init(void)
{
    edma_config_t userConfig;


    EDMA_GetDefaultConfig(&userConfig);
    EDMA_Init(EXAMPLE_DMA_BASEADDR, &userConfig);
    EDMA_CreateHandle(&g_EDMA_Handle, EXAMPLE_DMA_BASEADDR, EXAMPLE_DMA_CHANNEL);
    EDMA_SetCallback(&g_EDMA_Handle, EDMA_Callback, NULL);
    EDMA_ResetChannel(g_EDMA_Handle.base, g_EDMA_Handle.channel);

    EDMA_InstallTCDMemory(&g_EDMA_Handle, tcdMemoryPoolPtr, TCD_QUEUE_SIZE);

    EDMA_SetChannelMux(EXAMPLE_DMA_BASEADDR, EXAMPLE_DMA_CHANNEL, kDma0RequestMuxCtimer0M0);
}

void lptmr_init(void)
{
    lptmr_config_t lptmrConfig;

	LPTMR_GetDefaultConfig(&lptmrConfig);
    LPTMR_Init(LPTMR0, &lptmrConfig);
    LPTMR_SetTimerPeriod(LPTMR0, USEC_TO_COUNT(20000, 16000)); // 60Hz
    LPTMR_EnableInterrupts(LPTMR0, kLPTMR_TimerInterruptEnable);
    EnableIRQ(LPTMR0_IRQn);
    LPTMR_StartTimer(LPTMR0);
}

void ctimer_init(void)
{
    ctimer_config_t config;
    ctimer_match_config_t matchConfig0;
    uint32_t ctimer_freq;

    CTIMER_GetDefaultConfig(&config);
    CTIMER_Init(CTIMER0, &config);

    ctimer_freq = CLOCK_GetCTimerClkFreq(0);

    matchConfig0.enableCounterReset = true;
    matchConfig0.enableCounterStop  = false;
    matchConfig0.matchValue         = (uint32_t)(((uint64_t)400*(uint64_t)ctimer_freq)/(uint64_t)1000000000);
    matchConfig0.outControl         = kCTIMER_Output_NoAction;
    matchConfig0.outPinInitState    = false;
    matchConfig0.enableInterrupt    = true;

    CTIMER_SetupMatch(CTIMER0, kCTIMER_Match_0, &matchConfig0);
}

void DMA_set_transfer(void)
{
    edma_transfer_config_t transferConfig;
    EDMA_AbortTransfer(&g_EDMA_Handle);
    EDMA_PrepareTransfer(&transferConfig,
    					(void*)led_ws2812b_get_buff_ptr(),
						4,
						(void*)&(GPIO1->PTOR),
						4,
                        4,
						BUFF_SIZE,
						kEDMA_MemoryToPeripheral);

    EDMA_SubmitTransfer(&g_EDMA_Handle, &transferConfig);
    EDMA_StartTransfer(&g_EDMA_Handle);
}

void LPTMR0_IRQHandler(void)
{
	g_task_flag = 1;
    LPTMR_ClearStatusFlags(LPTMR0, kLPTMR_TimerCompareFlag);

    __DSB();
    __ISB();
}
