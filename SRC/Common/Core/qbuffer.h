/*
 * [ PROJECT   ]  SV_GMS_V100
 * [ License   ]  SAMJIN ELECTRONICS.,Co.Ltd
 * [ Author    ]  Copyright 2024 By HAG-SEONG KANG
 * [ E-MAIL    ]  hl5ugc@nate.com (82)10- 3841-9706
 * [ C  P  U   ]
 * [ Compller  ]  
 * [ Filename  ]  qbiffer.h
 * [ Version   ]  1.0
 * [ Created   ]  2024[¿ÀÈÄ 12:14:21 ]
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
 * Hagseong Kang  2024. 8. 2.    First release of this file
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
#ifndef SRC_COMMON_CORE_QBUFFER_H_
#define SRC_COMMON_CORE_QBUFFER_H_

#ifdef __cplusplus
extern "C" {
#endif
/* Includes */
#include "def.h"


 
// ---------------------------------------------------------------------------
// Define Global define
// --------------------------------------------------------------------------- 
// 

// ---------------------------------------------------------------------------
// Define typedef
// --------------------------------------------------------------------------- 
// 
typedef struct
{
  uint16_t in;
  uint16_t out;
  uint16_t len;

  char *p_buf;
} qUartBuff_t;
// ---------------------------------------------------------------------------
// Define  Global Function prototypes.
// --------------------------------------------------------------------------- 
//
void      qbufferInit(void);
bool      qbufferCreate(qUartBuff_t *p_node, char *p_buf, uint16_t length);
bool      qbufferWrite(qUartBuff_t *p_node,const char *p_data, uint16_t length);
bool      qbufferRead(qUartBuff_t *p_node,  char *p_data, uint16_t length);
bool      qbufferReadByte(qUartBuff_t *p_node, char *p_data);
char      qbufferRead1Byte(qUartBuff_t *p_node);
uint16_t  qbufferRxAvailable(qUartBuff_t *p_node);
uint16_t  qbufferTxAvailable(qUartBuff_t *p_node);
bool      qbufferEmpty(qUartBuff_t *p_node);
void      qbufferFlush(qUartBuff_t *p_node);

#ifdef __cplusplus
}
#endif
#endif /* qbiffer.h End Of File !! Well Done */
