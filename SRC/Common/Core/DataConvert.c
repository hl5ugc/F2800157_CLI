/*
 * [ PROJECT   ]  SV_GMS_V100
 * [ License   ]  SAMJIN ELECTRONICS.,Co.Ltd
 * [ Author    ]  Copyright 2024 By HAG-SEONG KANG
 * [ E-MAIL    ]  hl5ugc@nate.com (82)10- 3841-9706
 * [ C  P  U   ]
 * [ Compller  ]  
 * [ Filename  ]  DataConvert.c
 * [ Version   ]  1.0
 * [ Created   ]  2024[¿ÀÈÄ 2:19:37 ]
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
#include "DataConvert.h"
 
// ---------------------------------------------------------------------------
//  Define Macros .
// ---------------------------------------------------------------------------
//
 
// ---------------------------------------------------------------------------
//  Define TypeDef & Constants.
// ---------------------------------------------------------------------------
//
 
// ---------------------------------------------------------------------------
//  Define Private variables.
// ---------------------------------------------------------------------------
//
 
// ---------------------------------------------------------------------------
// Define Private function prototype.
// ---------------------------------------------------------------------------
//
static char     HexLowToUpper(const char LowerAlpabet);
static uint16_t hex2bin(const char * pSBuff);
static uint16_t asc2bin(const char * pBuff);

// ---------------------------------------------------------------------------
// Define Callback function prototype.
// ---------------------------------------------------------------------------
//

// ---------------------------------------------------------------------------
// Define Public function definitions. 
// ---------------------------------------------------------------------------
//
//
uint16_t MsgLen(const char *pBuff)
{
    uint16_t u16Ret = 0x00U;

    while(pBuff[u16Ret] != '\0')
    {
        u16Ret++ ;
        if(u16Ret > 128U) { break ; }
    }

    return (u16Ret);
}
uint16_t BuffLen(const uint16_t *pBuff)
{
    uint16_t u16Ret = 0x00U;

    while(pBuff[u16Ret] != '\0')
    {
        u16Ret++ ;
        if(u16Ret > 128U) { break ; }
    }

    return (u16Ret);
}
/*
 * @brief Byte data convert to 2digit ASCII Decimal
 *
 */
void cvtByte2DASC(uint16_t u8Data,char * const pBuff)
{
    uint16_t u8Cal = 0x00U ;
    //
    if(u8Data > 99U) { u8Data =  u8Data % 100U ; }
    //
    u8Cal =  u8Data / 10U ;
    pBuff[0x00U] = (u8Cal + 0x30U) & 0x00FFU ;
    //
    u8Cal =  u8Data % 10U ;
    pBuff[0x01U] = (u8Cal + 0x30U) & 0x00FFU ;
}
/*
 * @brief
 *
 */
void cvtByte3DASC(uint16_t u8Data,char * const pBuff)
{
    uint16_t u8Cal = 0x00U ;
    uint16_t u8Cal2 = 0x00U ;
    //
    u8Cal =  u8Data / 100U ;
    pBuff[0x00U] = (u8Cal + 0x30U) & 0x00FFU ;
    //
    u8Cal =  u8Data % 100U ;
    u8Cal2 = u8Cal / 10U ;
    pBuff[0x01U] = (u8Cal2 + 0x30U) & 0x00FFU ;
    //
    u8Cal2 =  u8Cal % 10U ;
    pBuff[0x02U] = (u8Cal2 + 0x30U) & 0x00FFU ;
}
/*
 * @brief
 *
 */
void cvtWord3DASC(uint16_t u16Data,char * const pBuff)
{
    uint16_t u8Cal = 0x00U ;
    uint16_t u8Cal2 = 0x00U ;
    //
    if(u16Data > 999U) { u16Data =  u16Data % 1000U ;  }
    //
    u8Cal =  u16Data / 100U ;
    pBuff[0x00U]  = (u8Cal + 0x30U) & 0x00FFU ;
    //
    u8Cal =  u16Data % 100U ;
    u8Cal2 = u8Cal / 10U ;
    pBuff[0x01U]  = (u8Cal2 + 0x30U) & 0x00FFU ;
    //
    u8Cal2 =  u8Cal % 10 ;
    pBuff[0x02U]  = (u8Cal2 + 0x30U) & 0x00FFU ;
}
/*
 * @brief
 *
 */
