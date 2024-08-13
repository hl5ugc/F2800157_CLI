/*
 * [ PROJECT   ]  A60132237_V00
 * [ License   ]  SAMJIN ELECTRONICS.,Co.Ltd
 * [ Author    ]  Copyright 2024 By HAG-SEONG KANG
 * [ E-MAIL    ]  hl5ugc@nate.com (82)10- 3841-9706
 * [ C  P  U   ]
 * [ Compller  ]  
 * [ Filename  ]  hwTimer.h
 * [ Version   ]  1.0
 * [ Created   ]  2024[¿ÀÈÄ 5:15:55 ]
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


/* Mutiple includes protection */
#ifndef SRC_COMMON_INCLUDE_HWTIMER_H_
#define SRC_COMMON_INCLUDE_HWTIMER_H_

#ifdef __cplusplus
extern "C" {
#endif
/* Includes */
#include "hw_def.h"


 
// ---------------------------------------------------------------------------
// Define Global define
// --------------------------------------------------------------------------- 
// 

// ---------------------------------------------------------------------------
// Define typedef
// --------------------------------------------------------------------------- 
// 
typedef enum
{
    CPU_TIMER0  = CPUTIMER0_BASE ,
    CPU_TIMER1  = CPUTIMER1_BASE ,
    CPU_TIMER2  = CPUTIMER2_BASE
} Timer_Ch_e;
// ---------------------------------------------------------------------------
// Define  Global Function prototypes.
// --------------------------------------------------------------------------- 
//
void HwTimerInit(void);
void HwTimerSet(Timer_Ch_e ch,uint16_t u16uSec);
void HwTimerIntEnable(Timer_Ch_e ch);

uint32_t millis(void);
void DelayMs(uint32_t u32Delay);

uint16_t HwTimerGetEvent(void);
void HwTimerSetEvent(uint16_t u16Event);
void HwTimerClearEvent(uint16_t u16Event);


#ifdef __cplusplus
}
#endif
#endif /* hwTimer.h End Of File !! Well Done */
