/**
 ******************************************************************************
 * @file           : main.c
 * @author         : EREN MERT YİĞİT
 * @brief          : Main program body
 ******************************************************************************
 *
 *4X4 MATRİX KEYPAD STM32F072-RB Implemented
 *
 *
 *
 *Input pins are PA0, PA1, PA4, PB0
 *
 *Output pins are PA8, PA9, PA10, PB5
 *
 ******************************************************************************
 */

#include <stdint.h>
#include<stdio.h>

void delay(void)
{
for(uint32_t i =0; i < 30000 ; i++);

}

int main(void)
{
	/*Pointed register addreses for operations*/
	uint32_t volatile *const pClkctrlreg   = (uint32_t*)0x40021014; //pointer typecasting  //AHB Adress pointer
	uint32_t volatile *const pPortAmodereg = (uint32_t*)0x48000000;
	uint32_t volatile *const pPortBmodereg = (uint32_t*)0x48000400;
	uint32_t volatile *const pPortAoutreg  = (uint32_t*)0x48000014;
	uint32_t volatile *const pPortBoutreg  = (uint32_t*)0x48000414;
	uint32_t volatile *const pPortAinreg   = (uint32_t*)0x48000010;
	uint32_t volatile *const pPortBinreg   = (uint32_t*)0x48000410;
	uint32_t volatile *const pPortAPullupreg =(uint32_t*)0x4800000C;
	uint32_t volatile *const pPortBPullupreg =(uint32_t*)0x4800040C;

	/*enable clocks for A and B ports*/
	*pClkctrlreg |= (3 << 17);


	/*configure output pins for ROWs*/
	*pPortAmodereg == 0x28000000; //Reset value of GPIOA_MODE register for masking
	*pPortAmodereg |= 0x00150000;    // Set PA8 - PA9 - PA10 as output mode

	*pPortBmodereg &= ~(0xFFFFFFFF);  //Reset all GPIOB_MODE register for masking
	*pPortBmodereg |= 0x00000400;     //Set PB5 as output mode


	/*configure input pins for Columns*/
    *pPortAmodereg &= 0xFFFFFCF0;     //Reset PA0 - PA1 - PA4
    *pPortBmodereg &= 0xFFFFFFFC;     //Reset PB0

    /*Enable internal pull-up resistors for Column Pins */
    *pPortAPullupreg &= ~(0xFFFFFFFF);
    *pPortAPullupreg |= 0x00000115;

    *pPortBPullupreg &= 0xFFFFFFFE;

while(1)
{
    /*Set all rows to HIGH */
    *pPortAoutreg |= (7 << 8);
    *pPortBoutreg |= (1 << 0);

    /*Set first row to low (PB5)*/
    *pPortBoutreg &= ~(1 << 5);

    /*scan the columns */
    //check if C1 (PB0) is low or high
    if( ! (*pPortBinreg & (1 << 0))) //get in if low
    {
    	//1 PRESSED
    	delay();    //put del
    	printf("1\n");
    }

    //check if C2 (PA0) is low or high
    if( ! (*pPortAinreg & (1 << 0)))
		{
			//2 PRESSED
    	delay();
			printf("2\n");
		}

    //check if C3 (PA1) is low or high
    if( ! (*pPortAinreg & (1 << 1)))
   		{
   			//3 PRESSED
    	delay();
   			printf("3\n");
   		}

    //check if C4 (PA4) is low or high
    if( ! (*pPortAinreg & (1 << 4)))
   		{
   			// A PRESSED
    	delay();

   		}

    /*Set all rows to HIGH again to make sure */
        *pPortAoutreg |= (7 << 8);
        *pPortBoutreg |= (1 << 0);


    /*Set row 2 to low (PA8)*/
       *pPortAoutreg &= ~(1 << 8);

       //check if C1 (PB0) is low or high
       if( ! (*pPortBinreg & (1 << 0))) //get in if low
       {
    	   //4 PRESSED
           	delay();    //put del
           	printf("4\n");
       }

           //check if C2 (PA0) is low or high
       if( ! (*pPortAinreg & (1 << 0)))
       {
    	   //5 PRESSED
           	delay();
       			printf("5\n");
       }

           //check if C3 (PA1) is low or high
       if( ! (*pPortAinreg & (1 << 1)))
       {
    	   //6 PRESSED
    	   delay();
    	   printf("6\n");
       }

           //check if C4 (PA4) is low or high
       if( ! (*pPortAinreg & (1 << 4)))
       {
    	   // B PRESSED
    	   delay();

       }

       /*Set all rows to HIGH again to make sure */
               *pPortAoutreg |= (7 << 8);
               *pPortBoutreg |= (1 << 0);


           /*Set row 3 to low (PA9)*/
              *pPortAoutreg &= ~(1 << 9);

              //check if C1 (PB0) is low or high
                     if( ! (*pPortBinreg & (1 << 0))) //get in if low
                     {
                  	   //7 PRESSED
                         	delay();    //put del
                         	printf("7\n");
                     }

                         //check if C2 (PA0) is low or high
                     if( ! (*pPortAinreg & (1 << 0)))
                     {
                  	   //8 PRESSED
                         	delay();
                     			printf("8\n");
                     }

                         //check if C3 (PA1) is low or high
                     if( ! (*pPortAinreg & (1 << 1)))
                     {
                  	   //9 PRESSED
                  	   delay();
                  	   printf("9\n");
                     }

                         //check if C4 (PA4) is low or high
                     if( ! (*pPortAinreg & (1 << 4)))
                     {
                  	   //C PRESSED
                  	   delay();

                     }


                     /*Set all rows to HIGH again to make sure */
                                   *pPortAoutreg |= (7 << 8);
                                   *pPortBoutreg |= (1 << 0);


                               /*Set row 4 to low (PA10)*/
                                  *pPortAoutreg &= ~(1 << 10);

                                  //check if C1 (PB0) is low or high
                                                      if( ! (*pPortBinreg & (1 << 0))) //get in if low
                                                      {
                                                   	   // * PRESSED
                                                          	delay();    //put del

                                                      }

                                                          //check if C2 (PA0) is low or high
                                                      if( ! (*pPortAinreg & (1 << 0)))
                                                      {
                                                   	   // 0 PRESSED
                                                          	delay();

                                                      }

                                                          //check if C3 (PA1) is low or high
                                                      if( ! (*pPortAinreg & (1 << 1)))
                                                      {
                                                   	   // # PRESSED
                                                   	   delay();

                                                      }

                                                          //check if C4 (PA4) is low or high
                                                      if( ! (*pPortAinreg & (1 << 4)))
                                                      {
                                                   	   // D PRESSED
                                                   	   delay();

                                                      }

}
    /* Loop forever */
	for(;;);
}
