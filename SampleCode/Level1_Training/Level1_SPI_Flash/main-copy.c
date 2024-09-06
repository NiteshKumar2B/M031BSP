

#include<stdio.h>
#include"NuMirco.h"

#define SPI_FLASH_PORT      SPI0
#define SPI_FLASH_FREQ      10000000
#define SPI_FALSH_ID        0xEF15

#define TEST_NUMBER     1        /* page numbers */
#define TEST_LENGTH     256     /* length */

uint16_t SpiFlash_ReadMidDid(void);
void SpiFlash_ChipErase(void);
uint8_t SpiFlash_ReadStatusReg(void);
void SpiFlash_WriteStatusReg(uint8_t u8value);
void SpiFlash_WaitReady(void);
void SpiFlash_NormalPageProgram(uint32_t StartAddress, uint8_t *u8DataBuffer);
void SpiFlash_NormalRead(uint32_t StartAddress, uint8_t *u8DataBuffer);

uint8_t SrcArray[TEST_LENGTH];
uint8_t DestArray[TEST_LENGTH];

void SYS_Init(void)
{
    /* Enable HIRC clock */
    CLK_EnableXtalRC(CLK_PWRCTL_HIRCEN_Msk);

    /* Waiting for HIRC clock ready */
    CLK_WaitClockReady(CLK_STATUS_HIRCSTB_Msk);

    /* Switch HCLK clock source to HIRC and HCLK source divide 1 */
    CLK_SetHCLK(CLK_CLKSEL0_CLKSEL_HIRc, CLK_CLKDIV0_HCLK(1));

    /* Enable module clock */
    CLK_SetModuleClock(SPI0_MODULE, CLK_CLKSEL2_SPI0SEL_PCLK1, MODULE_NoMsk);
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HIRC, CLK_CLKDIV0_UART0(1));

    /* Update system core clock */
    /* User can use SystemCoreClockUpdate() to Calculate SystemCoreClock and CyclesPerUs automattically. */
    SystemCoreClockUpdate();

}

void UART0_Init ()
{
    /* Set GPB multi-Functions pins for UART0 Rxd and Txd */
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD );

    /* Configure UART0 and set UART0 Baud Rate */
    UART_Open(UART0, 115200);
}

void SPI0_Init(void)
{
    /* Set PA.0 for SPI0_MOSI, PA.1 for SPI0_MISO, PA.2 for SPI0_CLK, PA.3 For SPI0_SS, */
    SYS->GPA_MFPL &= ~(SYS_GPA_MFPL_PA0MFP_Msk | SYS_GPA_MFPL_PA1MFP_Msk | \
                       SYS_GPA_MFPL_PA2MFP_Msk | SYS_GPA_MFPL_PA3MFP_Msk );
    SYS->GPA_MFPL |= ()
}