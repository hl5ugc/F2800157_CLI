/*
 * [ PROJECT   ]  A60132237_V00
 * [ License   ]  SAMJIN ELECTRONICS.,Co.Ltd
 * [ Author    ]  Copyright 2024 By HAG-SEONG KANG
 * [ E-MAIL    ]  hl5ugc@nate.com (82)10- 3841-9706
 * [ C  P  U   ]
 * [ Compller  ]  
 * [ Filename  ]  def.h
 * [ Version   ]  1.0
 * [ Created   ]  2024[¿ÀÈÄ 5:01:16 ]
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
#ifndef SRC_COMMON_DEF_H_
#define SRC_COMMON_DEF_H_

#ifdef __cplusplus
extern "C" {
#endif
/* Includes */
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

#include "device.h"
#include "driverlib.h"

// ---------------------------------------------------------------------------
// Define Global define
// --------------------------------------------------------------------------- 
// 
#define _DEF_OFF        0x0000U
#define _DEF_ON         0x0001U
//
#define _DEF_BIT0       0x0001U
#define _DEF_BIT1       0x0002U
#define _DEF_BIT2       0x0004U
#define _DEF_BIT3       0x0008U
#define _DEF_BIT4       0x0010U
#define _DEF_BIT5       0x0020U
#define _DEF_BIT6       0x0040U
#define _DEF_BIT7       0x0080U
#define _DEF_BIT8       0x0100U
#define _DEF_BIT9       0x0200U
#define _DEF_BIT10      0x0400U
#define _DEF_BIT11      0x0800U
#define _DEF_BIT12      0x1000U
#define _DEF_BIT13      0x2000U
#define _DEF_BIT14      0x4000U
#define _DEF_BIT15      0x8000U

#define _DEF_UART1      0x00U
#define _DEF_UART2      0x01U
#define _DEF_UART3      0x02U
// ---------------------------------------------------------------------------
// Define typedef
// --------------------------------------------------------------------------- 
// 
// ---------------------------------------------------------------------------
// Define  Global Function prototypes.
// --------------------------------------------------------------------------- 
//
#define HWREGH(x)       (*((volatile uint16_t *)(x)))


#ifdef __cplusplus
}
#endif
#endif /* def.h End Of File !! Well Done */
