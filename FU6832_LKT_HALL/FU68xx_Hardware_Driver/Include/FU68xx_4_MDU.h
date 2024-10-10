/**
 * @file	 FU68xx_4_MDU.h
 * @version	 V1.0.0
 * @author	 FortiorTech Hardware Team
 * @date	 2021-07-15	22:24:27
 * @brief	 This file contains	...
 * 
 * @copyright Copyright(C) 2022, Fortior Technology	Co., Ltd. All rights reserved.
 */

#ifndef	__FU68XX_4_MDU_H__
#define	__FU68XX_4_MDU_H__

// Include external	header file.
#include "FU68xx_4_MCU.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 有符号乘法，结果左移一位
 *
 * @CodeLen	0x0033(Xdata) 0x0029(Idata)	0x0021(Data)
 * @RunTime	2.86us(Xdata) 1.96us(Idata)	1.46us(Data)
 * @Exp		C =	A *	B *	2
 *
 * @param	iA	 (int16)  被乘数
 * @param	iB	 (int16)  乘数
 * @param	iCh	 (int16)  积的高16位
 * @param	iCl	 (int16)  积的低16位
 */
#define	MuiltS1_MDU(iA,	iB,	iCh, iCl)						do { \
																MDU_CR = MDURUN;\
																MDU_MD = 0x00;\
																MDU_A  = iA;\
																MDU_C  = iB;\
																NOP();\
																iCh	   = MDU_A;\
																iCl	   = MDU_B;\
																MDU_CR = MDUDONE;\
															} while	(0)

/**
 * 有符号乘法，结果左移一位,只取高位
 *
 * @CodeLen	0x002a(Xdata) 0x0024(Idata)	0x001c(Data)
 * @RunTime	2.25us(Xdata) 1.71us(Idata)	1.21us(Data)
 * @Exp		C =	A *	B *	2
 *
 * @param	iA	 (int16)  被乘数
 * @param	iB	 (int16)  乘数
 * @param	iCh	 (int16)  积的高16位
 */
#define	MuiltS1_H_MDU(iA, iB, iCh)							do { \
																MDU_CR = MDURUN;\
																MDU_MD = 0x00;\
																MDU_A  = iA;\
																MDU_C  = iB;\
																NOP();\
																iCh	   = MDU_A;\
																MDU_CR = MDUDONE;\
															} while	(0)

/**
 * 有符号乘法，结果左移一位,只取低位
 *
 * @CodeLen	0x002a(Xdata) 0x0024(Idata)	0x001c(Data)
 * @RunTime	2.25us(Xdata) 1.71us(Idata)	1.21us(Data)
 * @Exp		C =	A *	B *	2
 *
 * @param	iA	 (int16)  被乘数
 * @param	iB	 (int16)  乘数
 * @param	iCl	 (int16)  积的低16位
 */
#define	MuiltS1_L_MDU(iA, iB, iCl)							do { \
																MDU_CR = MDURUN;\
																MDU_MD = 0x00;\
																MDU_A  = iA;\
																MDU_C  = iB;\
																NOP();\
																iCl	   = MDU_B;\
																MDU_CR = MDUDONE;\
															} while	(0)

/**
 * 有符号乘法
 *
 * @CodeLen	0x0033(Xdata) 0x0029(Idata)	0x0021(Data)
 * @RunTime	2.88us(Xdata) 1.96us(Idata)	1.46us(Data)
 * @Exp		C =	A *	B
 *
 * @param	iA	 (int16)  被乘数
 * @param	iB	 (int16)  乘数
 * @param	iCh	 (int16)  积的高16位
 * @param	iCl	 (int16)  积的低16位
 */
#define	MuiltS_MDU(iA, iB, iCh,	iCl)						do { \
																MDU_CR = MDURUN;\
																MDU_MD = MDUMOD0;\
																MDU_A  = iA;\
																MDU_C  = iB;\
																NOP();\
																iCh	   = MDU_A;\
																iCl	   = MDU_B;\
																MDU_CR = MDUDONE;\
															} while	(0)

/**
 * 有符号乘法,只取高位
 *
 * @CodeLen	0x002a(Xdata) 0x0024(Idata)	0x001c(Data)
 * @RunTime	2.30us(Xdata) 1.71us(Idata)	1.21us(Data)
 * @Exp		C =	A *	B
 *
 * @param	iA	 (int16)  被乘数
 * @param	iB	 (int16)  乘数
 * @param	iCh	 (int16)  积的高16位
 */
