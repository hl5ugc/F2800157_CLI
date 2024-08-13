/*
 * [ PROJECT   ]  A60132237_V00
 * [ License   ]  SAMJIN ELECTRONICS.,Co.Ltd
 * [ Author    ]  Copyright 2024 By HAG-SEONG KANG
 * [ E-MAIL    ]  hl5ugc@nate.com (82)10- 3841-9706
 * [ C  P  U   ]
 * [ Compller  ]  
 * [ Filename  ]  cli.c
 * [ Version   ]  1.0
 * [ Created   ]  2024[¿ÀÈÄ 5:14:01 ]
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
#include "cli.h"
//
#include "uart.h"
#include "hwTimer.h"
#include "DataConvert.H"
// ---------------------------------------------------------------------------
//  Define Macros .
// ---------------------------------------------------------------------------
//
#define CLI_KEY_BACK              0x08U
#define CLI_KEY_DEL               0x7FU
#define CLI_KEY_ENTER             0x0DU
#define CLI_KEY_ESC               0x1BU
#define CLI_KEY_LEFT              0x44U
#define CLI_KEY_RIGHT             0x43U
#define CLI_KEY_UP                0x41U
#define CLI_KEY_DOWN              0x42U
#define CLI_KEY_HOME              0x31U
#define CLI_KEY_END               0x34U
#define CLI_PROMPT_STR            "hl5ugc>> "

#define CLI_ARGS_MAX              32
#define CLI_PRINT_BUF_MAX         32
// ---------------------------------------------------------------------------
//  Define TypeDef & Constants.
// ---------------------------------------------------------------------------
//
//typedef struct
//{
//  uint16_t   argc;
//  char     **argv;
//
//  uint16_t  (*getData)(uint16_t index);
//  uint16_t  (*getHexData)(uint16_t index);
//  char     *(*getStr)(uint16_t index);
//  bool      (*isStr)(uint16_t index, char *p_str);
//} cli_args_t;

enum
{
  CLI_RX_IDLE,
  CLI_RX_SP1,
  CLI_RX_SP2,
  CLI_RX_SP3,
  CLI_RX_SP4,
};
typedef struct
{
  char   cmd_str[CLI_CMD_NAME_MAX];
  char   help_str[CLI_CMD_NAME_MAX];
  void (*cmd_func)(cli_args_t *);
} cli_cmd_t;

typedef struct
{
  uint16_t     buf[CLI_LINE_BUF_MAX];
  uint16_t     buf_len;
  uint16_t     cursor;
  uint16_t     count;
} cli_line_t;

typedef struct
{
  uint16_t     ch;
  uint32_t    baud;
  bool        is_open;
  bool        is_log;
  uint16_t     log_ch;
  uint32_t    log_baud;
  uint16_t     state;
  char        print_buffer[CLI_PRINT_BUF_MAX];
  uint16_t    argc;
  char        *argv[CLI_ARGS_MAX];

  bool        hist_line_new;
  int8_t      hist_line_i;
  uint16_t     hist_line_last;
  uint16_t     hist_line_count;

  cli_line_t  line_buf[CLI_LINE_HIS_MAX];
  cli_line_t  line;

  uint16_t     cmd_count;
  cli_cmd_t   cmd_list[CLI_CMD_LIST_MAX];
  cli_args_t  cmd_args;
} cli_t;
// ---------------------------------------------------------------------------
//  Define Private variables.
// ---------------------------------------------------------------------------
//
cli_t   cli_node;
// ---------------------------------------------------------------------------
// Define Private function prototype.
// ---------------------------------------------------------------------------
//
static bool cliUpdate(cli_t *p_cli, char rx_data);
static void cliLineClean(cli_t *p_cli);
static void cliLineAdd(cli_t *p_cli);
static void cliLineChange(cli_t *p_cli, bool key_up);
static void cliShowPrompt(cli_t *p_cli);
static void cliShowLog(cli_t *p_cli);
static void cliToUpper(char *str);
static bool cliRunCmd(cli_t *p_cli);
static bool cliParseArgs(cli_t *p_cli);
//
static uint16_t cliArgsGetData(uint16_t index);
static uint16_t cliArgsGetHEXData(uint16_t index);
static char    *cliArgsGetStr(uint16_t index);
static bool     cliArgsIsStr(uint16_t index, char *p_str);

void cliShowList(cli_args_t *args);
static void cliDataCheck(cli_args_t *args);
// ---------------------------------------------------------------------------
// Define Callback function prototype.
// ---------------------------------------------------------------------------
//

// ---------------------------------------------------------------------------
// Define Public function definitions. 
// ---------------------------------------------------------------------------
//
bool cliInit(void)
{
  cli_node.is_open = false ;
  cli_node.is_log  = false ;
  cli_node.state   = CLI_RX_IDLE ;

  cli_node.hist_line_i      = 0;
  cli_node.hist_line_last   = 0;
  cli_node.hist_line_count  = 0 ;
  cli_node.hist_line_new    = false;

  cli_node.cmd_args.getData     = cliArgsGetData;
  cli_node.cmd_args.getHexData  = cliArgsGetHEXData;
  cli_node.cmd_args.getStr      = cliArgsGetStr;
  cli_node.cmd_args.isStr       = cliArgsIsStr;

  cliLineClean(&cli_node);  // line Buffer Init.

  cliAdd("help"," " ,cliShowList);
  // cliAdd("DataChk","4Hex 4Hex 4Hex", cliDataCheck); // Data Convertion Test
  return (true);
}
bool cliOpen(uint16_t ch, uint32_t baud)
{
  cli_node.ch = ch ;
  cli_node.baud = baud ;
  cli_node.is_open = uartOpen(ch,baud);

  return (cli_node.is_open);
}
bool cliOpenLog(uint16_t ch, uint32_t baud)
{
  cli_node.log_ch = ch ;
  cli_node.log_baud = baud ;

  cli_node.is_log = uartOpen(ch,baud);
  return (cli_node.is_log);
}
bool cliLogClose(void)
{
  cli_node.is_log = false;
  return true;
}
/**
 * @brief
 *
 * @return true
 * @return false
 */
