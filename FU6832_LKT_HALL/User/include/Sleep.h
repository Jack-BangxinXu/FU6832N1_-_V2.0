/* --------------------------- (C) COPYRIGHT 2022 Fortiortech ShenZhen -----------------------------
    File Name      : Sleep.h
    Author         : Fortiortech  Appliction Team
    Version        : V1.0
    Date           : 2022-09-13
    Description    : This file contains .c parameter used for Motor Control.
----------------------------------------------------------------------------------------------------
                                       All Rights Reserved
------------------------------------------------------------------------------------------------- */

/* Define to prevent recursive inclusion -------------------------------------------------------- */
#ifndef __SLEEP_H_
#define __SLEEP_H_


typedef struct
{
    uint32 SleepDelayCout;
    uint8  SleepFlag;
    uint8  SleepEn;
}SLEEPMODE;

extern SLEEPMODE      xdata SleepSet;
/*----- Sleep控制 -----*/
extern void Sleepmode_Init(void);
extern void Sleepmode(void);



#endif

