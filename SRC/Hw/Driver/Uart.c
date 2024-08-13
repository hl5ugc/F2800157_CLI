/*
 * [ PROJECT   ]  F2800157_FW_V100
 * [ License   ]  SAMJIN ELECTRONICS.,Co.Ltd
 * [ Author    ]  Copyright 2024 By HAG-SEONG KANG
 * [ E-MAIL    ]  hl5ugc@nate.com (82)10- 3841-9706
 * [ C  P  U   ]
 * [ Compller  ]  
 * [ Filename  ]  Uart.c
 * [ Version   ]  1.0
 * [ Created   ]  2024[¿ÀÈÄ 3:02:00 ]
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



/* Define Includes */
#include "Uart.h"
#include "qbuffer.h"
#include "dataConvert.h"
#include "sciUart.h"
// ---------------------------------------------------------------------------
//  Define Macros .
// ---------------------------------------------------------------------------
//
#define UART_MAX_CH         1U
#define USE_UART1
// ---------------------------------------------------------------------------
//  Define TypeDef & Constants.
// ---------------------------------------------------------------------------
//
 
// ---------------------------------------------------------------------------
//  Define Private variables.
// ---------------------------------------------------------------------------
//
#ifdef  USE_UART1
#define UARTA_TX_MAX_BUFF 64U
#define UARTA_RX_MAX_BUFF 64U
static  char tx_buff_a[UARTA_TX_MAX_BUFF];
static  char rx_buff_a[UARTA_RX_MAX_BUFF];
static volatile uint16_t useRxEvent = 0U;
static volatile uint16_t useRx1Wait = 0U;
static volatile uint16_t useTx1Wait = 0U;
#endif

static bool is_open[UART_MAX_CH];
static qUartBuff_t qUartTxBuff[UART_MAX_CH];
static qUartBuff_t qUartRxBuff[UART_MAX_CH];
// ---------------------------------------------------------------------------
// Define Private function prototype.
// ---------------------------------------------------------------------------
//

// ---------------------------------------------------------------------------
// Define Callback function prototype.
// ---------------------------------------------------------------------------
//
static void Uart1_Tx_CallBack(void);
static void Uart1_Rx_CallBack(void);
// ---------------------------------------------------------------------------
// Define Public function definitions. 
// ---------------------------------------------------------------------------
//
void uartInit(void)
{
    uint16_t u16i = 0U ;

    for(u16i=0U; u16i<UART_MAX_CH; u16i++)
    {
        is_open[u16i] = false ;
    }
}
bool uartOpen(uint16_t ch, uint32_t bps)
{
    char *pRxd_buff;
    char *pTxd_buff;
    uint16_t u16TxLenth = 0U;
    uint16_t u16RxLenth = 0U;
    (void)bps ;

    if(ch<UART_MAX_CH)
    {
        switch(ch)
        {
            case _DEF_UART1:
                sciUartInit();
                //
                is_open[ch] = true;
                pRxd_buff = &rx_buff_a[0x00U];
                pTxd_buff = &tx_buff_a[0x00U];
                u16TxLenth = UARTA_TX_MAX_BUFF;
                u16RxLenth = UARTA_RX_MAX_BUFF;
                //
                qbufferCreate(&qUartTxBuff[ch], pTxd_buff, u16TxLenth);
                qbufferCreate(&qUartRxBuff[ch], pRxd_buff, u16RxLenth);
                // Tx Rx Callback
                canSetSciCallback(ch,0x00U,Uart1_Tx_CallBack) ;
                canSetSciCallback(ch,0x01U,Uart1_Rx_CallBack) ;
                //
                sciUartRxEn(CPU_SCIA);
                sciUartTxEn(CPU_SCIA);

            break ;
        }
    }

    return (true);
}
/**
 * @brief  Function to read the number of data in the receive buff for communication
 *
 * @param ch        uart Channel
 * @return uint16_t  the number of data in the receive buff
 */
uint16_t uartRXAvailable(uint16_t ch)
{
  uint16_t u16Ret = 0;

  if (ch < UART_MAX_CH)
  {
    switch (ch)
    {
        case _DEF_UART1:
            u16Ret = qbufferRxAvailable(&qUartRxBuff[ch]);
          break;

        default:
          break;
    }
  }
  //
  return (u16Ret);
}
/**
 * @brief  Function to read the number of Available write data
 *         in the transmit buff for communication
 *
 * @param ch        uart Channel
 * @return uint16_t  the number of data in the receive buff
 */
