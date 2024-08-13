/*
 * [ PROJECT   ]  A60132237_V00
 * [ License   ]  SAMJIN ELECTRONICS.,Co.Ltd
 * [ Author    ]  Copyright 2024 By HAG-SEONG KANG
 * [ E-MAIL    ]  hl5ugc@nate.com (82)10- 3841-9706
 * [ C  P  U   ]
 * [ Compller  ]  
 * [ Filename  ]  Ap.c
 * [ Version   ]  1.0
 * [ Created   ]  2024[¿ÀÈÄ 5:09:02 ]
 * --------------------------------------------------------------------------
 * Revision History :
 * ------------------------------------------------------------------
 *
 *
 *  *.The use of this source code shall be deemed to have been 
 *    tacitly agreed by the user.
 *  *.This source code is freely available for personal learning 
 *    and research and development.
 *  *.In the case of secondary authoring or redistribution using this source, 
 *    it is essential The company name of SAMJIN ELECTRONICS must be specified.
 *  *.Do not sell or for-profit this source code.
 *	*.This clause and the original author mark are prohibited from being 
 *	  modified or deleted. 
 *  
 *------------------------------------------------------------------
 * --------------------------------------------------------------------------
 * Author         Date       Comments on this revision
 * --------------------------------------------------------------------------
 * Hagseong Kang  2024. 8. 1.    First release of this file
 * --------------------------------------------------------------------------
 * Additional Notes:
 * **************************************************************************
 */
 /**
 * @brief 
 * @param  
 * @return  
 */



/* Define Includes */
#include "Ap.h"
 
// ---------------------------------------------------------------------------
//  Define Macros .
// ---------------------------------------------------------------------------
//
 
// ---------------------------------------------------------------------------
//  Define TypeDef & Constants.
// ---------------------------------------------------------------------------
//
 
// ---------------------------------------------------------------------------
//  Define Private variables.
// ---------------------------------------------------------------------------
//
static uint32_t  CheckFifo = 0U ;
// ---------------------------------------------------------------------------
// Define Private function prototype.
// ---------------------------------------------------------------------------
//

// ---------------------------------------------------------------------------
// Define Callback function prototype.
// ---------------------------------------------------------------------------
//
 
// ---------------------------------------------------------------------------
// Define private function definitions.  
// ---------------------------------------------------------------------------
//
void apInit(void)
{
    uartOpen(_DEF_UART1,38400U) ;
    cliOpen(_DEF_UART1,38400U) ;
    //HwTimerSet(CPU_TIMER0,1000U) ; // 1mSec
    //HwTimerIntEnable(CPU_TIMER0);
}
void apMain(void)
{
    uint32_t preTime = 0x00U ;
    uint32_t i = 0x00U ;
    uint16_t LoopCount = 0x00U ;
    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    preTime = millis();

    cliShowMFG();

    while(1)
    {
        if((millis()-preTime) > 500U)
        {
            preTime = millis();
            LoopCount = LoopCount + 1U ;

            if(0x00U == (LoopCount % 2U))
            {
                GPIO_writePin(RED_LED_GPIO,0);
            }
            else {
                GPIO_writePin(RED_LED_GPIO,1);
            }
        }

        if(cliMain() ==  false )
        {
            uartMsgWrite(_DEF_UART1,"CLI Error");
            DelayMs(500);
        }
    }
}

// ---------------------------------------------------------------------------
//  Define Callbacks definitions.
// ---------------------------------------------------------------------------
//
 
// ---------------------------------------------------------------------------
//  Define CLI definitions.
// ---------------------------------------------------------------------------
//
/* Ap.c End Of File !! Well Done */
