









//  #include <stdio.h>
//	#include "NuMicro.h"
//	
//	#define DATA_COUNT	  16
//	#define TEST_PATTERN 0x00550000
//	#define SPI_CLK_FREQ 20000000
//	
//	#define SPI_PORT		SPI0
//	
//	
//	#define GPIO_SPI0_SS_ PA3
//	
//	#define SPI_CS_SET		GPIO_SPI0_SS = 1
//	#define SPI_CS_CLR		GPIO_SPI0_SS = 0
//	
//	uint32_t g_au32SourceData[DATA_COUNT];
//	uint32_t g_au32DestinationData[DATA_COUNT];
//	volatile uint32_t g_u32TxDataCount;
//	volatile uint32_t g_u32RxDataCount;
//	

//	/* function prototype declaration */
//	/* void HT1621_Init(void); */
//	
//	extern void HT1621_Init (void);
//	
////	void Display(void);
////	void dispee(void);
////	void display_segment(void);
//	unsigned int SPI_transfer (unsigned int input);
//	void endSPI(void);
//	void startSPI(void);
//	void SYS_Init(void);
//	void SPI_Init(void);
////	void Timer_Init(void);
//	
//  //unsigned int word=0;
//	unsigned long long word=0;



//int main(void)
//{
//	uint32_t u32DataCount;
//	uint32_t u32TimeOutCount;

//	/* Unlock Protected Registers */
//	SYS_UnlockReg();
//	/* Init System, IP Clock and multi-functions I/O. */
//	SYS_Init();
//	/* Lock Potected Registers */
//	SYS_LockReg();
//	
//	/* Configure UART); 115200, 8-bit word, no parity bit, 1 stip bit. */
//	UART_Open(UART0,115200);
//	
//	/* Init SPI */
//	SPI_Init();
//	
//	    /* Init TIMER */
//  //  Timer_Init();
//	
//	//HT1621_Init();
//	
//	
//	printf("\n\n");
//	printf("+--------------------------------------------------+");
//	printf("|     SPI Master Mode Sample Code                     |");
//	printf("+--------------------------------------------------+");
//	printf("\n");
//	printf("Configure SPI0 as a master. \n");
//	printf("Bit length of a transaction: 32\n");
//	printf("The I/O connection for SPI0_CLK(PA.2)\n");
//	printf("		SPI0_SS(PA.3)\n		SPI0_CLK(PA.2)\n");
//	printf("		SPI0_MISO(PA.1)\n		SPI0_CLK(PA.0)\n\n");
//	printf("SPI controller will enable FIFO mode and transfer %d data to a off-chip slave device.\n",DATA_COUNT);
//	printf("In the meanwhile the SPI controllerwill receive %d data from the off-chip slave device.\n",DATA_COUNT);
//	printf("After the transfer is done, the %d received data will be printed out.\n", DATA_COUNT);
//	printf("The SPI master configure is ready.\n");
//	
//	//SPI_EnablelenInt(SPI0, SPI_FIFO_TXTH_INT_MASK | SPI_FIFO_RXTO_INT_MASK);
//	//NVIC_EnableIRQ(SPI0_IRQn);
//	while(1)
//	{
//		//disp=setRegBit(DISP,3);
//		//disp=setRegBit(DISPS,5); \\%c
//		//disp|=setRegBit(DISPS3,3); \\LOAD
//		//PA3=0; 
//			HT1621_Init();		
//		
//		//TIMER_Delay(TIMER0, 100); //delay 100ms
//		unsigned int i;
//		for(i=0;i<=100;i++)
//		{
//					PA3=0; 

//			SPI_transfer(i);
//					PA3=1;
//       //TIMER_Delay(TIMER0, 100);
//			
//				__NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
//				__NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP();

//		  i++;
//		};
//	//	PA3=1;
//		
//		//TIMER_Delay(TIMER0, 100); //delay 100ms
//		for(i=0;i<=100;i++){i++;};
//					//Display();
//					//dispee();
//					//display_segment();
//		
//	__NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP();

