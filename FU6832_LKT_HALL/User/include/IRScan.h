/**************************** (C) COPYRIGHT 2015 Fortiortech shenzhen *****************************
* File Name          : IRScan.h
* Author             : Billy Long Fortiortech  Market Dept
* Version            : V1.0
* Date               : 01/07/2015
* Description        : This file contains all the common data types used for Motor Control.
***************************************************************************************************
* All Rights Reserved
**************************************************************************************************/ 

/* Define to prevent recursive inclusion --------------------------------------------------------*/
#ifndef __IRSCAN_H_
#define __IRSCAN_H_

#include "FU68xx_4_MCU.h"

#define		ShortPressMode									(0)
#define		LongPressMode										(1)
#define		UserCodeStudyMode								(LongPressMode)										//遥控学习模式：ShortPressMode:短按某个键执行学习；
																																						//LongPressMode：长按某个键学习
#define		StudyCode									 (IRALLOFF)													//对应执行学习功能的按键

#define 	UserCodeLength				    	(20)							//定义遥控地址码长度
#define 	DataCodeLength					    (8)								//定义遥控数据码长度
#define		CheckCodeLengh					    (4)
#define		AllCodeLength				  	    (UserCodeLength+DataCodeLength+CheckCodeLengh)															//定义遥控数据码长度

/*IR Scan Parameter*/                         
#define 	IRBitValue1TimeMax                (1.7)            // 数据为1时高电平长度最大值，单位ms    1.55ms
#define 	IRBitValue1TimeMin                (1.3)           // 数据为1时高电平长度最小值，单位ms
#define 	IRBitValue0TimeMax                (0.7)           // 数据为0时高电平长度最大值，单位ms 0.476ms
#define 	IRBitValue0TimeMin                (0.3)           // 数据为0时高电平长度最小值，单位ms
#define 	IRLeadCodeTimeMax				  (6.0)					 // 引导码周期长度最大值，单位ms 4.38ms
#define 	IRLeadCodeTimeMin				  (2.0)						 // 引导码周期长度最小值，单位ms
#define 	IRLeadCode0TimeMax				  (1.0)					 // 引导码周期长度最大值，单位ms 0.672ms
#define 	IRLeadCode0TimeMin				  (0.4)						 // 引导码周期长度最小值，单位ms

/*IR Scan*/
#define TempBitValue1Max                  (uint16)(IRBitValue1TimeMax*TIM4_Fre)
#define TempBitValue1Min                  (uint16)(IRBitValue1TimeMin*TIM4_Fre)
#define TempBitValue0Max               		(uint16)(IRBitValue0TimeMax*TIM4_Fre)
#define TempBitValue0Min               		(uint16)(IRBitValue0TimeMin*TIM4_Fre)
#define TempLeadCodeMax              			(uint16)(IRLeadCodeTimeMax*TIM4_Fre)
#define TempLeadCodeMin             			(uint16)(IRLeadCodeTimeMin*TIM4_Fre)
#define TempLeadCode0Max              			(uint16)(IRLeadCode0TimeMax*TIM4_Fre)
#define TempLeadCode0Min             			(uint16)(IRLeadCode0TimeMin*TIM4_Fre)

/*遥控码定义*/
#define IRALLOFF                          (0X0006)
#define IRFRCW                            (0X0004)
#define IRFRCCW                           (0X0011)
#define IRSpeed1                         	(0X0010)
#define IRSpeed2                         	(0X0012)
#define IRSpeed3                         	(0X001C)
#define IRSpeed4                         	(0X000A)
#define IRSpeed5                         	(0X000F)
#define IRSpeed6                         	(0X000C)
#define	IRAUTOPOWER1H						          (0X0002)
#define	IRAUTOPOWER2H						          (0X0009)
#define	IRAUTOPOWER4H					          	(0X0019)
#define	IRNatureWind						          (0x0015)

#define IRLED                        	  	(0X0008)
#define	IRONOFF					    	          	(0x0016)
/* Exported types -------------------------------------------------------------------------------*/
typedef struct
{	
	uint8   BYTE0;
	uint8   BYTE1;
	uint8   BYTE2;
	uint8   BYTE3;
	uint8   PID;
	uint8   B;
	
	uint32	BitValue;
	uint8 	BitCnt;
	uint16	Bit0Cnt;
	uint32	ByteValue;
	
	uint32	UserCode;
	uint32	DataCode;
	uint16	CurrentUserCode;
	uint16	CurrentDataCode;
  
	uint8 DataCodeNum;
	uint16 TempDataCode[4];
	uint8	IRReceiveFlag;
	uint8	OldDataCodeMixTimes0;
	uint8	OldDataCodeMixTimes1;
	uint8 OverFlowStatus;
	
	uint32	UserCodeLengthCover;
	uint32	DataCodeLengthCover;	
} IRScan_TypeDef;

typedef struct
{	
	uint8   NatureFlage;
	uint8   LEDONOFFStatus;
	uint8 	FlagONOFF;
	uint8 	ONOFFStatus;
	uint8 	FlagFR;
	uint8 	FlagSpeed;
	uint8	  FlagLED;
	uint8	  FlagNatureWind;
	uint8	  FlagAutoPower;
	uint8	  FlagUserCodeSave;	
	uint8	  FlagUserCodeSaveOFF;
	uint8 	FlagUserCodeRead;
	uint8  	FlagLED1Protect;
	uint8	  FlagLED2Protect;
	uint16	RunTimeLong;
	uint16 	TargetSpeed;
	uint16	SpeedLevel[10];
	
	
} IRControl_TypeDef;

typedef struct
{
	uint8 	FlagAutoPower;
	uint16 	Timer10sec;
	uint16 	ShutDowntime;
	uint16 	CurrentTime;
} IRControl_AutoPowerDef;

extern IRControl_AutoPowerDef AutoPowerState;
extern IRScan_TypeDef xdata IRScan;
extern IRControl_TypeDef xdata IRControl;

/* Exported functions ---------------------------------------------------------------------------*/
extern void IRInit(void);
extern void IRValue(void);
extern void SetSpeed(uint8 SpeedLevel);
extern void SetAutoPower(uint16 Time);
extern void IRScanControl(void);
extern void AutoPowerControl(void);
extern uint8 GetUserCode(void);
extern void IRONOFF_Control(void);
extern void NatureWind(void);
extern void LEDDisplay(void);
#endif