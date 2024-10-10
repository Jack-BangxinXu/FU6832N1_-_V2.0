/* --------------------------- (C) COPYRIGHT 2020 Fortiortech ShenZhen -----------------------------
    File Name      : MotorControl.h
    Author         : Fortiortech  Appliction Team
    Version        : V1.0
    Date           : 2020-04-11
    Description    : This file contains motor contorl parameter used for Motor Control.
----------------------------------------------------------------------------------------------------
                                       All Rights Reserved
------------------------------------------------------------------------------------------------- */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MOTORCONTROL_H_
#define __MOTORCONTROL_H_


/* Exported types -------------------------------------------------------------------------------*/

typedef enum
{
    mcReady     = 0,
    mcInit      = 1,
    mcCharge    = 2,
    mcTailWind  = 3,
    mcPosiCheck = 4,
    mcAlign     = 5,
    mcStart     = 6,
    mcRun       = 7,
    mcStop      = 8,
    mcFault     = 9,
    mcBrake     = 10
}MotStaType;

typedef union
{
    uint8 SetMode;                                                              // 整个配置模式使能位
    struct
    {
        uint8 CalibFlag        :1;                                              // 电流校准的标志位
        uint8 ChargeSetFlag    :1;                                              // 预充电配置标志位
        uint8 AlignSetFlag     :1;                                              // 预定位配置标志位
        uint8 TailWindSetFlag  :1;                                              // 顺逆风配置标志位
        uint8 StartSetFlag     :1;                                              // 启动配置标志位
        uint8 PosiCheckSetFlag :1;                                              // 位置检测配置标志位
    } SetFlag;
}MotStaM;



/* Exported variables ---------------------------------------------------------------------------*/
extern MotStaType mcState;
extern MotStaM    McStaSet;

/* Exported functions ---------------------------------------------------------------------------*/
extern void MC_Control(void);
extern void MotorcontrolInit(void);


#endif
