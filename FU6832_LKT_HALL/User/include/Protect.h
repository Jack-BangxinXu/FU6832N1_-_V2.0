/*  -------------------------- (C) COPYRIGHT 2020 Fortiortech ShenZhen ---------------------------*/
/*  File Name      : Protect.h
/*  Author         : Fortiortech  Appliction Team
/*  Version        : V1.0
/*  Date           : 2020-08-18
/*  Description    : 主要用于电机运行保护条件参数设置.
/*  ----------------------------------------------------------------------------------------------*/
/*                                     All Rights Reserved
/*  ----------------------------------------------------------------------------------------------*/

/*  Define to prevent recursive inclusion --------------------------------------------------------*/
#ifndef __PROTECT_H_
#define __PROTECT_H_
#include <Customer.h>

 /*硬件过流保护比较值来源*/
 #define Compare_DAC                    (0)                                   // DAC设置硬件过流值
 #define Compare_Hardware               (1)                                   // 硬件设置硬件过流值
 #define Compare_Mode                   (Compare_DAC)                      	  // 硬件过流值的来源

 #define OverHardcurrentValue           (20.0)                                 // (A) DAC模式下的硬件过流值

 /*软件过流保护*/
 #define OverSoftCurrent_DectTime       (5)                                    ///< (ms)软件过流检测时间
 #define OverSoftCurrentClrTime         (5)                                    ///< (ms)软件过流清零时间
 #define OverSoftCurrentValue           I_Value(20.0)                           // (A) 软件过流值

 /*过欠压保护*/
 #define Over_Protect_Voltage           (17.0)                                  // (V) 直流电压过压保护值
 #define Over_Recover_Vlotage           (16.0)                                  // (V) 直流电压过压保护恢复值
 #define Under_Protect_Voltage          (8.0)                                 	// (V) 直流电压欠压保护值
 #define Under_Recover_Vlotage          (9.0)                                  // (V) 直流电压欠压保护恢复值

 /*堵转保护*/
 #define MOTOR_SPEED_STAL_MAX_RPM       S_Value(8000.0)                                // (RPM) 堵转保护最大转速
 #define MOTOR_SPEED_STAL_MIN_RPM       S_Value(600.0)                                 // (RPM) 堵转保护最小转速

 /*缺相保护*/
#define PhaseLossCurrentValue          I_Value(0.5)                            // (A)  缺相电流值

/* -----NTC过温保护----- */
#define TemperatureProtectTime 			(10000)									     // (ms)温度保护检测时间
#define OVER_Temperature 		        Tempera_Value(0.408)						     // 过温保护阈值，根据NTC曲线设定，10K上拉电阻，132℃
#define UNDER_Temperature          		Tempera_Value(0.511)						     // 过温保护恢复阈值，根据NTC曲线设定，10K上拉电阻，122℃

/* -----偏置电压保护----- */
 #define GetCurrentOffsetValue          _Q14(0.1)                                  // (单位:100%)偏置电压保护误差范围，超过该范围保护 
 
/*  保护重启参数设置  */
#define OC_RecoveryTimes                    (255)                                 // 重启次数,设定值<255 达到重启次数后不再重启，设定值>=255，一直重启
#define OC_RecoveryDelayTime                (30000)                              // (ms)重启延迟时间

#define OV_RecoveryTimes                    (255)                                // 重启次数,设定值<255 达到重启次数后不再重启，设定值>=255，一直重启
#define OV_RecoveryDelayTime                (200)                                // (ms)重启延迟时间

#define LP_RecoveryTimes                    (5)                                  // 重启次数,设定值<255 达到重启次数后不再重启，设定值>=255，一直重启
#define LP_RecoveryDelayTime                (2000)                               // (ms)重启延迟时间

#define OT_RecoveryTimes                    (255)                                   // 重启次数,设定值<255 达到重启次数后不再重启，设定值>=255，一直重启
#define OT_RecoveryDelayTime                (2000)                                // (ms)重启延迟时间

#define Stall_RecoveryTimes                 (255)                                   // 重启次数,设定值<255 达到重启次数后不再重启，设定值>=255，一直重启
#define Stall_RecoveryDelayTime             (1000)                                // (ms)小于5次堵转重启延迟时间
#define Stall_RecoveryDelayTime2            (30000)                                // (ms)大于5次堵转重启延迟时间

#define WL_RecoveryTimes                   (255)                                      // (ms) 离水重启次数,设定值<255 达到重启次数后不再重启，设定值>=255，一直重启
#define WL_RecoveryDelayTime               (5000)                                     // ms)重启延迟时间

/* 软件保护恢复使能 */
#define ProtectRecoveryEn                   (1)                                      //保护恢复使能，0,不使能；1，使能

 /*保护使能*/
 #define OverSoftCurrentProtectEnable   (0)                                    // 软件过流保护，0,不使能；1，使能
 #define VoltageProtectEnable           (1)                                     // 电压保护，0,不使能；1，使能
 #define StallProtectEnable             (1)                                     // 堵转保护，0,不使能；1，使能
 #define PhaseLossProtectEnable         (1)                                     // 缺相保护，0,不使能；1，使能
 #define OverTPProtectEn                (1)                                     ///< 过温保护使能：     0,不使能；1，使能
 #define OffsetProtectEn                (1)                                     ///< 偏置电压保护：     0,不使能；1，使能
 