void cvtWord4DASC(uint16_t u16Data,char * const pBuff)
{
    uint16_t  u8Cal = 0x00U ;
    uint16_t u16Cal = 0x00U ;
    //
    if(u16Data > 9999U) { u16Data =  u16Data % 10000U ;  }
    //
    u8Cal =  u16Data / 1000U ;
    pBuff[0x00U] = (u8Cal + 0x30U) & 0x00FFU ;
    //
    u16Cal =  u16Data % 1000U ;
    u8Cal = u16Cal / 100U ;
    pBuff[0x01U]  = (u8Cal + 0x30U) & 0x00FFU ;
    //
    u16Cal =  u16Cal % 100U  ;
    u8Cal =  u16Cal / 10U ;
    pBuff[0x02U]  = (u8Cal + 0x30U) & 0x00FFU ;
    //
    u8Cal =  u16Cal % 10U ;
    pBuff[0x03U]  = (u8Cal + 0x30U) & 0x00FFU ;
}
/*
 * @brief
 *
 */
void cvtWord5DASC(uint16_t u16Data,char * const pBuff)
{
    uint16_t  u8Cal = 0x00U ;
    uint16_t u16Cal = 0x00U ;
    //
    u8Cal  =  u16Data / 10000U ;
    pBuff[0x00U] = u8Cal + 0x30U ;
    //
    u16Cal =  u16Data % 10000U ;
    u8Cal  = u16Cal / 1000U ;
    pBuff[0x01U] = (u8Cal + 0x30U) & 0x00FFU ;
    //
    u16Cal =  u16Cal % 1000U ;
    u8Cal  =  u16Cal / 100U ;
    pBuff[0x02U] = (u8Cal + 0x30U) & 0x00FFU ;
    //
    u16Cal =  u16Cal % 100U ;
    u8Cal  = u16Cal / 10U ;
    pBuff[0x03U] = (u8Cal + 0x30U) & 0x00FFU ;
    //
    u8Cal =  u16Cal % 10U ;
    pBuff[0x04U] = (u8Cal + 0x30U) & 0x00FFU ;
}
/*
 * @brief
 *
 */
void cvtByte2HEX(uint16_t u8Data,char * const pBuff)
{
    uint16_t u8Cal = 0x00U ;
    //
    u8Cal =  (u8Data >> 4) & 0x0FU ;
    if(u8Cal <= 9U)  { pBuff[0x00U] = u8Cal + 0x30U ; }
    else             { pBuff[0x00U] = u8Cal + 0x37U ; }
    //
    u8Cal =  (u8Data  & 0x0FU);
    if(u8Cal <= 9U)  { pBuff[0x01U] = u8Cal + 0x30U ; }
    else             { pBuff[0x01U] = u8Cal + 0x37U ; }

    pBuff[0x00U] &= 0x00FFU ;
    pBuff[0x01U] &= 0x00FFU ;
}
/*
 * @brief
 *
 */
void cvtWord4HEX(uint16_t u16Data,char * const pBuff)
{
    uint16_t u8Cal = 0x00U ;
    //
    u8Cal =  (u16Data >> 12U) & 0x0FU ;
    if(u8Cal <= 9U)  { pBuff[0x00U] = u8Cal + 0x30U ; }
    else             { pBuff[0x00U] = u8Cal + 0x37U ; }
    //
    u8Cal =  (u16Data >> 8U) & 0x0FU ;
    if(u8Cal <= 9U)  { pBuff[0x01U] = u8Cal + 0x30U ; }
    else             { pBuff[0x01U] = u8Cal + 0x37U ; }
    //
    u8Cal =  (u16Data >> 4U) & 0x0FU ;
    if(u8Cal <= 9U)  { pBuff[0x02U] = u8Cal + 0x30U ; }
    else             { pBuff[0x02U] = u8Cal + 0x37U ; }
    //
    u8Cal =  (u16Data  & 0x0FU);
    if(u8Cal <= 9U)  { pBuff[0x03U] = u8Cal + 0x30U ; }
    else             { pBuff[0x03U] = u8Cal + 0x37U ; }

    pBuff[0x00U] &= 0x00FFU ;
    pBuff[0x01U] &= 0x00FFU ;
    pBuff[0x02U] &= 0x00FFU ;
    pBuff[0x03U] &= 0x00FFU ;
}
/*
 * @brief
 *
 */