#define	MuiltS_H_MDU(iA, iB, iCh)							do { \
																MDU_CR = MDURUN;\
																MDU_MD = MDUMOD0;\
																MDU_A  = iA;\
																MDU_C  = iB;\
																NOP();\
																iCh	   = MDU_A;\
																MDU_CR = MDUDONE;\
															} while	(0)

/**
 * 有符号乘法,只取低位
 *
 * @CodeLen	0x002a(Xdata) 0x0024(Idata)	0x001c(Data)
 * @RunTime	2.30us(Xdata) 1.71us(Idata)	1.21us(Data)
 * @Exp		C =	A *	B
 *
 * @param	iA	 (int16)  被乘数
 * @param	iB	 (int16)  乘数
 * @param	iCl	 (int16)  积的低16位
 */
#define	MuiltS_L_MDU(iA, iB, iCl)							do { \
																MDU_CR = MDURUN;\
																MDU_MD = MDUMOD0;\
																MDU_A  = iA;\
																MDU_C  = iB;\
																NOP();\
																iCl	   = MDU_B;\
																MDU_CR = MDUDONE;\
															} while	(0)

/**
 * 无符号乘法
 *
 * @CodeLen	0x0033(Xdata) 0x0029(Idata)	0x0021(Data)
 * @RunTime	2.88us(Xdata) 1.96us(Idata)	1.46us(Data)
 * @Exp		C =	A *	B
 *
 * @param	wA	 (uint16)  被乘数
 * @param	wB	 (uint16)  乘数
 * @param	wCh	 (uint16)  积的高16位
 * @param	wCl	 (uint16)  积的低16位
 */
#define	Muilt_MDU(wA, wB, wCh, wCl)							do { \
																MDU_CR = MDURUN;\
																MDU_MD = MDUMOD1;\
																MDU_A  = wA;\
																MDU_C  = wB;\
																NOP();\
																wCh	   = MDU_A;\
																wCl	   = MDU_B;\
																MDU_CR = MDUDONE;\
															} while	(0)

/**
 * 无符号乘法,只取高位
 *
 * @CodeLen	0x002a(Xdata) 0x0024(Idata)	0x001c(Data)
 * @RunTime	2.30us(Xdata) 1.71us(Idata)	1.21us(Data)
 * @Exp		C =	A *	B
 *
 * @param	wA	 (uint16)  被乘数
 * @param	wB	 (uint16)  乘数
 * @param	wCh	 (uint16)  积的高16位
 */
#define	Muilt_H_MDU(wA,	wB,	wCh)							do { \
																MDU_CR = MDURUN;\
																MDU_MD = MDUMOD1;\
																MDU_A  = wA;\
																MDU_C  = wB;\
																NOP();\
																wCh	   = MDU_A;\
																MDU_CR = MDUDONE;\
															} while	(0)

/**
 * 无符号乘法,只取低位
 *
 * @CodeLen	0x002a(Xdata) 0x0024(Idata)	0x001c(Data)
 * @RunTime	2.30us(Xdata) 1.71us(Idata)	1.21us(Data)
 * @Exp		C =	A *	B
 *
 * @param	wA	 (uint16)  被乘数
 * @param	wB	 (uint16)  乘数
 * @param	wCl	 (uint16)  积的低16位
 */
#define	Muilt_L_MDU(wA,	wB,	wCl)							do { \
																MDU_CR = MDURUN;\
																MDU_MD = MDUMOD1;\
																MDU_A  = wA;\
																MDU_C  = wB;\
																NOP();\
																wCl	   = MDU_B;\
																MDU_CR = MDUDONE;\
															} while	(0)

/**
 * 低通滤波器
 *
 * @CodeLen	0x0049(Xdata) 0x003d(Idata)	0x002f(Data)
 * @RunTime	4.21us(Xdata) 2.88us(Idata)	2.29us(Data)
 * @Exp		Y += K * (X	- Y)
 *
 * @param	iYh	 (int16)  滤波输出的高16位(填入上一次计算的输出，取出新的输出)
 * @param	iYl	 (int16)  滤波输出的低16位(填入上一次计算的输出，取出新的输出)
 * @param	iX	 (int16)  滤波输入
 * @param	ucK	 (uint8)  滤波系数(Q8格式：0~255)
 */
#define	LPF_MDU(iX,	ucK, iYh, iYl)							do { \
																MDU_CR = MDURUN;\
																MDU_MD = MDUMOD2 | MDUMOD1;\
																MDU_D  = ucK;\
																MDU_A  = iX;\
																MDU_B  = iYh;\
																MDU_C  = iYl;\
																while (MDU_CR &	MDUBUSY);\
																iYh	   = MDU_B;\
																iYl	   = MDU_C;\
																MDU_CR = MDUDONE;\
															} while	(0)