bool cliMain(void)
{
  bool bRet = false ;

  if(cli_node.is_open == true)
  {
    bRet = true ;
    if(uartRXAvailable(cli_node.ch) > 0U)
    {
      cliUpdate(&cli_node,uartRead(cli_node.ch));
    }
  }

  return (bRet);
}
/**
 * @brief CallBack Function Add Function
 *
 * @param cmd_str   Command string
 * @param help_str  Help string
 * @param p_func    CallBack Function & Parameter
 */
bool cliAdd(const char *cmd_str, const char *help_str,void (*p_func)(cli_args_t *))
{
  bool bRet = false ;
  cli_t *p_cli = &cli_node ;
  uint16_t index = 0x00U ;

  if(p_cli->cmd_count < CLI_CMD_LIST_MAX)
  {
    index = p_cli->cmd_count ;
    strcpy(p_cli->cmd_list[index].cmd_str,cmd_str);
    strcpy(p_cli->cmd_list[index].help_str,help_str);
    p_cli->cmd_list[index].cmd_func = p_func ;

    cliToUpper(p_cli->cmd_list[index].cmd_str);
    p_cli->cmd_count = (p_cli->cmd_count + 1U) % CLI_CMD_LIST_MAX ;

    bRet = true ;
  }

  return (bRet);
}
bool cliKeepLoop(void)
{
  bool bRet = false ;
  cli_t *p_cli = &cli_node ;

  if(uartRXAvailable(p_cli->ch) == 0x00U) { bRet = true; }
  return (bRet);
}
/**
 * @brief Start CLI Message
 * [ License   ]  SAMJIN ELECTRONICS.,Co.Ltd
 * [ Author    ]  Copyright 2024 By HAG-SEONG KANG
 * [ E-MAIL    ]  hl5ugc@nate.com (82)10- 3841-9706
 * Project
 */