void  cvtByte7BASC(uint16_t u8Data,char * const pBuff)
{
    pBuff[0x00U] = (((u8Data >> 7U) & 0x01U) + '0') & 0X00FFU ;
    pBuff[0x01U] = (((u8Data >> 6U) & 0x01U) + '0') & 0X00FFU ;
    pBuff[0x02U] = (((u8Data >> 5U) & 0x01U) + '0') & 0X00FFU ;
    pBuff[0x03U] = (((u8Data >> 4U) & 0x01U) + '0') & 0X00FFU ;
    pBuff[0x04U] = (((u8Data >> 3U) & 0x01U) + '0') & 0X00FFU ;
    pBuff[0x05U] = (((u8Data >> 2U) & 0x01U) + '0') & 0X00FFU ;
    pBuff[0x06U] = (((u8Data >> 1U) & 0x01U) + '0') & 0X00FFU ;
    pBuff[0x07U] = ((u8Data         & 0x01U) + '0') & 0X00FFU ;
}

/*
 * @brief
 *
 */
//
void cvt2HEXBin(const char * pSBuff , uint16_t * const pData)
{
    uint16_t u8Cal = 0x00U ;
    uint16_t u8Len = 0x00U ;
    uint16_t u8Caltemp = 0x00U ;
    char     pBuff[4] = {0x00,};
    //
    u8Len = MsgLen(pSBuff) ;

    for(u8Cal = 0; u8Cal<u8Len; u8Cal++)
    {
        pBuff[u8Cal]  = HexLowToUpper(pSBuff[u8Cal]);
    }
    //
    if(u8Len == 2U)
    {
        u8Cal = pBuff[0x00U] ;
        if(u8Cal < 0x3AU) { u8Cal = u8Cal - 0x30U; }
        else              { u8Cal = u8Cal - 0x37U; }
        u8Caltemp = ((u8Cal << 4U )  & 0xF0U ) ;
        //
        u8Cal = pBuff[0x01U] ;
        if(u8Cal < 0x3AU) { u8Cal = u8Cal - 0x30U; }
        else              { u8Cal = u8Cal - 0x37U; }
        u8Caltemp = u8Caltemp +  u8Cal   ;
    //
    }
    else if(u8Len == 1)
    {
        u8Cal = pBuff[0x00U] ;
        if(u8Cal < 0x3AU) { u8Cal = u8Cal - 0x30U; }
        else              { u8Cal = u8Cal - 0x37U; }
        //
        u8Caltemp =  u8Cal  & 0x0FU;
    }
    else { u8Caltemp = 0U ; }
    //
    pData[0x00U] =  u8Caltemp & 0X00FFU ;
}
/*
 * @brief 4Byte Ascii Hex Convert to uint16_t data
 *
 */
