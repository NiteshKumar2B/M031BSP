/**************************************************************************//**
 * @file     main.c
 * @version  V3.00
 * @brief    Demonstrate how to calculate battery voltage( AVdd ) by using band-gap.
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#include <stdio.h>
#include "NuMicro.h"


/*---------------------------------------------------------------------------------------------------------*/
/* Define global variables and constants                                                                   */
/*---------------------------------------------------------------------------------------------------------*/
volatile uint32_t g_u32AdcIntFlag;
volatile uint32_t g_u32BandGapConvValue;

/**
  * @brief      Read Built-in Band-Gap conversion value
  * @param[in]  None
  * @return     Built-in Band-Gap conversion value
  * @details    This function is used to read Band-Gap conversion value.
  */
__STATIC_INLINE uint32_t FMC_ReadBandGap(void)
{
    FMC->ISPCMD = FMC_ISPCMD_READ_UID;            /* Set ISP Command Code */
    FMC->ISPADDR = 0x70u;                         /* Must keep 0x70 when read Band-Gap */
    FMC->ISPTRG = FMC_ISPTRG_ISPGO_Msk;           /* Trigger to start ISP procedure */
#if ISBEN
    __ISB();
#endif                                            /* To make sure ISP/CPU be Synchronized */
    while(FMC->ISPTRG & FMC_ISPTRG_ISPGO_Msk) {}  /* Waiting for ISP Done */

    return FMC->ISPDAT & 0xFFF;
}

void SYS_Init(void)
{
    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Enable HIRC clock (Internal RC 48 MHz) */
    CLK->PWRCTL |= CLK_PWRCTL_HIRCEN_Msk;

    /* Wait for HIRC clock ready */
    while((CLK->STATUS & CLK_STATUS_HIRCSTB_Msk) != CLK_STATUS_HIRCSTB_Msk);

    /* Select HCLK clock source as HIRC and HCLK source divider as 1 */
    CLK->CLKSEL0 = (CLK->CLKSEL0 & ~CLK_CLKSEL0_HCLKSEL_Msk) | CLK_CLKSEL0_HCLKSEL_HIRC;
    CLK->CLKDIV0 = (CLK->CLKDIV0 & ~CLK_CLKDIV0_HCLKDIV_Msk) | CLK_CLKDIV0_HCLK(1);

    /* Enable module clock */
    CLK->APBCLK0 |= CLK_APBCLK0_UART0CKEN_Msk;
    CLK->APBCLK0 |= CLK_APBCLK0_ADCCKEN_Msk;

    /* Switch UART0 clock source to HIRC */
    CLK->CLKSEL1 = (CLK->CLKSEL1 & ~CLK_CLKSEL1_UART0SEL_Msk) | CLK_CLKSEL1_UART0SEL_HIRC;
    CLK->CLKDIV0 = (CLK->CLKDIV0 & ~CLK_CLKDIV0_UART0DIV_Msk) | CLK_CLKDIV0_UART0(1);

    /* Switch ADC clock source to HIRC, set divider to 2, ADC clock is 48/2 MHz */
    CLK->CLKSEL2 = (CLK->CLKSEL2 & ~CLK_CLKSEL2_ADCSEL_Msk) | CLK_CLKSEL2_ADCSEL_PCLK1;
    CLK->CLKDIV0 = (CLK->CLKDIV0 & ~CLK_CLKDIV0_ADCDIV_Msk) | CLK_CLKDIV0_ADC(2);
    /* Update System Core Clock */
    /* User can use SystemCoreClockUpdate() to calculate PllClock, SystemCoreClock and CycylesPerUs automatically. */
    SystemCoreClockUpdate();

    /*----------------------------------------------------------------------*/
    /* Init I/O Multi-function                                              */
    /*----------------------------------------------------------------------*/

    /* Set GPB multi-function pins for UART0 RXD and TXD */
    SYS->GPB_MFPH = (SYS->GPB_MFPH & ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk)) |
                    (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);

    /* Lock protected registers */
    SYS_LockReg();
}