void cliShowMFG(void)
{
  if(cli_node.is_open == true)
  {
    uartMsgWrite(cli_node.ch,"\r\n");
    DelayMs(30);
    uartMsgWrite(cli_node.ch,"SAMJIN ELECTRONICS.,Co.Ltd \r\n");
    DelayMs(30);
    uartMsgWrite(cli_node.ch,"Copyright 2024 By HAG-SEONG KANG \r\n");
    DelayMs(30);
    uartMsgWrite(cli_node.ch,"hl5ugc@nate.com (82)10- 3841-9706\r\n\r\n");
    DelayMs(30);
    uartMsgWrite(cli_node.ch,"CLI For Project ..... \r\n\r\n");
    DelayMs(30);
    uartMsgWrite(cli_node.ch,CLI_PROMPT_STR);
    DelayMs(30);
  }
}
// ---------------------------------------------------------------------------
// Define Private function prototype.
// ---------------------------------------------------------------------------
//
bool cliUpdate(cli_t *p_cli, char rx_data)
{
  bool bRet = false ;
  uint16_t i = 0x00U ;
  uint16_t mov_len = 0x00U;
  char     txBuf[8] = {0x00U,};
  cli_line_t *line ;

  line = &p_cli->line;

  if(p_cli->state == CLI_RX_IDLE)
  {
    switch(rx_data)
    {
      case CLI_KEY_ENTER :
          if(line->count > 0U)
          {
            cliLineAdd(p_cli);
            cliRunCmd(p_cli);
          }
          line->count = 0;
          line->cursor = 0;
          line->buf[0] = 0;
          cliShowPrompt(p_cli);
          break;
      case CLI_KEY_ESC :
          p_cli->state = CLI_RX_SP1 ;
          break;
      case CLI_KEY_DEL :
          if(line->cursor < line->count)
          {
              mov_len = line->count - line->cursor;
              for (i=0; i<mov_len; i++)
              {
                line->buf[line->cursor + i - 1] = line->buf[line->cursor + i];
              }
              line->count--;
              line->buf[line->count] = 0;
              uartMsgWrite(p_cli->ch, "\x1B[1P");
          }
          break;
      case CLI_KEY_BACK : // backspace
          if((line->count > 0) && (line->cursor > 0))
          {
            if(line->cursor == line->count)
            {
              line->count-- ;
              line->buf[line->count] = 0x00U ;
            }
            if(line->cursor < line->count)
            {
              mov_len = line->count - line->cursor;
              for (i=0; i<mov_len; i++)
              {
                line->buf[line->cursor + i - 1] = line->buf[line->cursor + i];
              }
              line->count--;
              line->buf[line->count] = 0;
            }
          }
          //
          if(line->cursor > 0)
          {
            line->cursor-- ;
            uartMsgWrite(p_cli->ch, "\b \b\x1B[1P");
          }
          break ;
      default:
          if((line->count + 1) < line->buf_len)
          {
            if(line->cursor == line->count) // cursor location is input data last ( cursortext_ )
            {
              uartWrite(p_cli->ch,&rx_data,1U);
              line->buf[line->cursor] = rx_data ;
              line->count++;
              line->cursor++;
              line->buf[line->cursor] = 0 ;
            }
            if(line->cursor < line->count) // cursor location is input data Not last ( cursor-text )
            {
              mov_len = line->count - line->cursor;
              for (i=0U; i<mov_len; i++)
              {
                line->buf[line->count - i] = line->buf[line->count - i - 1];
              }
              line->buf[line->cursor] = rx_data;
              line->count++;
              line->cursor++;
              line->buf[line->count] = 0;

              uartMsgWrite(p_cli->ch, "\x1B[4h");
              uartWrite(p_cli->ch,&rx_data,1U);
              uartMsgWrite(p_cli->ch, "\x1B[4l");
            }
          }
          break;
    }
  }
  switch (p_cli->state)
  {
    case CLI_RX_SP1 :
      p_cli->state = CLI_RX_SP2 ;
      break;

    case CLI_RX_SP2 :
      p_cli->state = CLI_RX_SP3;
      break;

    case CLI_RX_SP3 :
      p_cli->state = CLI_RX_IDLE;
      //
      if (rx_data == CLI_KEY_LEFT)
      {
        if(line->cursor > 0U)
        {
          line->cursor--;
          txBuf[0] = 0x1BU;
          txBuf[1] = 0x5BU;
          txBuf[2] = rx_data;
          uartWrite(p_cli->ch, &txBuf[0], 3U);
        }
      }
      //
      if (rx_data == CLI_KEY_RIGHT)
      {
        if(line->cursor < line->buf_len)
        {
          line->cursor++;
          txBuf[0] = 0x1BU;
          txBuf[1] = 0x5BU;
          txBuf[2] = rx_data;
          uartWrite(p_cli->ch, &txBuf[0], 3U);
        }
      }
      //
      if (rx_data == CLI_KEY_UP)
      {
        cliLineChange(p_cli, true);
        uartMsgWrite(p_cli->ch, (char *)p_cli->line.buf);
      }
      //
      if (rx_data == CLI_KEY_DOWN)
      {
        cliLineChange(p_cli, false);
        uartMsgWrite(p_cli->ch, (char *)p_cli->line.buf);
      }
      //
      if (rx_data == CLI_KEY_HOME)
      {
        uartMsgByte2ASC(p_cli->ch,"\x1B[",line->cursor);
        uartMsgWrite(p_cli->ch, "D");

        line->cursor = 0;
        p_cli->state = CLI_RX_SP4;
      }
      //
      if (rx_data == CLI_KEY_END)
      {
        if (line->cursor < line->count)
        {
          mov_len = line->count - line->cursor;
          uartMsgByte2ASC(p_cli->ch,"\x1B[",mov_len);
          uartMsgWrite(p_cli->ch, "C");
        }
        if (line->cursor > line->count)
        {
          mov_len = line->cursor - line->count;
          uartMsgByte2ASC(p_cli->ch,"\x1B[",mov_len);
          uartMsgWrite(p_cli->ch, "D");
        }
        line->cursor = line->count;
        p_cli->state = CLI_RX_SP4;
      }
      //
      break;
    case CLI_RX_SP4 :
      p_cli->state = CLI_RX_IDLE;
      break;

    default:
      p_cli->state = CLI_RX_IDLE;
      break;
  }

  cliShowLog(p_cli);

  return bRet;
}
void cliLineClean(cli_t *p_cli)
{
  p_cli->line.count     = 0 ;
  p_cli->line.cursor    = 0 ;
  p_cli->line.buf_len   = CLI_LINE_BUF_MAX - 1U ;
  p_cli->line.buf[0x00] = 0x00U ;
}

