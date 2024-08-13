/*
 * [ PROJECT   ]  A60132237_V00
 * [ License   ]  SAMJIN ELECTRONICS.,Co.Ltd
 * [ Author    ]  Copyright 2024 By HAG-SEONG KANG
 * [ E-MAIL    ]  hl5ugc@nate.com (82)10- 3841-9706
 * [ C  P  U   ]
 * [ Compller  ]  
 * [ Filename  ]  hwTimer.c
 * [ Version   ]  1.0
 * [ Created   ]  2024[¿ÀÈÄ 5:17:33 ]
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
#include "hwTimer.h"
 
// ---------------------------------------------------------------------------
//  Define Macros .
// ---------------------------------------------------------------------------
//
#define TIMER_FREQ      200U
// ---------------------------------------------------------------------------
//  Define TypeDef & Constants.
// ---------------------------------------------------------------------------
//
 
// ---------------------------------------------------------------------------
//  Define Private variables.
// ---------------------------------------------------------------------------
//
volatile uint32_t cpuTimer0IntCount;
volatile uint32_t cpuTimer1IntCount;
volatile uint32_t cpuTimer2IntCount;
// ---------------------------------------------------------------------------
// Define Private function prototype.
// ---------------------------------------------------------------------------
//
static void configCPUTimer(uint32_t u32CpuTimer, uint16_t period);
static void configCPUTimer1(uint32_t cpuTimer, float freq, float period);
// ---------------------------------------------------------------------------
// Define Callback function prototype.
// ---------------------------------------------------------------------------
//
__interrupt void cpuTimer0ISR(void);
__interrupt void cpuTimer1ISR(void);
__interrupt void cpuTimer2ISR(void);
// ---------------------------------------------------------------------------
// Define Public function definitions. 
// ---------------------------------------------------------------------------
//
void HwTimerInit(void)
{
    // ISRs for each CPU Timer interrupt

    Interrupt_register(INT_TIMER0, &cpuTimer0ISR);
    Interrupt_register(INT_TIMER1, &cpuTimer1ISR);
    Interrupt_register(INT_TIMER2, &cpuTimer2ISR);

    //
    // Initialize timer period to maximum
    //
    CPUTimer_setPeriod(CPUTIMER0_BASE, 0xFFFFFFFF);
    CPUTimer_setPeriod(CPUTIMER1_BASE, 0xFFFFFFFF);
    CPUTimer_setPeriod(CPUTIMER2_BASE, 0xFFFFFFFF);
    //
    // Initialize pre-scale counter to divide by 1 (SYSCLKOUT)
    //
    CPUTimer_setPreScaler(CPUTIMER0_BASE, 0);
    CPUTimer_setPreScaler(CPUTIMER1_BASE, 0);
    CPUTimer_setPreScaler(CPUTIMER2_BASE, 0);
    //
    // Make sure timer is stopped
    //
    CPUTimer_stopTimer(CPUTIMER0_BASE);
    CPUTimer_stopTimer(CPUTIMER1_BASE);
    CPUTimer_stopTimer(CPUTIMER2_BASE);
    //
    // Reload all counter register with period value
    //
    CPUTimer_reloadTimerCounter(CPUTIMER0_BASE);
    CPUTimer_reloadTimerCounter(CPUTIMER1_BASE);
    CPUTimer_reloadTimerCounter(CPUTIMER2_BASE);
    //
    // Reset interrupt counter
    //
    cpuTimer0IntCount = 0;
    cpuTimer1IntCount = 0;
    cpuTimer2IntCount = 0;
    //
    configCPUTimer1(CPUTIMER0_BASE, DEVICE_SYSCLK_FREQ, 1000);

    CPUTimer_enableInterrupt(CPUTIMER0_BASE);
//    CPUTimer_enableInterrupt(CPUTIMER1_BASE);
//    CPUTimer_enableInterrupt(CPUTIMER2_BASE);

    Interrupt_enable(INT_TIMER0);
//    Interrupt_enable(INT_TIMER1);
//    Interrupt_enable(INT_TIMER2);
    CPUTimer_startTimer(CPUTIMER0_BASE);
}

void HwTimerSet(Timer_Ch_e ch,uint16_t u16uSec)
{
    configCPUTimer(ch, u16uSec);

}
void HwTimerIntEnable(Timer_Ch_e ch)
{


    switch(ch)
    {
        case CPU_TIMER0 :
            Interrupt_enable(INT_TIMER0);
            CPUTimer_startTimer(CPUTIMER0_BASE);
            CPUTimer_enableInterrupt(CPUTIMER0_BASE);
            break ;
        case CPU_TIMER1 :
            Interrupt_enable(INT_TIMER1);
            CPUTimer_startTimer(CPUTIMER1_BASE);
            CPUTimer_enableInterrupt(CPUTIMER1_BASE);
            break ;
        case CPU_TIMER2 :
            Interrupt_enable(INT_TIMER2);
            CPUTimer_startTimer(CPUTIMER2_BASE);
            CPUTimer_enableInterrupt(CPUTIMER2_BASE);
            break ;
    }

}

uint32_t millis(void)
{
    uint32_t u32Ret = 0x00U;

    u32Ret = cpuTimer0IntCount ;

    return (u32Ret);
}


void DelayMs(uint32_t u32Delay)
{
    uint32_t u32Temp = 0x00U;

    u32Temp = millis();

    while((millis() - u32Temp) < u32Delay) ;
}

uint16_t HwTimerGetEvent(void)
{
    uint16_t u16Ret = 0x00U;



    return (u16Ret);
}
void HwTimerSetEvent(uint16_t u16Event)
{

}
void HwTimerClearEvent(uint16_t u16Event)
{

}
// ---------------------------------------------------------------------------
// Define private function definitions.  
// ---------------------------------------------------------------------------
//
void configCPUTimer1(uint32_t cpuTimer, float freq, float period)
{
    uint32_t temp;

    //
    // Initialize timer period:
    //
    temp = (uint32_t)((freq / 1000000) * period);
    CPUTimer_setPeriod(cpuTimer, temp - 1);

    //
    // Set pre-scale counter to divide by 1 (SYSCLKOUT):
    //
    CPUTimer_setPreScaler(cpuTimer, 0);

    //
    // Initializes timer control register. The timer is stopped, reloaded,
    // free run disabled, and interrupt enabled.
    // Additionally, the free and soft bits are set
    //
    CPUTimer_stopTimer(cpuTimer);
    CPUTimer_reloadTimerCounter(cpuTimer);
    CPUTimer_setEmulationMode(cpuTimer,
                              CPUTIMER_EMULATIONMODE_STOPAFTERNEXTDECREMENT);
    CPUTimer_enableInterrupt(cpuTimer);

    //
    // Resets interrupt counters for the three cpuTimers
    //
    if (cpuTimer == CPUTIMER0_BASE)
    {
        cpuTimer0IntCount = 0;
    }
    else if(cpuTimer == CPUTIMER1_BASE)
    {
        cpuTimer1IntCount = 0;
    }
    else if(cpuTimer == CPUTIMER2_BASE)
    {
        cpuTimer2IntCount = 0;
    }
}
/**
 *  period is uSec
 */