void ADC_FunctionTest()
{
    int32_t  i32ConversionData;
    int32_t  i32BuiltInData;

    printf("\n");
    printf("+----------------------------------------------------------------------------+\n");
    printf("|     ADC for calculate battery voltage( AVdd ) by using band-gap test       |\n");
    printf("+----------------------------------------------------------------------------+\n\n");

    printf("+----------------------------------------------------------------------+\n");
    printf("|   ADC clock source -> PCLK1  = 48 MHz                                |\n");
    printf("|   ADC clock divider          = 2                                     |\n");
    printf("|   ADC clock                  = 48 MHz / 2 = 24 MHz                   |\n");
    printf("|   ADC extended sampling time = 71                                    |\n");
    printf("|   ADC conversion time = 17 + ADC extended sampling time = 88         |\n");
    printf("|   ADC conversion rate = 24 MHz / 88 = 272.7 ksps                     |\n");
    printf("+----------------------------------------------------------------------+\n");

    /* Enable ADC converter */
    ADC->ADCR |= ADC_ADCR_ADEN_Msk;

    /* Do calibration for ADC to decrease the effect of electrical random noise. */
    ADC->ADCALSTSR |= ADC_ADCALSTSR_CALIF_Msk;  /* Clear Calibration Finish Interrupt Flag */
    ADC->ADCALR |= ADC_ADCALR_CALEN_Msk;        /* Enable Calibration function */
    ADC_START_CONV(ADC);                        /* Start to calibration */
    while((ADC->ADCALSTSR & ADC_ADCALSTSR_CALIF_Msk) != ADC_ADCALSTSR_CALIF_Msk);   /* Wait calibration finish */


    /* Set input mode as single-end, Single mode, and select channel 29 (band-gap voltage) */
    ADC->ADCR = (ADC->ADCR & ~(ADC_ADCR_DIFFEN_Msk | ADC_ADCR_ADMD_Msk)) |
                (ADC_ADCR_DIFFEN_SINGLE_END | ADC_ADCR_ADMD_SINGLE);

    ADC->ADCHER = (ADC->ADCHER & ~ADC_ADCHER_CHEN_Msk) | (BIT29);

    /* To sample band-gap precisely, the ADC capacitor must be charged at least 3 us for charging the ADC capacitor ( Cin )*/
    /* Sampling time = extended sampling time + 1 */
    /* 1/24000000 * (Sampling time) = 3 us */
    ADC->ESMPCTL = (ADC->ESMPCTL & ~ADC_ESMPCTL_EXTSMPT_Msk) | (71<<ADC_ESMPCTL_EXTSMPT_Pos);


    /* Clear the A/D interrupt flag for safe */
    ADC->ADSR0 = ADC_ADF_INT;

    /* Enable the sample module interrupt.  */
    ADC->ADCR |= ADC_ADCR_ADIE_Msk;  // Enable sample module A/D interrupt.
    NVIC_EnableIRQ(ADC_IRQn);

    printf(" Press any key to start the test\n\n");
    getchar();

    /* Reset the ADC interrupt indicator and trigger sample module to start A/D conversion */
    g_u32AdcIntFlag = 0;
    ADC_START_CONV(ADC);

    /* Wait ADC conversion done */
    while(g_u32AdcIntFlag == 0);

    /* Disable the A/D interrupt */
    ADC->ADCR &= ~ADC_ADCR_ADIE_Msk;

    /* Get the conversion result of the channel 29 */
    i32ConversionData = ADC_GET_CONVERSION_DATA(ADC, 29);


    /* Enable FMC ISP function to read built-in band-gap A/D conversion result*/
    SYS_UnlockReg();
    FMC->ISPCTL |=  FMC_ISPCTL_ISPEN_Msk;
    i32BuiltInData = FMC_ReadBandGap();

    /* Use Conversion result of Band-gap to calculating AVdd */

    printf("      AVdd           i32BuiltInData                   \n");
    printf("   ---------- = -------------------------             \n");
    printf("      3072          i32ConversionData                 \n");
    printf("                                                      \n");
    printf("AVdd =  3072 * i32BuiltInData / i32ConversionData     \n\n");

    printf("Built-in band-gap A/D conversion result: 0x%X (%d) \n", i32BuiltInData, i32BuiltInData);
    printf("Conversion result of Band-gap:           0x%X (%d) \n\n", i32ConversionData, i32ConversionData);

    printf("AVdd = 3072 * %d / %d = %d mV \n\n", i32BuiltInData, i32ConversionData, 3072*i32BuiltInData/i32ConversionData);
}

void ADC_IRQHandler(void)
{
    g_u32AdcIntFlag = 1;
    ADC_CLR_INT_FLAG(ADC, ADC_ADF_INT); /* Clear the A/D interrupt flag */
}

/*----------------------------------------------------------------------*/
/* Init UART0                                                           */
/*----------------------------------------------------------------------*/
void UART0_Init(void)
{
    /* Reset UART0 */
    SYS->IPRST1 |=  SYS_IPRST1_UART0RST_Msk;
    SYS->IPRST1 &= ~SYS_IPRST1_UART0RST_Msk;

    /* Configure UART0 and set UART0 baud rate */
    UART0->BAUD = UART_BAUD_MODE2 | UART_BAUD_MODE2_DIVIDER(__HIRC, 115200);
    UART0->LINE = UART_WORD_LEN_8 | UART_PARITY_NONE | UART_STOP_BIT_1;
}


int32_t main(void)
{
    /* Init System, IP clock and multi-function I/O. */
    SYS_Init();

    /* Init UART0 for printf */
    UART0_Init();

    printf("\nSystem clock rate: %d Hz", SystemCoreClock);

    /* ADC function test */
    ADC_FunctionTest();

    /* Disable ADC IP clock */
    CLK->APBCLK0 &= ~(CLK_APBCLK0_ADCCKEN_Msk);

    /* Disable External Interrupt */
    NVIC_DisableIRQ(ADC_IRQn);

    printf("Exit ADC sample code\n");

    while(1);
}