void cliLineAdd(cli_t *p_cli)
{
  p_cli->line_buf[p_cli->hist_line_last] = p_cli->line ;

  if(p_cli->hist_line_count < CLI_LINE_HIS_MAX)
  {
    p_cli->hist_line_count++ ;
  }

  p_cli->hist_line_i    = p_cli->hist_line_last ;
  p_cli->hist_line_last = (p_cli->hist_line_last + 1) % CLI_LINE_HIS_MAX;
  p_cli->hist_line_new  = true;

}
void cliLineChange(cli_t *p_cli, bool key_up)
{
  uint16_t change_i = 0x00U;

  if(p_cli->hist_line_count > 0U)
  {
    if(p_cli->line.cursor > 0U)
    { // Todo
      uartMsgByte2ASC(p_cli->ch,"\x1B[",p_cli->line.cursor);
      uartMsgWrite(p_cli->ch, "D");
    }
    if (p_cli->line.count > 0)
    { // Todo
      uartMsgByte2ASC(p_cli->ch, "\x1B[", p_cli->line.count);
      uartMsgWrite(p_cli->ch, "P");
    }
    if (key_up == true)
    {
      if (p_cli->hist_line_new == true)
      {
        p_cli->hist_line_i = p_cli->hist_line_last;
      }
      p_cli->hist_line_i = (p_cli->hist_line_i + p_cli->hist_line_count - 1) % p_cli->hist_line_count;
      change_i = p_cli->hist_line_i;
    }
    else
    {
      p_cli->hist_line_i = (p_cli->hist_line_i + 1) % p_cli->hist_line_count;
      change_i = p_cli->hist_line_i;
    }

    p_cli->line = p_cli->line_buf[change_i];
    p_cli->line.cursor = p_cli->line.count;

    p_cli->hist_line_new = false;
  }
}
void cliShowPrompt(cli_t *p_cli)
{
  uartMsgWrite(p_cli->ch, "\n\r");
  uartMsgWrite(p_cli->ch, CLI_PROMPT_STR);
}
void cliShowLog(cli_t *p_cli)
{
  // uint16_t i = 0x00U;

  if(cli_node.is_log == true)
  {
  //   uartPrintf(p_cli->log_ch, "Cursor  : %d\n", p_cli->line.cursor);
  //   uartPrintf(p_cli->log_ch, "Count   : %d\n", p_cli->line.count);
  //   uartPrintf(p_cli->log_ch, "buf_len : %d\n", p_cli->line.buf_len);
  //   uartPrintf(p_cli->log_ch, "buf     : %s\n", p_cli->line.buf);
  //   uartPrintf(p_cli->log_ch, "line_i  : %d\n", p_cli->hist_line_i);
  //   uartPrintf(p_cli->log_ch, "line_lt : %d\n", p_cli->hist_line_last);
  //   uartPrintf(p_cli->log_ch, "line_c  : %d\n", p_cli->hist_line_count);

  //   for (i=0; i<p_cli->hist_line_count; i++)
  //   {
  //     uartPrintf(p_cli->log_ch, "buf %d   : %s\n", i, p_cli->line_buf[i].buf);
  //   }
    uartWrite(p_cli->log_ch, "\n",1U);
  }
}
/**
 * @brief CallBack Function Run by Command line data
 *
 */