uint16_t uartTXAvailable(uint16_t ch)
{
  uint16_t u16Ret = 0;

  if (ch < UART_MAX_CH)
  {
    switch (ch)
    {
    case _DEF_UART1:

        u16Ret = qbufferTxAvailable(&qUartTxBuff[ch]);

      break;
    default:
      break;
    }
  }
  //
  return (u16Ret);
}
/**
 * @brief   Function to read 1byte data of RX buffs for communication
 *
 * @param   ch        qUartRxBuff[ch]
 * @return  uint16_t   read buffer data 1 byte return
 */
char uartRead(uint16_t ch)
{
    char cResult = 0U;

  if (ch < UART_MAX_CH)
  {
    switch (ch)
    {
        case _DEF_UART1:
          qbufferReadByte(&qUartRxBuff[ch], &cResult);
          break;

        default:
          break;
    }
  }
  return (cResult) ;
}
//
/**
 * @brief Function to read bytes data of RX buffs for communication
 *
 * @param ch        uart channel
 * @param pMsg      read buff
 * @param u16Len     read data length
 * @return uint16_t  read bytes
 */
uint16_t uartReadMsg(uint16_t ch, char *pMsg, uint16_t u16Len)
{
  uint16_t u16Ret = 0;
  //
  if (ch < UART_MAX_CH)
  {
    switch (ch)
    {
        case _DEF_UART1:
          if (u16Len <= qbufferRxAvailable(&qUartRxBuff[ch]))
          {
            qbufferRead(&qUartRxBuff[ch], pMsg, u16Len);
            u16Ret = u16Len;
          }
          break;
        default:
          break;
    }
  }
  //
  return u16Ret;
}

/**
 * @brief Function to Write bytes data of TX buffs for communication
 *
 * @param ch        uart channel
 * @param p_data    write buff
 * @param u16Len     write data bytes
 * @return uint16_t  write bytes
 */
uint16_t uartWrite(uint16_t ch,const char *p_data, uint16_t u16Len)
{
  uint16_t result = 0;
  //uint16_t u8TxData  = 0;

  if (ch < UART_MAX_CH)
  {
    switch (ch)
    {
      case _DEF_UART1:

        while (qbufferEmpty(&qUartTxBuff[ch]) != true) ;
        if (qbufferEmpty(&qUartTxBuff[ch]) == true)
        {
            qbufferFlush(&qUartTxBuff[ch]);
            qbufferWrite(&qUartTxBuff[ch], &p_data[0x00U], u16Len);
            sciUartTxEn(CPU_SCIA);  // Tx Int enable
        }
        break;

      default:
        break;
    }
  }
  //
  return result;
}
/**
 * @brief MSG Send to uart and uint16_t Data Convert to 2bytes ASCII HEX
 *
 * @param ch      Uart Channel
 * @param pBuf    MSG string buffer pointer
 * @param u8Byte  Convert uint16_t Data to 2bytes ASCII HEX
 * @example (p_cli->ch,"\x1B[",line->cursor);
 */
void uartMsgByte2ASC(uint16_t ch, const char * pBuf, uint16_t u8Byte)
{
    char u8Msg[2];
    //
    uartWrite(ch,pBuf, MsgLen(pBuf));
    cvtByte2DASC(u8Byte,&u8Msg[0x00U]);
    //
}
void uartByte2ASC(uint16_t ch, uint16_t u8Byte)
{
    char u8Msg[2];
    //
    cvtByte2DASC(u8Byte, &u8Msg[0x00U]);
    uartWrite(ch, (const char *)u8Msg, 2);
    //
}
void uartMsgByte3ASC(uint16_t ch, const char *pBuf, uint16_t u8Byte)
{
    char u8Msg[3];
    //
    uartWrite(ch, pBuf, MsgLen(pBuf));
    cvtByte3DASC(u8Byte, &u8Msg[0x00U]);
    uartWrite(ch, (const char *)u8Msg, 3);
    //
}
void uartByte3ASC(uint16_t ch, uint16_t u8Byte)
{
    char u8Msg[3];
    //
    cvtByte3DASC(u8Byte, &u8Msg[0x00U]);
    uartWrite(ch, (const char *)u8Msg, 3);
    //
}
void uartMsgWord3DASC(uint16_t ch, const char *pBuf, uint16_t u16Data)
{
    char u8Msg[3];
    //
    uartWrite(ch, pBuf, MsgLen(pBuf));
    cvtWord3DASC(u16Data, &u8Msg[0x00U]);
    uartWrite(ch, (const char *)u8Msg, 3);
}
void uartWord3DASC(uint16_t ch, uint16_t u16Data)
{
    char u8Msg[3];
    //
    cvtWord3DASC(u16Data,&u8Msg[0x00U]);
    uartWrite(ch,  (const char *)u8Msg, 3U);

}
void uartMsgWord4DASC(uint16_t ch, const char *pBuf, uint16_t u16Data)
{
    char u8Msg[4];
    //
    uartWrite(ch, pBuf, MsgLen(pBuf));
    cvtWord4DASC(u16Data,&u8Msg[0x00U]);
    uartWrite(ch, (const char *)u8Msg, 4U);
}
void uartWord4DASC(uint16_t ch, uint16_t u16Data)
{
    char u8Msg[4];
    //
    cvtWord4DASC(u16Data,&u8Msg[0x00U]);
    uartWrite(ch, (const char *)u8Msg, 4U);
}
void uartMsgWord5DASC(uint16_t ch, const char *pBuf, uint16_t u16Data)
{
    char u8Msg[5];
    //
    uartWrite(ch, pBuf, MsgLen(pBuf));
    cvtWord5DASC(u16Data, &u8Msg[0x00U]);
    uartWrite(ch, (const char *)u8Msg, 5U);
}
void uartWord5DASC(uint16_t ch, uint16_t u16Data)
{
    char u8Msg[5];
    //
    cvtWord5DASC(u16Data,&u8Msg[0x00U]);
    uartWrite(ch,(const char *)u8Msg, 5U);
}

