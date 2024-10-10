/* --------------------------- (C) COPYRIGHT 2020 Fortiortech ShenZhen -----------------------------
    File Name      : AddFunction.h
    Author         : Fortiortech  Appliction Team
    Version        : V1.0
    Date           : 2020-04-11
    Description    : This file contains all the common data types used for Motor Control.
----------------------------------------------------------------------------------------------------
                                       All Rights Reserved
------------------------------------------------------------------------------------------------- */
/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef __AddFunction_H_
#define __AddFunction_H_

/******************************************************************************/
#include <FU68xx_4_Type.h>
/******************************************************************************/

/* Exported types ------------------------------------------------------------*/

typedef struct
{
    uint32 ONOFF_Times;                                                         // 启停次数
    uint16 ON_Count;                                                            // 运行时间计数
    uint16 OFF_Count;                                                           // 停止时间计数
    uint8  ONOFF_Flag;                                                          // 启停测试中启动标志位
} ONVarible;

typedef struct
{
    int16 mcDcbusFlt;                                                          // 母线电压
    int16 mcADCCurrentbus;                                                      // 母线电流  
	int16 mcADCCurrentbus_LSB;                                                      // 母线滤波电流  
    int16  mcDcbusFlt_LSB;                                                      // 当前母线电压滤波后的值
    int16  NTCTempFlt;                                                            // NTC电压值
    uint16 CtrlMode;                                                            // 控制模式
    int16  Powerlpf;                                                            // 功率滤波后的值
    int16  Powerlpf_LSB;                                                        // 功率滤波后的值
    int16  mcIqref;                                                             // Q轴给定电流
    int16  QoutValue;
    int16  DoutValue;
  
	int16  Ref;                                                                 // 控制目标给定
    int16  IqRef;                                                               // Q轴给定电流
    int16  IdRef;                                                               // D轴给定电流
    int16  IqSpeedRef;                                                            // Q轴速度给定电流
    int16  IqADCCurrentRef;                                                      // Q轴母线电流给定电流

	
    int16  mcPosCheckAngle;                                                     // 位置检测的角度
    int16  SpeedFlt;                                                            // 当前速度滤波后的值
    int16  SpeedFlt_LSB;                                                        // 当前速度滤波后的值
    uint16 EsValue;                                                             // 当前FOC_ESQU滤波后的值
    uint16 LoopTime;                                                           // 环路控制周期
    uint16 State_Count;                                                         // 电机各个状态的时间计数  
    uint8  WindFlag;	
}FOCCTRL;



typedef struct
{
    uint8  TargetFR;                  // 设置的目标方向
    int16  TargetValue;
    int16  ActualValue;
    int16  IncValue;
    int16  DecValue;
    uint8  FlagONOFF;
	uint8  FlagFR;
}MCRAMP;


typedef struct
{
    uint16 PwmCompare;               // 比较值
    uint16 PwmCompareUpdate;
    uint16 PwmArr;                   // 周期值
    uint16 PwmCompareOld;            // 上一次的比较值
    uint16 PwmArrOld;                // 上一次的周期值
    uint8  PwmFlag;                  // PWM标志位，置1期间不更新duty
    uint16 PwmArrUpdate;             // 计算中的周期值
    uint16 PwmDuty;                  // PWM占空比，Q15格式
    uint16 PwmSclk;                  // PWM频率
    int16  PwmUpdateFlag;            // PWM新的duty更新
    uint32 PwmVSum;                  // PWM的总和
    uint16 PwmCnt;                   // PWM求平均技术
    uint8  PwmDivFlag;               // PWM的除法标志位
    uint8  PwmDealFlag;
}PWMINPUTCAL;

typedef struct
{
    uint16 CycleTimeCnt;           // 周期计数
    uint16 CycleTime;              // 周期时间
    uint16 LowlevelCnt;            // 拉低电平计数
} FGFAULTFEEDBACK;


/* Exported variables ---------------------------------------------------------------------------*/
extern PWMINPUTCAL    xdata mcPwmInput;

extern ONVarible       ONOFFTest;
extern FOCCTRL        xdata mcFocCtrl;
extern MCRAMP         xdata MotorSpeed;
extern int16          xdata VSP;
extern FGFAULTFEEDBACK         xdata   FGFault_feedback;     ///< FG故障反馈结构体变量

/* Exported functions ---------------------------------------------------------------------------*/
extern void   VariablesPreInit(void);
extern int16  HW_One_PI(int16 Xn1);
extern int16  HW_One_PI2(int16 Xn1);
extern void   Speed_response(void);
extern void   TargetSpeed_Colletion(void);
extern void   Motor_Ramp(void);

extern void   TickCycle_1ms(void);

extern int16  HW_One_PI(int16 Xn1);
extern int16  HW_One_PI2(int16 Xn1);
extern void   FaultProcess(void);
extern uint32  Abs_F32(int32 value);
extern uint16  Abs_F16(int16 value);
extern void   StarRampDealwith(void);
extern void   ONOFF_Starttest(void);
extern uint16 Power_Currt;

extern void   VSPSample(void);
extern void   PWMInputCapture(void);
extern void   PWM_OUT(void);

extern void   SCLKInputCapture(void);
extern void   FGOutput(void);
extern void   FRControl(void);
extern void APP_DIV(void);

#endif