//			
//		//disp=clrRegBit(DISP14,3);
//		//DISP14=disp;
//		
//		//disp=clrRegBit(DISP12,3);
//		// DISP12=disp;
//		
//	}
//	
//}/*-------------------------------------Main Function over here---------------------------------------------------------*/




//void SYS_Init(void)
//{
//		/*----------------------------------------------*/
//		/* Init System Clock */  
//		/*---------------------------------------------*/
//    /* Enable HIRC clock */
//    CLK_EnableXtalRC(CLK_PWRCTL_HIRCEN_Msk);

//    /* Waiting for HIRC clock ready */
//    CLK_WaitClockReady(CLK_STATUS_HIRCSTB_Msk);

//    /* Switch HCLK clock source to HIRC and HCLK source divide 1 */
//    CLK_SetHCLK(CLK_CLKSEL0_HCLKSEL_HIRC, CLK_CLKDIV0_HCLK(1));

//		/* Select HIRC as the clock source of UART0 */
//		CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HIRC, CLK_CLKDIV0_UART0(1));
//	
//		/* select PCLK1 as the clock source of SPI0 */
//		CLK_SetModuleClock(SPI0_MODULE, CLK_CLKSEL2_SPI0SEL_PCLK1, MODULE_NoMsk);
//		/* Enable UART peripheral clock */
//		CLK_EnableModuleClock(UART0_MODULE);
//		/* Enable SPI perpheral clock */
//		CLK_EnableModuleClock(SPI0_MODULE);
//		
////		    CLK_EnableModuleClock(TMR0_MODULE);
////				    CLK_SetModuleClock(TMR0_MODULE, CLK_CLKSEL1_TMR0SEL_HXT, NULL);   



//    /* Enable module clock */
//   // CLK_EnableModuleClock(UART0_MODULE);
//   //CLK_EnableModuleClock(SPI0_MODULE);  
///*---------------------------------------------------------------------*/
///* Init I/O Multi-function */

///* Set PB Multi-function pins for UART0 RXD=PB.12 and TXD=PB.13 */
//	SYS->GPB_MFPH = (SYS->GPB_MFPH & ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk))|
//									(SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);

///* Setup SPI0 multi-function pins */
///* PA.3 is SPI0_SS, PA.2 is SPI0_CLK,
//	 PA.1 is SPI0.MISO, PA.0 is SPI0_MOSI */
//	 SYS->GPA_MFPL = (SYS->GPA_MFPL & ~(/*SYS_GPA_MFPL_PA3MFP_Msk |*/
//																		 SYS_GPA_MFPL_PA2MFP_Msk |
//																		 /*SYS_GPA_MFPL_PA1MFP_Msk | */
//																		 SYS_GPA_MFPL_PA0MFP_Msk)) |
//		 (/*SYS_GPA_MFPL_PA3MFP_SPI0_SS | */
//		 SYS_GPA_MFPL_PA2MFP_SPI0_CLK | 
//		 /*SYS_GPA_MFPL_PA1MFP_SPI0_MISO | */
//		 SYS_GPA_MFPL_PA0MFP_SPI0_MOSI);
//		 GPIO_SetMode(PA, (BIT3),	GPIO_MODE_OUTPUT); //SPI0_SS //if you are using Three pin 
//		 
//    /* Update System Core Clock */
//    /* User can use SystemCoreClockUpdate() to calculate SystemCoreClock and CyclesPerUs automatically. */
//    SystemCoreClockUpdate();
//		    /* Set module clock */
//    /*CLK_SetModuleClock(SPI0_MODULE, CLK_CLKSEL2_SPI0SEL_PCLK1, MODULE_NoMsk);
//    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HIRC, CLK_CLKDIV0_UART0(1)); */
//}

////void Timer_Init(void)
////{
////    /**************  TIMER0 ***************/
////    /* Set TIMER0 in periodic mode ,frequency 1Hz and enable its interrupt */
////    TIMER_Open(TIMER0, TIMER_PERIODIC_MODE, 1);
////    TIMER_EnableInt(TIMER0);
////    NVIC_EnableIRQ(TMR0_IRQn);