void  cvt4HEXBin(const char * pSBuff , uint16_t * const pData)
{
    uint16_t  u8Cal = 0x00U ;
    uint16_t  u8Len = 0x00U ;
    uint16_t  u16Caltemp = 0x00U;
    uint16_t  pBuff[4] = {0x00,};
    //
    u8Len = MsgLen(pSBuff) ;
    for(u8Cal = 0U; u8Cal<u8Len; u8Cal++)
    {
        pBuff[u8Cal]  = HexLowToUpper(pSBuff[u8Cal]) &0x00FFU;
    }
    //
    if(u8Len == 4U)
    {
        u8Cal = pBuff[0x00U] ;
        if(u8Cal < 0x3AU) { u8Cal = u8Cal - 0x30U; }
        else              { u8Cal = u8Cal - 0x37U; }
        u16Caltemp = ((u8Cal << 12U)  & 0xF000U ) ;
        //
        u8Cal = pBuff[0x01U] ;
        if(u8Cal < 0x3AU) { u8Cal = u8Cal - 0x30U; }
        else              { u8Cal = u8Cal - 0x37U; }
        u16Caltemp = u16Caltemp + ((u8Cal << 8U)  & 0x0F00U ) ;
        //
        u8Cal = pBuff[0x02U] ;
        if(u8Cal < 0x3AU) { u8Cal = u8Cal - 0x30U; }
        else              { u8Cal = u8Cal - 0x37U; }
        u16Caltemp = u16Caltemp + ((u8Cal << 4U)  & 0x00F0U ) ;
        //
        u8Cal = pBuff[0x03U] ;
        if(u8Cal < 0x3AU) { u8Cal = u8Cal - 0x30U; }
        else              { u8Cal = u8Cal - 0x37U; }
        u16Caltemp = u16Caltemp +  u8Cal   ;
        //
    }
    else if(u8Len == 3U)
    {
        //
        u8Cal = pBuff[0x00U] ;
        if(u8Cal < 0x3AU) { u8Cal = u8Cal - 0x30U; }
        else              { u8Cal = u8Cal - 0x37U; }
        u16Caltemp = ((u8Cal << 8U)  & 0x0F00U ) ;
        //
        u8Cal = pBuff[0x01U] ;
        if(u8Cal < 0x3AU) { u8Cal = u8Cal - 0x30U; }
        else              { u8Cal = u8Cal - 0x37U; }
        u16Caltemp = u16Caltemp + ((u8Cal << 4U)  & 0x00F0U ) ;
        //
        u8Cal = pBuff[0x02U] ;
        if(u8Cal < 0x3AU) { u8Cal = u8Cal - 0x30U; }
        else              { u8Cal = u8Cal - 0x37U; }
        u16Caltemp = u16Caltemp +  u8Cal   ;
        //
    }
    else if(u8Len == 2U)
    {
        u8Cal = pBuff[0x00U] ;
        if(u8Cal < 0x3AU) { u8Cal = u8Cal - 0x30U; }
        else              { u8Cal = u8Cal - 0x37U; }
        u16Caltemp = ((u8Cal << 4U)  & 0x00F0U ) ;
        //
        u8Cal = pBuff[0x01U] ;
        if(u8Cal < 0x3AU) { u8Cal = u8Cal - 0x30U; }
        else              { u8Cal = u8Cal - 0x37U; }
        u16Caltemp = u16Caltemp + u8Cal   ;
        //
    }
    else if(u8Len == 1U)
    {
        u8Cal = pBuff[0x00U] ;
        if(u8Cal < 0x3AU) { u8Cal = u8Cal - 0x30U; }
        else              { u8Cal = u8Cal - 0x37U; }
        u16Caltemp = u8Cal   ;
        //
    }
    else { u16Caltemp = 0U ; }

    pData[0x00U] =  u16Caltemp ;

}
/*
 * @brief
 *
 */
void  cvt6HEXBin(const char * pSBuff , uint32_t * const pData)
{

    uint16_t  u8Len = 0x00U ;
    uint32_t  u32Caltemp = 0x00U ;
    //
    u32Caltemp  =  0x00U ;
    //
    u8Len = MsgLen(pSBuff) ;
    //
    if(u8Len == 8U)
    {
        u32Caltemp  = (uint32_t)hex2bin(&pSBuff[0x06U]) << 24U;
        u32Caltemp += (uint32_t)hex2bin(&pSBuff[0x04U]) << 16U;
        u32Caltemp += (uint32_t)hex2bin(&pSBuff[0x02U]) << 8U;
        u32Caltemp += (uint32_t)hex2bin(&pSBuff[0x00U]) << 0U;

    }
    else if(u8Len == 6)
    {
        u32Caltemp  = (uint32_t)hex2bin(&pSBuff[0x04U]) << 16U;
        u32Caltemp += (uint32_t)hex2bin(&pSBuff[0x02U]) << 8U;
        u32Caltemp += (uint32_t)hex2bin(&pSBuff[0x00U]) << 0U;
    }
    else if(u8Len == 4)
    {
        u32Caltemp  = (uint32_t)hex2bin(&pSBuff[0x02U]) << 8U;
        u32Caltemp += (uint32_t)hex2bin(&pSBuff[0x00U]) << 0U;
    }
    else if(u8Len == 2)
    {
        u32Caltemp  = (uint32_t)hex2bin(&pSBuff[0x00U]) << 0U;
    }
    else { u32Caltemp  = 0U ; }
    //
    pData[0x00U] =  u32Caltemp  ;
}
/**
 * @brief ASCII Decimal Data Convert TO uint16_t Data
 *
 * @param pBuff ASCII Decimal Data String
 * @param pData Return uint16_t Data
 */
