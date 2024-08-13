/*
 * [ PROJECT   ]  A60132237_V00
 * [ License   ]  SAMJIN ELECTRONICS.,Co.Ltd
 * [ Author    ]  Copyright 2024 By HAG-SEONG KANG
 * [ E-MAIL    ]  hl5ugc@nate.com (82)10- 3841-9706
 * [ C  P  U   ]
 * [ Compller  ]  
 * [ Filename  ]  hw_def.h
 * [ Version   ]  1.0
 * [ Created   ]  2024[¿ÀÈÄ 5:03:50 ]
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
#ifndef SRC_HW_HW_DEF_H_
#define SRC_HW_HW_DEF_H_

#ifdef __cplusplus
extern "C" {
#endif
/* Includes */
#include "def.h"



 
// ---------------------------------------------------------------------------
// Define Global define
// --------------------------------------------------------------------------- 
// 
#define _USE_HW_TIMER0
#define      HW_TIMER0_MAX_CB         5


//#define _USE_HW_UART
//#define      HW_UART_MAX_CH           1
//#define      HW_UART_PORT             _DEF_UART1
//#define      HW_COM_OUT_DELAY         3 // 38400

#define _USE_HW_CLI
#define _CLI_UART     _DEF_UART1

#define      HW_CLI_LINE_HIS_MAX      4
#define      HW_CLI_LINE_BUF_MAX      32
#define      HW_CLI_CMD_LIST_MAX      16
#define      HW_CLI_CMD_NAME_MAX      16
#define      HW_CLI_HLP_NAME_MAX      16

// ---------------------------------------------------------------------------
// Define typedef
// --------------------------------------------------------------------------- 
// 
// ---------------------------------------------------------------------------
// Define  Global Function prototypes.
// --------------------------------------------------------------------------- 
//



#ifdef __cplusplus
}
#endif
#endif /* hw_def.h End Of File !! Well Done */