/**
 * @brief Msg & uint16_t Data Convert to 2bytes ASCII HEX and Send Uart
 *
 * @param ch      Uart Channel
 * @param pBuf    MSG Buffer Pointer
 * @param u8Data  Convert uint16_t Data to 2bytes ASCII HEX
 * @example
 */
void uartMsgByte2Hex(uint16_t ch,const char *pBuf, uint16_t u8Data)
{
  char u8Msg[2];
  //
  uartWrite(ch, pBuf, MsgLen(pBuf));
  cvtByte2HEX(u8Data, &u8Msg[0x00U]);
  uartWrite(ch, u8Msg, 2);
}
/**
 * @brief uint16_t Data Convert to 2bytes ASCII HEX and Send Uart
 *
 * @param ch      Uart Channel
 * @param u8Data  Convert uint16_t Data to 2bytes ASCII HEX
 */
void uartByte2Hex(uint16_t ch, uint16_t u8Data)
{
  char u8Msg[2];
  //
  cvtByte2HEX(u8Data, &u8Msg[0x00U]);
  uartWrite(ch, u8Msg, 2);
}
/**
 * @brief   MSG & uint16_t Data Convert to 4bytes ASCII HEX and Send Uart
 *
 * @param ch      Uart Channel
 * @param pBuf    MSG Buffer Pointer
 * @param u16Data Convert uint16_t Data to 4bytes ASCII HEX
 */
void uartMsgWord4Hex(uint16_t ch, const char *pBuf, uint16_t u16Data)
{
  char u8Msg[4];
  //
  uartWrite(ch, pBuf, MsgLen(pBuf));
  cvtWord4HEX(u16Data, &u8Msg[0x00U]);
  uartWrite(ch, u8Msg, 4);
  //
}
/**
 * @brief uint16_t Data Convert to 4bytes ASCII HEX and Send Uart
 *
 * @param ch      Uart Channel
 * @param u8Data  Convert uint16_t Data to 4bytes ASCII HEX
 */
void uartWord4Hex(uint16_t ch, uint16_t u16Data)
{
  char u8Msg[4];
  //
  cvtWord4HEX(u16Data, &u8Msg[0x00U]);
  uartWrite(ch, u8Msg, 4);
  //
}
/**
 * @brief   MSG & uint16_t Data Convert to 7bytes ASCII Binary and Send Uart
 *
 * @param ch
 * @param pBuf
 * @param u8Data
 */
void uartMsgByte7BASC(uint16_t ch, const char *pBuf, uint16_t u8Data)
{
  char u8Msg[8];
  //
  uartWrite(ch, pBuf, MsgLen(pBuf));
  cvtByte7BASC(u8Data, &u8Msg[0x00U]);
  uartWrite(ch, u8Msg, 8);
}
void uartByte7BASC(uint16_t ch, uint16_t u8Data)
{
  char u8Msg[8];
  //
  cvtByte7BASC(u8Data, &u8Msg[0x00U]);
  uartWrite(ch, u8Msg, 8);
}
// ---------------------------------------------------------------------
uint16_t uartMsgWrite(uint16_t ch, const char *pBuf)
{
  uint16_t u16Ret = 0x00U;
  u16Ret = uartWrite(ch, pBuf, MsgLen(pBuf));
  return (u16Ret);
}
//uint16_t uartMsgWrite(uint16_t ch, const uint16_t *pBuf)
//{
//  uint16_t u16Ret = 0x00U;
//  u16Ret = uartWrite(ch, (const uint16_t *)pBuf, MsgLen(pBuf));
//  return (u16Ret);
//}
/**
 * @brief Cal_. Wait Delay time for long massages.
 *
 * @param len :count  out bytes
 */