void cvt6ASCBin(const char *pBuff , uint16_t * const pData)
{
    uint16_t u16Cal = 0x00U ;
    uint16_t  u8Len  = 0x00U ;
    pData[0x00U]    = 0x00U ;
    //
    u8Len = MsgLen(pBuff) ;
    if((u8Len > 0U) && (u8Len <= 5U))
    {
        switch(u8Len)
        {
            case 5U: // 65535
                u16Cal  = (uint16_t)(asc2bin(&pBuff[0x00U]) * 10000U) ;
                u16Cal += (uint16_t)(asc2bin(&pBuff[0x01U]) * 1000U) ;
                u16Cal += (uint16_t)(asc2bin(&pBuff[0x02U]) * 100U) ;
                u16Cal += (uint16_t)(asc2bin(&pBuff[0x03U]) * 10U );
                u16Cal += (uint16_t)(asc2bin(&pBuff[0x04U]))  ;
                break ;
            case 4U: // 9999
                u16Cal  = (uint16_t)(asc2bin(&pBuff[0x00U]) * 1000U) ;
                u16Cal += (uint16_t)(asc2bin(&pBuff[0x01U]) * 100U);
                u16Cal += (uint16_t)(asc2bin(&pBuff[0x02U]) * 10U) ;
                u16Cal += (uint16_t)(asc2bin(&pBuff[0x03U]))  ;
                break ;
            case 3U: // 999
                u16Cal  = (uint16_t)(asc2bin(&pBuff[0x00U]) * 100U) ;
                u16Cal += (uint16_t)(asc2bin(&pBuff[0x01U]) * 10U) ;
                u16Cal += (uint16_t)(asc2bin(&pBuff[0x02U]))  ;
                break ;
            case 2U: // 99
                u16Cal  = (uint16_t)(asc2bin(&pBuff[0x00U]) * 10U) ;
                u16Cal += (uint16_t)(asc2bin(&pBuff[0x01U])) ;
                break ;
            default:
                u16Cal  = (uint16_t)(asc2bin(&pBuff[0x00U]))  ;
                break ;
        }

        pData[0x00U] = u16Cal ;
    }
}

// ---------------------------------------------------------------------------
// Define private function definitions.  
// ---------------------------------------------------------------------------
//

/**
 * @brief
 *
 * @param  pBuff
 * @return uint16_t (uint8_t)
 */
uint16_t hex2bin(const char * pSBuff)
{
    uint16_t u8Cal = 0x00U ;
    uint16_t u8Caltemp = 0x00U ;
    char     pBuff[2] = {0x00U,0x00U} ;
    //
    pBuff[0x00U]  = HexLowToUpper(pSBuff[0x00U]);
    pBuff[0x01U]  = HexLowToUpper(pSBuff[0x01U]);
    //
    u8Cal = pBuff[0x00U] & 0x00FFU ;
    if(u8Cal < 0x3AU) { u8Cal = u8Cal - 0x30U; }
    else              { u8Cal = u8Cal - 0x37U; }
    u8Caltemp = ((u8Cal << 4U )  & 0xF0U ) ;
    //
    u8Cal = pBuff[0x01U] ;
    if(u8Cal < 0x3AU) { u8Cal = u8Cal - 0x30U; }
    else              { u8Cal = u8Cal - 0x37U; }
    u8Caltemp = u8Caltemp +  u8Cal   ;
    //
    return (u8Caltemp & 0x00FFU) ;
}
/**
 * @brief   ASCII Decimal Data Convert To uint16_t Data
 *
 * @param   pBuff   ASCII Decimal
 * @return  uint16_t Converted uint16_t Data
 */
uint16_t asc2bin(const char * pBuff)
{
    uint16_t u8Ret = 0x00U ;
    uint16_t u8Cal = 0x00U ;

    u8Cal = pBuff[0x00U] & 0x00FFU ;
    if((u8Cal >= '0') && (u8Cal <= '9'))
    {
        u8Ret = (u8Cal - 0x30U) ;
    }

    return (u8Ret & 0x00FFU );
}
/**
 * @brief LowerAlpabet To UpperAlpabet
 *
 * @param LowerApabet
 * @return uint16_t : UpperAlpabet
 */
char HexLowToUpper(const char LowerAlpabet)
{
    char cResult = 0x00U;

    if((LowerAlpabet >= 'a') && (LowerAlpabet <= 'z'))
    {
        if(LowerAlpabet <= 'f')
        {
            cResult  = LowerAlpabet - 32U ;
        }
        else
        {
            cResult  = 0x30U ;
        }
    }
    else { cResult = LowerAlpabet ; }

    return (cResult & 0x00FFU);
}
// ---------------------------------------------------------------------------
//  Define Callbacks definitions.
// ---------------------------------------------------------------------------
//
 
// ---------------------------------------------------------------------------
//  Define CLI definitions.
// ---------------------------------------------------------------------------
//
/* DataConvert.c End Of File !! Well Done */
