/*
 * [ PROJECT   ]  A60132237_V00
 * [ License   ]  SAMJIN ELECTRONICS.,Co.Ltd
 * [ Author    ]  Copyright 2024 By HAG-SEONG KANG
 * [ E-MAIL    ]  hl5ugc@nate.com (82)10- 3841-9706
 * [ C  P  U   ]
 * [ Compller  ]  
 * [ Filename  ]  cli.h
 * [ Version   ]  1.0
 * [ Created   ]  2024[오후 5:11:37 ]
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
#ifndef SRC_COMMON_INCLUDE_CLI_H_
#define SRC_COMMON_INCLUDE_CLI_H_

#ifdef __cplusplus
extern "C" {
#endif
/* Includes */
#include "hw_def.h"

#ifdef _USE_HW_CLI
 
// ---------------------------------------------------------------------------
// Define Global define
// --------------------------------------------------------------------------- 
// 
#define CLI_CMD_LIST_MAX      HW_CLI_CMD_LIST_MAX
#define CLI_CMD_NAME_MAX      HW_CLI_CMD_NAME_MAX
#define CLI_HLP_STR_MAX       HW_CLI_HLP_NAME_MAX

#define CLI_LINE_HIS_MAX      HW_CLI_LINE_HIS_MAX
#define CLI_LINE_BUF_MAX      HW_CLI_LINE_BUF_MAX
// ---------------------------------------------------------------------------
// Define typedef
// --------------------------------------------------------------------------- 
// 
// Callback 함수를 부를때 넘길 파라메트
typedef struct
{
  uint16_t   argc;
  char     **argv;

  uint16_t  (*getData)(uint8_t index);
  uint16_t  (*getHexData)(uint8_t index);
  char     *(*getStr)(uint8_t index);
  bool      (*isStr)(uint8_t index, char *p_str);
} cli_args_t;
// ---------------------------------------------------------------------------
// Define  Global Function prototypes.
// --------------------------------------------------------------------------- 
//

bool cliInit(void);

bool cliOpen(uint16_t ch, uint32_t baud);
bool cliOpenLog(uint16_t ch, uint32_t baud);
bool cliLogClose(void);
bool cliMain(void);
void cliShowMFG(void);

// void cliPrintf(const char *fmt, ...);
bool cliAdd(const char *cmd_str, const char *help_str,void (*p_func)(cli_args_t *)) ;
bool cliKeepLoop(void);

#endif

#ifdef __cplusplus
}

#endif
#endif /* cli.h End Of File !! Well Done */