//void com_OutDelay(uint16_t len)
//{
//  uint16_t u8Delay_time = 0x01U ;
//  if(len > COM_OUT_DELAY )
//  {
//    u8Delay_time = len / COM_OUT_DELAY ;
//    if( (len % COM_OUT_DELAY) != 0x00U )
//    {
//      u8Delay_time = u8Delay_time + 1U ;
//    }
//  }
//  delay_ms(u8Delay_time);
//}
uint16_t uartFlashWrite(uint16_t ch, char *pBuf)
{
  uint16_t u16Ret = 0x00U;
  char u8Msg[32] = {
      0x00U,
  };
  uint16_t u16Len = 0x00U;

  while (pBuf[u16Len] != 0x00U)
  {
    u8Msg[u16Len] = pBuf[u16Len];
    u16Len++;
  }
  u16Ret = uartWrite(ch, u8Msg, u16Len);

  return (u16Ret);
}
uint16_t uartPrintf(uint16_t ch, char *pBuf, uint16_t u16Len)
{
  uint16_t u16Ret = 0x00U;
  u16Ret = uartWrite(ch, pBuf, u16Len);
  return (u16Ret);
}
/**
 * @brief max data 40bytes for printf
 *
 * @param ch    : Com Port
 * @param fmt   :
 * @param ...
 * @return uint16_t : output length
 */
/*
      'i' - the function argument is a signed decimal integer;
      'd' - the function argument is a signed decimal integer;
      'u' - the function argument is an unsigned decimal integer;
      'e' - the function argument is a float, that will be outputted using the [-]d.dddddd e[¢®¨ú]dd format
      'E' - the function argument is a float, that will be outputted using the [-]d.dddddd E[¢®¨ú]dd format
      'f' - the function argument is a float, that will be outputted using the [-]ddd.dddddd  format
      'x' - the function argument is an unsigned hexadecimal integer, that will be outputted with lowercase characters;
      'X' - the function argument is an unsigned hexadecimal integer, that will be outputted with with uppercase characters;
      'c' - the function argument is a single character;
      's' - the function argument is a pointer to a null terminated char string located in RAM;
      'p' - the function argument is a pointer to a null terminated char string located in FLASH;
      '%' - the '%' character will be outputted.
*/

uint16_t uartflashPrintf(uint16_t ch, char *fmt, ...)
{
  uint16_t u16Ret = 0x00U;
  va_list args;
  char buf[128];
  //
  va_start(args, fmt);
  u16Ret = vsprintf(buf, fmt, args);
  va_end(args);
  //
  u16Ret = uartWrite(ch, (char *)buf, u16Ret);
  //
  return (u16Ret);
}

// ---------------------------------------------------------------------------
// Define private function definitions.  
// ---------------------------------------------------------------------------
//
 
// ---------------------------------------------------------------------------
//  Define Callbacks definitions.
// ---------------------------------------------------------------------------
//
static void Uart1_Tx_CallBack(void)
{
    uint16_t u16Ret = 0x00U ;
    uint16_t i = 0U ;
    uint16_t u16TxFifo = 0x00U ;
    char     txData = 0x00U ;

    u16Ret = qbufferRxAvailable(&qUartTxBuff[0x00U]);

    if(u16Ret > 0U)
    {
        u16TxFifo =(16U - SCI_getTxFIFOStatus(SCIA_BASE)) ;
        if(u16Ret < u16TxFifo)
        {
            for(i=0; i<u16Ret; i++ )
            {
                qbufferReadByte(&qUartTxBuff[0x00U], &txData);
                HWREGH(CPU_SCIA + SCI_O_TXBUF) = txData ;
            }
        }
        else
        {
            for(i=0; i<u16TxFifo ; i++ )
            {
                qbufferReadByte(&qUartTxBuff[0x00U], &txData);
                HWREGH(CPU_SCIA + SCI_O_TXBUF) = txData ;
            }
        }
 
    }
    else
    {
        SCI_disableInterrupt(CPU_SCIA,SCI_INT_TXFF);
    }

    SCI_clearInterruptStatus(SCIA_BASE, SCI_INT_TXFF);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP9);
}
static void Uart1_Rx_CallBack(void)
{
    char     rxData = 0x00U ;
    // check Rxd Fifo

    rxData = (uint16_t)(HWREGH(SCIA_BASE + SCI_O_RXBUF) & SCI_RXBUF_SAR_M);
    qbufferWrite(&qUartRxBuff[0x00U], &rxData, 1U);

    SCI_clearOverflowStatus(SCIA_BASE);
    SCI_clearInterruptStatus(SCIA_BASE, SCI_INT_RXFF);
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP9);
}
// ---------------------------------------------------------------------------
//  Define CLI definitions.
// ---------------------------------------------------------------------------
//
/* Uart.c End Of File !! Well Done */
