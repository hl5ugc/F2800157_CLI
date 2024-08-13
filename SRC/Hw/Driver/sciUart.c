/*
 * [ PROJECT   ]  A60132237_V00
 * [ License   ]  SAMJIN ELECTRONICS.,Co.Ltd
 * [ Author    ]  Copyright 2024 By HAG-SEONG KANG
 * [ E-MAIL    ]  hl5ugc@nate.com (82)10- 3841-9706
 * [ C  P  U   ]
 * [ Compller  ]  
 * [ Filename  ]  sciUart.c
 * [ Version   ]  1.0
 * [ Created   ]  2024[¿ÀÈÄ 6:22:53 ]
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



/* Define Includes */
#include "sciUart.h"

// ---------------------------------------------------------------------------
//  Define Macros .
// ---------------------------------------------------------------------------
//

// ---------------------------------------------------------------------------
//  Define TypeDef & Constants.
// ---------------------------------------------------------------------------
//
typedef struct
{
    void (*callBack)(void) ;

} SCI_CB_tbl_t ;

typedef void (*cbSCi_t)(void);
// ---------------------------------------------------------------------------
//  Define Private variables.
// ---------------------------------------------------------------------------
//
static  SCI_CB_tbl_t SCITX_CB_tbl[SCI_MAX_CB] ;
static  SCI_CB_tbl_t SCIRX_CB_tbl[SCI_MAX_CB] ;
// ---------------------------------------------------------------------------
// Define Private function prototype.
// ---------------------------------------------------------------------------
//
static void sciaGPIOSet(void);
static void initSCIAFIFO(void);
// ---------------------------------------------------------------------------
// Define Callback function prototype.
// ---------------------------------------------------------------------------
//
__interrupt void sciaRXFIFOISR(void);
__interrupt void sciaTXFIFOISR(void);
// ---------------------------------------------------------------------------
// Define Public function definitions. 
// ---------------------------------------------------------------------------
//
 void sciUartInit(void)
 {
     uint16_t u16i = 0x00U ;

     sciaGPIOSet();
     //
     for(u16i = 0U ; u16i<SCI_MAX_CB ; u16i++)
     {
         SCIRX_CB_tbl[u16i].callBack = NULL ;
         SCITX_CB_tbl[u16i].callBack = NULL ;
     }
     // Interrupts that are used in this example are re-mapped to
     // ISR functions found within this file.
     //
     Interrupt_register(INT_SCIA_RX, sciaRXFIFOISR);
     Interrupt_register(INT_SCIA_TX, sciaTXFIFOISR);
     //
     // Initialize the Device Peripherals:
     //
     initSCIAFIFO();
     // buffer Init...
     Interrupt_enable(INT_SCIA_RX);
     Interrupt_enable(INT_SCIA_TX);

     Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP9);
 }
 /**
  * @brief Function to Write byte data of TX BUFF
  *
  * @param ch        uart channel base address
  * @param sendData  write data
  */
void sciUartSendByte(SCI_Ch_e ch,uint16_t sendData)
{

    HWREGH(ch + SCI_O_TXBUF) = (sendData & 0x00FFU) ;

}
char sciUartReadByte(SCI_Ch_e ch)
{
    char u16Ret = 0x00U ;
    u16Ret = (char)(HWREGH(ch + SCI_O_RXBUF) & 0x00FFU);
    return (u16Ret);
}
void sciUartTxEn(SCI_Ch_e ch)
{
    SCI_enableInterrupt(ch,  SCI_INT_TXFF);
}
void sciUartRxEn(SCI_Ch_e ch)
{
    SCI_performSoftwareReset(ch);

    SCI_resetTxFIFO(ch);
    SCI_resetRxFIFO(ch);
}
// ---------------------------------------------------------------------------
// Define private function definitions.  
// ---------------------------------------------------------------------------
//
static void sciaGPIOSet(void)
{
    //
    // GPIO28 is the SCI Rx pin.
    //
    GPIO_setPinConfig(DEVICE_GPIO_CFG_SCIRXDA);
    GPIO_setDirectionMode(28U, GPIO_DIR_MODE_IN);
    GPIO_setPadConfig(28U, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(28U, GPIO_QUAL_ASYNC);
    //
    // GPIO29 is the SCI Tx pin.
    //
    GPIO_setPinConfig(DEVICE_GPIO_CFG_SCITXDA);
    GPIO_setDirectionMode(29U, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(29U, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(29U, GPIO_QUAL_ASYNC);
}
//
// initSCIAFIFO - Configure SCIA FIFO
//
static void initSCIAFIFO(void)
{
    //
    // 8 char bits, 1 stop bit, no parity. Baud rate is 38400.
    //
    SCI_setConfig(SCIA_BASE, DEVICE_LSPCLK_FREQ, 38400U, (SCI_CONFIG_WLEN_8 |
                                                        SCI_CONFIG_STOP_ONE |
                                                        SCI_CONFIG_PAR_NONE));
    SCI_enableModule(SCIA_BASE);
    //SCI_enableLoopback(SCIA_BASE);
    SCI_resetChannels(SCIA_BASE);
    SCI_enableFIFO(SCIA_BASE);
    //
    // RX and TX FIFO Interrupts Enabled
    //
    //SCI_enableInterrupt(SCIA_BASE, (SCI_INT_RXFF | SCI_INT_TXFF));
    SCI_enableInterrupt(SCIA_BASE, SCI_INT_RXFF );
    SCI_disableInterrupt(SCIA_BASE, SCI_INT_RXERR);

    //
    // The transmit FIFO generates an interrupt when FIFO status
    // bits are less than or equal to 2 out of 16 words
    // The receive FIFO generates an interrupt when FIFO status
    // bits are greater than equal to 2 out of 16 words
    //
    SCI_setFIFOInterruptLevel(SCIA_BASE, SCI_FIFO_TX0, SCI_FIFO_RX1);
    SCI_performSoftwareReset(SCIA_BASE);

    SCI_resetTxFIFO(SCIA_BASE);
    SCI_resetRxFIFO(SCIA_BASE);
}
//
// ---------------------------------------------------------------------------
//  Define Callbacks definitions.
// ---------------------------------------------------------------------------
//
void canSetSciCallback(uint8_t ch, uint16_t TxRx , void (*callBack)(void))
{
  if(ch < SCI_MAX_CB )
  {
      if(TxRx == 0x00U)
      {
          if(SCITX_CB_tbl[ch].callBack == NULL )
          {
              SCITX_CB_tbl[ch].callBack = callBack ;
          }
      }
      else
      {
          if(SCIRX_CB_tbl[ch].callBack == NULL )
          {
              SCIRX_CB_tbl[ch].callBack = callBack ;
          }
      }
  }
}
//
// sciaTXFIFOISR - SCIA Transmit FIFO ISR
//
 __interrupt void sciaTXFIFOISR(void)
{
     (*SCITX_CB_tbl[0U].callBack)() ;
}

//
// sciaRXFIFOISR - SCIA Receive FIFO ISR
//
 __interrupt void sciaRXFIFOISR(void)
{
     (*SCIRX_CB_tbl[0U].callBack)() ;
}
// ---------------------------------------------------------------------------
//  Define CLI definitions.
// ---------------------------------------------------------------------------
//
/* sciUart.c End Of File !! Well Done */