bool cliRunCmd(cli_t *p_cli)
{
  bool bRet = false;
  uint16_t i= 0x00U ;

  if (cliParseArgs(p_cli) == true)
  {
    //cliPrintf("\r\n");
    uartMsgWrite(p_cli->ch, "\r\n");
    cliToUpper(p_cli->argv[0]);

    for (i=0; i<p_cli->cmd_count; i++)
    {
      if (strcmp(p_cli->argv[0], p_cli->cmd_list[i].cmd_str) == 0)
      {
        p_cli->cmd_args.argc =  p_cli->argc - 1;
        p_cli->cmd_args.argv = &p_cli->argv[1];
        p_cli->cmd_list[i].cmd_func(&p_cli->cmd_args);
        break;
      }
    }
  }

  return bRet;
}
bool cliParseArgs(cli_t *p_cli)
{
    bool bRet = false ;
    char *tok ;
    //char *next_ptr ;
    uint16_t argc = 0 ;
    //static flash char *delim = " \f\n\r\t\v" ;
    char *delim = " "  ;
    char *cmdline ;
    char **argv ;
    //
    p_cli->argc = 0 ;
    //
    cmdline = (char *)p_cli->line.buf ;
    argv    = p_cli->argv ;
    argv[argc] = NULL ;
    /*
    if(tok= strok_r(cmdline,delm,&next_ptr); tok ; tok = strok_r(NULL,delm,&next_ptr))
    {
        argv[argc++] = tok ;
    }
    */
    tok = strtok(cmdline,delim);
    if(tok == NULL)
    {
        return (false) ;
    }
    while( tok != NULL)
    {
        argv[argc++] = tok ;
        tok = strtok(NULL," ");

    }
    p_cli->argc = argc ;
    //
    if(argc > 0)
    {
        bRet = true ;
    }
    //
    return bRet ;
}
/**
 * @brief abcd string Convert To ABCD string
 *
 * @param str string Buffer
 */
void cliToUpper(char *str)
{
  uint16_t u8i = 0x00U;
  uint16_t u8Str_ch = 0x00U ;

  for(u8i=0x00U; u8i < CLI_CMD_NAME_MAX; u8i++)
  {
    u8Str_ch = str[u8i] ;
    if(u8Str_ch == 0x00U) { break; }
    if((u8Str_ch >= 'a') && (u8Str_ch <= 'z'))
    {
      u8Str_ch = ( u8Str_ch - 'a') + 'A' ;
      str[u8i] = u8Str_ch ;
    }
  }
  //
  if(u8i == CLI_CMD_NAME_MAX) { str[u8i] = 0x00U ; }
}
/**
 * @brief   arg data convert to uint16
 *
 * @param   index
 * @return  uint16_t
 */
// Todo Convert 3byte ASC Dec to uint16_t   (023)
// Todo Convert 3byte ASC Dec to uint16_t   (325)
// Todo Convert 2byte ASC Hex to uint16_t   (0x32)
// Todo Convert 4byte ASC Hex to uint16_t   (0xAA12)
uint16_t cliArgsGetData(uint16_t index)
{
  uint16_t u16Ret = 0x00U ;
  cli_t *p_cli = &cli_node ;
  char *pStrData = NULL ;

  if(index < p_cli->cmd_args.argc)
  {
    // u16Ret = (uint16_t)strtoul((const char * ) p_cli->cmd_args.argv[index], (char **)NULL, (int) 0);
    // Check ASCII DECIMAL or ASCII HEX
    pStrData = p_cli->cmd_args.argv[index];
    if(pStrData[0x00U] == '0')
    {
      if((pStrData[0x01U] == 'x') || (pStrData[0x01U] == 'X'))
      {
        cvt4HEXBin(&pStrData[2],&u16Ret);
      }
      else
      {
        cvt6ASCBin(pStrData,&u16Ret);
      }
    }
    else { cvt6ASCBin(pStrData,&u16Ret); }
  }

  return (u16Ret);
}

