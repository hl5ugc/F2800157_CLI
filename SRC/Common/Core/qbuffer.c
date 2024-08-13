/*
 * [ PROJECT   ]  SV_GMS_V100
 * [ License   ]  SAMJIN ELECTRONICS.,Co.Ltd
 * [ Author    ]  Copyright 2024 By HAG-SEONG KANG
 * [ E-MAIL    ]  hl5ugc@nate.com (82)10- 3841-9706
 * [ C  P  U   ]
 * [ Compller  ]  
 * [ Filename  ]  qbuffer.c
 * [ Version   ]  1.0
 * [ Created   ]  2024[¿ÀÈÄ 12:14:31 ]
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



/* Define Includes */
#include "qbuffer.h"
// ---------------------------------------------------------------------------
// Define  Global Function prototypes.
// ---------------------------------------------------------------------------
//
void qbufferInit(void)
{

}

bool qbufferCreate(qUartBuff_t *p_node, char *p_buf, uint16_t length)
{
  bool result = true;

  p_node->in    = 0U;
  p_node->out   = 0U;
  p_node->len   = length;
  p_node->p_buf = p_buf;

  return result;
}

bool qbufferWrite(qUartBuff_t *p_node, const char *p_data, uint16_t length)
{
  bool bRet = true;
  uint16_t u8i = 0x00U ;
  uint16_t u8NextWr = 0x00U ;

  for (u8i=0; u8i<length; u8i++)
  {
    u8NextWr = (p_node->in + 1U) % p_node->len;

    if(u8NextWr != p_node->out)
    {
      if(p_node->p_buf != NULL)
      {
         p_node->p_buf[p_node->in] = p_data[u8i];
      }
      p_node->in = u8NextWr ;
    }
    else
    {
      bRet = false ;
    }
  }

  return bRet;
}

bool qbufferRead(qUartBuff_t *p_node, char *p_data, uint16_t length)
{
  bool bRet = false;
  uint16_t i ;

  for (i=0; i<length; i++)
  {
    if (p_node->out != p_node->in)
    {
      p_data[i] = p_node->p_buf[p_node->out];
      if(++p_node->out >= p_node->len )
      {
        p_node->out = 0 ;
      }
      bRet = true;
    }
  }

  return bRet;
}

bool qbufferReadByte(qUartBuff_t *p_node, char *p_data)
{
  bool bRet = false ;

  if (p_node->out != p_node->in)
  {
    *p_data = p_node->p_buf[p_node->out];
    if(++p_node->out >= p_node->len )
    {
      p_node->out = 0 ;
    }
    bRet = true;
  }
  return bRet;
}
char qbufferRead1Byte(qUartBuff_t *p_node)
{
  char bRet = 0x00U ;

  if (p_node->out != p_node->in)
  {
    bRet = p_node->p_buf[p_node->out];
    if(++p_node->out >= p_node->len )
    {
      p_node->out = 0 ;
    }
  }

  return bRet;
}
/**
 * @brief Function How many bytes in Buffer
 *
 * @param p_node    buffer struct
 * @return uint16_t  Read Available bytes in buffer
 */
uint16_t qbufferRxAvailable(qUartBuff_t *p_node)
{
  uint16_t u8Ret = 0U;

  if(p_node->out == p_node->in ) {
    u8Ret = 0U ;
  }
  else if(p_node->out > p_node->in )
  {
    u8Ret = (uint16_t)(p_node->len - p_node->out );
    u8Ret = (uint16_t)(u8Ret + p_node->in) ;
  }
  else {
    u8Ret = (uint16_t)(p_node->in - p_node->out) ;
  }

  return u8Ret;
}
/*
*/
uint16_t qbufferTxAvailable(qUartBuff_t *p_node)
{
  uint16_t u8Ret  = 0U ;

  if(p_node->in == p_node->out ) {
    u8Ret = p_node->len ;
  }
  else if(p_node->in > p_node->out )
  {
    u8Ret = (uint16_t)(p_node->len - p_node->in );
    u8Ret = (uint16_t)(u8Ret + p_node->out) ;
  }
  else
  {
    u8Ret = (uint16_t)(p_node->out - p_node->in) ;
  }

  return u8Ret;
}

bool qbufferEmpty(qUartBuff_t *p_node)
{
  bool bResult = false ;

  if(p_node->in ==   p_node->out)
  {
    bResult = true ;
  }
  //
  return bResult ;
}
void qbufferFlush(qUartBuff_t *p_node)
{
  p_node->in  = 0U;
  p_node->out = 0U;
}
// ---------------------------------------------------------------------------
// Define private function definitions.
// ---------------------------------------------------------------------------
//

// ---------------------------------------------------------------------------
//  Define Callbacks definitions.
// ---------------------------------------------------------------------------
//
/* qbuffer.c End Of File !! Well Done */
