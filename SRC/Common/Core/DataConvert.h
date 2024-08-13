/*
 * [ PROJECT   ]  SV_GMS_V100
 * [ License   ]  SAMJIN ELECTRONICS.,Co.Ltd
 * [ Author    ]  Copyright 2024 By HAG-SEONG KANG
 * [ E-MAIL    ]  hl5ugc@nate.com (82)10- 3841-9706
 * [ C  P  U   ]
 * [ Compller  ]  
 * [ Filename  ]  DataConvert.h
 * [ Version   ]  1.0
 * [ Created   ]  2024[¿ÀÈÄ 2:19:46 ]
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
#ifndef SRC_COMMON_CORE_DATACONVERT_H_
#define SRC_COMMON_CORE_DATACONVERT_H_

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
// ---------------------------------------------------------------------------
// Define  Global Function prototypes.
// --------------------------------------------------------------------------- 
//
uint16_t MsgLen(const char *pBuff);
uint16_t BuffLen(const uint16_t *pBuff);

void cvtByte2DASC(uint16_t u8Data,char * const pBuff);
void cvtByte3DASC(uint16_t u8Data,char * const pBuff);
void cvtWord3DASC(uint16_t u16Data,char * const pBuff);
void cvtWord4DASC(uint16_t u16Data,char * const pBuff);
void cvtWord5DASC(uint16_t u16Data,char * const pBuff);
void cvtByte2HEX(uint16_t u8Data,char * const pBuff);
void cvtWord4HEX(uint16_t u16Data,char * const pBuff);
void cvtByte7BASC(uint16_t u8Data,char * const pBuff);
void cvt2HEXBin(const char * pSBuff , uint16_t * const pData);
void cvt4HEXBin(const char * pSBuff , uint16_t * const pData);
void cvt6HEXBin(const char * pSBuff , uint32_t * const pData);
void cvt6ASCBin(const char * pBuff ,  uint16_t * const pData);
#ifdef __cplusplus
}
#endif
#endif /* DataConvert.h End Of File !! Well Done */
