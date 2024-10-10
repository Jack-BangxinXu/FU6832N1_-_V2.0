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
 * �з��ų˷����������һλ
 *
 * @CodeLen	0x0033(Xdata) 0x0029(Idata)	0x0021(Data)
 * @RunTime	2.86us(Xdata) 1.96us(Idata)	1.46us(Data)
 * @Exp		C =	A *	B *	2
 *
 * @param	iA	 (int16)  ������
 * @param	iB	 (int16)  ����
 * @param	iCh	 (int16)  ���ĸ�16λ
 * @param	iCl	 (int16)  ���ĵ�16λ
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
 * �з��ų˷����������һλ,ֻȡ��λ
 *
 * @CodeLen	0x002a(Xdata) 0x0024(Idata)	0x001c(Data)
 * @RunTime	2.25us(Xdata) 1.71us(Idata)	1.21us(Data)
 * @Exp		C =	A *	B *	2
 *
 * @param	iA	 (int16)  ������
 * @param	iB	 (int16)  ����
 * @param	iCh	 (int16)  ���ĸ�16λ
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
 * �з��ų˷����������һλ,ֻȡ��λ
 *
 * @CodeLen	0x002a(Xdata) 0x0024(Idata)	0x001c(Data)
 * @RunTime	2.25us(Xdata) 1.71us(Idata)	1.21us(Data)
 * @Exp		C =	A *	B *	2
 *
 * @param	iA	 (int16)  ������
 * @param	iB	 (int16)  ����
 * @param	iCl	 (int16)  ���ĵ�16λ
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
 * �з��ų˷�
 *
 * @CodeLen	0x0033(Xdata) 0x0029(Idata)	0x0021(Data)
 * @RunTime	2.88us(Xdata) 1.96us(Idata)	1.46us(Data)
 * @Exp		C =	A *	B
 *
 * @param	iA	 (int16)  ������
 * @param	iB	 (int16)  ����
 * @param	iCh	 (int16)  ���ĸ�16λ
 * @param	iCl	 (int16)  ���ĵ�16λ
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
 * �з��ų˷�,ֻȡ��λ
 *
 * @CodeLen	0x002a(Xdata) 0x0024(Idata)	0x001c(Data)
 * @RunTime	2.30us(Xdata) 1.71us(Idata)	1.21us(Data)
 * @Exp		C =	A *	B
 *
 * @param	iA	 (int16)  ������
 * @param	iB	 (int16)  ����
 * @param	iCh	 (int16)  ���ĸ�16λ
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
 * �з��ų˷�,ֻȡ��λ
 *
 * @CodeLen	0x002a(Xdata) 0x0024(Idata)	0x001c(Data)
 * @RunTime	2.30us(Xdata) 1.71us(Idata)	1.21us(Data)
 * @Exp		C =	A *	B
 *
 * @param	iA	 (int16)  ������
 * @param	iB	 (int16)  ����
 * @param	iCl	 (int16)  ���ĵ�16λ
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
 * �޷��ų˷�
 *
 * @CodeLen	0x0033(Xdata) 0x0029(Idata)	0x0021(Data)
 * @RunTime	2.88us(Xdata) 1.96us(Idata)	1.46us(Data)
 * @Exp		C =	A *	B
 *
 * @param	wA	 (uint16)  ������
 * @param	wB	 (uint16)  ����
 * @param	wCh	 (uint16)  ���ĸ�16λ
 * @param	wCl	 (uint16)  ���ĵ�16λ
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
 * �޷��ų˷�,ֻȡ��λ
 *
 * @CodeLen	0x002a(Xdata) 0x0024(Idata)	0x001c(Data)
 * @RunTime	2.30us(Xdata) 1.71us(Idata)	1.21us(Data)
 * @Exp		C =	A *	B
 *
 * @param	wA	 (uint16)  ������
 * @param	wB	 (uint16)  ����
 * @param	wCh	 (uint16)  ���ĸ�16λ
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
 * �޷��ų˷�,ֻȡ��λ
 *
 * @CodeLen	0x002a(Xdata) 0x0024(Idata)	0x001c(Data)
 * @RunTime	2.30us(Xdata) 1.71us(Idata)	1.21us(Data)
 * @Exp		C =	A *	B
 *
 * @param	wA	 (uint16)  ������
 * @param	wB	 (uint16)  ����
 * @param	wCl	 (uint16)  ���ĵ�16λ
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
 * ��ͨ�˲���
 *
 * @CodeLen	0x0049(Xdata) 0x003d(Idata)	0x002f(Data)
 * @RunTime	4.21us(Xdata) 2.88us(Idata)	2.29us(Data)
 * @Exp		Y += K * (X	- Y)
 *
 * @param	iYh	 (int16)  �˲�����ĸ�16λ(������һ�μ���������ȡ���µ����)
 * @param	iYl	 (int16)  �˲�����ĵ�16λ(������һ�μ���������ȡ���µ����)
 * @param	iX	 (int16)  �˲�����
 * @param	ucK	 (uint8)  �˲�ϵ��(Q8��ʽ��0~255)
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
 * 32Bit/16Bit����----����
 *
 * @CodeLen	0x0043(Xdata) 0x003a(Idata)	0x002c(Data)
 * @RunTime	4.46us(Xdata) 3.50us(Idata)	2.67us(Data)
 * @Exp		C =	A /	B
 *
 * @param	wAh	 (uint16)  �������ĸ�16λ
 * @param	wAl	 (uint16)  �������ĵ�16λ
 * @param	wB	 (uint16)  ����
 * @param	wCh	 (uint16)  �̵ĸ�16λ
 * @param	wCl	 (uint16)  �̵ĵ�16λ
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
 * 32Bit/16Bit����----����,ֻȡ��λ
 *
 * @CodeLen	0(Xdata) 0(Idata) 0(Data)
 * @RunTime	0(Xdata) 0(Idata) 0(Data)
 * @Exp		C =	A /	B
 *
 * @param	wAh	 (uint16)  �������ĸ�16λ
 * @param	wAl	 (uint16)  �������ĵ�16λ
 * @param	wB	 (uint16)  ����
 * @param	wCh	 (uint16)  �̵ĸ�16λ
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
 * 32Bit/16Bit����----����,ֻȡ��λ
 *
 * @CodeLen	0(Xdata) 0(Idata) 0(Data)
 * @RunTime	0(Xdata) 0(Idata) 0(Data)
 * @Exp		C =	A /	B
 *
 * @param	wAh	 (uint16)  �������ĸ�16λ
 * @param	wAl	 (uint16)  �������ĵ�16λ
 * @param	wB	 (uint16)  ����
 * @param	wCl	 (uint16)  �̵ĵ�16λ
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
 * 32Bit/16Bit����----����
 *
 * @CodeLen	0x0039(Xdata) 0x0033(Idata)	0x0026(Data)
 * @RunTime	3.86us(Xdata) 3.21us(Idata)	2.42us(Data)
 * @Exp		C =	A %	B
 *
 * @param	wAh	 (uint16)  �������ĸ�16λ
 * @param	wAl	 (uint16)  �������ĵ�16λ
 * @param	wB	 (uint16)  ����
 * @param	wC	 (uint16)  ����
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
 * Sin/Cos����������ת��
 *
 * @CodeLen	0x0043(Xdata) 0x003a(Idata)	0x002c(Data)
 * @RunTime	4.46us(Xdata) 3.38us(Idata)	2.67us(Data)
 * @Exp		Sin	= Cos0 * Sin0(Theta) + Sin0	* Cos0(Theta)
 *			Cos	= Cos0 * Cos0(Theta) - Sin0	* Sin0(Theta)
 *
 * @param	iCos0	(int16)	 ��ʼCosֵ
 * @param	iTheta	(int16)	 �Ƕ�
 * @param	iSin0	(int16)	 ��ʼSinֵ
 * @param	iCos	(int16)	 Cos������
 * @param	iSin	(int16)	 Sin������
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
 * �ǶȺͷ�ֵ����
 *
 * @CodeLen	0x0038(Xdata) 0x002e(Idata)	0x0026(Data)
 * @RunTime	3.83us(Xdata) 2.92us(Idata)	2.42us(Data)
 * @Exp		Us	  =	Sqrt(Sin^2 + Cos^2)
 *			Theta =	Atan(Sin / Cos)
 *
 * @param	iCos	(int16)	 �����Cosֵ
 * @param	iSin	(int16)	 �����Sinֵ
 * @param	iUs		(int16)	 ��ֵ������
 * @param	iTheta	(int16)	 �Ƕȼ�����
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
 * �Ƕȼ���
 *
 * @CodeLen	0(Xdata) 0(Idata) 0(Data)
 * @RunTime	0(Xdata) 0(Idata) 0(Data)
 * @Exp		Theta =	Atan(Sin / Cos)
 *
 * @param	iCos	(int16)	 �����Cosֵ
 * @param	iSin	(int16)	 �����Sinֵ
 * @param	iTheta	(int16)	 �Ƕȼ�����
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
 * ��ֵ����
 *
 * @CodeLen	0(Xdata) 0(Idata) (Data)
 * @RunTime	0(Xdata) 0(Idata) (Data)
 * @Exp		Us	  =	Sqrt(Sin^2 + Cos^2)
 *
 * @param	iCos	(int16)	 �����Cosֵ
 * @param	iSin	(int16)	 �����Sinֵ
 * @param	iUs		(int16)	 ��ֵ������
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
 * ��ֵ��ͨ�˲���
 *
 * @CodeLen	0x0039(Xdata) 0x0033(Idata)	0x0026(Data)
 * @RunTime	6.00us(Xdata) 4.71us(Idata)	3.63us(Data)
 * @Exp		Y += K * (Sqrt(Sin^2 + Cos^2) -	Y)
 *
 * @param	iCos  (int16)  �����Cosֵ
 * @param	iSin  (int16)  �����Sinֵ
 * @param	ucK	  (uint8)  �˲�ϵ��(Q8��ʽ��0~255)
 * @param	iYh	  (int16)  �˲�����ĸ�16λ(������һ�μ���������ȡ���µ����)
 * @param	iYl	  (int16)  �˲�����ĵ�16λ(������һ�μ���������ȡ���µ����)
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
 * �˳�����----����
 *
 * @CodeLen	0x0046(Xdata) 0x003b(Idata)	0x002f(Data)
 * @RunTime	4.58us(Xdata) 3.54us(Idata)	2.79us(Data)
 * @Exp		D =	A *	B /	C
 *
 * @param	wA	 (uint16)  ������
 * @param	wB	 (uint16)  ����
 * @param	wC	 (uint16)  ����
 * @param	wDh	 (uint16)  �̵ĸ�16λ
 * @param	wDl	 (uint16)  �̵ĵ�16λ
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
 * �˳�����----����,ֻȡ��λ
 *
 * @CodeLen	0(Xdata) 0(Idata) 0(Data)
 * @RunTime	0(Xdata) 0(Idata) 0(Data)
 * @Exp		D =	A *	B /	C
 *
 * @param	wA	 (uint16)  ������
 * @param	wB	 (uint16)  ����
 * @param	wC	 (uint16)  ����
 * @param	wDh	 (uint16)  �̵ĸ�16λ
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
 * �˳�����----����,ֻȡ��λ
 *
 * @CodeLen	0(Xdata) 0(Idata) 0(Data)
 * @RunTime	0(Xdata) 0(Idata) 0(Data)
 * @Exp		D =	A *	B /	C
 *
 * @param	wA	 (uint16)  ������
 * @param	wB	 (uint16)  ����
 * @param	wC	 (uint16)  ����
 * @param	wDl	 (uint16)  �̵ĵ�16λ
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
 * �˳�����----����
 *
 * @CodeLen	0x003c(Xdata) 0x0034(Idata)	0x0029(Data)
 * @RunTime	4.00us(Xdata) 3.25us(Idata)	2.54us(Data)
 * @Exp		D =	A *	B %	C
 *
 * @param	wA	(uint16)  ������
 * @param	wB	(uint16)  ����
 * @param	wC	(uint16)  ����
 * @param	wD	(uint16)  ����
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