typedef struct
{
    uint8  OverCurCnt;                                                          // 软件过流计数

	uint8  OverCurCntClr;
	int16  Is; 
    uint16 Max_ia;                                                              // IA的最大值
    uint16 Max_ib;                                                              // IB的最大值
	uint16 Max_ic;                                                              // IC的最大值

	uint16 Abs_ia;
	uint16 Abs_ib;
	uint16 Abs_ic;
}CurrentVarible;

typedef struct
{
    uint8 SecondStartTimes;                                                    // 二次启动保护的次数
    uint8 StallTimes;                                                          // 堵转保护次数
    uint8 LossPHTimes;                                                         // 缺相保护次数
    uint8 CurrentPretectTimes;                                                 // 过流保护次数
    uint8 StartFlag;                                                          // 启动保护的标志位，用于判断哪个方法起作用
    uint8 StallFlag;                                                          // 堵转保护的标志位，用于判断哪个方法起作用
    uint8 VoltagePretectTimes;                                                // 电压保护次数
}ProtectVarible;

typedef struct
{
    //voltage protect
    uint16 OverVoltDetecCnt;                                                    // 过压检测计数
    uint16 UnderVoltDetecCnt;                                                   // 欠压检测计数、

    //stall protect
    uint16 StallDelayCnt;                                                       // 堵转延迟判断计时
    uint16 StallDectEs;                                                         // method 1，与ES相关
    uint16 StallDectSpeed;                                                      // method 2，与速度相关
    uint16 StallSpeedAndEsCnt;                                                  // 堵转保护恢复时间
    
	//Loss Phase protect
    uint16 Lphasecnt;                                                           // 缺相保护计时
    uint16 AOpencnt ;                                                           // A缺相计数
    uint16 BOpencnt ;                                                           // B缺相计数
    uint16 COpencnt ;                                                           // C缺相计数
	uint16 DectCycleCnt; 
	
    //start protect
    uint16 StartESCount;                                                         // 启动保护判断ES的计数
    uint16 StartDelay;                                                           // 启动保护判断ES的延迟
    uint16 StartFocmode;                                                         // 启动保护判断FOCMODE状态的计时 
    //NTC protect
    uint16 NTCDetecCnt;                                                         //过温保护
}FaultVarible;

typedef enum
{
    FaultNoSource      = 0,                                                     // 无故障
    FaultHardOVCurrent = 1,                                                     // 硬件过流
    FaultSoftOVCurrent = 2,                                                     // 软件过流
    FaultUnderVoltageDC = 3,                                                     // 欠压保护
    FaultOverVoltageDC   = 4,                                                     // 过压保护
    FaultPhaseLost     = 5,                                                     // 缺相保护
    FaultStall         = 6,                                                     // 堵转保护
    FaultNtcOTErr      = 7,                                               ///< NTC过温
	FaultOffset        = 9,                                                     ///< 偏置电压保护 
} FaultStateType;

typedef struct
{
    uint16 DC_DelayTcnt;
    uint16 LP_DelayTcnt;
    uint16 OT_DelayTcnt;
    uint16 OverCurrent_DelayTcnt;
    uint16 Stall_DealyTcnt;
    uint16 WL_DelayTcnt;
    
    uint8  OV_Times; 
    uint8  OT_Times;
    uint8  LP_Times;
    uint8  OverCurrent_Times;
    uint8  Stall_Times;
    uint8  WL_Times;
    
    uint32      AllReCnt;//正常运行计数
    uint8       StallFeedbackFlag;	        // 堵转反馈标志位
    uint8       LossPHFeedbackFlag;        // 缺相反馈标志位
    uint8       CurrentPretectFeedbackFlag;// 过流反馈标志位
    uint8       TempProtectFeedbackFlag;   // 过温反馈标志位
    uint8       UnderVolFeedbackFlag;   // 欠压反馈标志位
    uint8       OverVolFeedbackFlag;   // 过压反馈标志位
    
}FaultRecoverTypedef;

extern FaultVarible   xdata mcFaultDect;
extern CurrentVarible  mcCurVarible;
extern ProtectVarible xdata mcProtectTime;
extern FaultStateType xdata mcFaultSource;
extern FaultRecoverTypedef          xdata   Restart;

extern void   Fault_OverUnderVoltage(void);
extern void   Fault_OverCurrent(void);
extern void   Fault_OverCurrentRecover(void);
extern void   Fault_Stall(void);
extern void   Fault_PhaseLoss(void);
extern void   Fault_Detection(void);
extern void   Fault_GetCurrentOffset(void);
extern void   Fault_Recovery(void);
extern void Fault_Detection(void);
#endif

