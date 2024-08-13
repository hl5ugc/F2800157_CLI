/*
 * [ PROJECT   ]  A60132237_V00
 * [ License   ]  SAMJIN ELECTRONICS.,Co.Ltd
 * [ Author    ]  Copyright 2024 By HAG-SEONG KANG
 * [ E-MAIL    ]  hl5ugc@nate.com (82)10- 3841-9706
 * [ C  P  U   ]
 * [ Compller  ]  
 * [ Filename  ]  sciUart.h
 * [ Version   ]  1.0
 * [ Created   ]  2024[¿ÀÈÄ 6:23:05 ]
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
#ifndef SRC_COMMON_INCLUDE_SCIUART_H_
#define SRC_COMMON_INCLUDE_SCIUART_H_

#ifdef __cplusplus
extern "C" {
#endif
/* Includes */
#include "hw_def.h"

// ---------------------------------------------------------------------------
// Define Global define
// --------------------------------------------------------------------------- 
// 
#define SCI_MAX_CB          1U  // SCIa
// ---------------------------------------------------------------------------
// Define typedef
// --------------------------------------------------------------------------- 
// 
typedef enum
{
    CPU_SCIA  = SCIA_BASE ,
    CPU_SCIB  = SCIB_BASE ,
    CPU_SCIC  = SCIC_BASE
} SCI_Ch_e;
// ---------------------------------------------------------------------------
// Define  Global Function prototypes.
// --------------------------------------------------------------------------- 
//
void sciUartInit(void);

void sciUartTxEn(SCI_Ch_e ch);
void sciUartRxEn(SCI_Ch_e ch);
char sciUartReadByte(SCI_Ch_e ch);
void sciUartSendByte(SCI_Ch_e ch,uint16_t sendData);

void canSetSciCallback(uint8_t ch, uint16_t TxRx , void (*callBack)(void));
#ifdef __cplusplus
}
#endif
#endif /* sciUart.h End Of File !! Well Done */
