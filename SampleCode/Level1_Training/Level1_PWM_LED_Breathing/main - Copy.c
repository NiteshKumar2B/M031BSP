/* https://www.youtube.com/watch?v=1qjwDOcVT_M&ab_channel=NuvotonTechnology Video Link */

#include<stdio.h>
#include"NuMicro.h"

/*-------------------------------------------------------------------------------------------------------*/
/* Macro, type and constant definations                                                                  */
/*-------------------------------------------------------------------------------------------------------*/

#define PWM_Prescaler       48
#define PWM_Period          1999

/*-------------------------------------------------------------------------------------------------------*/
/* Global Variables                                                                                      */
/*-------------------------------------------------------------------------------------------------------*/

volatile uint8_t g_u8Forward = 1;
volatile uint8_t g_u32BreadthingCount = 0;

void SYS_Init(void)
{
    /*-------------------------------------------------------------------------------------------------*/
    /* Init System Clock                                                                               */
    /*-------------------------------------------------------------------------------------------------*/
    /* Enable HIRC clock */
    CLK_EnableXtalRC(CLK_PWRCTL_HIRCEN_Msk);

    /* Waiting for HIRC clock Ready */
    CLK_WaitClockReady(CLK_STATUS_HIRCSTB_Msk);

    /* Switch HCLK clock source to HIRC and HIRC clock divide 1*/
    CLK_SetHCLK(CLK_CLKSEL0_HCLKSEL_HIRC, CLK_CLKDIV0_HCLK(1));

    /* Enable PWM1 Module clock */
    CLK_EnableMoudleClock(PWM_Module);

/* --------------------------------------------------------------------------------------------------*/
/* PWM Clock Frequency Configuration                                                                 */
/*---------------------------------------------------------------------------------------------------*/
/* Set PLL clock as 96MHz form HIRC/4*/
CLK_EnablePLL(CLK_PLLCTL_PLLSRC_HIRC_DIV4,96000000);

/* Waiting for PLL clock ready */
CLK_WaitClockReady(CLK_STATUS_PLLSTB_Msk);




}

