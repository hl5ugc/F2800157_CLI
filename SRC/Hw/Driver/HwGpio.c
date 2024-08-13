/*
 * [ PROJECT   ]  F2800157_FW_V100
 * [ License   ]  SAMJIN ELECTRONICS.,Co.Ltd
 * [ Author    ]  Copyright 2024 By HAG-SEONG KANG
 * [ E-MAIL    ]  hl5ugc@nate.com (82)10- 3841-9706
 * [ C  P  U   ]
 * [ Compller  ]  
 * [ Filename  ]  HwGpio.c
 * [ Version   ]  1.0
 * [ Created   ]  2024[¿ÀÈÄ 4:02:28 ]
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
 * Hagseong Kang  2024. 8. 5.    First release of this file
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
#include "HwGpio.h"
#include "cli.h"
#include "HwTimer.h"
#include "uart.h"
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
 
// ---------------------------------------------------------------------------
// Define Private function prototype.
// ---------------------------------------------------------------------------
//
void LED_GPIO_init(void);
// ---------------------------------------------------------------------------
// Define Callback function prototype.
// ---------------------------------------------------------------------------
//

static void cliGpio(cli_args_t *args);
// ---------------------------------------------------------------------------
// Define Public function definitions. 
// ---------------------------------------------------------------------------
//
void HwGpioInit(void)
{
    EALLOW;

    LED_GPIO_init();

    EDIS;

    cliAdd("GPIO","[1/2]",cliGpio);
}
 
// ---------------------------------------------------------------------------
// Define private function definitions.  
// ---------------------------------------------------------------------------
//
void LED_GPIO_init(void)
{
    GPIO_setPinConfig(GPIO_35_GPIO35);
    GPIO_setPadConfig(RED_LED_GPIO, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(RED_LED_GPIO, GPIO_QUAL_SYNC);
    GPIO_setDirectionMode(RED_LED_GPIO, GPIO_DIR_MODE_OUT);
    GPIO_writePin(RED_LED_GPIO,1U);

    GPIO_setPinConfig(GPIO_49_GPIO49);
    GPIO_setPadConfig(GREEN_LED_GPIO, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(GREEN_LED_GPIO, GPIO_QUAL_SYNC);
    GPIO_setDirectionMode(GREEN_LED_GPIO, GPIO_DIR_MODE_OUT);
    GPIO_writePin(GREEN_LED_GPIO,1U);

    GPIO_setPinConfig(GPIO_22_GPIO22);
    GPIO_setPadConfig(22U, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(22U, GPIO_QUAL_SYNC);
    GPIO_setDirectionMode(22U, GPIO_DIR_MODE_OUT);
    GPIO_writePin(22U,1U);
}
// ---------------------------------------------------------------------------
//  Define Callbacks definitions.
// ---------------------------------------------------------------------------
//
 

// ---------------------------------------------------------------------------
//  Define CLI definitions.
// ---------------------------------------------------------------------------
//
void cliGpio(cli_args_t *args)
{
  uint16_t u16Ret = 0x01U;
  uint16_t u16SelectPin = 0x00U ;

  if(args->argc == 1)
  {
    u16SelectPin = (uint16_t)args->getData(0) ; // ASCII DECMAL & HEX Convert to binary

    if((u16SelectPin >= 0x01U) && (u16SelectPin <= 49U))
    {
        u16Ret = 0x00U;
        while(cliKeepLoop())
        {
            GPIO_writePin(u16SelectPin,1U);
            DelayMs(200);
            GPIO_writePin(u16SelectPin,0U);
            DelayMs(200);
        }
    }
  }
  //
  if(u16Ret != 0x00)
  {
    uartMsgWrite(_DEF_UART1,"hl5ugc>> GPIO [0..32] \r\n");  DelayMs(50);
  }
}
/* HwGpio.c End Of File !! Well Done */
