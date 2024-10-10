/**************************** (C) COPYRIGHT 2018 Fortiortech shenzhen *****************************
* File Name          : FOCTailDect.h
* Author             : Bruce, Fortiortech Hardware
* Version            : V1.0
* Date               : 2017-12-27
* Description        : This file contains all the common data types used for
*                      Motor Control.
***************************************************************************************************
* All Rights Reserved
**************************************************************************************************/
#ifndef __FOCTAILDETECT_H_
#define __FOCTAILDETECT_H_

#include <FU68xx_4.h>
#include <Customer.h>

/****************************FOC TaildWind参数变量**************************/
typedef struct
{
    uint16 TailWindSpeed;               // 顺逆风速度
    uint8  MotorDir;                    // 电机方向
    uint8  AngleState;                  // 角度状态
    uint8  MotorTailWindState;          // 电机顺逆风状态
    uint8  SpeedStoreNum;               // 速度计算的次数
    uint16 SpeedCountTimer;             // 速度检测计时
    uint8  SpeedTimerClearStatus;       // 速度检测计时的清零标志位
    uint32 TempThailWindSpeedBase;      // 顺逆风速度基准
    uint8  SpeedOverFlowStatus;         // 转速溢出标志
    uint8  ShakeTimes;                  // 1和3状态来回抖动的次数
    uint8  TailWindBrakeCount;          // 逆风刹车次数计数
    uint8  AntiFlag;                    // 不同转速的反转标志
    uint8  ThetaStep;                   // 顺逆风步骤
}MotorTailWindTypeDef;


#define NormalTailWind                  (0)
#define BrakeTailWind                   (1)

#define BaseTimerFre                    (1000)          //Hz
#define ThailWindSpeedBase              ((BaseTimerFre / 2) * 60 / Pole_Pairs)//没必要除以2
#define TailWindStartMinSpeed           (uint16)(200.0 / TailWind_Time * 60.0 / Pole_Pairs)      //顺风启动的最低转速


extern MotorTailWindTypeDef xdata  TailWindDetect;

extern void FOCTailWindInit(void);
extern void FOCTailWindTimeLimit(void);
extern void TailWindSpeedDetect(void);
extern void FOCCloseLoopStart(void);
extern void FOCTailWindDealwith(void);
extern void TailWindDealwith(void);
#endif