/**
 * 32Bit/16Bit除法----求商
 *
 * @CodeLen	0x0043(Xdata) 0x003a(Idata)	0x002c(Data)
 * @RunTime	4.46us(Xdata) 3.50us(Idata)	2.67us(Data)
 * @Exp		C =	A /	B
 *
 * @param	wAh	 (uint16)  被除数的高16位
 * @param	wAl	 (uint16)  被除数的低16位
 * @param	wB	 (uint16)  除数
 * @param	wCh	 (uint16)  商的高16位
 * @param	wCl	 (uint16)  商的低16位
 */
#define	DivQ_MDU(wAh, wAl, wB, wCh,	wCl)					do {\
																MDU_CR = MDURUN;\
																MDU_MD = MDUMOD1 | MDUMOD0;\
																MDU_A  = wAh;\
																MDU_B  = wAl;\
																MDU_C  = wB;\
																while (MDU_CR &	MDUBUSY);\
																wCh	   = MDU_A;\
																wCl	   = MDU_B;\
																MDU_CR = MDUDONE;\
															} while	(0)

/**
 * 32Bit/16Bit除法----求商,只取高位
 *
 * @CodeLen	0(Xdata) 0(Idata) 0(Data)
 * @RunTime	0(Xdata) 0(Idata) 0(Data)
 * @Exp		C =	A /	B
 *
 * @param	wAh	 (uint16)  被除数的高16位
 * @param	wAl	 (uint16)  被除数的低16位
 * @param	wB	 (uint16)  除数
 * @param	wCh	 (uint16)  商的高16位
 */
#define	DivQ_H_MDU(wAh,	wAl, wB, wCh)						do {\
																MDU_CR = MDURUN;\
																MDU_MD = MDUMOD1 | MDUMOD0;\
																MDU_A  = wAh;\
																MDU_B  = wAl;\
																MDU_C  = wB;\
																while (MDU_CR &	MDUBUSY);\
																wCh	   = MDU_A;\
																MDU_CR = MDUDONE;\
															} while	(0)

/**
 * 32Bit/16Bit除法----求商,只取低位
 *
 * @CodeLen	0(Xdata) 0(Idata) 0(Data)
 * @RunTime	0(Xdata) 0(Idata) 0(Data)
 * @Exp		C =	A /	B
 *
 * @param	wAh	 (uint16)  被除数的高16位
 * @param	wAl	 (uint16)  被除数的低16位
 * @param	wB	 (uint16)  除数
 * @param	wCl	 (uint16)  商的低16位
 */
#define	DivQ_L_MDU(wAh,	wAl, wB, wCl)						do {\
																MDU_CR = MDURUN;\
																MDU_MD = MDUMOD1 | MDUMOD0;\
																MDU_A  = wAh;\
																MDU_B  = wAl;\
																MDU_C  = wB;\
																while (MDU_CR &	MDUBUSY);\
																wCl	   = MDU_B;\
																MDU_CR = MDUDONE;\
															} while	(0)

/**
 * 32Bit/16Bit除法----求余
 *
 * @CodeLen	0x0039(Xdata) 0x0033(Idata)	0x0026(Data)
 * @RunTime	3.86us(Xdata) 3.21us(Idata)	2.42us(Data)
 * @Exp		C =	A %	B
 *
 * @param	wAh	 (uint16)  被除数的高16位
 * @param	wAl	 (uint16)  被除数的低16位
 * @param	wB	 (uint16)  除数
 * @param	wC	 (uint16)  余数
 */
#define	DivR_MDU(wAh, wAl, wB, wC)							do {\
																MDU_CR = MDURUN;\
																MDU_MD = MDUMOD1 | MDUMOD0;\
																MDU_A  = wAh;\
																MDU_B  = wAl;\
																MDU_C  = wB;\
																while (MDU_CR &	MDUBUSY);\
																wC	   = MDU_C;\
																MDU_CR = MDUDONE;\
															} while	(0)

/**
 * Sin/Cos计算与坐标转换
 *
 * @CodeLen	0x0043(Xdata) 0x003a(Idata)	0x002c(Data)
 * @RunTime	4.46us(Xdata) 3.38us(Idata)	2.67us(Data)
 * @Exp		Sin	= Cos0 * Sin0(Theta) + Sin0	* Cos0(Theta)
 *			Cos	= Cos0 * Cos0(Theta) - Sin0	* Sin0(Theta)
 *
 * @param	iCos0	(int16)	 初始Cos值
 * @param	iTheta	(int16)	 角度
 * @param	iSin0	(int16)	 初始Sin值
 * @param	iCos	(int16)	 Cos计算结果
 * @param	iSin	(int16)	 Sin计算结果
 */