////}
//		 	 
//void SPI_Init(void)
//{
//	/*-----------------------------------------------------------------------------------------*/
//	/* Init SPI                                                                                */
//	/*-----------------------------------------------------------------------------------------*/
//	SPI_Open(SPI0, SPI_MASTER, SPI_MODE_0, 16, SPI_CLK_FREQ);
//	/* Enable the automatic hardware slave select funtion. select the ss pin and consfigure */
//	//SPI_EnableAutoSS(SPI0, SPI_SS, SPI_SSACTIVE_LOW);
//	SPI_DisableAutoSS(SPI0);
//  SPI_SetFIFO(SPI0,2,2);

//} //178over

//void timer(void)
//{
//	
//}



























//void startSPI()
//{
//	/* SPI_CS_CLR; SPI_SET_SS)LOW(SPI_PORT); */
//	PA3=0; /* ACTIVE LOW Slave select pin , (ss=0 means data sending )*/ 
//	
//}
//	
//void endSPI()
//{
//	/* SPI_CS_SET; */
//	PA3=1; /* Active HIgh Slavre select pin, (ss=1 means data sending stop) */
//}

//unsigned int SPI_transfer(unsigned int input)
//{
//	unsigned int output=0xff;
//	SPI_ClearTxFIFO(SPI0); /* Clear SPI FIFO */
//	SPI_ClearRxFIFO(SPI0);
//	
//	SPI_WRITE_TX(SPI0,(input & 0xFF00)>>8);
//	SPI_WRITE_TX(SPI0,(input & 0x00FF));
//	
//	while (SPI_IS_BUSY(SPI0));
//	output = SPI_READ_RX(SPI0);
//	return output;
//	
//}


///* From HT1621LCM.c File */

//uint16_t digit=0;
////#define GCD_GCE  PORTCbits.RC11

//void battery_display(void);
//void endSPI(void);
//void startSPI(void);

////#define INVSW  PORTCbits.RC8 */


//void HT1621_Init(void)
//{
//	  startSPI();               /* CS_CS=0; */  //cs=1;
//		word=0x8000 ;               //0xA000 0x8000
//		SPI_transfer(word);
//	  endSPI();                /* CS_CS=1; */ //cs=1;
//	
//	__NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP();

//	
//	  startSPI(); /* CS_CS=0; */ //cs=1; //shi
//		word=0x8040; //0x8040;
//		SPI_transfer(word);
//  	endSPI(); /* CS_CS=1 */ //cs=1;
//	
//	
//	__NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP();

//	
//	
//  	startSPI(); /* CS_CS=0; */ //cs=1; //shi
//		word=0x8080;
//		SPI_transfer(word);
//	  endSPI(); /* CS_CS=1 */ //cs=1;
//	__NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
//	
//  	startSPI(); /* CS_CS=0; */ //cs=1; //shi
//		word=0x8040;
//		SPI_transfer(word);
//	  endSPI(); /* CS_CS=1 */ //cs=1;
//	__NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
//	
//	  startSPI(); /* CS_CS=0; */ //cs=1; //shi
//		word=0x8100;
//		SPI_transfer(word);
//	  endSPI(); /* CS_CS=1 */ //cs=1;
//	__NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
//	
//	  startSPI(); /* CS_CS=0; */ //cs=1; //shi
//		word=0x9000;
//		SPI_transfer(word);
//	  endSPI(); /* CS_CS=1 */ //cs=1;
//	__NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
//	
//	startSPI(); /* CS_CS=0; */ //cs=1; //shi
//		word=0x8520;
//		SPI_transfer(word);
//	endSPI(); /* CS_CS=1 */ //cs=1;
//	__NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
//	
//	  startSPI(); /* CS_CS=0; */ //cs=1; //shi
//		word=0x8300;
//		SPI_transfer(word);
//	  endSPI(); /* CS_CS=1 */ //cs=1;
//	__NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
//	
//	  startSPI(); /* CS_CS=0; */ //cs=1; //shi
//		word=0x94E0;
//		SPI_transfer(word);
//	  endSPI(); /* CS_CS=1 */ //cs=1;
//	__NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP();

//}


// 