uint16_t cliArgsGetHEXData(uint16_t index)
{
  uint16_t u16Ret = 0x00U ;
  cli_t *p_cli = &cli_node ;
  char *pHexStr = NULL ;

  if(index < p_cli->cmd_args.argc)
  {
    pHexStr = p_cli->cmd_args.argv[index];
    cvt4HEXBin(&pHexStr[2],&u16Ret);
  }

  return (u16Ret);
}
char *cliArgsGetStr(uint16_t index)
{
  char *cRet = NULL ;
  cli_t *p_cli = &cli_node ;
  if(index < p_cli->cmd_args.argc)
  {
    cRet = p_cli->cmd_args.argv[index] ;
  }

  return (cRet);
}
bool cliArgsIsStr(uint16_t index, char *p_str)
{
  bool bRet = false ;
  cli_t *p_cli = &cli_node ;

  if(index < p_cli->cmd_args.argc)
  {
     if(strcmp(p_str,p_cli->cmd_args.argv[index]) == 0x00U)
     {
        bRet = true ;
     }
  }
  return (bRet);
}
// void cliPrintf(const char *fmt, ...)
// {
//   va_list arg;
//   va_start (arg, fmt);
//   int32_t len;
//   cli_t *p_cli = &cli_node;


//   len = vsnprintf(p_cli->print_buffer, 32, fmt, arg);
//   va_end (arg);

//   uartWrite(p_cli->ch, (uint16_t *)p_cli->print_buffer, len);
// }
// ---------------------------------------------------------------------------
//  Define Callbacks definitions.
// ---------------------------------------------------------------------------
//
void cliShowList(cli_args_t *args)
{
  uint16_t i = 0x00U ;
  cli_t *p_cli = &cli_node ;

  (void)args ;

  uartMsgWrite(p_cli->ch,"\r\n");
  uartMsgWrite(p_cli->ch,"----------- cmd list ----------\r\n");
  DelayMs(10);

  for(i=0x00U; i<p_cli->cmd_count;i++)
  {
    uartMsgWrite(p_cli->ch,p_cli->cmd_list[i].cmd_str);
    uartMsgWrite(p_cli->ch," ");
    DelayMs(10);
    uartMsgWrite(p_cli->ch,p_cli->cmd_list[i].help_str);
    uartMsgWrite(p_cli->ch,"\r\n");
    DelayMs(10);
  }
  uartMsgWrite(p_cli->ch,"-------------------------------\r\n");
  DelayMs(10);
}

/**
 * @brief ASCII DECIMAL or HEX Convert to 2bytes Binary
 *
 * @param args hl5ugc>> datachk 0x1234 0x789 0x85
 */
void cliDataCheck(cli_args_t *args)
{
  uint16_t u16Indata = 0 ;

  uartMsgByte2ASC(_DEF_UART1,"args->argc = ",args->argc);


  if(args->argc >= 1)
  {
    uartMsgWrite(_DEF_UART1,"\n\rargv[0] = ") ;
    uartMsgWrite(_DEF_UART1,args->argv[0]);
    u16Indata = args->getData(0) ; // ASCII DECMAL & HEX Convert to binary
    uartMsgWord5DASC(_DEF_UART1," => ",u16Indata);
    //
    if(args->argc >= 2)
    {
      uartMsgWrite(_DEF_UART1,"\n\rargv[1] = ") ;
      uartMsgWrite(_DEF_UART1,args->argv[1]);
      u16Indata = args->getData(1) ; // ASCII DECMAL & HEX Convert to binary
      uartMsgWord5DASC(_DEF_UART1," => ",u16Indata);
      if(args->argc >= 3)
      {
        uartMsgWrite(_DEF_UART1,"\n\rargv[2] = ") ;
        uartMsgWrite(_DEF_UART1,args->argv[2]);
        u16Indata = args->getData(2) ; // ASCII DECMAL & HEX Convert to binary
        uartMsgWord5DASC(_DEF_UART1," => ",u16Indata);

      }
    }
  }
}
// ---------------------------------------------------------------------------
// Define private function definitions.  
// ---------------------------------------------------------------------------
//
 
// ---------------------------------------------------------------------------
//  Define Callbacks definitions.
// ---------------------------------------------------------------------------
//
 
// ---------------------------------------------------------------------------
//  Define CLI definitions.
// ---------------------------------------------------------------------------
//
/* cli.c End Of File !! Well Done */
