/*
 * [ PROJECT   ]  F2800157_FW_V100
 * [ License   ]  SAMJIN ELECTRONICS.,Co.Ltd
 * [ Author    ]  Copyright 2024 By HAG-SEONG KANG
 * [ E-MAIL    ]  hl5ugc@nate.com (82)10- 3841-9706
 * [ C  P  U   ]
 * [ Compller  ]  
 * [ Filename  ]  Uart.h
 * [ Version   ]  1.0
 * [ Created   ]  2024[¿ÀÈÄ 3:02:09 ]
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
 * Hagseong Kang  2024. 8. 13.    First release of this file
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
#ifndef SRC_COMMON_INCLUDE_UART_H_
#define SRC_COMMON_INCLUDE_UART_H_

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
// ---------------------------------------------------------------------------
// Define  Global Function prototypes.
// --------------------------------------------------------------------------- 
//
void uartInit(void);
bool uartOpen(uint16_t ch, uint32_t bps);
uint16_t uartRXAvailable(uint16_t ch) ;
uint16_t uartTXAvailable(uint16_t ch) ;
char uartRead(uint16_t ch);
uint16_t uartWrite(uint16_t ch, const char *p_data, uint16_t u8Len);
//uint16_t uartMsgWrite(uint16_t ch,const uint16_t *pBuf);
uint16_t uartMsgWrite(uint16_t ch, const char *pBuf);

void uartMsgByte2ASC(uint16_t ch,const char *pBuf,uint16_t u8Byte);
void uartByte2ASC(uint16_t ch, uint16_t u8Byte);
void uartMsgByte3ASC(uint16_t ch,const char *pBuf,uint16_t u8Byte);
void uartByte3ASC(uint16_t ch,uint16_t u8Byte);
void uartMsgWord3DASC(uint16_t ch,const char *pBuf,uint16_t u16Data);
void uartWord3DASC(uint16_t ch, uint16_t u16Data);
void uartMsgWord4DASC(uint16_t ch,const char *pBuf,uint16_t u16Data);
void uartWord4DASC(uint16_t ch, uint16_t u16Data);
void uartMsgWord5DASC(uint16_t ch,const char *pBuf,uint16_t u16Data);
void uartWord5DASC(uint16_t ch, uint16_t u16Data);

void uartMsgByte2Hex(uint16_t ch,const char *pBuf,uint16_t u8Data);
void uartByte2Hex(uint16_t ch,uint16_t u8Data);
void uartMsgWord4Hex(uint16_t ch,const char *pBuf,uint16_t u16Data);
void uartWord4Hex(uint16_t ch,uint16_t u16Data);

void uartMsgByte7BASC(uint16_t ch,const char *pBuf,uint16_t u8Data);
void uartByte7BASC(uint16_t ch,uint16_t u8Data);

uint16_t uartflashPrintf(uint16_t ch, char *fmt, ...);
uint16_t uartPrintf(uint16_t ch,char *pBuf,uint16_t u8Len);
#ifdef __cplusplus
}
#endif
#endif /* Uart.h End Of File !! Well Done */
