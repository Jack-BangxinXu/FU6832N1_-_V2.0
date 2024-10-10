/**
 * @file	 FU68xx_4_MCU.h
 * @version	 V1.0.0
 * @author	 FortiorTech Hardware Team
 * @date	 2021-07-15	22:23:59
 * @brief	 This file contains	...
 * 
 * @copyright Copyright(C) 2022, Fortior Technology	Co., Ltd. All rights reserved.
 */

#ifndef	__FU68XX_4_MCU_H__
#define	__FU68XX_4_MCU_H__

// Include external	header file.
#include "FU68xx_4_Type.h"

#ifdef __cplusplus
extern "C" {
#endif


/**************************************************************************************************///Define Macro
#define	FREC							(24000000)								// MCU工作频率
	
/**************************************************************************************************///Function Subject
#define	SetReg(reg,	val1, val2)			((reg) = (reg) & (~(val1)) | (val2))	// 将reg中val1对应的位写val2
#define	SetBit(reg,	val)				((reg) |=  (val))						// 将reg中val对应的位写1
#define	ClrBit(reg,	val)				((reg) &= ~(val))						// 将reg中val对应的位写0
#define	XorBit(reg,	val)				((reg) ^=  (val))						// 将reg中val对应的位取反
#define	ReadBit(reg, val)				(((reg)	& (val)) ==	(val))				// 判断reg中val对应的位是否为1
/**************************************************************************************************///Register Map
// 搜索快照寄存器请在Keil搜索"[0-9A-Z]__[A-Z]"，勾选"Match Case"和"Regular Expressior"
// 快速搜索外设方法:在搜索对话框中输入"//"+外设名称.例:搜索TIMER1,则输入"//TIM1"

/******************************************************************************///SFR
 //sfr16   DPTR							  =	0x82;								  // RV:0000H  8051指针
SFR16(DPTR,	0x82);
 //sfr	   PSW							  =	0xd0;								  // RV:  00H  8051状态寄存器
 //sbit	   CY										= PSW^7;					  //			   rw--	进/借位标志
 //sbit	   AC										= PSW^6;					  //			   rw--	BCD进/借位标志
 //sbit	   F0										= PSW^5;					  //			   rw--	用户自定义标志0
 //sbit	   RS1										= PSW^4;					  //			   rw--	R寄存器换页位1
 //sbit	   RS0										= PSW^3;					  //			   rw--	R寄存器换页位0
 //sbit	   OV										= PSW^2;					  //			   rw--	算术运算溢出标志
 //sbit	   F1										= PSW^1;					  //			   rw--	用户自定义标志1
 //sbit	   P										= PSW^0;					  //			   rw--	奇偶标志
SFR(PSW, 0xd0);
	SBIT(CY, 0xd0, 7);
	SBIT(AC, 0xd0, 6);
	SBIT(F0, 0xd0, 5);
	SBIT(RS1,0xd0, 4);
	SBIT(RS0,0xd0, 3);
	SBIT(OV, 0xd0, 2);
	SBIT(F1, 0xd0, 1);
	SBIT(P,	 0xd0, 0);

 //sfr	   ACC							  =	0xe0;								  // RV:  00H  8051	A寄存器
SFR(ACC, 0xe0);
/******************************************************************************///RST
 //sfr	   RST_SR						  =	0xc9;								  // RV:  xxH  复位状态寄存器
SFR(RST_SR,	0xc9);
 #define RSTPOW									  0x80							//				 r--- 上电复位标志
 #define RSTCLR									  0x80							//				 w1-- 上电复位标志
 #define RSTEXT									  0x40							//				 r--- 外部复位标志
 #define RSTLVD									  0x20							//				 r--- 低压复位标志
 #define RSTEOS									  0x10							//				 r--- 电应力过度复位标志
 #define RSTWDT									  0x08							//				 r--- 看门狗复位标志
 #define RSTFED									  0x04							//				 r--- 代码保护复位
 #define RSTDBG									  0x02							//				 r--- 调试接口复位
 #define SOFTR									  0x01							//				 rw1- 清除复位标志
/******************************************************************************///RTC
 #define RTC_TM							*(_IO uint16 xdata *)0x402c
 #define RTC_STA						*(_IO  uint8 xdata *)0x402e
 #define RTC_EN									  0x80							//				 rw-- RTC使能
 #define RTC_IF									  0x40							//				 rw-- RTC中断标志
 #define ISOSCEN								  0x10							//				 rw-- 内部慢时钟使能
/******************************************************************************///CLOCK_CAL
 #define CAL_CR0						*(_IO  uint8 xdata *)0x4044
 #define CAL_STA								  0x80							//				 w-- CLOCK_CAL使能,	r--	0-->Done 1-->ING
 #define CAL_CR1						*(_IO  uint8 xdata *)0x4045
/******************************************************************************///IRQ
 //	IRQ	Channel
 //	LVW/TSD			interrupt 0
 //	INT0			interrupt 1
 //	INT1			interrupt 2
 //	DRV				interrupt 3
 //	TIM2			interrupt 4
 //	TIM1			interrupt 5
 //	ADC				interrupt 6
 //	CMP				interrupt 7
 //	RTC				interrupt 8
 //	TIM3			interrupt 9
 //	TIM4			interrupt 10
 //	SysTick			interrupt 11
 //	I2C/UART1		interrupt 13
 //	SPI/UART2		interrupt 14
 //	DMA				interrupt 15

 //sfr	   TCON							  =	0x88;								  // RV:  00H  8051中断控制寄存器
 //sbit	   TSDIF									= TCON^5;					  //			   rw--	TSD温度感应中断标志
 //sbit	   IT11										= TCON^4;					  //			   rw--	外部中断1触发配置1
 //sbit	   IT10										= TCON^3;					  //			   rw--	外部中断1触发配置0
 //sbit	   IF0										= TCON^2;					  //			   rw--	外部中断0标志
 //sbit	   IT01										= TCON^1;					  //			   rw--	外部中断0触发配置1
 //sbit	   IT00										= TCON^0;					  //			   rw--	外部中断0触发配置0
SFR(TCON, 0x88);
 	SBIT(TSDIF,0x88, 5);
	SBIT(IT11, 0x88, 4);
	SBIT(IT10, 0x88, 3);
	SBIT(IF0,  0x88, 2);
	SBIT(IT01, 0x88, 1);
	SBIT(IT00, 0x88, 0);
	
 //sfr	   IE							  =	0xa8;								  // RV:  00H  8051	中断开关	
// sbit	   EA										= IE^7;						  //			   rw--	MCU总中断使能
// sbit	   RTCIE									= IE^6;						  //			   rw--	RTC中断使能
// sbit	   ES0										= IE^4;						  //			   rw--	UART中断使能
// sbit	   SPIIE									= IE^3;						  //			   rw--	SPI中断使能
// sbit	   EX1										= IE^2;						  //			   rw--	外部中断1使能
// sbit	   TSDIE									= IE^1;						  //			   rw--	TSD中断使能
// sbit	   EX0										= IE^0;						  //			   rw--	外部中断0使能
 SFR(IE, 0xa8);
	SBIT(EA,   0xa8, 7);
	SBIT(RTCIE,0xa8, 6);
	SBIT(ES0,  0xa8, 4);
	SBIT(SPIIE,0xa8, 3);
	SBIT(EX1,  0xa8, 2);
	SBIT(TSDIE,0xa8, 1);
	SBIT(EX0,  0xa8, 0);

// sfr	   IP0							  =	0xb8;								  // RV:  00H  外设中断优先级设置G0
// sbit	   PDRV1									= IP0^7;					  //			   rw--	DRV优先级配置1
// sbit	   PDRV0									= IP0^6;					  //			   rw--	DRV优先级配置0
// sbit	   PX11										= IP0^5;					  //			   rw--	外部中断1优先级配置1
// sbit	   PX10										= IP0^4;					  //			   rw--	外部中断1优先级配置0
// sbit	   PX01										= IP0^3;					  //			   rw--	外部中断0优先级配置1
// sbit	   PX00										= IP0^2;					  //			   rw--	外部中断0优先级配置0
// sbit	   PLVW1									= IP0^1;					  //			   rw--	LVW优先级配置1
// sbit	   PLVW0									= IP0^0;					  //			   rw--	LVW优先级配置0
SFR(IP0, 0xb8);
	SBIT(PDRV1,	0xb8, 7);
	SBIT(PDRV0,	0xb8, 6);
	SBIT(PX11,	0xb8, 5);
	SBIT(PX10,	0xb8, 4);
	SBIT(PX01,	0xb8, 3);
	SBIT(PX00,	0xb8, 2);
	SBIT(PLVW_TSD1,	0xb8, 1);
	SBIT(PLVW_TSD0,	0xb8, 0);
 	
// sfr	   IP1							  =	0xc0;								  // RV:  00H  外设中断优先级设置G1
// sbit	   PCMP1									= IP1^7;					  //			   rw--	CMP优先级配置1
// sbit	   PCMP0									= IP1^6;					  //			   rw--	CMP优先级配置0
// sbit	   PADC1									= IP1^5;					  //			   rw--	ADC优先级配置1
// sbit	   PADC0									= IP1^4;					  //			   rw--	ADC优先级配置0
// sbit	   PTIM11									= IP1^3;					  //			   rw--	TIM1优先级配置1
// sbit	   PTIM10									= IP1^2;					  //			   rw--	TIM1优先级配置0
// sbit	   PTIM21									= IP1^1;					  //			   rw--	TIM2优先级配置1
// sbit	   PTIM20									= IP1^0;					  //			   rw--	TIM2优先级配置0
SFR(IP1, 0xc0);
	SBIT(PCMP1,	 0xc0, 7);
	SBIT(PCMP0,	 0xc0, 6);
	SBIT(PADC1,	 0xc0, 5);
	SBIT(PADC0,	 0xc0, 4);
 	SBIT(PTIM11, 0xc0, 3);
 	SBIT(PTIM10, 0xc0, 2);
 	SBIT(PTIM21, 0xc0, 1);
 	SBIT(PTIM20, 0xc0, 0);
 	
// sfr	   IP2							  =	0xc8;								  // RV:  00H  外设中断优先级设置G2
// sbit	   PTSD1									= IP2^7;					  //			   rw--	TSD优先级配置1
// sbit	   PTSD0									= IP2^6;					  //			   rw--	TSD优先级配置0
// sbit	   PTIM4S1									= IP2^5;					  //			   rw--	TIM4/SysTick优先级配置1
// sbit	   PTIM4S0									= IP2^4;					  //			   rw--	TIM4/SysTick优先级配置0
// sbit	   PTIM31									= IP2^3;					  //			   rw--	TIM3优先级配置1
// sbit	   PTIM30									= IP2^2;					  //			   rw--	TIM3优先级配置0
// sbit	   PRTC1									= IP2^1;					  //			   rw--	RTC优先级配置1
// sbit	   PRTC0									= IP2^0;					  //			   rw--	RTC优先级配置0
SFR(IP2, 0xc8);
	SBIT(PTIM41, 0xc8, 7);
	SBIT(PTIM40, 0xc8, 6);
 	SBIT(PSYSTICK1,0xc8, 5);
 	SBIT(PSYSTICK0,0xc8, 4);
 	SBIT(PTIM31, 0xc8, 3);
 	SBIT(PTIM30, 0xc8, 2);
	SBIT(PRTC1,	 0xc8, 1);
	SBIT(PRTC0,	 0xc8, 0);
 	
// sfr	   IP3							  =	0xd8;								  // RV:  00H  外设中断优先级设置G3
// sbit	   PDMA1									= IP3^7;					  //			   rw--	DMA优先级配置1
// sbit	   PDMA0									= IP3^6;					  //			   rw--	DMA优先级配置0
// sbit	   PSPI_UT21								= IP3^5;					  //			   rw--	SPI/UT2优先级配置1
// sbit	   PSPI_UT20								= IP3^4;					  //			   rw--	SPI/UT2优先级配置0
// sbit	   PI2C_UT11								= IP3^3;					  //			   rw--	I2C/UT1优先级配置1
// sbit	   PI2C_UT10								= IP3^2;					  //			   rw--	I2C/UT1优先级配置0
// sbit	   PCMP31									= IP3^1;					  //			   rw--	CMP3优先级配置1
// sbit	   PCMP30									= IP3^0;					  //			   rw--	CMP3优先级配置0
 SFR(IP3, 0xd8);
 	SBIT(PDMA1,		0xd8, 7);
 	SBIT(PDMA0,		0xd8, 6);
	SBIT(PSPI_UT21,	0xd8, 5);
	SBIT(PSPI_UT20,	0xd8, 4);
	SBIT(PI2C_UT11,	0xd8, 3);
	SBIT(PI2C_UT10,	0xd8, 2);
	SBIT(PCMP31,	0xd8, 1);
	SBIT(PCMP30,	0xd8, 0);
/******************************************************************************///I2C
 #define I2C_CR							*(_IO  uint8 xdata *)0x4028			   // RV:  00H	I2C控制寄存器
 #define I2CEN									  0x80							//				 rw-- I2C使能
 #define I2CMS									  0x40							//				 rw-- 主/从机模式选择
 #define I2CSPD1								  0x04							//				 rw-- 速度配置1
 #define I2CSPD0								  0x02							//				 rw-- 速度配置0
 #define I2CIE									  0x01							//				 rw-- 中断控制

 #define I2C_SR							*(_IO  uint8 xdata *)0x402b			   // RV:  00H	I2C状态寄存器
 #define I2CBSY									  0x80							//				 r--- I2C忙标志
 #define DMOD									  0x40							//				 rw-- I2C读写控制
 #define I2CSTA									  0x10							//				 rw-- START信号控制
 #define I2CSTP									  0x08							//				 rw-- STOP信号控制
 #define STR									  0x04							//				 rw-- I2C事件完成标志
 #define NACK									  0x02							//				 rw-- 应答信号控制
 #define I2CIF									  0x01							//				 r--- 中断标志

 #define I2C_ID							*(_IO  uint8 xdata *)0x4029			   // RV:  00H	本机2C地址
 #define GC										  0x01							//				 广播模式

 #define I2C_DR							*(_IO  uint8 xdata *)0x402a			   // RV:  00H	I2C数据寄存器
/******************************************************************************///SPI
 #define SPI_CR0						*(_IO  uint8 xdata *)0x4030			   // RV:  0bH	SPI控制寄存器1
 #define SPIBSY									  0x80							//				 r--- 忙标志
 #define SPIMS									  0x40							//				 rw-- 主/从机配置
 #define CPHA									  0x20							//				 rw-- 时钟相位
 #define CPOL									  0x10							//				 rw-- 时钟空闲电平
 #define SLVSEL									  0x08							//				 r--- NSS处理后的信号
 #define NSSIN									  0x04							//				 r--- NSS即时信号
 #define SRMT									  0x02							//				 r--- 移位寄存器空标志
 #define RXBMT									  0x01							//				 r--- 接收缓冲器空标志

 #define SPI_CR1						*(_IO  uint8 xdata *)0x4031			   // RV:  02H	SPI控制寄存器2
 #define SPIIF									  0x80							//				 rw0- 中断标志
 #define WCOL									  0x40							//				 rw0- 写冲突标志
 #define MODF									  0x20							//				 rw0- 模式错误标志
 #define RXOVRN									  0x10							//				 rw0- 接收溢出标志
 #define NSSMOD1								  0x08							//				 rw-- SPI模式配置位1
 #define NSSMOD0								  0x04							//				 rw-- SPI模式配置位0
 #define TXBMT									  0x02							//				 r--- 发送缓冲器空标志
 #define SPIEN									  0x01							//				 rw-- SPI使能

 #define SPI_CLK						*(_IO  uint8 xdata *)0x4032			   // RV:  00H	SPI时钟配置寄存器
 #define SPI_DR							*(_IO  uint8 xdata *)0x4033			   // RV:  00H	SPI数据寄存器
/******************************************************************************///UART
// sfr	   UT_CR						  =	0x98;								  // RV:  00H  UART控制寄存器
// sbit	   UT_MOD1									= UT_CR^7;					  //			   rw--	UART模式配置1
// sbit	   UT_MOD0									= UT_CR^6;					  //			   rw--	UART模式配置0
// sbit	   SM2										= UT_CR^5;					  //			   rw--	多机通信使能
// sbit	   REN										= UT_CR^4;					  //			   rw--	接收使能
// sbit	   TB8										= UT_CR^3;					  //			   rw--	9位模式下发送的第9位
// sbit	   RB8										= UT_CR^2;					  //			   rw--	9位模式下接收的第9位
// sbit	   TI										= UT_CR^1;					  //			   rw--	发送完成标志
// sbit	   RI										= UT_CR^0;					  //			   rw--	接收完成标志
 SFR(UT_CR,	0x98);
 	SBIT(UT_MOD1,0x98, 7);
 	SBIT(UT_MOD0,0x98, 6);
 	SBIT(SM2,	 0x98, 5);
	SBIT(REN,	 0x98, 4);
	SBIT(TB8,	 0x98, 3);
	SBIT(RB8,	 0x98, 2);
	SBIT(TI,	 0x98, 1);
	SBIT(RI,	 0x98, 0);
 	
 //sfr	   UT_DR						  =	0x99;								  // RV:  00H  UART数据寄存器
 SFR(UT_DR,	0x99);
 //sfr16   UT_BAUD						  =	0x9a;								  // RV:009bH  UART波特率控制寄存器
 SFR16(UT_BAUD,	0x9a);
 
 #define UART_2xBAUD							  0x8000						//				 rw--倍频使能

 //sfr	   UT2_CR						  =	0x8a;								  // RV:  00H  UART2控制寄存器
 SFR(UT2_CR, 0x8a);
 #define UT2MOD1																	0x80
 #define UT2MOD0																	0x40
 #define UT2SM2																		0x20
 #define UT2REN																		0x10
 #define UT2TB8																		0x08
 #define UT2RB8																		0x04
 #define UT2TI																		0x02
 #define UT2RI																		0x01

 #define UT2_BAUD						*(_IO uint16 xdata *)0x4042			   // RV:009bH	UART2波特率控制寄存器
 #define BAUD2_SEL								  0x8000						//				 rw--倍频使能
 #define UART2CH								  0x4000						//				 rw--UART2功能转移使能
 #define UART2IEN								  0x2000						//				 rw--UART2中断使能
 //sfr	   UT2_DR						  =	0x89;								  // RV:  00H  UART2数据寄存器
  SFR(UT2_DR, 0x89);
/******************************************************************************///LIN
 #define LIN_CR							*(_IO  uint8 xdata *)0x40e0			   // RV:0000H	LIN控制寄存器
 #define LINIE									  0x08							//				 rw-- LIN中断使能
 #define CHKMOD									  0x04							//				 rw-- 校验模式配置
 #define LINRW									  0x02							//				 rw-- 读写模式配置
 #define AUTOSIZE								  0x01							//				 rw-- 根据ID自动设置数据长度使能

 #define LIN_SR							*(_IO  uint8 xdata *)0x40e1			   // RV:0000H	LIN状态寄存器
 #define ERRSYNC								  0x80							//				 r--- 同步错误,	同步超时或同步过快
 #define ERRCHK									  0x40							//				 r--- 数据校验错误
 #define ERRPRTY								  0x20							//				 r--- ID校验错误
 #define ABORT									  0x10							//				 r--- 传输被中断, 如果传输时收到帧头或者LIN_CR[LIN_STOP]置1, 那么该位置1
 #define LINACT									  0x08							//				 r--- LIN总线上处于活动状态
 #define LINIDLE								  0x04							//				 rw0- LIN总线上处于空闲状态并持续4s
 #define LINDONE								  0x02							//				 rw-- LIN传输完成
 #define LINREQ									  0x01							//				 rw-- LIN收到帧头

 #define LIN_CSR						*(_IO  uint8 xdata *)0x40e2			   // RV:0000H	LIN状态控制寄存器
 #define LINSLP									  0x20							//				 rw-- LIN的睡眠状态
 #define CLRERR									  0x10							//				 rw0- 清除错误标志
 #define LINWAKEUP								  0x08							//				 rw1- 读: LIN是否被唤醒; 写: 发送唤醒信号
 #define LINACK									  0x04							//				 w1-- 用于响应帧头,	在该位置1前必须将校验模式, 读写模式, 数据, 数据长度准备好
 #define LINSTOP								  0x02							//				 w1-- 中断当前的传输
 #define LINEN									  0x01							//				 rw-- LIN使能

 #define LIN_ID							*(_I   uint8 xdata *)0x40e3			   // RV:0000H	LIN收到的ID的寄存器
 #define LIN_SIZE						*(_IO  uint8 xdata *)0x40e4			   // RV:0000H	LIN数据长度寄存器
 #define LIN_BAUD						*(_I  uint16 xdata *)0x40e6			   // RV:04afH	LIN波特率寄存器
/******************************************************************************///MDU
 //sfr	   MDU_CR						  =	0xc1;								  // RV:  00H  MDU控制寄存器
   SFR(MDU_CR, 0xc1);
 #define MDUBUSY								  0x80							//				 r--- MDU繁忙标志
 #define MDUDONE								  0x40							//				 w--- 终止MDU运算
 #define MDURUN									  0x20							//				 w--- 启动MDU运算

 //sfr	   MDU_MD						  =	0xca;								  // RV:  00H  MDU模式配置
 SFR(MDU_MD, 0xca);
 #define MDUMOD2								  0x04							//				 rw-- MDU模式配置2
 #define MDUMOD1								  0x02							//				 rw-- MDU模式配置1
 #define MDUMOD0								  0x01							//				 rw-- MDU模式配置0

 //sfr16   MDU_A						  =	0xc6;								  // RV:0000H  MDU数据寄存器A
 //sfr16   MDU_B						  =	0xc4;								  // RV:0000H  MDU数据寄存器B
 //sfr16   MDU_C						  =	0xc2;								  // RV:0000H  MDU数据寄存器C
 //sfr	   MDU_D						  =	0xcb;								  // RV:  00H  MDU数据寄存器D
  SFR16(MDU_A, 0xc6);
  SFR16(MDU_B, 0xc4);
  SFR16(MDU_C, 0xc2);
  SFR(MDU_D, 0xcb);
/******************************************************************************///PI
 #define PI0_KP							*(_IO  uint16 xdata *)0x02e0			   // RV:0000H	PI1上二个输入误差
 #define PI0_KI							*(_IO  uint16 xdata *)0x02e2			   // RV:0000H	PI1的微分参数
 #define PI0_UKMAX						*(_IO  uint16 xdata *)0x02e4			   // RV:0000H	PI0的比例参数
 #define PI0_UKMIN						*(_IO  uint16 xdata *)0x02e6			   // RV:0000H	PI0的积分参数
 #define PI0_EK1						*(_IO  uint16 xdata *)0x02e8			   // RV:0000H	PI0的输出允许的最大值
 #define PI0_EK							*(_IO  uint16 xdata *)0x02ea			   // RV:0000H	PI0的输出允许的最小值
 #define PI0_UKH						*(_IO  uint16 xdata *)0x02ec			   // RV:0000H	PI0的上一个输入误差
 #define PI0_UKL						*(_IO  uint16 xdata *)0x02ee			   // RV:0000H	PI0的误差输入

 #define PI1_KP							*(_IO  uint16 xdata *)0x02d0			   // RV:0000H	PI1的比例参数
 #define PI1_KI							*(_IO  uint16 xdata *)0x02d2			   // RV:0000H	PI1的积分参数
 #define PI1_UKMAX						*(_IO  uint16 xdata *)0x02d4			   // RV:0000H	PI1的输出允许的最大值
 #define PI1_UKMIN						*(_IO  uint16 xdata *)0x02d6			   // RV:0000H	PI1的输出允许的最小值
 #define PI1_EK1						*(_IO  uint16 xdata *)0x02d8			   // RV:0000H	PI1的上一个输入误差
 #define PI1_EK							*(_IO  uint16 xdata *)0x02da			   // RV:0000H	PI1的误差输入
 #define PI1_UKH						*(_IO  uint16 xdata *)0x02dc			   // RV:0000H	PI1的输出结果高16位
 #define PI1_UKL						*(_IO  uint16 xdata *)0x02de			   // RV:0000H	PI1的输出结果低16位

 #define PI2_KP							*(_IO  uint16 xdata *)0x02bc			   // RV:0000H	PI2的比例参数
 #define PI2_KI							*(_IO  uint16 xdata *)0x02be			   // RV:0000H	PI2的积分参数
 #define PI2_UKMAX						*(_IO  uint16 xdata *)0x02c0			   // RV:0000H	PI2的输出允许的最大值
 #define PI2_UKMIN						*(_IO  uint16 xdata *)0x02c2			   // RV:0000H	PI2的输出允许的最小值
 #define PI2_EK1						*(_IO  uint16 xdata *)0x02c4			   // RV:0000H	PI2的上一个输入误差
 #define PI2_EK							*(_IO  uint16 xdata *)0x02c6			   // RV:0000H	PI2的误差输入
 #define PI2_UKH						*(_IO  uint16 xdata *)0x02c8			   // RV:0000H	PI2的输出结果高16位
 #define PI2_UKL						*(_IO  uint16 xdata *)0x02ca			   // RV:0000H	PI2的输出结果低16位
 #define PI2_KD							*(_IO  uint16 xdata *)0x02cc			   // RV:0000H	PI2上二个输入误差
 #define PI2_EK2						*(_IO  uint16 xdata *)0x02ce			   // RV:0000H	PI2的微分参数

 #define PI3_KP							*(_IO  uint16 xdata *)0x02a8			   // RV:0000H	PI3的比例参数
 #define PI3_KI							*(_IO  uint16 xdata *)0x02aa			   // RV:0000H	PI3的积分参数
 #define PI3_UKMAX						*(_IO  uint16 xdata *)0x02ac			   // RV:0000H	PI3的输出允许的最大值
 #define PI3_UKMIN						*(_IO  uint16 xdata *)0x02ae			   // RV:0000H	PI3的输出允许的最小值
 #define PI3_EK1						*(_IO  uint16 xdata *)0x02b0			   // RV:0000H	PI3的上一个输入误差
 #define PI3_EK							*(_IO  uint16 xdata *)0x02b2			   // RV:0000H	PI3的误差输入
 #define PI3_UKH						*(_IO  uint16 xdata *)0x02b4			   // RV:0000H	PI3的输出结果高16位
 #define PI3_UKL						*(_IO  uint16 xdata *)0x02b6			   // RV:0000H	PI3的输出结果低16位
 #define PI3_KD							*(_IO  uint16 xdata *)0x02b8			   // RV:0000H	PI3上二个输入误差
 #define PI3_EK2						*(_IO  uint16 xdata *)0x02ba			   // RV:0000H	PI3的微分参数

 //sfr	   PI_CR						  =	0xf9;								  // RV:  00H  PI控制寄存器
 SFR(PI_CR,	0xf9);
 #define T2TSS									  0x80							//				 rw-- TIM2步进模式输入使能
 #define T2RPD									  0x40							//				 rw-- RPD使能
 #define PIBSY									  0X10							//				 rw-- PI繁忙
 #define PI3STA									  0x08							//				 rw-- PI3使能
 #define PI2STA									  0x04							//				 rw-- PI2使能
 #define PI1STA									  0x02							//				 rw-- PI1使能
 #define PI0STA									  0x01							//				 rw-- PI0使能
/******************************************************************************///FOC
 #define FOC_CR0						*(_IO  uint8 xdata *)0x409f			   // RV:  00H	FOC控制寄存器0
 #define OMIF									  0x80							//				 r--- 当前转速>FOC_EFREQMIN为1
 #define OMAF									  0x40							//				 r--- 当前转速>FOC_EFREQMAX为1
 #define MERRS1									  0x20							//				 rw-- 滑膜算法的MAX	ERR选择
 #define MERRS0									  0x10							//				 rw-- 滑膜算法的MAX	ERR选择
 #define UCSEL									  0x08							//				 rw-- UDC采样通道选择0：AD2	1:AD14
 #define OMAS									  0x04							//				 rw-- 估算速度过大时输出选择位
 #define ESCMS									  0x02							//				 rw-- omega计算模式为ATAN
 #define EDIS									  0x01							//				 rw-- EALPHA/EBETA自动更新禁止

 #define FOC_CR1						*(_IO  uint8 xdata *)0x40a0			   // RV:  00H	FOC控制寄存器1
 #define OVMDL									  0x80							//				 rw-- 过调制使能
 #define EFAE									  0x40							//				 rw-- 估算器强制角度使能
 #define RFAE									  0x20							//				 rw-- 强制爬坡角度使能
 #define ANGM									  0x10							//				 rw-- 角度模式选择
 #define CSM1									  0x08							//				 rw-- 电流采样模式配置1
 #define CSM0									  0x04							//				 rw-- 电流采样模式配置0
 #define SPWMSEL								  0x02							//				 rw-- SPWM模式选择
 #define SVPWMEN								  0x01							//				 rw-- SVPWM/SPWM选择

 #define FOC_CR2						*(_IO  uint8 xdata *)0x40a1			   // RV:  00H	FOC控制寄存器2
 #define ESEL									  0x80							//				 rw-- 估算器模式
 #define ICLR									  0x40							//				 rw-- FOC__IA/B/CMAX清零
 #define F5SEG									  0x20							//				 rw-- 7/5段式SVPWM模式
 #define DSS									  0x10							//				 rw-- 2/3电阻采样模式
 #define CSOC1									  0x08							//				 rw-- 电流采样基准校准配置1
 #define CSOC0									  0x04							//				 rw-- 电流采样基准校准配置0
 #define UQD									  0x02							//				 rw-- 禁能Q轴PI
 #define UDD									  0x01							//				 rw-- 禁能D轴PI

 #define FOC_EKP						*(_IO  int16 xdata *)0x4074			   // RV:0000H	估算器的PI的P参数
 #define FOC_EKI						*(_IO  int16 xdata *)0x4076			   // RV:0000H	估算器的PI的I参数
 #define FOC_KSLIDE						*(_IO  int16 xdata *)0x4078			   // RV:0000H	估算器SMO模式下的KSLIDE	 或	 PLL模式下的KP
 #define FOC_EKLPFMIN					*(_IO  int16 xdata *)0x407a			   // RV:0000H	估算器SMO模式下BMF的LPF系数最小值  或  PLL模式下的KI
 #define FOC_EBMFK						*(_IO  int16 xdata *)0x407c			   // RV:0000H	估算器反电动势的LPF系数
 #define FOC_OMEKLPF					*(_IO  int16 xdata *)0x407e			   // RV:0000H	估算器速度计算的LPF系数
 #define FOC_FBASE						*(_IO  int16 xdata *)0x4080			   // RV:0000H	估算器角度增量(OMEGA)的系数
 #define FOC_EFREQACC					*(_IO uint16 xdata *)0x4082			   // RV:0000H	估算器在强制角度模式下的OMEGA增量
 #define FOC_EFREQMIN					*(_IO  int16 xdata *)0x4084			   // RV:0000H	估算器在强制角度模式下的OMEGA最小值
 #define FOC_EFREQHOLD					*(_IO  int16 xdata *)0x4086			   // RV:0000H	估算器在强制角度模式下的OMEGA保持值
 #define FOC_EFREQMAX					*(_IO  uint8 xdata *)0x406f			   // RV:  00H	估算器的强制角度模式下的OMEGA最大值
 #define FOC_EK3						*(_IO  int16 xdata *)0x4088			   // RV:0000H	估算器估算电流的系数3
 #define FOC_EK4						*(_IO  int16 xdata *)0x408a			   // RV:0000H	估算器估算电流的系数4
 #define FOC_EK1						*(_IO  int16 xdata *)0x408c			   // RV:0000H	估算器估算电流的系数1
 #define FOC_EK2						*(_IO  int16 xdata *)0x408e			   // RV:0000H	估算器估算电流的系数2
 #define FOC_IDREF						*(_IO  int16 xdata *)0x4090			   // RV:0000H	D轴电流参考值
 #define FOC_IQREF						*(_IO  int16 xdata *)0x4092			   // RV:0000H	Q轴电流参考值
 #define FOC_DQKP						*(_IO  int16 xdata *)0x4094			   // RV:0000H	DQ轴PI的比例参数
 #define FOC_DQKI						*(_IO  int16 xdata *)0x4096			   // RV:0000H	DQ轴PI的积分参数
 #define FOC__UDCFLT					*(_I   int16 xdata *)0x4098			   // RV:0000H	滤波后的母线电压
 #define FOC_TSMIN						*(_IO  uint8 xdata *)0x40a2			   // RV:  00H	单电阻模式下的ADC采样窗口  或  双三电阻模式下死区补偿
 #define FOC_TGLI						*(_IO  uint8 xdata *)0x40a3			   // RV:  00H	上桥导通窄脉冲消除
 #define FOC_TBLO						*(_IO  uint8 xdata *)0x40a4			   // RV:  00H	三电阻电流采样的屏蔽时间
 #define FOC_TRGDLY						*(_IO	int8 xdata *)0x40a5			   // RV:  00H	单电阻模式下ADC采样触发延迟	 或	 双三电阻模式下电流采样时机
 #define FOC_CSO						*(_IO  int16 xdata *)0x40a6			   // RV:4040H	电流采样基准值
 #define FOC__RTHESTEP					*(_IO  int16 xdata *)0x40a8			   // RV:0000H	爬坡速度
 #define FOC_RTHEACC					*(_O   int16 xdata *)0x40aa			   // RV:0000H	爬坡加速度
 #define FOC__EOMELPF					*(_I   int16 xdata *)0x40aa			   // RV:0000H	滤波后速度
 #define FOC__RTHECNT					*(_IO  uint8 xdata *)0x40ac			   // RV:  00H	爬坡次数
 #define FOC__THECOR					*(_IO  uint8 xdata *)0x40ad			   // RV:  01H	爬坡模式切换到估算模式的角度修正值
 #define FOC__EMF						*(_I   int16 xdata *)0x40ae			   // RV:0000H	估算器估算的反电动势EMF
 #define FOC__THECOMP					*(_O   int16 xdata *)0x40ae			   // RV:0000H	角度补偿值，用于补偿估算器估算出的角度
 #define FOC_DMAX						*(_IO  int16 xdata *)0x40b0			   // RV:0000H	D轴PI控制器的输出上限
 #define FOC_DMIN						*(_IO  int16 xdata *)0x40b2			   // RV:0000H	D轴PI控制器的输出下限
 #define FOC_QMAX						*(_IO  int16 xdata *)0x40b4			   // RV:0000H	Q轴PI控制器的输出上限
 #define FOC_QMIN						*(_IO  int16 xdata *)0x40b6			   // RV:0000H	Q轴PI控制器的输出下限
 #define FOC__UD						*(_IO  int16 xdata *)0x40b8			   // RV:0000H	D轴电压输出值
 #define FOC__UQ						*(_IO  int16 xdata *)0x40ba			   // RV:0000H	Q轴电压输出值
 #define FOC__ID						*(_I   int16 xdata *)0x40bc			   // RV:0000H	D轴反馈电流值
 #define FOC__IQ						*(_I   int16 xdata *)0x40be			   // RV:0000H	Q轴反馈电流值
 #define FOC__IBET						*(_I   int16 xdata *)0x40c0			   // RV:0000H	β轴采样电流值
 #define FOC__VBET						*(_I   int16 xdata *)0x40c2			   // RV:0000H	β轴电压输出值
 #define FOC_UDCPS						*(_O   int16 xdata *)0x40c2			   // RV:0000H	D轴的电压前馈补偿
 #define FOC__VALP						*(_I   int16 xdata *)0x40c4			   // RV:0000H	α轴电压输出值
 #define FOC_UQCPS						*(_O   int16 xdata *)0x40c4			   // RV:0000H	Q轴的电压前馈补偿
 #define FOC__IC						*(_I   int16 xdata *)0x40c6			   // RV:0000H	C相电流
 #define FOC__IB						*(_I   int16 xdata *)0x40c8			   // RV:0000H	B相电流
 #define FOC__IA						*(_I   int16 xdata *)0x40ca			   // RV:0000H	A相电流
 #define FOC__THETA						*(_IO  int16 xdata *)0x40cc			   // RV:0000H	电机电角度
 #define FOC__ETHETA					*(_IO  int16 xdata *)0x40ce			   // RV:0000H	估算器估算的角度
 #define FOC__EALP						*(_IO  int16 xdata *)0x40d0			   // RV:0000H	估算器估算反电动势的α轴值
 #define FOC__EBET						*(_IO  int16 xdata *)0x40d2			   // RV:0000H	估算器估算反电动势的β轴值
 #define FOC__EOME						*(_IO  int16 xdata *)0x40d4			   // RV:0000H	估算器估算的速度
 #define FOC__UQEX						*(_I   int16 xdata *)0x40d6			   // RV:0000H	Q轴的电压溢出值，用于弱磁控制
 #define FOC_KFG						*(_O  uint16 xdata *)0x40d6			   // RV:0000H	FG计算系数
 #define FOC__POW						*(_I   int16 xdata *)0x40d8			   // RV:0000H	电机当前运行功率
 #define FOC_EOMEKLPF					*(_O   uint8 xdata *)0x40d8			   // RV:0000H	EOMELPF的滤波系数
 #define FOC__IAMAX						*(_I   int16 xdata *)0x40da			   // RV:0000H	A相电流最大值
 #define FOC__IBMAX						*(_I   int16 xdata *)0x40dc			   // RV:0000H	B相电流最大值
 #define FOC__ICMAX						*(_I   int16 xdata *)0x40de			   // RV:0000H	C相电流最大值
/******************************************************************************///TIM1
 #define TIM1_CR0						*(_IO  uint8 xdata *)0x4068			   // RV:  00H	TIMER1控制寄存器0
 #define T1RWEN									  0x80							//				 r0w- T1RCEN操作允许
 #define T1CFLT1								  0x40							//				 rw-- 换相滤波配置1
 #define T1CFLT0								  0x20							//				 rw-- 换相滤波配置0
 #define T1FORC									  0x10							//				 rw-- 60°强制换相
 #define T1OPS1									  0x08							//				 rw-- 数据传输方式配置1
 #define T1OPS0									  0x04							//				 rw-- 数据传输方式配置0
 #define T1BCEN									  0x02							//				 rw-- 基本定时器计数使能
 #define T1RCEN									  0x01							//				 rw-- 重载定时器计数使能

 #define TIM1_CR1						*(_IO  uint8 xdata *)0x4069			   // RV:  00H	TIMER1控制寄存器1
 #define T1BAPE									  0x80							//				 rw-- TIM1__BARR自动装载使能

 #define TIM1_CR2						*(_IO  uint8 xdata *)0x406a			   // RV:  00H	TIMER1控制寄存器2
 #define T1BRS									  0x80							//				 rw-- 基本定时器复位源选择

 #define TIM1_CR3						*(_IO  uint8 xdata *)0x406b			   // RV:  00H	TIMER1控制寄存器3
 #define T1AFL									  0x80							//
 #define T1PSC2									  0x40							//				 rw-- 定时器分频配置2
 #define T1PSC1									  0x20							//				 rw-- 定时器分频配置1
 #define T1PSC0									  0x10							//				 rw-- 定时器分频配置0
 #define T1TIS1									  0x08							//				 rw-- 输入源选择配置1
 #define T1TIS0									  0x04							//				 rw-- 输入源选择配置0
 #define T1INM1									  0x02							//				 rw-- 输入源噪声滤波配置1
 #define T1INM0									  0x01							//				 rw-- 输入源噪声滤波配置0

 #define TIM1_CR4						*(_IO  uint8 xdata *)0x406c			   // RV:  00H	TIMER1控制寄存器4
 #define T1CST2									  0x04							//				 rw-- 换相状态机配置2
 #define T1CST1									  0x02							//				 rw-- 换相状态机配置1
 #define T1CST0									  0x01							//				 rw-- 换相状态机配置0

 #define TIM1_IER						*(_IO  uint8 xdata *)0x406d			   // RV:  00H	TIMER1中断控制
 #define T1UPD									  0x80							//				 r0w- OPS=00时，触发数据传输
 #define T1MAME									  0x40							//
 #define T1ADIE									  0x20							//
 #define T1BOIE									  0x10							//				 rw-- 基本定时器上溢中断使能
 #define T1ROIE									  0x08							//				 rw-- 重载定时器上溢中断使能
 #define T1WTIE									  0x04							//				 rw-- 写入时序中断使能
 #define T1PDIE									  0x02							//				 rw-- 位置检测中断使能
 #define T1BDIE									  0x01							//				 rw-- 屏蔽续流结束中断使能

 #define TIM1_SR						*(_IO  uint8 xdata *)0x406e			   // RV:  00H	TIMER1状态
 #define T1ADIF									  0x20							//
 #define T1BOIF									  0x10							//				 rw0- 基本定时器上溢中断标志
 #define T1ROIF									  0x08							//				 rw0- 重载定时器上溢中断标志
 #define T1WTIF									  0x04							//				 rw0- 写入时序中断标志
 #define T1PDIF									  0x02							//				 rw0- 位置检测中断标志
 #define T1BDIF									  0x01							//				 rw0- 屏蔽续流结束中断标志

 #define TIM1_DBR1						*(_IO uint16 xdata *)0x4074			   // RV:0000H	TIMER1在CST=1的数据
 #define TIM1_DBR2						*(_IO uint16 xdata *)0x4076			   // RV:0000H	TIMER1在CST=2的数据
 #define TIM1_DBR3						*(_IO uint16 xdata *)0x4078			   // RV:0000H	TIMER1在CST=3的数据
 #define TIM1_DBR4						*(_IO uint16 xdata *)0x407a			   // RV:0000H	TIMER1在CST=4的数据
 #define TIM1_DBR5						*(_IO uint16 xdata *)0x407c			   // RV:0000H	TIMER1在CST=5的数据
 #define TIM1_DBR6						*(_IO uint16 xdata *)0x407e			   // RV:0000H	TIMER1在CST=6的数据
 #define TIM1_DBR7						*(_IO uint16 xdata *)0x4080			   // RV:0000H	TIMER1在CST=7的数据
 #define T1CPE2									  0x4000						//				 rw-- 输入沿极性和比较器选择配置2
 #define T1CPE1									  0x2000						//				 rw-- 输入沿极性和比较器选择配置1
 #define T1CPE0									  0x1000						//				 rw-- 输入沿极性和比较器选择配置0
 #define T1WHP									  0x0800						//				 rw-- W相上管输出极性
 #define T1WLP									  0x0400						//				 rw-- W相下管输出极性
 #define T1VHP									  0x0200						//				 rw-- V相上管输出极性
 #define T1VLP									  0x0100						//				 rw-- V相下管输出极性
 #define T1UHP									  0x0080						//				 rw-- U相上管输出极性
 #define T1ULP									  0x0040						//				 rw-- U相下管输出极性
 #define T1WHE									  0x0020						//				 rw-- W相上管输出使能
 #define T1WLE									  0x0010						//				 rw-- W相下管输出使能
 #define T1VHE									  0x0008						//				 rw-- V相上管输出使能
 #define T1VLE									  0x0004						//				 rw-- V相下管输出使能
 #define T1UHE									  0x0002						//				 rw-- U相上管输出使能
 #define T1ULE									  0x0001						//				 rw-- U相下管输出使能

 #define TIM1_BCOR						*(_IO uint16 xdata *)0x4070			   // RV:0000H	捕获基本定时器计数值滤波值
 #define TIM1__BCNTR					*(_IO uint16 xdata *)0x4082			   // RV:0000H	基本定时器计数值
 #define TIM1__BCCR						*(_IO uint16 xdata *)0x4084			   // RV:0000H	捕获基本定时器计数值
 #define TIM1__BARR						*(_IO uint16 xdata *)0x4086			   // RV:0000H	基本定时器自动重载值
 #define TIM1__RARR						*(_IO uint16 xdata *)0x4088			   // RV:0000H	重载定时器自动重载值
 #define TIM1__RCNTR					*(_IO uint16 xdata *)0x408a			   // RV:0000H	重载定时器计数值
 #define TIM1__ITRIP					*(_I  uint16 xdata *)0x4098			   // RV:0000H	滤波后的母线电流
 #define TIM1__UCOP						*(_IO uint16 xdata *)0x408c
 #define TIM1__UFLP						*(_IO uint16 xdata *)0x408e
 #define TIM1__URES						*(_IO uint16 xdata *)0x4090
 #define TIM1__UIGN						*(_IO uint16 xdata *)0x4092
 #define TIM1_KF						*(_IO uint16 xdata *)0x4094
 #define TIM1_KR						*(_IO uint16 xdata *)0x4096
/******************************************************************************///TIM2
 //sfr	   TIM2_CR0						  =	0xa1;								  // RV:  00H  TIMER2控制寄存器0
 SFR(TIM2_CR0, 0xa1);
 #define T2PSC2									  0x80							//				 rw-- 定时器分频配置2
 #define T2PSC1									  0x40							//				 rw-- 定时器分频配置1
 #define T2PSC0									  0x20							//				 rw-- 定时器分频配置0
 #define T2OCM									  0x10							//				 rw-- 定时器比较匹配模式/QEP&步进模式配置
 #define T2IRE									  0x08							//				 rw-- 比较匹配/脉宽检测/方向改变中断使能
 #define T2CES									  0x04							//				 rw-- 边沿模式选择
 #define T2MOD1									  0x02							//				 rw-- 定时器模式配置1
 #define T2MOD0									  0x01							//				 rw-- 定时器模式配置0

 //sfr	   TIM2_CR1						  =	0xa9;								  // RV:  00H  TIMER2控制寄存器1
  SFR(TIM2_CR1,	0xa9);
 #define T2IR									  0x80							//				 rw0- 比较匹配标志
 #define T2IP									  0x40							//				 rw0- 周期检测/计数匹配标志
 #define T2IF									  0x20							//				 rw0- 计数上溢标志
 #define T2IPE									  0x10							//				 rw-- 周期检测/计数匹配中断使能
 #define T2IFE									  0x08							//				 rw-- 上溢中断使能
 #define T2FE									  0x04							//				 rw-- 噪声滤波使能
 #define T2DIR									  0x02							//				 r--- QEP/步进方向信号
 #define T2CEN									  0x01							//				 rw-- 定时器使能

 //sfr16   TIM2__DR						  =	0xac;								  // RV:0000H  TIMER2匹配值
 //sfr16   TIM2__ARR					  =	0xae;								  // RV:0000H  TIMER2重载值
 //sfr16   TIM2__CNTR					  =	0xaa;								  // RV:0000H  TIMER2计数值
 SFR16(TIM2__DR,   0xac);
 SFR16(TIM2__ARR,  0xae);
 SFR16(TIM2__CNTR, 0xaa);
/******************************************************************************///TIM3
 //sfr	   TIM3_CR0						  =	0x9c;								  // RV:  00H  TIMER3控制寄存器0
 SFR(TIM3_CR0, 0x9c);
 #define T3PSC2									  0x80							//				 rw-- 定时器分频配置2
 #define T3PSC1									  0x40							//				 rw-- 定时器分频配置1
 #define T3PSC0									  0x20							//				 rw-- 定时器分频配置0
 #define T3OCM									  0x10							//				 rw-- 定时器比较匹配/捕获脉宽模式配置
 #define T3IRE									  0x08							//				 rw-- 比较匹配/捕获脉宽中断
 #define T3OPM									  0x02							//				 rw-- 单次模式使能
 #define T3MOD									  0x01							//				 rw-- 定时器模式配置0

 //sfr	   TIM3_CR1						  =	0x9d;								  // RV:  00H  TIMER3控制寄存器1
 SFR(TIM3_CR1, 0x9d);
 #define T3IR									  0x80							//				 rw0- 比较匹配/捕获脉宽标志
 #define T3IP									  0x40							//				 rw0- 周期检测标志
 #define T3IF									  0x20							//				 rw0- 计数上溢标志
 #define T3IPE									  0x10							//				 rw-- 周期检测中断使能
 #define T3IFE									  0x08							//				 rw-- 上溢中断使能
 #define T3NM1									  0x04							//				 rw-- 噪音滤波配置1
 #define T3NM0									  0x02							//				 rw-- 噪音滤波配置0
 #define T3EN									  0x01							//				 rw-- 定时器使能

 //sfr16   TIM3__DR						  =	0xa4;								  // RV:0000H  TIMER3匹配值
 //sfr16   TIM3__ARR					  =	0xa6;								  // RV:0000H  TIMER3重载值
 //sfr16   TIM3__CNTR					  =	0xa2;								  // RV:0000H  TIMER3计数值
 SFR16(TIM3__DR,   0xa4);
 SFR16(TIM3__ARR,  0xa6);
 SFR16(TIM3__CNTR, 0xa2);
/******************************************************************************///TIM4
 //sfr	   TIM4_CR0						  =	0x9e;								  // RV:  00H  TIMER4控制寄存器0
 SFR(TIM4_CR0, 0x9e);	
 #define T4PSC2									  0x80							//				 rw-- 定时器分频配置2
 #define T4PSC1									  0x40							//				 rw-- 定时器分频配置1
 #define T4PSC0									  0x20							//				 rw-- 定时器分频配置0
 #define T4OCM									  0x10							//				 rw-- 定时器比较匹配/捕获脉宽模式配置
 #define T4IRE									  0x08							//				 rw-- 比较匹配/捕获脉宽中断
 #define T4OPM									  0x02							//				 rw-- 单次模式使能
 #define T4MOD									  0x01							//				 rw-- 定时器模式配置0

 //sfr	   TIM4_CR1						  =	0x9f;								  // RV:  00H  TIMER4控制寄存器1
 SFR(TIM4_CR1, 0x9f);
 #define T4IR									  0x80							//				 rw0- 比较匹配/捕获脉宽标志
 #define T4IP									  0x40							//				 rw0- 周期检测标志
 #define T4IF									  0x20							//				 rw0- 计数上溢标志
 #define T4IPE									  0x10							//				 rw-- 周期检测中断使能
 #define T4IFE									  0x08							//				 rw-- 上溢中断使能
 #define T4NM1									  0x04							//				 rw-- 噪音滤波配置1
 #define T4NM0									  0x02							//				 rw-- 噪音滤波配置0
 #define T4EN									  0x01							//				 rw-- 定时器使能

 //sfr16   TIM4__DR						  =	0x94;								  // RV:0000H  TIMER4匹配值
 //sfr16   TIM4__ARR					  =	0x96;								  // RV:0000H  TIMER4重载值
 //sfr16   TIM4__CNTR					  =	0x92;								  // RV:0000H  TIMER4计数值
 SFR16(TIM4__DR,   0x94);
 SFR16(TIM4__ARR,  0x96);
 SFR16(TIM4__CNTR, 0x92);
/******************************************************************************///SYSTICK
 #define SYST_ARR						*(_IO uint16 xdata *)0x4064			   // RV:5dbfH	SysTick重载值
/******************************************************************************///DRV
 //sfr	   DRV_OUT						  =	0xf8;								  // RV:  00H  驱动输出控制寄存器
// sbit	   MOE										= DRV_OUT^7;				  //			   rw--	主输出使能
// sbit	   OISWL									= DRV_OUT^5;				  //			   rw--	WL & XL输出空闲电平
// sbit	   OISWH									= DRV_OUT^4;				  //			   rw--	WH & XH输出空闲电平
// sbit	   OISVL									= DRV_OUT^3;				  //			   rw--	VL输出空闲电平
// sbit	   OISVH									= DRV_OUT^2;				  //			   rw--	VH输出空闲电平
// sbit	   OISUL									= DRV_OUT^1;				  //			   rw--	UL输出空闲电平
// sbit	   OISUH									= DRV_OUT^0;				  //			   rw--	UH输出空闲电平
SFR(DRV_OUT, 0xf8);
	SBIT(MOE,	0xf8, 7);
	SBIT(OISWL,	0xf8, 5);
	SBIT(OISWH,	0xf8, 4);
	SBIT(OISVL,	0xf8, 3);
	SBIT(OISVH,	0xf8, 2);
	SBIT(OISUL,	0xf8, 1);
	SBIT(OISUH,	0xf8, 0);
 	
 #define DRV_DR							*(_IO uint16 xdata *)0x4058			   // RV:0000H	手动控制输出时设定的比较值
 #define DRV_COMR						*(_IO uint16 xdata *)0x405a			   // RV:0000H	计数器的比较匹配值

 #define DRV_CMR						*(_IO uint16 xdata *)0x405c			   // RV:0000H	输出配置寄存器
 #define WHP									  0x0800						//				 rw-- W相上管输出极性
 #define WLP									  0x0400						//				 rw-- W相下管输出极性
 #define VHP									  0x0200						//				 rw-- V相上管输出极性
 #define VLP									  0x0100						//				 rw-- V相下管输出极性
 #define UHP									  0x0080						//				 rw-- U相上管输出极性
 #define ULP									  0x0040						//				 rw-- U相下管输出极性
 #define WHE									  0x0020						//				 rw-- W相上管输出使能
 #define WLE									  0x0010						//				 rw-- W相下管输出使能
 #define VHE									  0x0008						//				 rw-- V相上管输出使能
 #define VLE									  0x0004						//				 rw-- V相下管输出使能
 #define UHE									  0x0002						//				 rw-- U相上管输出使能
 #define ULE									  0x0001						//				 rw-- U相下管输出使能

 #define DRV_ARR						*(_IO uint16 xdata *)0x405e			   // RV:0000H	计数器重载值
 #define DRV_DTR						*(_IO  uint8 xdata *)0x4060			   // RV:  00H	上下管死区时间
 #define DRV_CNTR						*(_IO uint16 xdata *)0x4067			   // RV:0000H	计数器值

 #define DRV_SR							*(_IO  uint8 xdata *)0x4061			   // RV:  00H	Driver状态寄存器
 #define SYSTIF									  0x80							//				 rw0- SysTick中断标志
 #define SYSTIE									  0x40							//				 rw-- SysTick中断使能
 #define FGIF									  0x20							//				 rw0- FG中断标志
 #define DCIF									  0x10							//				 rw0- 比较匹配中断标志
 #define FGIE									  0x08							//				 rw-- FG中断使能
 #define DCIP									  0x04							//				 rw-- 产生比较匹配中断的间隔
 #define DCIM1									  0x02							//				 rw-- 比较匹配中断模式配置1
 #define DCIM0									  0x01							//				 rw-- 比较匹配中断模式配置0

 #define DRV_CR							*(_IO  uint8 xdata *)0x4062			   // RV:  00H	Driver控制寄存器
 #define DRVEN									  0x80							//				 rw-- 计数器使能
 #define DDIR									  0x40							//				 rw-- 输出方向
 #define FOCEN									  0x20							//				 rw-- FOC/SVPWM/SPWM模块使能
 #define DRPE									  0x10							//				 rw-- DRV_DR预装载使能
 #define OCS									  0x08							//				 rw-- 比较值来源选择
 #define MESEL									  0x04							//				 rw-- ME核工作模式选择
 #define DRVOE									  0x01							//				 rw-- Driver输出使能
/******************************************************************************///WDT
#define	CCFG1							*(_O   uint8 xdata *)0x401E				  // RV:  00H  
 #define	LVWIE								  0x40							//				 rw-- LVW(low voltage warning) detect interrupt enable
#define	WDT_EN									  0x20							//				 rw-- WDT使能
 
 #define WDT_CR							*(_IO  uint8 xdata *)0x4026			   // RV:  00H	看门狗控制寄存器
 #define WDTF									  0x02							//				 rw0- 看门狗复位标志
 #define WDTRF									  0x01							//				 rw-- 看门狗初始化标志

 #define WDT_ARR						*(_IO  uint8 xdata *)0x4027			   // RV:  00H	看门狗重载计数器
/******************************************************************************///GPIO
// sfr	   P0							  =	0x80;								  // RV:  00H  Port	0
// sbit	   GP00										= P0^0;
// sbit	   GP01										= P0^1;
// sbit	   GP02										= P0^2;
// sbit	   GP03										= P0^3;
// sbit	   GP04										= P0^4;
// sbit	   GP05										= P0^5;
// sbit	   GP06										= P0^6;
// sbit	   GP07										= P0^7;
 SFR(P0, 0x80);
 	SBIT(GP00, 0x80, 0);
 	SBIT(GP01, 0x80, 1);
 	SBIT(GP02, 0x80, 2);
 	SBIT(GP03, 0x80, 3);
 	SBIT(GP04, 0x80, 4);
 	SBIT(GP05, 0x80, 5);
 	SBIT(GP06, 0x80, 6);
 	SBIT(GP07, 0x80, 7);
 
// sfr	   P1							  =	0x90;								  // RV:  00H  Port	1
// sbit	   GP10										= P1^0;
// sbit	   GP11										= P1^1;
// sbit	   GP12										= P1^2;
// sbit	   GP13										= P1^3;
// sbit	   GP14										= P1^4;
// sbit	   GP15										= P1^5;
// sbit	   GP16										= P1^6;
// sbit	   GP17										= P1^7;
  SFR(P1, 0x90);
 	SBIT(GP10, 0x90, 0);
 	SBIT(GP11, 0x90, 1);
 	SBIT(GP12, 0x90, 2);
 	SBIT(GP13, 0x90, 3);
 	SBIT(GP14, 0x90, 4);
 	SBIT(GP15, 0x90, 5);
 	SBIT(GP16, 0x90, 6);
 	SBIT(GP17, 0x90, 7);
 	
// sfr	   P2							  =	0xa0;								  // RV:  00H  Port	2
// sbit	   GP20										= P2^0;
// sbit	   GP21										= P2^1;
// sbit	   GP22										= P2^2;
// sbit	   GP23										= P2^3;
// sbit	   GP24										= P2^4;
// sbit	   GP25										= P2^5;
// sbit	   GP26										= P2^6;
// sbit	   GP27										= P2^7;
 SFR(P2, 0xa0);
 	SBIT(GP20, 0xa0, 0);
 	SBIT(GP21, 0xa0, 1);
 	SBIT(GP22, 0xa0, 2);
 	SBIT(GP23, 0xa0, 3);
 	SBIT(GP24, 0xa0, 4);
 	SBIT(GP25, 0xa0, 5);
 	SBIT(GP26, 0xa0, 6);
 	SBIT(GP27, 0xa0, 7);
 	
// sfr	   P3							  =	0xb0;								  // RV:  00H  Port	3
// sbit	   GP30										= P3^0;
// sbit	   GP31										= P3^1;
// sbit	   GP32										= P3^2;
// sbit	   GP33										= P3^3;
// sbit	   GP34										= P3^4;
// sbit	   GP35										= P3^5;
// sbit	   GP36										= P3^6;
// sbit	   GP37										= P3^7;
 SFR(P3, 0xb0);
 	SBIT(GP30, 0xb0, 0);
 	SBIT(GP31, 0xb0, 1);
 	SBIT(GP32, 0xb0, 2);
 	SBIT(GP33, 0xb0, 3);
 	SBIT(GP34, 0xb0, 4);
 	SBIT(GP35, 0xb0, 5);
 	SBIT(GP36, 0xb0, 6);
 	SBIT(GP37, 0xb0, 7);
 	
// sfr	   P4							  =	0xe8;								  // RV:  00H  Port	4
// sbit	   GP42										= P4^2;
// sbit	   GP43										= P4^3;
// sbit	   GP44										= P4^4;
// sbit	   GP45										= P4^5;
 SFR(P4, 0xe8);
 	//SBIT(GP00, P0, 0);
 	//SBIT(GP01, P0, 1);
 	SBIT(GP42, 0xe8, 2);
 	SBIT(GP43, 0xe8, 3);
 	SBIT(GP44, 0xe8, 4);
 	SBIT(GP45, 0xe8, 5);
 	//SBIT(GP06, P0, 6);
 	//SBIT(GP07, P0, 7);
 	
 //sfr	   P0_OE						  =	0xfc;								  // RV:  00H  P0输出使能寄存器
 SFR(P0_OE,	0xfc);
 #define P0_PU							*(_IO  uint8 xdata *)0x4053			   // RV:  00H	P0上拉使能寄存器
 #define P07									  0x80							//				 rw-- 使能端口7
 #define P06									  0x40							//				 rw-- 使能端口6
 #define P05									  0x20							//				 rw-- 使能端口5
 #define P04									  0x10							//				 rw-- 使能端口4
 #define P03									  0x08							//				 rw-- 使能端口3
 #define P02									  0x04							//				 rw-- 使能端口2
 #define P01									  0x02							//				 rw-- 使能端口1
 #define P00									  0x01							//				 rw-- 使能端口0

// sfr	   P1_IE						  =	0xd1;								  // RV:  00H  P1外部中断使能寄存器
// sfr	   P1_IF						  =	0xd2;								  // RV:  00H  P1外部中断状态寄存器
// sfr	   P1_OE						  =	0xfd;								  // RV:  00H  P1输出使能寄存器
 SFR(P1_IE,	0xd1);
 SFR(P1_IF,	0xd2);
 SFR(P1_OE,	0xfd);
 #define P1_PU							*(_IO  uint8 xdata *)0x4054			   // RV:  00H	P1上拉使能寄存器
 #define P17									  0x80							//				 rw-- 使能端口7
 #define P16									  0x40							//				 rw-- 使能端口6
 #define P15									  0x20							//				 rw-- 使能端口5
 #define P14									  0x10							//				 rw-- 使能端口4
 #define P13									  0x08							//				 rw-- 使能端口3
 #define P12									  0x04							//				 rw-- 使能端口2
 #define P11									  0x02							//				 rw-- 使能端口1
 #define P10									  0x01							//				 rw-- 使能端口0

 #define P1_AN							*(_IO  uint8 xdata *)0x4050			   // RV:  00H	P1模拟使能寄存器
 #define P17									  0x80							//				 rw-- 使能端口7
 #define P16									  0x40							//				 rw-- 使能端口6
 #define P15									  0x20							//				 rw-- 使能端口5
 #define P14									  0x10							//				 rw-- 使能端口4
 #define HBMOD									  0x08							//				 rw-- 端口3模式配置
 #define ODE1									  0x02							//				 rw-- P01漏极开路使能
 #define ODE0									  0x01							//				 rw-- P00漏极开路使能

// sfr	   P2_IE						  =	0xd3;								  // RV:  00H  P2外部中断使能寄存器
// sfr	   P2_IF						  =	0xd4;								  // RV:  00H  P2外部中断状态寄存器
// sfr	   P2_OE						  =	0xfe;								  // RV:  00H  P2输出使能寄存器
 SFR(P2_IE,	0xd3);
 SFR(P2_IF,	0xd4);
 SFR(P2_OE,	0xfe);
 #define P2_PU							*(_IO  uint8 xdata *)0x4055			   // RV:  00H	P2上拉使能寄存器
 #define P2_AN							*(_IO  uint8 xdata *)0x4051			   // RV:  00H	P2模拟使能寄存器
 #define P27									  0x80							//				 rw-- 使能端口7
 #define P26									  0x40							//				 rw-- 使能端口6
 #define P25									  0x20							//				 rw-- 使能端口5
 #define P24									  0x10							//				 rw-- 使能端口4
 #define P23									  0x08							//				 rw-- 使能端口3
 #define P22									  0x04							//				 rw-- 使能端口2
 #define P21									  0x02							//				 rw-- 使能端口1
 #define P20									  0x01							//				 rw-- 使能端口0

 //sfr	   P3_OE						  =	0xff;								  // RV:  00H  P3输出使能寄存器
 SFR(P3_OE,	0xff);
 #define P3_PU							*(_IO  uint8 xdata *)0x4056			   // RV:  00H	P3上拉使能寄存器
 #define P37									  0x80							//				 rw-- 使能端口7
 #define P36									  0x40							//				 rw-- 使能端口6
 #define P35									  0x20							//				 rw-- 使能端口5
 #define P34									  0x10							//				 rw-- 使能端口4
 #define P33									  0x08							//				 rw-- 使能端口3
 #define P32									  0x04							//				 rw-- 使能端口2
 #define P31									  0x02							//				 rw-- 使能端口1
 #define P30									  0x01							//				 rw-- 使能端口0

 #define P3_AN							*(_IO  uint8 xdata *)0x4052			   // RV:  00H	P3模拟使能寄存器
 #define P11_PL									  0x80							//				 rw-- P11下拉使能
 #define P01_PL									  0x40							//				 rw-- P01下拉使能
 #define P35									  0x20							//				 rw-- 使能端口5
 #define P34									  0x10							//				 rw-- 使能端口4
 #define P33									  0x08							//				 rw-- 使能端口3
 #define P32									  0x04							//				 rw-- 使能端口2
 #define P31									  0x02							//				 rw-- 使能端口1
 #define P30									  0x01							//				 rw-- 使能端口0

 //sfr	   P4_OE						  =	0xe9;								  // RV:  00H  P4输出使能寄存器
 SFR(P4_OE,	0xe9);
 #define P4_PU							*(_IO  uint8 xdata *)0x4057			   // RV:  00H	P4上拉使能寄存器
 #define P45									  0x20							//				 rw-- 使能端口5
 #define P44									  0x10							//				 rw-- 使能端口4
 #define P43									  0x08							//				 rw-- 使能端口3
 #define P42									  0x04							//				 rw-- 使能端口2

 #define PIN7									  0x80							//				 rw-- PIN7,	用于替代上面的端口编号
 #define PIN6									  0x40							//				 rw-- PIN6,	用于替代上面的端口编号
 #define PIN5									  0x20							//				 rw-- PIN5,	用于替代上面的端口编号
 #define PIN4									  0x10							//				 rw-- PIN4,	用于替代上面的端口编号
 #define PIN3									  0x08							//				 rw-- PIN3,	用于替代上面的端口编号
 #define PIN2									  0x04							//				 rw-- PIN2,	用于替代上面的端口编号
 #define PIN1									  0x02							//				 rw-- PIN1,	用于替代上面的端口编号
 #define PIN0									  0x01							//				 rw-- PIN0,	用于替代上面的端口编号

 #define PH_SEL							*(_IO  uint8 xdata *)0x404c			   // RV:  00H	端口复用
 #define SPITMOD								  0x80							//				 rw-- SPI从机发送端在发送完成后变为高阻态
 #define UART1EN								  0x40							//				 rw-- 端口复用为UART
 #define UART2EN								  0x20							//				 rw-- UART端口功能转移
 #define T4SEL									  0x10							//				 rw-- 端口复用为TIM4
 #define T3SEL									  0x08							//				 rw-- 端口复用为TIM3
 #define T2SEL									  0x04							//				 rw-- 端口复用为TIM2
 #define T2SSEL									  0x02							//				 rw-- 端口复用为TIM2S
 #define XOE									  0x01							//				 rw-- 端口复用为X相驱动端

 #define PH_SEL1						*(_IO  uint8 xdata *)0x404d			   // RV:  00H	端口复用
 #define SPICT									  0x04							//				 rw-- SPI功能转移
 #define T4CT									  0x02							//				 rw-- TIM4功能转移
 #define T3CT									  0x01							//				 rw-- TIM3功能转移

/******************************************************************************///ADC
 #define ADC_MASK						*(_IO uint16 xdata *)0x4036			   // RV:3000H	ADC通道使能和部分通道采样时间配置
 #define CH14EN									  0x4000						//				 rw-- ADC通道14使能
 #define CH13EN									  0x2000						//				 rw-- ADC通道13使能
 #define CH12EN									  0x1000						//				 rw-- ADC通道12使能
 #define CH11EN									  0x0800						//				 rw-- ADC通道11使能
 #define CH10EN									  0x0400						//				 rw-- ADC通道10使能
 #define CH9EN									  0x0200						//				 rw-- ADC通道9使能
 #define CH8EN									  0x0100						//				 rw-- ADC通道8使能
 #define CH7EN									  0x0080						//				 rw-- ADC通道7使能
 #define CH6EN									  0x0040						//				 rw-- ADC通道6使能
 #define CH5EN									  0x0020						//				 rw-- ADC通道5使能
 #define CH4EN									  0x0010						//				 rw-- ADC通道4使能
 #define CH3EN									  0x0008						//				 rw-- ADC通道3使能
 #define CH2EN									  0x0004						//				 rw-- ADC通道2使能
 #define CH1EN									  0x0002						//				 rw-- ADC通道1使能
 #define CH0EN									  0x0001						//				 rw-- ADC通道0使能

 #define ADC_SYSC						*(_IO  uint8 xdata *)0x4038			   // RV:  33H	ADC通道采样时间配置

 #define ADC_CR							*(_IO  uint8 xdata *)0x4039			   // RV:  00H	ADC控制寄存器
 #define ADCEN									  0x80							//				 rw-- 使能ADC
 #define ADCBSY									  0x40							//				 rw1- ADC启动 &	ADC忙标志
 #define ADCRATIO								  0x20							//				 rw-- AD14采VCC电压使用的分压比
 #define ADCTM1									  0x10							//				 rw-- DRV触发ADC启动模式
 #define ADCTM0									  0x08							//				 rw-- 00不触发01上升沿10下降沿11双沿
 #define ADCALIGN								  0x04							//				 rw-- ADC数据次高位对齐
 #define ADCIE									  0x02							//				 rw-- ADC中断使能
 #define ADCIF									  0x01							//				 rw-- ADC中断标志

 #define ADC0_DR						*(_I  uint16 xdata *)0x0300			   // RV:0000H	ADC通道0转换结果
 #define ADC1_DR						*(_I  uint16 xdata *)0x0302			   // RV:0000H	ADC通道1转换结果
 #define ADC2_DR						*(_I  uint16 xdata *)0x0304			   // RV:0000H	ADC通道2转换结果
 #define ADC3_DR						*(_I  uint16 xdata *)0x0306			   // RV:0000H	ADC通道3转换结果
 #define ADC4_DR						*(_I  uint16 xdata *)0x0308			   // RV:0000H	ADC通道4转换结果
 #define ADC5_DR						*(_I  uint16 xdata *)0x030a			   // RV:0000H	ADC通道5转换结果
 #define ADC6_DR						*(_I  uint16 xdata *)0x030c			   // RV:0000H	ADC通道6转换结果
 #define ADC7_DR						*(_I  uint16 xdata *)0x030e			   // RV:0000H	ADC通道7转换结果
 #define ADC8_DR						*(_I  uint16 xdata *)0x0310			   // RV:0000H	ADC通道8转换结果
 #define ADC9_DR						*(_I  uint16 xdata *)0x0312			   // RV:0000H	ADC通道9转换结果
 #define ADC10_DR						*(_I  uint16 xdata *)0x0314			   // RV:0000H	ADC通道10转换结果
 #define ADC11_DR						*(_I  uint16 xdata *)0x0316			   // RV:0000H	ADC通道11转换结果
 #define ADC12_DR						*(_I  uint16 xdata *)0x0318			   // RV:0000H	ADC通道12转换结果
 #define ADC13_DR						*(_I  uint16 xdata *)0x031a			   // RV:0000H	ADC通道13转换结果
 #define ADC14_DR						*(_I  uint16 xdata *)0x031c			   // RV:0000H	ADC通道14转换结果
/*****************************************************************************///DAC
 #define DAC_CR							*(_IO  uint8 xdata *)0x4035			   // RV:  00H	DAC控制寄存器
 #define DAC0_1EN								  0x80							//				 rw-- DAC0&1使能
 #define DACMOD									  0x40							//				 rw-- DAC模式配置
 #define ADC_SYSCH3								  0x20							// ADC_SYSCH[3:0]
 #define ADC_SYSCH2								  0x10							// CH8/9/10/11/12/13采样时间配置
 #define ADC_SYSCH1								  0x08							//
 #define ADC_SYSCH0								  0x04							//

 #define DAC0_DR						 *(_IO	uint8 xdata *)0x404b				// RV:	00H	 DAC0输出值[8:1]
 #define DAC1_DR						 *(_IO	uint8 xdata *)0x404A				// RV:	00H	 DAC1输出值
 #define DAC0_DR_0								  0x80							 //	RV:	 00H  DAC0输出值[0]

/******************************************************************************///DMA
 #define DMA0_CR0						*(_IO  uint8 xdata *)0x403a			   // RV:  00H	DMA通道0配置 & DMA公共配置
 #define DMA1_CR0						*(_IO  uint8 xdata *)0x403b			   // RV:  00H	DMA通道1配置 & Debug设置
 #define DMAEN									  0x80							//				 rw-- DMA通道0/1使能
 #define DMABSY									  0x40							//				 rw1- DMA通道0/1状态/启动
 #define DMACFG2								  0x20							//				 rw-- DMA通道0/1外设与方向选择位2
 #define DMACFG1								  0x10							//				 rw-- DMA通道0/1外设与方向选择位1
 #define DMACFG0								  0x08							//				 rw-- DMA通道0/1外设与方向选择位0
 #define DBGSW									  0x04							//				 rw-- DMA通道1	DBG模式指向区域
 #define DBGEN									  0x02							//				 rw-- DMA通道1	DBG模式使能
 #define DMAIE									  0x04							//				 rw-- DMA中断使能,位于DMA_CR0
 #define ENDIAN									  0x02							//				 rw-- DMA数据传输顺序,位于DMA_CR0
 #define DMAIF									  0x01							//				 rw0- DMA通道0/1中断标志位

 #define DMA0_LEN						*(_IO  uint8 xdata *)0x403c			   // RV:  00H	DMA通道0传输长度配置
 #define DMA1_LEN						*(_IO  uint8 xdata *)0x403d			   // RV:  00H	DMA通道1传输长度配置

 #define DMA0_BA						*(_IO uint16 xdata *)0x403e			   // RV:0000H	DMA通道0传输地址配置
 #define DMA1_BA						*(_IO uint16 xdata *)0x4040			   // RV:0000H	DMA通道1传输地址配置
/******************************************************************************///VREF & VHALF
 #define VREF_VHALF_CR					*(_IO  uint8 xdata *)0x404f			   // RV:  00H	VREF & VHALF控制寄存器
 #define VRVSEL1								  0x80							//				 rw-- VREF电压配置1
 #define VRVSEL0								  0x40							//				 rw-- VREF电压配置0
 #define VREFEN									  0x10							//				 rw-- VREF使能
 #define VHALFEN								  0x01							//				 rw-- VHALF使能
/******************************************************************************///AMP
 #define AMP0_GAIN						*(_IO  uint8 xdata *)0x4034			   // RV:  00H	AMP0 PGA SET
 #define AMP0_GAIN2								  0x04							//				 rw-- AMP0放大倍数
 #define AMP0_GAIN1								  0x02							//				 rw-- AMP0放大倍数
 #define AMP0_GAIN0								  0x01							//				 rw-- AMP0放大倍数
 
 #define AMP_CR							*(_IO  uint8 xdata *)0x404e			   // RV:  00H	运放控制寄存器
 #define AMP2EN									  0x04							//				 rw-- 运放2使能
 #define AMP1EN									  0x02							//				 rw-- 运放1使能
 #define AMP0EN									  0x01							//				 rw-- 运放0使能
/******************************************************************************///CMP
 //sfr	   CMP_CR0						  =	0xd5;								  // RV:  00H  比较器控制寄存器0
 SFR(CMP_CR0, 0xd5);
 #define CMP3IM1								  0x80							//				 rw-- CMP3中断模式配置1
 #define CMP3IM0								  0x40							//				 rw-- CMP3中断模式配置0
 #define CMP2IM1								  0x20							//				 rw-- CMP2中断模式配置1
 #define CMP2IM0								  0x10							//				 rw-- CMP2中断模式配置0
 #define CMP1IM1								  0x08							//				 rw-- CMP1中断模式配置1
 #define CMP1IM0								  0x04							//				 rw-- CMP1中断模式配置0
 #define CMP0IM1								  0x02							//				 rw-- CMP0中断模式配置1
 #define CMP0IM0								  0x01							//				 rw-- CMP0中断模式配置0

 //sfr	   CMP_CR1						  =	0xd6;								  // RV:  00H  比较器控制寄存器1
 SFR(CMP_CR1, 0xd6);
 #define HALLSEL								  0x80							//				 rw-- 霍尔信号输入选择
 #define CMP3MOD1								  0x40							//				 rw-- CMP3正输入端选择配置1
 #define CMP3MOD0								  0x20							//				 rw-- CMP3正输入端选择配置0
 #define CMP3EN									  0x10							//				 rw-- CMP3使能
 #define CMP3HYS								  0x08							//				 rw-- CMP3迟滞使能
 #define CMP0HYS2								  0x04							//				 rw-- CMP0迟滞电压配置2
 #define CMP0HYS1								  0x02							//				 rw-- CMP0迟滞电压配置1
 #define CMP0HYS0								  0x01							//				 rw-- CMP0迟滞电压配置0

 //sfr	   CMP_CR2						  =	0xda;								  // RV:  00H  比较器控制寄存器2
 SFR(CMP_CR2, 0xda);
 #define CMP4EN									  0x80							//				 rw-- CMP4使能
 #define CMP0MOD1								  0x40							//				 rw-- CMP0模式配置1
 #define CMP0MOD0								  0x20							//				 rw-- CMP0模式配置0
 #define CMP0SEL1								  0x10							//				 rw-- CMP0端口组合配置1
 #define CMP0SEL0								  0x08							//				 rw-- CMP0端口组合配置0
 #define CMP0CSEL1								  0x04							//				 rw-- CMP0轮询速度配置1
 #define CMP0CSEL0								  0x02							//				 rw-- CMP0轮询速度配置0
 #define CMP0EN									  0x01							//				 rw-- CMP0使能

 //sfr	   CMP_CR3						  =	0xdc;								  // RV:  00H  比较器控制寄存器3
 SFR(CMP_CR3, 0xdc);
 #define CMPDTEN								  0x80							//				 rw-- 比较器死区采样使能
 #define DBGSEL1								  0x40							//				 rw-- DBG信号配置1
 #define DBGSEL0								  0x20							//				 rw-- DBG信号配置0
 #define SAMSEL1								  0x10							//				 rw-- CMP0/1/2 & ADC 采样时机配置1
 #define SAMSEL0								  0x08							//				 rw-- CMP0/1/2 & ADC 采样时机配置0
 #define CMPSEL2								  0x04							//				 rw-- 比较器输出选择配置2
 #define CMPSEL1								  0x02							//				 rw-- 比较器输出选择配置1
 #define CMPSEL0								  0x01							//				 rw-- 比较器输出选择配置0

 //sfr	   CMP_CR4						  =	0xe1;								  // RV:  00H  比较器控制寄存器4
 SFR(CMP_CR4, 0xe1);
 #define CMP4OUT								  0x80							//				 rw-- CMP5比较结果
 #define FAEN									  0x04							//				 rw-- 滤波采样系数扩大使能
 #define CMP0_FS								  0x02							//				 rw-- CMP1/2功能转移使能

 //sfr	   CMP_SR						  =	0xd7;								  // RV:  00H  比较器状态寄存器
 SFR(CMP_SR, 0xd7);
 #define CMP3IF									  0x80							//				 rw0- CMP3中断标志
 #define CMP2IF									  0x40							//				 rw0- CMP2中断标志
 #define CMP1IF									  0x20							//				 rw0- CMP1中断标志
 #define CMP0IF									  0x10							//				 rw0- CMP0中断标志
 #define CMP3OUT								  0x08							//				 r--- CMP3比较结果
 #define CMP2OUT								  0x04							//				 r--- CMP2比较结果
 #define CMP1OUT								  0x02							//				 r--- CMP1比较结果
 #define CMP0OUT								  0x01							//				 r--- CMP0比较结果

 //sfr	   EVT_FILT						  =	0xd9;								  // RV:  00H  驱动保护功能
 SFR(EVT_FILT, 0xd9);
 #define MOEMD1									  0x10							//				 rw-- MOE自动控制配置1
 #define MOEMD0									  0x08							//				 rw-- MOE自动控制配置0
 #define EFSRC									  0x04							//				 rw-- 母线保护滤波模块输入来源
 #define EFDIV1									  0x02							//				 rw-- 母线电流保护滤波配置1
 #define EFDIV0									  0x01							//				 rw-- 母线电流保护滤波配置0

 #define CMP_SAMR						*(_IO  uint8 xdata *)0x40ad			   // RV:  00H	比较器采样配置
/******************************************************************************///FLASH
 //sfr	   FLA_KEY						  =	0x84;								  // RV:  00H  FLASH解锁寄存器
 SFR(FLA_KEY, 0x84);
 #define FLAKSTA1								  0x02							//				 rw-- FLASH解锁状态位1
 #define FLAKSTA0								  0x01							//				 rw-- FLASH解锁状态位0

 //sfr	   FLA_CR						  =	0x85;								  // RV:  00H  FLASH控制寄存器
 SFR(FLA_CR, 0x85);
 #define FLAERR									  0x10							//				 r--- FLASH错误标志位
 #define FLAACT									  0x08							//				 rw1- FLASH操作开始
 #define FLAPRE									  0x04							//				 rw-- FLASH预编程使能
 #define FLAERS									  0x02							//				 rw-- FLASH清除使能
 #define FLAEN									  0x01							//				 rw-- FLASH编程使能
/******************************************************************************///CRC
 #define CRC_DIN						*(_O   uint8 xdata *)0x4021			   // RV:  00H	CRC数据输入寄存器

 #define CRC_CR							*(_IO  uint8 xdata *)0x4022			   // RV:	0H	CRC控制寄存器
 #define CRCDONE								  0x10							//				 r1-- 自动CRC完成标志
 #define CRCDINI								  0x08							//				 r0w1 CRC初始化
 #define CRCVAL									  0x04							//				 rw-- CRC初始化的值
 #define AUTOINT								  0x02							//				 rw-- CRC自动计算使能
 #define CRCPNT									  0x01							//				 rw-- CRC结果访问位置

 #define CRC_DR							*(_IO  uint8 xdata *)0x4023			   // RV:  00H	CRC结果输出寄存器
 #define CRC_BEG						*(_IO  uint8 xdata *)0x4024			   // RV:  00H	CRC自动计算的起始位置
 #define CRC_CNT						*(_IO  uint8 xdata *)0x4025			   // RV:  00H	CRC块数计数器
/******************************************************************************///TSD
 #define TSD_CR							*(_IO  uint8 xdata *)0x402f			   // RV:	0H	TSD控制寄存器
 #define TSDEN									  0x80							//				 rw-- TSD使能
 #define TSDADJ3								  0x08							//				 rw-- TSD温度调节
 #define TSDADJ2								  0x04							//				 rw-- TSD温度调节
 #define TSDADJ1								  0x02							//				 rw-- TSD温度调节
 #define TSDADJ0								  0x01							//				 rw-- TSD温度调节
/******************************************************************************///POWER
 //sfr	   PCON							  =	0x87;								  // RV:  00H  MCU功率控制寄存器
 SFR(PCON, 0x87);
 #define GF3									  0x20							//				 rw-- 通用标志3
 #define GF2									  0x10							//				 rw-- 通用标志2
 #define GF1									  0x08							//				 rw-- 通用标志1
 #define LDOM									  0x04							//				 rw-- LDO5功耗模式选择
 #define STOP									  0x02							//				 rw-- MCU睡眠使能
 #define IDLE									  0x01							//				 rw-- MCU待机使能

 //sfr	   LVSR							  =	0xdb;								  // RV:  00H  状态寄存器
 SFR(LVSR, 0xdb);
 #define EXT0CFG2								  0x20							//				 rw-- 外部中断0端口配置2
 #define EXT0CFG1								  0x10							//				 rw-- 外部中断0端口配置1
 #define EXT0CFG0								  0x08							//				 rw-- 外部中断0端口配置0
 #define TSDF									  0x04							//				 rw-- 过温标志位
 #define LVWF									  0x02							//				 rw-- VCC低电压标志
 #define LVWIF									  0x01							//				 rw-- VCC低电压中断标志


#ifdef __cplusplus
}
#endif

#endif	//__FU68XX_4_MCU_H__


/*** (C) Copyright 2022	Fortior	Technology Co.,	Ltd. ***/