#define	SinCos_MDU(iCos0, iTheta, iSin0, iCos, iSin)		do {\
																MDU_CR = MDURUN;\
																MDU_MD = MDUMOD2;\
																MDU_A  = iCos0;\
																MDU_B  = iTheta;\
																MDU_C  = iSin0;\
																while (MDU_CR &	MDUBUSY);\
																iCos   = MDU_A;\
																iSin   = MDU_C;\
																MDU_CR = MDUDONE;\
															} while	(0)

/**
 * 角度和幅值计算
 *
 * @CodeLen	0x0038(Xdata) 0x002e(Idata)	0x0026(Data)
 * @RunTime	3.83us(Xdata) 2.92us(Idata)	2.42us(Data)
 * @Exp		Us	  =	Sqrt(Sin^2 + Cos^2)
 *			Theta =	Atan(Sin / Cos)
 *
 * @param	iCos	(int16)	 输入的Cos值
 * @param	iSin	(int16)	 输入的Sin值
 * @param	iUs		(int16)	 幅值计算结果
 * @param	iTheta	(int16)	 角度计算结果
 */
#define	Atan_MDU(iCos, iSin, iUs, iTheta)					do {\
																MDU_CR = MDURUN;\
																MDU_MD = MDUMOD2 | MDUMOD0;\
																MDU_A  = iCos;\
																MDU_B  = 0;\
																MDU_C  = iSin;\
																while (MDU_CR &	MDUBUSY);\
																iUs	   = MDU_A;\
																iTheta = MDU_B;\
																MDU_CR = MDUDONE;\
															} while	(0)

/**
 * 角度计算
 *
 * @CodeLen	0(Xdata) 0(Idata) 0(Data)
 * @RunTime	0(Xdata) 0(Idata) 0(Data)
 * @Exp		Theta =	Atan(Sin / Cos)
 *
 * @param	iCos	(int16)	 输入的Cos值
 * @param	iSin	(int16)	 输入的Sin值
 * @param	iTheta	(int16)	 角度计算结果
 */
#define	Atan_Theta_MDU(iCos, iSin, iTheta)					do {\
																MDU_CR = MDURUN;\
																MDU_MD = MDUMOD2 | MDUMOD0;\
																MDU_A  = iCos;\
																MDU_B  = 0;\
																MDU_C  = iSin;\
																while (MDU_CR &	MDUBUSY);\
																iTheta = MDU_B;\
																MDU_CR = MDUDONE;\
															} while	(0)

/**
 * 幅值计算
 *
 * @CodeLen	0(Xdata) 0(Idata) (Data)
 * @RunTime	0(Xdata) 0(Idata) (Data)
 * @Exp		Us	  =	Sqrt(Sin^2 + Cos^2)
 *
 * @param	iCos	(int16)	 输入的Cos值
 * @param	iSin	(int16)	 输入的Sin值
 * @param	iUs		(int16)	 幅值计算结果
 */
#define	Atan_Us_MDU(iCos, iSin,	iUs)						do {\
																MDU_CR = MDURUN;\
																MDU_MD = MDUMOD2 | MDUMOD0;\
																MDU_A  = iCos;\
																MDU_B  = 0;\
																MDU_C  = iSin;\
																while (MDU_CR &	MDUBUSY);\
																iUs	   = MDU_A;\
																MDU_CR = MDUDONE;\
															} while	(0)

/**
 * 幅值低通滤波器
 *
 * @CodeLen	0x0039(Xdata) 0x0033(Idata)	0x0026(Data)
 * @RunTime	6.00us(Xdata) 4.71us(Idata)	3.63us(Data)
 * @Exp		Y += K * (Sqrt(Sin^2 + Cos^2) -	Y)
 *
 * @param	iCos  (int16)  输入的Cos值
 * @param	iSin  (int16)  输入的Sin值
 * @param	ucK	  (uint8)  滤波系数(Q8格式：0~255)
 * @param	iYh	  (int16)  滤波输出的高16位(填入上一次计算的输出，取出新的输出)
 * @param	iYl	  (int16)  滤波输出的低16位(填入上一次计算的输出，取出新的输出)
 */
