/**************************** (C) COPYRIGHT 2018 Fortiortech shenzhen *****************************
* File Name          : RSDDetect.h
* Author             : Bruce, Fortiortech Hardware
* Version            : V1.0
* Date               : 2017-12-27
* Description        : This file contains all the common data types used for
*                      Motor Control.
***************************************************************************************************
* All Rights Reserved
**************************************************************************************************/
#ifndef __RSDDETECT_H_
#define __RSDDETECT_H_

#include <FU68xx_4_MCU.h>
#include <Customer.h>

/****************************RSD参数变量**************************/
typedef struct
{
    uint16 RSDStepTime[4];              // 一个脉冲的周期值
    uint16 RSDTimes;                    // 进入RSD中断次数
    uint16 RSDPeriod;                   // 1/4圈的周期值,除数不能超过16位
    int16  RSDCount;                    // RSD的脉冲数
    uint8  RSDState;                    // RSD的状态
    uint16 RSDSpeed;                    // RSD的速度
    uint8  RSDDir;                      // 顺逆风方向
    uint8   RSDFlag;                     // RSD的标志
    uint8  RSDCCWFlag;                  // 反转的强弱标志
    uint8  RSDCCWTimes;                 // 反转刹车的次数
    uint32 RSDSpeedBase;                // RSD的速度基准
    uint16 RSDCCWSBRCnt;                // RSD反转后启动前刹车计数
    uint8  RSDStep;                     // 周期值计数
    uint8  RSDBRFlag;                   // RSD反转后启动前刹车标志
}MotorRSDTypeDef;

#define   RSDSpeedBaseStep			    (int32)(32767.0/4.0*(TIM2_Fre*60/Pole_Pairs/MOTOR_SPEED_BASE))

#define     Forward                     (0)
#define     Reverse                     (1)
#define     Static                      (2)


extern MotorRSDTypeDef     xdata    RSDDetect;//用于读寄存器的值，需Idata

extern void Time2_RSD_Init(void);
extern void CMP_RSD_Init(void);
extern void RSDDealwith(void);
extern void RSDFRDetect(void);
extern void RSDDetectInit(void);
extern void RSDFOCCloseLoopStart(void);

/****************************end RSD参数变量*******************************/

#endif