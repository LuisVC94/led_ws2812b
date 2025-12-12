#include "board.h"
#include "app.h"
#include "fsl_debug_console.h"
#include "fsl_edma.h"
#include <stdlib.h>
#include "led_WS2812B.h"
#include "fsl_ctimer.h"
#include "fsl_lptmr.h"
#include "sweater.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define TCD_QUEUE_SIZE   1U
#define DEBAUNCER_DIV	 20

#define START_MODE k_state_machine_efect_color_tree
/*******************************************************************************
 * Prototypes
 ******************************************************************************/



/*******************************************************************************
 * Variables
 ******************************************************************************/
static edma_handle_t g_EDMA_Handle;

AT_QUICKACCESS_SECTION_DATA_ALIGN(edma_tcd_t tcdMemoryPoolPtr[TCD_QUEUE_SIZE], sizeof(edma_tcd_t));

// For led array --------------------------------------------------------------
static led_ws2812b_rgb_t g_led_array[N_LEDS] = {0};
// ----------------------------------------------------------------------------

static uint8_t g_task_flag = 0;

static state_machine_sweater_t g_effect = START_MODE;

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



int main(void)
{
	uint32_t counter = 0;
	uint32_t div = 0;
	led_ws2812b_rgb_t color;
	uint32_t efect_div = 0;
	uint32_t debauncer_div = 0;
	uint8_t btn_released = 1;
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
    		if(debauncer_div >= DEBAUNCER_DIV)
    		{
    			if(GPIO_PinRead(GPIO0, 6)) btn_released = 1;
    			if((!GPIO_PinRead(GPIO0, 6)) && btn_released)
    			{
    				if(g_effect < k_state_machine_efect_celebration) g_effect ++;
    				else g_effect = 0;
    				btn_released = 0;
    			}
    			debauncer_div = 0;
    		}
    		else
    		{
    			debauncer_div ++;
    		}
    	    if(div >= efect_div)
    	    {
        	    led_ws2812b_prepare_buff(g_led_array);
        		DMA_set_transfer();
        	    CTIMER_StartTimer(CTIMER0);

        	    switch(g_effect)
        	    {
					case k_state_machine_efect_color_tree:
						effect_color_tree(g_led_array);
						efect_div = 50;
					break;

					case k_state_machine_efect_wy_tree_1:
						effect_wy_tree_1(g_led_array);
						efect_div = 20;
					break;

					case k_state_machine_efect_wy_tree_2:
						effect_wy_tree_2(g_led_array);
						efect_div = 0;
					break;

					case k_state_machine_efect_epilepsia:
						effect_epilepsia(g_led_array);
						efect_div = 5;
					break;

					case k_state_machine_efect_white:
						effect_white(g_led_array);
						efect_div = 20;
					break;

					case k_state_machine_efect_spiral:
						effect_spiral(g_led_array);
						efect_div = 1;
					break;

					case k_state_machine_efect_rainbow:
						effect_rainbow(g_led_array);
						efect_div = 5;
					break;

					case k_state_machine_efect_celebration:
						effect_celebration(g_led_array);
						efect_div = 20;
					break;
        	    }
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
    LPTMR_SetTimerPeriod(LPTMR0, USEC_TO_COUNT(20000, 5000)); // 60Hz
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