#define	Atan_LPF_MDU(iCos, iSin, ucK, iYh, iYl)				do {\
																MDU_CR = MDURUN;\
																MDU_MD = MDUMOD2 | MDUMOD0;\
																MDU_A  = iCos;\
																MDU_B  = 0;\
																MDU_C  = iSin;\
																while (MDU_CR &	MDUBUSY);\
																MDU_MD = MDUMOD2 | MDUMOD1;\
																MDU_D  = ucK;\
																MDU_B  = iYh;\
																MDU_C  = iYl;\
																while (MDU_CR &	MDUBUSY);\
																iYh	   = MDU_B;\
																iYl	   = MDU_C;\
																MDU_CR = MDUDONE;\
															} while	(0)

/**
 * 乘除法器----求商
 *
 * @CodeLen	0x0046(Xdata) 0x003b(Idata)	0x002f(Data)
 * @RunTime	4.58us(Xdata) 3.54us(Idata)	2.79us(Data)
 * @Exp		D =	A *	B /	C
 *
 * @param	wA	 (uint16)  被乘数
 * @param	wB	 (uint16)  乘数
 * @param	wC	 (uint16)  除数
 * @param	wDh	 (uint16)  商的高16位
 * @param	wDl	 (uint16)  商的低16位
 */
#define	Muilt_DivQ_MDU(wA, wB, wC, wDh,	wDl)				do {\
																MDU_CR = MDURUN;\
																MDU_MD = MDUMOD1;\
																MDU_A  = wA;\
																MDU_C  = wB;\
																MDU_MD = MDUMOD1 | MDUMOD0;\
																MDU_C  = wC;\
																while (MDU_CR &	MDUBUSY);\
																wDh	   = MDU_A;\
																wDl	   = MDU_B;\
																MDU_CR = MDUDONE;\
															} while	(0)

/**
 * 乘除法器----求商,只取高位
 *
 * @CodeLen	0(Xdata) 0(Idata) 0(Data)
 * @RunTime	0(Xdata) 0(Idata) 0(Data)
 * @Exp		D =	A *	B /	C
 *
 * @param	wA	 (uint16)  被乘数
 * @param	wB	 (uint16)  乘数
 * @param	wC	 (uint16)  除数
 * @param	wDh	 (uint16)  商的高16位
 */
#define	Muilt_DivQ_H_MDU(wA, wB, wC, wDh)					do {\
																MDU_CR = MDURUN;\
																MDU_MD = MDUMOD1;\
																MDU_A  = wA;\
																MDU_C  = wB;\
																MDU_MD = MDUMOD1 | MDUMOD0;\
																MDU_C  = wC;\
																while (MDU_CR &	MDUBUSY);\
																wDh	   = MDU_A;\
																MDU_CR = MDUDONE;\
															} while	(0)

/**
 * 乘除法器----求商,只取低位
 *
 * @CodeLen	0(Xdata) 0(Idata) 0(Data)
 * @RunTime	0(Xdata) 0(Idata) 0(Data)
 * @Exp		D =	A *	B /	C
 *
 * @param	wA	 (uint16)  被乘数
 * @param	wB	 (uint16)  乘数
 * @param	wC	 (uint16)  除数
 * @param	wDl	 (uint16)  商的低16位
 */
#define	Muilt_DivQ_L_MDU(wA, wB, wC, wDl)					do {\
																MDU_CR = MDURUN;\
																MDU_MD = MDUMOD1;\
																MDU_A  = wA;\
																MDU_C  = wB;\
																MDU_MD = MDUMOD1 | MDUMOD0;\
																MDU_C  = wC;\
																while (MDU_CR &	MDUBUSY);\
																wDl	   = MDU_B;\
																MDU_CR = MDUDONE;\
															} while	(0)

/**
 * 乘除法器----求余
 *
 * @CodeLen	0x003c(Xdata) 0x0034(Idata)	0x0029(Data)
 * @RunTime	4.00us(Xdata) 3.25us(Idata)	2.54us(Data)
 * @Exp		D =	A *	B %	C
 *
 * @param	wA	(uint16)  被乘数
 * @param	wB	(uint16)  乘数
 * @param	wC	(uint16)  除数
 * @param	wD	(uint16)  余数
 */
#define	Muilt_DivR_MDU(wA, wB, wC, wD)						do {\
																MDU_CR = MDURUN;\
																MDU_MD = MDUMOD1;\
																MDU_A  = wA;\
																MDU_C  = wB;\
																MDU_MD = MDUMOD1 | MDUMOD0;\
																MDU_C  = wC;\
																while (MDU_CR &	MDUBUSY);\
																wD	   = MDU_C;\
																MDU_CR = MDUDONE;\
															} while	(0)




#ifdef __cplusplus
}
#endif

#endif	//__FU68XX_4_MDU_H__


/*** (C) Copyright 2022	Fortior	Technology Co.,	Ltd. ***/