static void configCPUTimer(uint32_t u32CpuTimer, uint16_t period)
{
    uint32_t u32temp = 0x00U;

    u32temp = (uint32_t)(period * 1000000U) ;
    u32temp =  (uint32_t)(u32temp * TIMER_FREQ );

    CPUTimer_setPeriod(u32CpuTimer, u32temp);
    //
    // Set pre-scale counter to divide by 1 (SYSCLKOUT):
    //
    CPUTimer_setPreScaler(u32CpuTimer, 0);
    //
    // Initializes timer control register. The timer is stopped, reloaded,
    // free run disabled, and interrupt enabled.
    // Additionally, the free and soft bits are set
    //
    CPUTimer_stopTimer(u32CpuTimer);
    CPUTimer_reloadTimerCounter(u32CpuTimer);
    CPUTimer_setEmulationMode(u32CpuTimer,
                              CPUTIMER_EMULATIONMODE_STOPAFTERNEXTDECREMENT);
    CPUTimer_enableInterrupt(u32CpuTimer);
    //
    // Resets interrupt counters for the three cpuTimers
    //
    if (u32CpuTimer == CPUTIMER0_BASE)
    {
        cpuTimer0IntCount = 0U ;
    }
    else if(u32CpuTimer == CPUTIMER1_BASE)
    {
        cpuTimer1IntCount = 0U ;
    }
    else if(u32CpuTimer == CPUTIMER2_BASE)
    {
        cpuTimer2IntCount = 0U ;
    }
}
// ---------------------------------------------------------------------------
//  Define Callbacks definitions.
// ---------------------------------------------------------------------------
//
// cpuTimer0ISR - Counter for CpuTimer0
//
__interrupt void cpuTimer0ISR(void)
{
    cpuTimer0IntCount++;
    //
    // Acknowledge this interrupt to receive more interrupts from group 1
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);
}
//
// cpuTimer1ISR - Counter for CpuTimer1
//
__interrupt void cpuTimer1ISR(void)
{
    cpuTimer1IntCount++;
}
//
// cpuTimer2ISR - Counter for CpuTimer2
//
__interrupt void cpuTimer2ISR(void)
{
    cpuTimer2IntCount++;
}

 
// ---------------------------------------------------------------------------
//  Define CLI definitions.
// ---------------------------------------------------------------------------
//
/* hwTimer.c End Of File !! Well Done */
