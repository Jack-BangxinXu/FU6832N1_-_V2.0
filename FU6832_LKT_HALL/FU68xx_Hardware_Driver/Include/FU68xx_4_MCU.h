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
#define	FREC							(24000000)								// MCU����Ƶ��
	
/**************************************************************************************************///Function Subject
#define	SetReg(reg,	val1, val2)			((reg) = (reg) & (~(val1)) | (val2))	// ��reg��val1��Ӧ��λдval2
#define	SetBit(reg,	val)				((reg) |=  (val))						// ��reg��val��Ӧ��λд1
#define	ClrBit(reg,	val)				((reg) &= ~(val))						// ��reg��val��Ӧ��λд0
#define	XorBit(reg,	val)				((reg) ^=  (val))						// ��reg��val��Ӧ��λȡ��
#define	ReadBit(reg, val)				(((reg)	& (val)) ==	(val))				// �ж�reg��val��Ӧ��λ�Ƿ�Ϊ1
/**************************************************************************************************///Register Map
// �������ռĴ�������Keil����"[0-9A-Z]__[A-Z]"����ѡ"Match Case"��"Regular Expressior"
// �����������跽��:�������Ի���������"//"+��������.��:����TIMER1,������"//TIM1"

/******************************************************************************///SFR
 //sfr16   DPTR							  =	0x82;								  // RV:0000H  8051ָ��
SFR16(DPTR,	0x82);
 //sfr	   PSW							  =	0xd0;								  // RV:  00H  8051״̬�Ĵ���
 //sbit	   CY										= PSW^7;					  //			   rw--	��/��λ��־
 //sbit	   AC										= PSW^6;					  //			   rw--	BCD��/��λ��־
 //sbit	   F0										= PSW^5;					  //			   rw--	�û��Զ����־0
 //sbit	   RS1										= PSW^4;					  //			   rw--	R�Ĵ�����ҳλ1
 //sbit	   RS0										= PSW^3;					  //			   rw--	R�Ĵ�����ҳλ0
 //sbit	   OV										= PSW^2;					  //			   rw--	�������������־
 //sbit	   F1										= PSW^1;					  //			   rw--	�û��Զ����־1
 //sbit	   P										= PSW^0;					  //			   rw--	��ż��־
SFR(PSW, 0xd0);
	SBIT(CY, 0xd0, 7);
	SBIT(AC, 0xd0, 6);
	SBIT(F0, 0xd0, 5);
	SBIT(RS1,0xd0, 4);
	SBIT(RS0,0xd0, 3);
	SBIT(OV, 0xd0, 2);
	SBIT(F1, 0xd0, 1);
	SBIT(P,	 0xd0, 0);

 //sfr	   ACC							  =	0xe0;								  // RV:  00H  8051	A�Ĵ���
SFR(ACC, 0xe0);
/******************************************************************************///RST
 //sfr	   RST_SR						  =	0xc9;								  // RV:  xxH  ��λ״̬�Ĵ���
SFR(RST_SR,	0xc9);
 #define RSTPOW									  0x80							//				 r--- �ϵ縴λ��־
 #define RSTCLR									  0x80							//				 w1-- �ϵ縴λ��־
 #define RSTEXT									  0x40							//				 r--- �ⲿ��λ��־
 #define RSTLVD									  0x20							//				 r--- ��ѹ��λ��־
 #define RSTEOS									  0x10							//				 r--- ��Ӧ�����ȸ�λ��־
 #define RSTWDT									  0x08							//				 r--- ���Ź���λ��־
 #define RSTFED									  0x04							//				 r--- ���뱣����λ
 #define RSTDBG									  0x02							//				 r--- ���Խӿڸ�λ
 #define SOFTR									  0x01							//				 rw1- �����λ��־
/******************************************************************************///RTC
 #define RTC_TM							*(_IO uint16 xdata *)0x402c
 #define RTC_STA						*(_IO  uint8 xdata *)0x402e
 #define RTC_EN									  0x80							//				 rw-- RTCʹ��
 #define RTC_IF									  0x40							//				 rw-- RTC�жϱ�־
 #define ISOSCEN								  0x10							//				 rw-- �ڲ���ʱ��ʹ��
/******************************************************************************///CLOCK_CAL
 #define CAL_CR0						*(_IO  uint8 xdata *)0x4044
 #define CAL_STA								  0x80							//				 w-- CLOCK_CALʹ��,	r--	0-->Done 1-->ING
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

 //sfr	   TCON							  =	0x88;								  // RV:  00H  8051�жϿ��ƼĴ���
 //sbit	   TSDIF									= TCON^5;					  //			   rw--	TSD�¶ȸ�Ӧ�жϱ�־
 //sbit	   IT11										= TCON^4;					  //			   rw--	�ⲿ�ж�1��������1
 //sbit	   IT10										= TCON^3;					  //			   rw--	�ⲿ�ж�1��������0
 //sbit	   IF0										= TCON^2;					  //			   rw--	�ⲿ�ж�0��־
 //sbit	   IT01										= TCON^1;					  //			   rw--	�ⲿ�ж�0��������1
 //sbit	   IT00										= TCON^0;					  //			   rw--	�ⲿ�ж�0��������0
SFR(TCON, 0x88);
 	SBIT(TSDIF,0x88, 5);
	SBIT(IT11, 0x88, 4);
	SBIT(IT10, 0x88, 3);
	SBIT(IF0,  0x88, 2);
	SBIT(IT01, 0x88, 1);
	SBIT(IT00, 0x88, 0);
	
 //sfr	   IE							  =	0xa8;								  // RV:  00H  8051	�жϿ���	
// sbit	   EA										= IE^7;						  //			   rw--	MCU���ж�ʹ��
// sbit	   RTCIE									= IE^6;						  //			   rw--	RTC�ж�ʹ��
// sbit	   ES0										= IE^4;						  //			   rw--	UART�ж�ʹ��
// sbit	   SPIIE									= IE^3;						  //			   rw--	SPI�ж�ʹ��
// sbit	   EX1										= IE^2;						  //			   rw--	�ⲿ�ж�1ʹ��
// sbit	   TSDIE									= IE^1;						  //			   rw--	TSD�ж�ʹ��
// sbit	   EX0										= IE^0;						  //			   rw--	�ⲿ�ж�0ʹ��
 SFR(IE, 0xa8);
	SBIT(EA,   0xa8, 7);
	SBIT(RTCIE,0xa8, 6);
	SBIT(ES0,  0xa8, 4);
	SBIT(SPIIE,0xa8, 3);
	SBIT(EX1,  0xa8, 2);
	SBIT(TSDIE,0xa8, 1);
	SBIT(EX0,  0xa8, 0);

// sfr	   IP0							  =	0xb8;								  // RV:  00H  �����ж����ȼ�����G0
// sbit	   PDRV1									= IP0^7;					  //			   rw--	DRV���ȼ�����1
// sbit	   PDRV0									= IP0^6;					  //			   rw--	DRV���ȼ�����0
// sbit	   PX11										= IP0^5;					  //			   rw--	�ⲿ�ж�1���ȼ�����1
// sbit	   PX10										= IP0^4;					  //			   rw--	�ⲿ�ж�1���ȼ�����0
// sbit	   PX01										= IP0^3;					  //			   rw--	�ⲿ�ж�0���ȼ�����1
// sbit	   PX00										= IP0^2;					  //			   rw--	�ⲿ�ж�0���ȼ�����0
// sbit	   PLVW1									= IP0^1;					  //			   rw--	LVW���ȼ�����1
// sbit	   PLVW0									= IP0^0;					  //			   rw--	LVW���ȼ�����0
SFR(IP0, 0xb8);
	SBIT(PDRV1,	0xb8, 7);
	SBIT(PDRV0,	0xb8, 6);
	SBIT(PX11,	0xb8, 5);
	SBIT(PX10,	0xb8, 4);
	SBIT(PX01,	0xb8, 3);
	SBIT(PX00,	0xb8, 2);
	SBIT(PLVW_TSD1,	0xb8, 1);
	SBIT(PLVW_TSD0,	0xb8, 0);
 	
// sfr	   IP1							  =	0xc0;								  // RV:  00H  �����ж����ȼ�����G1
// sbit	   PCMP1									= IP1^7;					  //			   rw--	CMP���ȼ�����1
// sbit	   PCMP0									= IP1^6;					  //			   rw--	CMP���ȼ�����0
// sbit	   PADC1									= IP1^5;					  //			   rw--	ADC���ȼ�����1
// sbit	   PADC0									= IP1^4;					  //			   rw--	ADC���ȼ�����0
// sbit	   PTIM11									= IP1^3;					  //			   rw--	TIM1���ȼ�����1
// sbit	   PTIM10									= IP1^2;					  //			   rw--	TIM1���ȼ�����0
// sbit	   PTIM21									= IP1^1;					  //			   rw--	TIM2���ȼ�����1
// sbit	   PTIM20									= IP1^0;					  //			   rw--	TIM2���ȼ�����0
SFR(IP1, 0xc0);
	SBIT(PCMP1,	 0xc0, 7);
	SBIT(PCMP0,	 0xc0, 6);
	SBIT(PADC1,	 0xc0, 5);
	SBIT(PADC0,	 0xc0, 4);
 	SBIT(PTIM11, 0xc0, 3);
 	SBIT(PTIM10, 0xc0, 2);
 	SBIT(PTIM21, 0xc0, 1);
 	SBIT(PTIM20, 0xc0, 0);
 	
// sfr	   IP2							  =	0xc8;								  // RV:  00H  �����ж����ȼ�����G2
// sbit	   PTSD1									= IP2^7;					  //			   rw--	TSD���ȼ�����1
// sbit	   PTSD0									= IP2^6;					  //			   rw--	TSD���ȼ�����0
// sbit	   PTIM4S1									= IP2^5;					  //			   rw--	TIM4/SysTick���ȼ�����1
// sbit	   PTIM4S0									= IP2^4;					  //			   rw--	TIM4/SysTick���ȼ�����0
// sbit	   PTIM31									= IP2^3;					  //			   rw--	TIM3���ȼ�����1
// sbit	   PTIM30									= IP2^2;					  //			   rw--	TIM3���ȼ�����0
// sbit	   PRTC1									= IP2^1;					  //			   rw--	RTC���ȼ�����1
// sbit	   PRTC0									= IP2^0;					  //			   rw--	RTC���ȼ�����0
SFR(IP2, 0xc8);
	SBIT(PTIM41, 0xc8, 7);
	SBIT(PTIM40, 0xc8, 6);
 	SBIT(PSYSTICK1,0xc8, 5);
 	SBIT(PSYSTICK0,0xc8, 4);
 	SBIT(PTIM31, 0xc8, 3);
 	SBIT(PTIM30, 0xc8, 2);
	SBIT(PRTC1,	 0xc8, 1);
	SBIT(PRTC0,	 0xc8, 0);
 	
// sfr	   IP3							  =	0xd8;								  // RV:  00H  �����ж����ȼ�����G3
// sbit	   PDMA1									= IP3^7;					  //			   rw--	DMA���ȼ�����1
// sbit	   PDMA0									= IP3^6;					  //			   rw--	DMA���ȼ�����0
// sbit	   PSPI_UT21								= IP3^5;					  //			   rw--	SPI/UT2���ȼ�����1
// sbit	   PSPI_UT20								= IP3^4;					  //			   rw--	SPI/UT2���ȼ�����0
// sbit	   PI2C_UT11								= IP3^3;					  //			   rw--	I2C/UT1���ȼ�����1
// sbit	   PI2C_UT10								= IP3^2;					  //			   rw--	I2C/UT1���ȼ�����0
// sbit	   PCMP31									= IP3^1;					  //			   rw--	CMP3���ȼ�����1
// sbit	   PCMP30									= IP3^0;					  //			   rw--	CMP3���ȼ�����0
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
 #define I2C_CR							*(_IO  uint8 xdata *)0x4028			   // RV:  00H	I2C���ƼĴ���
 #define I2CEN									  0x80							//				 rw-- I2Cʹ��
 #define I2CMS									  0x40							//				 rw-- ��/�ӻ�ģʽѡ��
 #define I2CSPD1								  0x04							//				 rw-- �ٶ�����1
 #define I2CSPD0								  0x02							//				 rw-- �ٶ�����0
 #define I2CIE									  0x01							//				 rw-- �жϿ���

 #define I2C_SR							*(_IO  uint8 xdata *)0x402b			   // RV:  00H	I2C״̬�Ĵ���
 #define I2CBSY									  0x80							//				 r--- I2Cæ��־
 #define DMOD									  0x40							//				 rw-- I2C��д����
 #define I2CSTA									  0x10							//				 rw-- START�źſ���
 #define I2CSTP									  0x08							//				 rw-- STOP�źſ���
 #define STR									  0x04							//				 rw-- I2C�¼���ɱ�־
 #define NACK									  0x02							//				 rw-- Ӧ���źſ���
 #define I2CIF									  0x01							//				 r--- �жϱ�־

 #define I2C_ID							*(_IO  uint8 xdata *)0x4029			   // RV:  00H	����2C��ַ
 #define GC										  0x01							//				 �㲥ģʽ

 #define I2C_DR							*(_IO  uint8 xdata *)0x402a			   // RV:  00H	I2C���ݼĴ���
/******************************************************************************///SPI
 #define SPI_CR0						*(_IO  uint8 xdata *)0x4030			   // RV:  0bH	SPI���ƼĴ���1
 #define SPIBSY									  0x80							//				 r--- æ��־
 #define SPIMS									  0x40							//				 rw-- ��/�ӻ�����
 #define CPHA									  0x20							//				 rw-- ʱ����λ
 #define CPOL									  0x10							//				 rw-- ʱ�ӿ��е�ƽ
 #define SLVSEL									  0x08							//				 r--- NSS�������ź�
 #define NSSIN									  0x04							//				 r--- NSS��ʱ�ź�
 #define SRMT									  0x02							//				 r--- ��λ�Ĵ����ձ�־
 #define RXBMT									  0x01							//				 r--- ���ջ������ձ�־

 #define SPI_CR1						*(_IO  uint8 xdata *)0x4031			   // RV:  02H	SPI���ƼĴ���2
 #define SPIIF									  0x80							//				 rw0- �жϱ�־
 #define WCOL									  0x40							//				 rw0- д��ͻ��־
 #define MODF									  0x20							//				 rw0- ģʽ�����־
 #define RXOVRN									  0x10							//				 rw0- ���������־
 #define NSSMOD1								  0x08							//				 rw-- SPIģʽ����λ1
 #define NSSMOD0								  0x04							//				 rw-- SPIģʽ����λ0
 #define TXBMT									  0x02							//				 r--- ���ͻ������ձ�־
 #define SPIEN									  0x01							//				 rw-- SPIʹ��

 #define SPI_CLK						*(_IO  uint8 xdata *)0x4032			   // RV:  00H	SPIʱ�����üĴ���
 #define SPI_DR							*(_IO  uint8 xdata *)0x4033			   // RV:  00H	SPI���ݼĴ���
/******************************************************************************///UART
// sfr	   UT_CR						  =	0x98;								  // RV:  00H  UART���ƼĴ���
// sbit	   UT_MOD1									= UT_CR^7;					  //			   rw--	UARTģʽ����1
// sbit	   UT_MOD0									= UT_CR^6;					  //			   rw--	UARTģʽ����0
// sbit	   SM2										= UT_CR^5;					  //			   rw--	���ͨ��ʹ��
// sbit	   REN										= UT_CR^4;					  //			   rw--	����ʹ��
// sbit	   TB8										= UT_CR^3;					  //			   rw--	9λģʽ�·��͵ĵ�9λ
// sbit	   RB8										= UT_CR^2;					  //			   rw--	9λģʽ�½��յĵ�9λ
// sbit	   TI										= UT_CR^1;					  //			   rw--	������ɱ�־
// sbit	   RI										= UT_CR^0;					  //			   rw--	������ɱ�־
 SFR(UT_CR,	0x98);
 	SBIT(UT_MOD1,0x98, 7);
 	SBIT(UT_MOD0,0x98, 6);
 	SBIT(SM2,	 0x98, 5);
	SBIT(REN,	 0x98, 4);
	SBIT(TB8,	 0x98, 3);
	SBIT(RB8,	 0x98, 2);
	SBIT(TI,	 0x98, 1);
	SBIT(RI,	 0x98, 0);
 	
 //sfr	   UT_DR						  =	0x99;								  // RV:  00H  UART���ݼĴ���
 SFR(UT_DR,	0x99);
 //sfr16   UT_BAUD						  =	0x9a;								  // RV:009bH  UART�����ʿ��ƼĴ���
 SFR16(UT_BAUD,	0x9a);
 
 #define UART_2xBAUD							  0x8000						//				 rw--��Ƶʹ��

 //sfr	   UT2_CR						  =	0x8a;								  // RV:  00H  UART2���ƼĴ���
 SFR(UT2_CR, 0x8a);
 #define UT2MOD1																	0x80
 #define UT2MOD0																	0x40
 #define UT2SM2																		0x20
 #define UT2REN																		0x10
 #define UT2TB8																		0x08
 #define UT2RB8																		0x04
 #define UT2TI																		0x02
 #define UT2RI																		0x01

 #define UT2_BAUD						*(_IO uint16 xdata *)0x4042			   // RV:009bH	UART2�����ʿ��ƼĴ���
 #define BAUD2_SEL								  0x8000						//				 rw--��Ƶʹ��
 #define UART2CH								  0x4000						//				 rw--UART2����ת��ʹ��
 #define UART2IEN								  0x2000						//				 rw--UART2�ж�ʹ��
 //sfr	   UT2_DR						  =	0x89;								  // RV:  00H  UART2���ݼĴ���
  SFR(UT2_DR, 0x89);
/******************************************************************************///LIN
 #define LIN_CR							*(_IO  uint8 xdata *)0x40e0			   // RV:0000H	LIN���ƼĴ���
 #define LINIE									  0x08							//				 rw-- LIN�ж�ʹ��
 #define CHKMOD									  0x04							//				 rw-- У��ģʽ����
 #define LINRW									  0x02							//				 rw-- ��дģʽ����
 #define AUTOSIZE								  0x01							//				 rw-- ����ID�Զ��������ݳ���ʹ��

 #define LIN_SR							*(_IO  uint8 xdata *)0x40e1			   // RV:0000H	LIN״̬�Ĵ���
 #define ERRSYNC								  0x80							//				 r--- ͬ������,	ͬ����ʱ��ͬ������
 #define ERRCHK									  0x40							//				 r--- ����У�����
 #define ERRPRTY								  0x20							//				 r--- IDУ�����
 #define ABORT									  0x10							//				 r--- ���䱻�ж�, �������ʱ�յ�֡ͷ����LIN_CR[LIN_STOP]��1, ��ô��λ��1
 #define LINACT									  0x08							//				 r--- LIN�����ϴ��ڻ״̬
 #define LINIDLE								  0x04							//				 rw0- LIN�����ϴ��ڿ���״̬������4s
 #define LINDONE								  0x02							//				 rw-- LIN�������
 #define LINREQ									  0x01							//				 rw-- LIN�յ�֡ͷ

 #define LIN_CSR						*(_IO  uint8 xdata *)0x40e2			   // RV:0000H	LIN״̬���ƼĴ���
 #define LINSLP									  0x20							//				 rw-- LIN��˯��״̬
 #define CLRERR									  0x10							//				 rw0- ��������־
 #define LINWAKEUP								  0x08							//				 rw1- ��: LIN�Ƿ񱻻���; д: ���ͻ����ź�
 #define LINACK									  0x04							//				 w1-- ������Ӧ֡ͷ,	�ڸ�λ��1ǰ���뽫У��ģʽ, ��дģʽ, ����, ���ݳ���׼����
 #define LINSTOP								  0x02							//				 w1-- �жϵ�ǰ�Ĵ���
 #define LINEN									  0x01							//				 rw-- LINʹ��

 #define LIN_ID							*(_I   uint8 xdata *)0x40e3			   // RV:0000H	LIN�յ���ID�ļĴ���
 #define LIN_SIZE						*(_IO  uint8 xdata *)0x40e4			   // RV:0000H	LIN���ݳ��ȼĴ���
 #define LIN_BAUD						*(_I  uint16 xdata *)0x40e6			   // RV:04afH	LIN�����ʼĴ���
/******************************************************************************///MDU
 //sfr	   MDU_CR						  =	0xc1;								  // RV:  00H  MDU���ƼĴ���
   SFR(MDU_CR, 0xc1);
 #define MDUBUSY								  0x80							//				 r--- MDU��æ��־
 #define MDUDONE								  0x40							//				 w--- ��ֹMDU����
 #define MDURUN									  0x20							//				 w--- ����MDU����

 //sfr	   MDU_MD						  =	0xca;								  // RV:  00H  MDUģʽ����
 SFR(MDU_MD, 0xca);
 #define MDUMOD2								  0x04							//				 rw-- MDUģʽ����2
 #define MDUMOD1								  0x02							//				 rw-- MDUģʽ����1
 #define MDUMOD0								  0x01							//				 rw-- MDUģʽ����0

 //sfr16   MDU_A						  =	0xc6;								  // RV:0000H  MDU���ݼĴ���A
 //sfr16   MDU_B						  =	0xc4;								  // RV:0000H  MDU���ݼĴ���B
 //sfr16   MDU_C						  =	0xc2;								  // RV:0000H  MDU���ݼĴ���C
 //sfr	   MDU_D						  =	0xcb;								  // RV:  00H  MDU���ݼĴ���D
  SFR16(MDU_A, 0xc6);
  SFR16(MDU_B, 0xc4);
  SFR16(MDU_C, 0xc2);
  SFR(MDU_D, 0xcb);
/******************************************************************************///PI
 #define PI0_KP							*(_IO  uint16 xdata *)0x02e0			   // RV:0000H	PI1�϶����������
 #define PI0_KI							*(_IO  uint16 xdata *)0x02e2			   // RV:0000H	PI1��΢�ֲ���
 #define PI0_UKMAX						*(_IO  uint16 xdata *)0x02e4			   // RV:0000H	PI0�ı�������
 #define PI0_UKMIN						*(_IO  uint16 xdata *)0x02e6			   // RV:0000H	PI0�Ļ��ֲ���
 #define PI0_EK1						*(_IO  uint16 xdata *)0x02e8			   // RV:0000H	PI0�������������ֵ
 #define PI0_EK							*(_IO  uint16 xdata *)0x02ea			   // RV:0000H	PI0������������Сֵ
 #define PI0_UKH						*(_IO  uint16 xdata *)0x02ec			   // RV:0000H	PI0����һ���������
 #define PI0_UKL						*(_IO  uint16 xdata *)0x02ee			   // RV:0000H	PI0���������

 #define PI1_KP							*(_IO  uint16 xdata *)0x02d0			   // RV:0000H	PI1�ı�������
 #define PI1_KI							*(_IO  uint16 xdata *)0x02d2			   // RV:0000H	PI1�Ļ��ֲ���
 #define PI1_UKMAX						*(_IO  uint16 xdata *)0x02d4			   // RV:0000H	PI1�������������ֵ
 #define PI1_UKMIN						*(_IO  uint16 xdata *)0x02d6			   // RV:0000H	PI1������������Сֵ
 #define PI1_EK1						*(_IO  uint16 xdata *)0x02d8			   // RV:0000H	PI1����һ���������
 #define PI1_EK							*(_IO  uint16 xdata *)0x02da			   // RV:0000H	PI1���������
 #define PI1_UKH						*(_IO  uint16 xdata *)0x02dc			   // RV:0000H	PI1����������16λ
 #define PI1_UKL						*(_IO  uint16 xdata *)0x02de			   // RV:0000H	PI1����������16λ

 #define PI2_KP							*(_IO  uint16 xdata *)0x02bc			   // RV:0000H	PI2�ı�������
 #define PI2_KI							*(_IO  uint16 xdata *)0x02be			   // RV:0000H	PI2�Ļ��ֲ���
 #define PI2_UKMAX						*(_IO  uint16 xdata *)0x02c0			   // RV:0000H	PI2�������������ֵ
 #define PI2_UKMIN						*(_IO  uint16 xdata *)0x02c2			   // RV:0000H	PI2������������Сֵ
 #define PI2_EK1						*(_IO  uint16 xdata *)0x02c4			   // RV:0000H	PI2����һ���������
 #define PI2_EK							*(_IO  uint16 xdata *)0x02c6			   // RV:0000H	PI2���������
 #define PI2_UKH						*(_IO  uint16 xdata *)0x02c8			   // RV:0000H	PI2����������16λ
 #define PI2_UKL						*(_IO  uint16 xdata *)0x02ca			   // RV:0000H	PI2����������16λ
 #define PI2_KD							*(_IO  uint16 xdata *)0x02cc			   // RV:0000H	PI2�϶����������
 #define PI2_EK2						*(_IO  uint16 xdata *)0x02ce			   // RV:0000H	PI2��΢�ֲ���

 #define PI3_KP							*(_IO  uint16 xdata *)0x02a8			   // RV:0000H	PI3�ı�������
 #define PI3_KI							*(_IO  uint16 xdata *)0x02aa			   // RV:0000H	PI3�Ļ��ֲ���
 #define PI3_UKMAX						*(_IO  uint16 xdata *)0x02ac			   // RV:0000H	PI3�������������ֵ
 #define PI3_UKMIN						*(_IO  uint16 xdata *)0x02ae			   // RV:0000H	PI3������������Сֵ
 #define PI3_EK1						*(_IO  uint16 xdata *)0x02b0			   // RV:0000H	PI3����һ���������
 #define PI3_EK							*(_IO  uint16 xdata *)0x02b2			   // RV:0000H	PI3���������
 #define PI3_UKH						*(_IO  uint16 xdata *)0x02b4			   // RV:0000H	PI3����������16λ
 #define PI3_UKL						*(_IO  uint16 xdata *)0x02b6			   // RV:0000H	PI3����������16λ
 #define PI3_KD							*(_IO  uint16 xdata *)0x02b8			   // RV:0000H	PI3�϶����������
 #define PI3_EK2						*(_IO  uint16 xdata *)0x02ba			   // RV:0000H	PI3��΢�ֲ���

 //sfr	   PI_CR						  =	0xf9;								  // RV:  00H  PI���ƼĴ���
 SFR(PI_CR,	0xf9);
 #define T2TSS									  0x80							//				 rw-- TIM2����ģʽ����ʹ��
 #define T2RPD									  0x40							//				 rw-- RPDʹ��
 #define PIBSY									  0X10							//				 rw-- PI��æ
 #define PI3STA									  0x08							//				 rw-- PI3ʹ��
 #define PI2STA									  0x04							//				 rw-- PI2ʹ��
 #define PI1STA									  0x02							//				 rw-- PI1ʹ��
 #define PI0STA									  0x01							//				 rw-- PI0ʹ��
/******************************************************************************///FOC
 #define FOC_CR0						*(_IO  uint8 xdata *)0x409f			   // RV:  00H	FOC���ƼĴ���0
 #define OMIF									  0x80							//				 r--- ��ǰת��>FOC_EFREQMINΪ1
 #define OMAF									  0x40							//				 r--- ��ǰת��>FOC_EFREQMAXΪ1
 #define MERRS1									  0x20							//				 rw-- ��Ĥ�㷨��MAX	ERRѡ��
 #define MERRS0									  0x10							//				 rw-- ��Ĥ�㷨��MAX	ERRѡ��
 #define UCSEL									  0x08							//				 rw-- UDC����ͨ��ѡ��0��AD2	1:AD14
 #define OMAS									  0x04							//				 rw-- �����ٶȹ���ʱ���ѡ��λ
 #define ESCMS									  0x02							//				 rw-- omega����ģʽΪATAN
 #define EDIS									  0x01							//				 rw-- EALPHA/EBETA�Զ����½�ֹ

 #define FOC_CR1						*(_IO  uint8 xdata *)0x40a0			   // RV:  00H	FOC���ƼĴ���1
 #define OVMDL									  0x80							//				 rw-- ������ʹ��
 #define EFAE									  0x40							//				 rw-- ������ǿ�ƽǶ�ʹ��
 #define RFAE									  0x20							//				 rw-- ǿ�����½Ƕ�ʹ��
 #define ANGM									  0x10							//				 rw-- �Ƕ�ģʽѡ��
 #define CSM1									  0x08							//				 rw-- ��������ģʽ����1
 #define CSM0									  0x04							//				 rw-- ��������ģʽ����0
 #define SPWMSEL								  0x02							//				 rw-- SPWMģʽѡ��
 #define SVPWMEN								  0x01							//				 rw-- SVPWM/SPWMѡ��

 #define FOC_CR2						*(_IO  uint8 xdata *)0x40a1			   // RV:  00H	FOC���ƼĴ���2
 #define ESEL									  0x80							//				 rw-- ������ģʽ
 #define ICLR									  0x40							//				 rw-- FOC__IA/B/CMAX����
 #define F5SEG									  0x20							//				 rw-- 7/5��ʽSVPWMģʽ
 #define DSS									  0x10							//				 rw-- 2/3�������ģʽ
 #define CSOC1									  0x08							//				 rw-- ����������׼У׼����1
 #define CSOC0									  0x04							//				 rw-- ����������׼У׼����0
 #define UQD									  0x02							//				 rw-- ����Q��PI
 #define UDD									  0x01							//				 rw-- ����D��PI

 #define FOC_EKP						*(_IO  int16 xdata *)0x4074			   // RV:0000H	��������PI��P����
 #define FOC_EKI						*(_IO  int16 xdata *)0x4076			   // RV:0000H	��������PI��I����
 #define FOC_KSLIDE						*(_IO  int16 xdata *)0x4078			   // RV:0000H	������SMOģʽ�µ�KSLIDE	 ��	 PLLģʽ�µ�KP
 #define FOC_EKLPFMIN					*(_IO  int16 xdata *)0x407a			   // RV:0000H	������SMOģʽ��BMF��LPFϵ����Сֵ  ��  PLLģʽ�µ�KI
 #define FOC_EBMFK						*(_IO  int16 xdata *)0x407c			   // RV:0000H	���������綯�Ƶ�LPFϵ��
 #define FOC_OMEKLPF					*(_IO  int16 xdata *)0x407e			   // RV:0000H	�������ٶȼ����LPFϵ��
 #define FOC_FBASE						*(_IO  int16 xdata *)0x4080			   // RV:0000H	�������Ƕ�����(OMEGA)��ϵ��
 #define FOC_EFREQACC					*(_IO uint16 xdata *)0x4082			   // RV:0000H	��������ǿ�ƽǶ�ģʽ�µ�OMEGA����
 #define FOC_EFREQMIN					*(_IO  int16 xdata *)0x4084			   // RV:0000H	��������ǿ�ƽǶ�ģʽ�µ�OMEGA��Сֵ
 #define FOC_EFREQHOLD					*(_IO  int16 xdata *)0x4086			   // RV:0000H	��������ǿ�ƽǶ�ģʽ�µ�OMEGA����ֵ
 #define FOC_EFREQMAX					*(_IO  uint8 xdata *)0x406f			   // RV:  00H	��������ǿ�ƽǶ�ģʽ�µ�OMEGA���ֵ
 #define FOC_EK3						*(_IO  int16 xdata *)0x4088			   // RV:0000H	���������������ϵ��3
 #define FOC_EK4						*(_IO  int16 xdata *)0x408a			   // RV:0000H	���������������ϵ��4
 #define FOC_EK1						*(_IO  int16 xdata *)0x408c			   // RV:0000H	���������������ϵ��1
 #define FOC_EK2						*(_IO  int16 xdata *)0x408e			   // RV:0000H	���������������ϵ��2
 #define FOC_IDREF						*(_IO  int16 xdata *)0x4090			   // RV:0000H	D������ο�ֵ
 #define FOC_IQREF						*(_IO  int16 xdata *)0x4092			   // RV:0000H	Q������ο�ֵ
 #define FOC_DQKP						*(_IO  int16 xdata *)0x4094			   // RV:0000H	DQ��PI�ı�������
 #define FOC_DQKI						*(_IO  int16 xdata *)0x4096			   // RV:0000H	DQ��PI�Ļ��ֲ���
 #define FOC__UDCFLT					*(_I   int16 xdata *)0x4098			   // RV:0000H	�˲����ĸ�ߵ�ѹ
 #define FOC_TSMIN						*(_IO  uint8 xdata *)0x40a2			   // RV:  00H	������ģʽ�µ�ADC��������  ��  ˫������ģʽ����������
 #define FOC_TGLI						*(_IO  uint8 xdata *)0x40a3			   // RV:  00H	���ŵ�ͨխ��������
 #define FOC_TBLO						*(_IO  uint8 xdata *)0x40a4			   // RV:  00H	�������������������ʱ��
 #define FOC_TRGDLY						*(_IO	int8 xdata *)0x40a5			   // RV:  00H	������ģʽ��ADC���������ӳ�	 ��	 ˫������ģʽ�µ�������ʱ��
 #define FOC_CSO						*(_IO  int16 xdata *)0x40a6			   // RV:4040H	����������׼ֵ
 #define FOC__RTHESTEP					*(_IO  int16 xdata *)0x40a8			   // RV:0000H	�����ٶ�
 #define FOC_RTHEACC					*(_O   int16 xdata *)0x40aa			   // RV:0000H	���¼��ٶ�
 #define FOC__EOMELPF					*(_I   int16 xdata *)0x40aa			   // RV:0000H	�˲����ٶ�
 #define FOC__RTHECNT					*(_IO  uint8 xdata *)0x40ac			   // RV:  00H	���´���
 #define FOC__THECOR					*(_IO  uint8 xdata *)0x40ad			   // RV:  01H	����ģʽ�л�������ģʽ�ĽǶ�����ֵ
 #define FOC__EMF						*(_I   int16 xdata *)0x40ae			   // RV:0000H	����������ķ��綯��EMF
 #define FOC__THECOMP					*(_O   int16 xdata *)0x40ae			   // RV:0000H	�ǶȲ���ֵ�����ڲ���������������ĽǶ�
 #define FOC_DMAX						*(_IO  int16 xdata *)0x40b0			   // RV:0000H	D��PI���������������
 #define FOC_DMIN						*(_IO  int16 xdata *)0x40b2			   // RV:0000H	D��PI���������������
 #define FOC_QMAX						*(_IO  int16 xdata *)0x40b4			   // RV:0000H	Q��PI���������������
 #define FOC_QMIN						*(_IO  int16 xdata *)0x40b6			   // RV:0000H	Q��PI���������������
 #define FOC__UD						*(_IO  int16 xdata *)0x40b8			   // RV:0000H	D���ѹ���ֵ
 #define FOC__UQ						*(_IO  int16 xdata *)0x40ba			   // RV:0000H	Q���ѹ���ֵ
 #define FOC__ID						*(_I   int16 xdata *)0x40bc			   // RV:0000H	D�ᷴ������ֵ
 #define FOC__IQ						*(_I   int16 xdata *)0x40be			   // RV:0000H	Q�ᷴ������ֵ
 #define FOC__IBET						*(_I   int16 xdata *)0x40c0			   // RV:0000H	�����������ֵ
 #define FOC__VBET						*(_I   int16 xdata *)0x40c2			   // RV:0000H	�����ѹ���ֵ
 #define FOC_UDCPS						*(_O   int16 xdata *)0x40c2			   // RV:0000H	D��ĵ�ѹǰ������
 #define FOC__VALP						*(_I   int16 xdata *)0x40c4			   // RV:0000H	�����ѹ���ֵ
 #define FOC_UQCPS						*(_O   int16 xdata *)0x40c4			   // RV:0000H	Q��ĵ�ѹǰ������
 #define FOC__IC						*(_I   int16 xdata *)0x40c6			   // RV:0000H	C�����
 #define FOC__IB						*(_I   int16 xdata *)0x40c8			   // RV:0000H	B�����
 #define FOC__IA						*(_I   int16 xdata *)0x40ca			   // RV:0000H	A�����
 #define FOC__THETA						*(_IO  int16 xdata *)0x40cc			   // RV:0000H	�����Ƕ�
 #define FOC__ETHETA					*(_IO  int16 xdata *)0x40ce			   // RV:0000H	����������ĽǶ�
 #define FOC__EALP						*(_IO  int16 xdata *)0x40d0			   // RV:0000H	���������㷴�綯�ƵĦ���ֵ
 #define FOC__EBET						*(_IO  int16 xdata *)0x40d2			   // RV:0000H	���������㷴�綯�ƵĦ���ֵ
 #define FOC__EOME						*(_IO  int16 xdata *)0x40d4			   // RV:0000H	������������ٶ�
 #define FOC__UQEX						*(_I   int16 xdata *)0x40d6			   // RV:0000H	Q��ĵ�ѹ���ֵ���������ſ���
 #define FOC_KFG						*(_O  uint16 xdata *)0x40d6			   // RV:0000H	FG����ϵ��
 #define FOC__POW						*(_I   int16 xdata *)0x40d8			   // RV:0000H	�����ǰ���й���
 #define FOC_EOMEKLPF					*(_O   uint8 xdata *)0x40d8			   // RV:0000H	EOMELPF���˲�ϵ��
 #define FOC__IAMAX						*(_I   int16 xdata *)0x40da			   // RV:0000H	A��������ֵ
 #define FOC__IBMAX						*(_I   int16 xdata *)0x40dc			   // RV:0000H	B��������ֵ
 #define FOC__ICMAX						*(_I   int16 xdata *)0x40de			   // RV:0000H	C��������ֵ
/******************************************************************************///TIM1
 #define TIM1_CR0						*(_IO  uint8 xdata *)0x4068			   // RV:  00H	TIMER1���ƼĴ���0
 #define T1RWEN									  0x80							//				 r0w- T1RCEN��������
 #define T1CFLT1								  0x40							//				 rw-- �����˲�����1
 #define T1CFLT0								  0x20							//				 rw-- �����˲�����0
 #define T1FORC									  0x10							//				 rw-- 60��ǿ�ƻ���
 #define T1OPS1									  0x08							//				 rw-- ���ݴ��䷽ʽ����1
 #define T1OPS0									  0x04							//				 rw-- ���ݴ��䷽ʽ����0
 #define T1BCEN									  0x02							//				 rw-- ������ʱ������ʹ��
 #define T1RCEN									  0x01							//				 rw-- ���ض�ʱ������ʹ��

 #define TIM1_CR1						*(_IO  uint8 xdata *)0x4069			   // RV:  00H	TIMER1���ƼĴ���1
 #define T1BAPE									  0x80							//				 rw-- TIM1__BARR�Զ�װ��ʹ��

 #define TIM1_CR2						*(_IO  uint8 xdata *)0x406a			   // RV:  00H	TIMER1���ƼĴ���2
 #define T1BRS									  0x80							//				 rw-- ������ʱ����λԴѡ��

 #define TIM1_CR3						*(_IO  uint8 xdata *)0x406b			   // RV:  00H	TIMER1���ƼĴ���3
 #define T1AFL									  0x80							//
 #define T1PSC2									  0x40							//				 rw-- ��ʱ����Ƶ����2
 #define T1PSC1									  0x20							//				 rw-- ��ʱ����Ƶ����1
 #define T1PSC0									  0x10							//				 rw-- ��ʱ����Ƶ����0
 #define T1TIS1									  0x08							//				 rw-- ����Դѡ������1
 #define T1TIS0									  0x04							//				 rw-- ����Դѡ������0
 #define T1INM1									  0x02							//				 rw-- ����Դ�����˲�����1
 #define T1INM0									  0x01							//				 rw-- ����Դ�����˲�����0

 #define TIM1_CR4						*(_IO  uint8 xdata *)0x406c			   // RV:  00H	TIMER1���ƼĴ���4
 #define T1CST2									  0x04							//				 rw-- ����״̬������2
 #define T1CST1									  0x02							//				 rw-- ����״̬������1
 #define T1CST0									  0x01							//				 rw-- ����״̬������0

 #define TIM1_IER						*(_IO  uint8 xdata *)0x406d			   // RV:  00H	TIMER1�жϿ���
 #define T1UPD									  0x80							//				 r0w- OPS=00ʱ���������ݴ���
 #define T1MAME									  0x40							//
 #define T1ADIE									  0x20							//
 #define T1BOIE									  0x10							//				 rw-- ������ʱ�������ж�ʹ��
 #define T1ROIE									  0x08							//				 rw-- ���ض�ʱ�������ж�ʹ��
 #define T1WTIE									  0x04							//				 rw-- д��ʱ���ж�ʹ��
 #define T1PDIE									  0x02							//				 rw-- λ�ü���ж�ʹ��
 #define T1BDIE									  0x01							//				 rw-- �������������ж�ʹ��

 #define TIM1_SR						*(_IO  uint8 xdata *)0x406e			   // RV:  00H	TIMER1״̬
 #define T1ADIF									  0x20							//
 #define T1BOIF									  0x10							//				 rw0- ������ʱ�������жϱ�־
 #define T1ROIF									  0x08							//				 rw0- ���ض�ʱ�������жϱ�־
 #define T1WTIF									  0x04							//				 rw0- д��ʱ���жϱ�־
 #define T1PDIF									  0x02							//				 rw0- λ�ü���жϱ�־
 #define T1BDIF									  0x01							//				 rw0- �������������жϱ�־

 #define TIM1_DBR1						*(_IO uint16 xdata *)0x4074			   // RV:0000H	TIMER1��CST=1������
 #define TIM1_DBR2						*(_IO uint16 xdata *)0x4076			   // RV:0000H	TIMER1��CST=2������
 #define TIM1_DBR3						*(_IO uint16 xdata *)0x4078			   // RV:0000H	TIMER1��CST=3������
 #define TIM1_DBR4						*(_IO uint16 xdata *)0x407a			   // RV:0000H	TIMER1��CST=4������
 #define TIM1_DBR5						*(_IO uint16 xdata *)0x407c			   // RV:0000H	TIMER1��CST=5������
 #define TIM1_DBR6						*(_IO uint16 xdata *)0x407e			   // RV:0000H	TIMER1��CST=6������
 #define TIM1_DBR7						*(_IO uint16 xdata *)0x4080			   // RV:0000H	TIMER1��CST=7������
 #define T1CPE2									  0x4000						//				 rw-- �����ؼ��ԺͱȽ���ѡ������2
 #define T1CPE1									  0x2000						//				 rw-- �����ؼ��ԺͱȽ���ѡ������1
 #define T1CPE0									  0x1000						//				 rw-- �����ؼ��ԺͱȽ���ѡ������0
 #define T1WHP									  0x0800						//				 rw-- W���Ϲ��������
 #define T1WLP									  0x0400						//				 rw-- W���¹��������
 #define T1VHP									  0x0200						//				 rw-- V���Ϲ��������
 #define T1VLP									  0x0100						//				 rw-- V���¹��������
 #define T1UHP									  0x0080						//				 rw-- U���Ϲ��������
 #define T1ULP									  0x0040						//				 rw-- U���¹��������
 #define T1WHE									  0x0020						//				 rw-- W���Ϲ����ʹ��
 #define T1WLE									  0x0010						//				 rw-- W���¹����ʹ��
 #define T1VHE									  0x0008						//				 rw-- V���Ϲ����ʹ��
 #define T1VLE									  0x0004						//				 rw-- V���¹����ʹ��
 #define T1UHE									  0x0002						//				 rw-- U���Ϲ����ʹ��
 #define T1ULE									  0x0001						//				 rw-- U���¹����ʹ��

 #define TIM1_BCOR						*(_IO uint16 xdata *)0x4070			   // RV:0000H	���������ʱ������ֵ�˲�ֵ
 #define TIM1__BCNTR					*(_IO uint16 xdata *)0x4082			   // RV:0000H	������ʱ������ֵ
 #define TIM1__BCCR						*(_IO uint16 xdata *)0x4084			   // RV:0000H	���������ʱ������ֵ
 #define TIM1__BARR						*(_IO uint16 xdata *)0x4086			   // RV:0000H	������ʱ���Զ�����ֵ
 #define TIM1__RARR						*(_IO uint16 xdata *)0x4088			   // RV:0000H	���ض�ʱ���Զ�����ֵ
 #define TIM1__RCNTR					*(_IO uint16 xdata *)0x408a			   // RV:0000H	���ض�ʱ������ֵ
 #define TIM1__ITRIP					*(_I  uint16 xdata *)0x4098			   // RV:0000H	�˲����ĸ�ߵ���
 #define TIM1__UCOP						*(_IO uint16 xdata *)0x408c
 #define TIM1__UFLP						*(_IO uint16 xdata *)0x408e
 #define TIM1__URES						*(_IO uint16 xdata *)0x4090
 #define TIM1__UIGN						*(_IO uint16 xdata *)0x4092
 #define TIM1_KF						*(_IO uint16 xdata *)0x4094
 #define TIM1_KR						*(_IO uint16 xdata *)0x4096
/******************************************************************************///TIM2
 //sfr	   TIM2_CR0						  =	0xa1;								  // RV:  00H  TIMER2���ƼĴ���0
 SFR(TIM2_CR0, 0xa1);
 #define T2PSC2									  0x80							//				 rw-- ��ʱ����Ƶ����2
 #define T2PSC1									  0x40							//				 rw-- ��ʱ����Ƶ����1
 #define T2PSC0									  0x20							//				 rw-- ��ʱ����Ƶ����0
 #define T2OCM									  0x10							//				 rw-- ��ʱ���Ƚ�ƥ��ģʽ/QEP&����ģʽ����
 #define T2IRE									  0x08							//				 rw-- �Ƚ�ƥ��/������/����ı��ж�ʹ��
 #define T2CES									  0x04							//				 rw-- ����ģʽѡ��
 #define T2MOD1									  0x02							//				 rw-- ��ʱ��ģʽ����1
 #define T2MOD0									  0x01							//				 rw-- ��ʱ��ģʽ����0

 //sfr	   TIM2_CR1						  =	0xa9;								  // RV:  00H  TIMER2���ƼĴ���1
  SFR(TIM2_CR1,	0xa9);
 #define T2IR									  0x80							//				 rw0- �Ƚ�ƥ���־
 #define T2IP									  0x40							//				 rw0- ���ڼ��/����ƥ���־
 #define T2IF									  0x20							//				 rw0- ���������־
 #define T2IPE									  0x10							//				 rw-- ���ڼ��/����ƥ���ж�ʹ��
 #define T2IFE									  0x08							//				 rw-- �����ж�ʹ��
 #define T2FE									  0x04							//				 rw-- �����˲�ʹ��
 #define T2DIR									  0x02							//				 r--- QEP/���������ź�
 #define T2CEN									  0x01							//				 rw-- ��ʱ��ʹ��

 //sfr16   TIM2__DR						  =	0xac;								  // RV:0000H  TIMER2ƥ��ֵ
 //sfr16   TIM2__ARR					  =	0xae;								  // RV:0000H  TIMER2����ֵ
 //sfr16   TIM2__CNTR					  =	0xaa;								  // RV:0000H  TIMER2����ֵ
 SFR16(TIM2__DR,   0xac);
 SFR16(TIM2__ARR,  0xae);
 SFR16(TIM2__CNTR, 0xaa);
/******************************************************************************///TIM3
 //sfr	   TIM3_CR0						  =	0x9c;								  // RV:  00H  TIMER3���ƼĴ���0
 SFR(TIM3_CR0, 0x9c);
 #define T3PSC2									  0x80							//				 rw-- ��ʱ����Ƶ����2
 #define T3PSC1									  0x40							//				 rw-- ��ʱ����Ƶ����1
 #define T3PSC0									  0x20							//				 rw-- ��ʱ����Ƶ����0
 #define T3OCM									  0x10							//				 rw-- ��ʱ���Ƚ�ƥ��/��������ģʽ����
 #define T3IRE									  0x08							//				 rw-- �Ƚ�ƥ��/���������ж�
 #define T3OPM									  0x02							//				 rw-- ����ģʽʹ��
 #define T3MOD									  0x01							//				 rw-- ��ʱ��ģʽ����0

 //sfr	   TIM3_CR1						  =	0x9d;								  // RV:  00H  TIMER3���ƼĴ���1
 SFR(TIM3_CR1, 0x9d);
 #define T3IR									  0x80							//				 rw0- �Ƚ�ƥ��/���������־
 #define T3IP									  0x40							//				 rw0- ���ڼ���־
 #define T3IF									  0x20							//				 rw0- ���������־
 #define T3IPE									  0x10							//				 rw-- ���ڼ���ж�ʹ��
 #define T3IFE									  0x08							//				 rw-- �����ж�ʹ��
 #define T3NM1									  0x04							//				 rw-- �����˲�����1
 #define T3NM0									  0x02							//				 rw-- �����˲�����0
 #define T3EN									  0x01							//				 rw-- ��ʱ��ʹ��

 //sfr16   TIM3__DR						  =	0xa4;								  // RV:0000H  TIMER3ƥ��ֵ
 //sfr16   TIM3__ARR					  =	0xa6;								  // RV:0000H  TIMER3����ֵ
 //sfr16   TIM3__CNTR					  =	0xa2;								  // RV:0000H  TIMER3����ֵ
 SFR16(TIM3__DR,   0xa4);
 SFR16(TIM3__ARR,  0xa6);
 SFR16(TIM3__CNTR, 0xa2);
/******************************************************************************///TIM4
 //sfr	   TIM4_CR0						  =	0x9e;								  // RV:  00H  TIMER4���ƼĴ���0
 SFR(TIM4_CR0, 0x9e);	
 #define T4PSC2									  0x80							//				 rw-- ��ʱ����Ƶ����2
 #define T4PSC1									  0x40							//				 rw-- ��ʱ����Ƶ����1
 #define T4PSC0									  0x20							//				 rw-- ��ʱ����Ƶ����0
 #define T4OCM									  0x10							//				 rw-- ��ʱ���Ƚ�ƥ��/��������ģʽ����
 #define T4IRE									  0x08							//				 rw-- �Ƚ�ƥ��/���������ж�
 #define T4OPM									  0x02							//				 rw-- ����ģʽʹ��
 #define T4MOD									  0x01							//				 rw-- ��ʱ��ģʽ����0

 //sfr	   TIM4_CR1						  =	0x9f;								  // RV:  00H  TIMER4���ƼĴ���1
 SFR(TIM4_CR1, 0x9f);
 #define T4IR									  0x80							//				 rw0- �Ƚ�ƥ��/���������־
 #define T4IP									  0x40							//				 rw0- ���ڼ���־
 #define T4IF									  0x20							//				 rw0- ���������־
 #define T4IPE									  0x10							//				 rw-- ���ڼ���ж�ʹ��
 #define T4IFE									  0x08							//				 rw-- �����ж�ʹ��
 #define T4NM1									  0x04							//				 rw-- �����˲�����1
 #define T4NM0									  0x02							//				 rw-- �����˲�����0
 #define T4EN									  0x01							//				 rw-- ��ʱ��ʹ��

 //sfr16   TIM4__DR						  =	0x94;								  // RV:0000H  TIMER4ƥ��ֵ
 //sfr16   TIM4__ARR					  =	0x96;								  // RV:0000H  TIMER4����ֵ
 //sfr16   TIM4__CNTR					  =	0x92;								  // RV:0000H  TIMER4����ֵ
 SFR16(TIM4__DR,   0x94);
 SFR16(TIM4__ARR,  0x96);
 SFR16(TIM4__CNTR, 0x92);
/******************************************************************************///SYSTICK
 #define SYST_ARR						*(_IO uint16 xdata *)0x4064			   // RV:5dbfH	SysTick����ֵ
/******************************************************************************///DRV
 //sfr	   DRV_OUT						  =	0xf8;								  // RV:  00H  ����������ƼĴ���
// sbit	   MOE										= DRV_OUT^7;				  //			   rw--	�����ʹ��
// sbit	   OISWL									= DRV_OUT^5;				  //			   rw--	WL & XL������е�ƽ
// sbit	   OISWH									= DRV_OUT^4;				  //			   rw--	WH & XH������е�ƽ
// sbit	   OISVL									= DRV_OUT^3;				  //			   rw--	VL������е�ƽ
// sbit	   OISVH									= DRV_OUT^2;				  //			   rw--	VH������е�ƽ
// sbit	   OISUL									= DRV_OUT^1;				  //			   rw--	UL������е�ƽ
// sbit	   OISUH									= DRV_OUT^0;				  //			   rw--	UH������е�ƽ
SFR(DRV_OUT, 0xf8);
	SBIT(MOE,	0xf8, 7);
	SBIT(OISWL,	0xf8, 5);
	SBIT(OISWH,	0xf8, 4);
	SBIT(OISVL,	0xf8, 3);
	SBIT(OISVH,	0xf8, 2);
	SBIT(OISUL,	0xf8, 1);
	SBIT(OISUH,	0xf8, 0);
 	
 #define DRV_DR							*(_IO uint16 xdata *)0x4058			   // RV:0000H	�ֶ��������ʱ�趨�ıȽ�ֵ
 #define DRV_COMR						*(_IO uint16 xdata *)0x405a			   // RV:0000H	�������ıȽ�ƥ��ֵ

 #define DRV_CMR						*(_IO uint16 xdata *)0x405c			   // RV:0000H	������üĴ���
 #define WHP									  0x0800						//				 rw-- W���Ϲ��������
 #define WLP									  0x0400						//				 rw-- W���¹��������
 #define VHP									  0x0200						//				 rw-- V���Ϲ��������
 #define VLP									  0x0100						//				 rw-- V���¹��������
 #define UHP									  0x0080						//				 rw-- U���Ϲ��������
 #define ULP									  0x0040						//				 rw-- U���¹��������
 #define WHE									  0x0020						//				 rw-- W���Ϲ����ʹ��
 #define WLE									  0x0010						//				 rw-- W���¹����ʹ��
 #define VHE									  0x0008						//				 rw-- V���Ϲ����ʹ��
 #define VLE									  0x0004						//				 rw-- V���¹����ʹ��
 #define UHE									  0x0002						//				 rw-- U���Ϲ����ʹ��
 #define ULE									  0x0001						//				 rw-- U���¹����ʹ��

 #define DRV_ARR						*(_IO uint16 xdata *)0x405e			   // RV:0000H	����������ֵ
 #define DRV_DTR						*(_IO  uint8 xdata *)0x4060			   // RV:  00H	���¹�����ʱ��
 #define DRV_CNTR						*(_IO uint16 xdata *)0x4067			   // RV:0000H	������ֵ

 #define DRV_SR							*(_IO  uint8 xdata *)0x4061			   // RV:  00H	Driver״̬�Ĵ���
 #define SYSTIF									  0x80							//				 rw0- SysTick�жϱ�־
 #define SYSTIE									  0x40							//				 rw-- SysTick�ж�ʹ��
 #define FGIF									  0x20							//				 rw0- FG�жϱ�־
 #define DCIF									  0x10							//				 rw0- �Ƚ�ƥ���жϱ�־
 #define FGIE									  0x08							//				 rw-- FG�ж�ʹ��
 #define DCIP									  0x04							//				 rw-- �����Ƚ�ƥ���жϵļ��
 #define DCIM1									  0x02							//				 rw-- �Ƚ�ƥ���ж�ģʽ����1
 #define DCIM0									  0x01							//				 rw-- �Ƚ�ƥ���ж�ģʽ����0

 #define DRV_CR							*(_IO  uint8 xdata *)0x4062			   // RV:  00H	Driver���ƼĴ���
 #define DRVEN									  0x80							//				 rw-- ������ʹ��
 #define DDIR									  0x40							//				 rw-- �������
 #define FOCEN									  0x20							//				 rw-- FOC/SVPWM/SPWMģ��ʹ��
 #define DRPE									  0x10							//				 rw-- DRV_DRԤװ��ʹ��
 #define OCS									  0x08							//				 rw-- �Ƚ�ֵ��Դѡ��
 #define MESEL									  0x04							//				 rw-- ME�˹���ģʽѡ��
 #define DRVOE									  0x01							//				 rw-- Driver���ʹ��
/******************************************************************************///WDT
#define	CCFG1							*(_O   uint8 xdata *)0x401E				  // RV:  00H  
 #define	LVWIE								  0x40							//				 rw-- LVW(low voltage warning) detect interrupt enable
#define	WDT_EN									  0x20							//				 rw-- WDTʹ��
 
 #define WDT_CR							*(_IO  uint8 xdata *)0x4026			   // RV:  00H	���Ź����ƼĴ���
 #define WDTF									  0x02							//				 rw0- ���Ź���λ��־
 #define WDTRF									  0x01							//				 rw-- ���Ź���ʼ����־

 #define WDT_ARR						*(_IO  uint8 xdata *)0x4027			   // RV:  00H	���Ź����ؼ�����
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
 	
 //sfr	   P0_OE						  =	0xfc;								  // RV:  00H  P0���ʹ�ܼĴ���
 SFR(P0_OE,	0xfc);
 #define P0_PU							*(_IO  uint8 xdata *)0x4053			   // RV:  00H	P0����ʹ�ܼĴ���
 #define P07									  0x80							//				 rw-- ʹ�ܶ˿�7
 #define P06									  0x40							//				 rw-- ʹ�ܶ˿�6
 #define P05									  0x20							//				 rw-- ʹ�ܶ˿�5
 #define P04									  0x10							//				 rw-- ʹ�ܶ˿�4
 #define P03									  0x08							//				 rw-- ʹ�ܶ˿�3
 #define P02									  0x04							//				 rw-- ʹ�ܶ˿�2
 #define P01									  0x02							//				 rw-- ʹ�ܶ˿�1
 #define P00									  0x01							//				 rw-- ʹ�ܶ˿�0

// sfr	   P1_IE						  =	0xd1;								  // RV:  00H  P1�ⲿ�ж�ʹ�ܼĴ���
// sfr	   P1_IF						  =	0xd2;								  // RV:  00H  P1�ⲿ�ж�״̬�Ĵ���
// sfr	   P1_OE						  =	0xfd;								  // RV:  00H  P1���ʹ�ܼĴ���
 SFR(P1_IE,	0xd1);
 SFR(P1_IF,	0xd2);
 SFR(P1_OE,	0xfd);
 #define P1_PU							*(_IO  uint8 xdata *)0x4054			   // RV:  00H	P1����ʹ�ܼĴ���
 #define P17									  0x80							//				 rw-- ʹ�ܶ˿�7
 #define P16									  0x40							//				 rw-- ʹ�ܶ˿�6
 #define P15									  0x20							//				 rw-- ʹ�ܶ˿�5
 #define P14									  0x10							//				 rw-- ʹ�ܶ˿�4
 #define P13									  0x08							//				 rw-- ʹ�ܶ˿�3
 #define P12									  0x04							//				 rw-- ʹ�ܶ˿�2
 #define P11									  0x02							//				 rw-- ʹ�ܶ˿�1
 #define P10									  0x01							//				 rw-- ʹ�ܶ˿�0

 #define P1_AN							*(_IO  uint8 xdata *)0x4050			   // RV:  00H	P1ģ��ʹ�ܼĴ���
 #define P17									  0x80							//				 rw-- ʹ�ܶ˿�7
 #define P16									  0x40							//				 rw-- ʹ�ܶ˿�6
 #define P15									  0x20							//				 rw-- ʹ�ܶ˿�5
 #define P14									  0x10							//				 rw-- ʹ�ܶ˿�4
 #define HBMOD									  0x08							//				 rw-- �˿�3ģʽ����
 #define ODE1									  0x02							//				 rw-- P01©����·ʹ��
 #define ODE0									  0x01							//				 rw-- P00©����·ʹ��

// sfr	   P2_IE						  =	0xd3;								  // RV:  00H  P2�ⲿ�ж�ʹ�ܼĴ���
// sfr	   P2_IF						  =	0xd4;								  // RV:  00H  P2�ⲿ�ж�״̬�Ĵ���
// sfr	   P2_OE						  =	0xfe;								  // RV:  00H  P2���ʹ�ܼĴ���
 SFR(P2_IE,	0xd3);
 SFR(P2_IF,	0xd4);
 SFR(P2_OE,	0xfe);
 #define P2_PU							*(_IO  uint8 xdata *)0x4055			   // RV:  00H	P2����ʹ�ܼĴ���
 #define P2_AN							*(_IO  uint8 xdata *)0x4051			   // RV:  00H	P2ģ��ʹ�ܼĴ���
 #define P27									  0x80							//				 rw-- ʹ�ܶ˿�7
 #define P26									  0x40							//				 rw-- ʹ�ܶ˿�6
 #define P25									  0x20							//				 rw-- ʹ�ܶ˿�5
 #define P24									  0x10							//				 rw-- ʹ�ܶ˿�4
 #define P23									  0x08							//				 rw-- ʹ�ܶ˿�3
 #define P22									  0x04							//				 rw-- ʹ�ܶ˿�2
 #define P21									  0x02							//				 rw-- ʹ�ܶ˿�1
 #define P20									  0x01							//				 rw-- ʹ�ܶ˿�0

 //sfr	   P3_OE						  =	0xff;								  // RV:  00H  P3���ʹ�ܼĴ���
 SFR(P3_OE,	0xff);
 #define P3_PU							*(_IO  uint8 xdata *)0x4056			   // RV:  00H	P3����ʹ�ܼĴ���
 #define P37									  0x80							//				 rw-- ʹ�ܶ˿�7
 #define P36									  0x40							//				 rw-- ʹ�ܶ˿�6
 #define P35									  0x20							//				 rw-- ʹ�ܶ˿�5
 #define P34									  0x10							//				 rw-- ʹ�ܶ˿�4
 #define P33									  0x08							//				 rw-- ʹ�ܶ˿�3
 #define P32									  0x04							//				 rw-- ʹ�ܶ˿�2
 #define P31									  0x02							//				 rw-- ʹ�ܶ˿�1
 #define P30									  0x01							//				 rw-- ʹ�ܶ˿�0

 #define P3_AN							*(_IO  uint8 xdata *)0x4052			   // RV:  00H	P3ģ��ʹ�ܼĴ���
 #define P11_PL									  0x80							//				 rw-- P11����ʹ��
 #define P01_PL									  0x40							//				 rw-- P01����ʹ��
 #define P35									  0x20							//				 rw-- ʹ�ܶ˿�5
 #define P34									  0x10							//				 rw-- ʹ�ܶ˿�4
 #define P33									  0x08							//				 rw-- ʹ�ܶ˿�3
 #define P32									  0x04							//				 rw-- ʹ�ܶ˿�2
 #define P31									  0x02							//				 rw-- ʹ�ܶ˿�1
 #define P30									  0x01							//				 rw-- ʹ�ܶ˿�0

 //sfr	   P4_OE						  =	0xe9;								  // RV:  00H  P4���ʹ�ܼĴ���
 SFR(P4_OE,	0xe9);
 #define P4_PU							*(_IO  uint8 xdata *)0x4057			   // RV:  00H	P4����ʹ�ܼĴ���
 #define P45									  0x20							//				 rw-- ʹ�ܶ˿�5
 #define P44									  0x10							//				 rw-- ʹ�ܶ˿�4
 #define P43									  0x08							//				 rw-- ʹ�ܶ˿�3
 #define P42									  0x04							//				 rw-- ʹ�ܶ˿�2

 #define PIN7									  0x80							//				 rw-- PIN7,	�����������Ķ˿ڱ��
 #define PIN6									  0x40							//				 rw-- PIN6,	�����������Ķ˿ڱ��
 #define PIN5									  0x20							//				 rw-- PIN5,	�����������Ķ˿ڱ��
 #define PIN4									  0x10							//				 rw-- PIN4,	�����������Ķ˿ڱ��
 #define PIN3									  0x08							//				 rw-- PIN3,	�����������Ķ˿ڱ��
 #define PIN2									  0x04							//				 rw-- PIN2,	�����������Ķ˿ڱ��
 #define PIN1									  0x02							//				 rw-- PIN1,	�����������Ķ˿ڱ��
 #define PIN0									  0x01							//				 rw-- PIN0,	�����������Ķ˿ڱ��

 #define PH_SEL							*(_IO  uint8 xdata *)0x404c			   // RV:  00H	�˿ڸ���
 #define SPITMOD								  0x80							//				 rw-- SPI�ӻ����Ͷ��ڷ�����ɺ��Ϊ����̬
 #define UART1EN								  0x40							//				 rw-- �˿ڸ���ΪUART
 #define UART2EN								  0x20							//				 rw-- UART�˿ڹ���ת��
 #define T4SEL									  0x10							//				 rw-- �˿ڸ���ΪTIM4
 #define T3SEL									  0x08							//				 rw-- �˿ڸ���ΪTIM3
 #define T2SEL									  0x04							//				 rw-- �˿ڸ���ΪTIM2
 #define T2SSEL									  0x02							//				 rw-- �˿ڸ���ΪTIM2S
 #define XOE									  0x01							//				 rw-- �˿ڸ���ΪX��������

 #define PH_SEL1						*(_IO  uint8 xdata *)0x404d			   // RV:  00H	�˿ڸ���
 #define SPICT									  0x04							//				 rw-- SPI����ת��
 #define T4CT									  0x02							//				 rw-- TIM4����ת��
 #define T3CT									  0x01							//				 rw-- TIM3����ת��

/******************************************************************************///ADC
 #define ADC_MASK						*(_IO uint16 xdata *)0x4036			   // RV:3000H	ADCͨ��ʹ�ܺͲ���ͨ������ʱ������
 #define CH14EN									  0x4000						//				 rw-- ADCͨ��14ʹ��
 #define CH13EN									  0x2000						//				 rw-- ADCͨ��13ʹ��
 #define CH12EN									  0x1000						//				 rw-- ADCͨ��12ʹ��
 #define CH11EN									  0x0800						//				 rw-- ADCͨ��11ʹ��
 #define CH10EN									  0x0400						//				 rw-- ADCͨ��10ʹ��
 #define CH9EN									  0x0200						//				 rw-- ADCͨ��9ʹ��
 #define CH8EN									  0x0100						//				 rw-- ADCͨ��8ʹ��
 #define CH7EN									  0x0080						//				 rw-- ADCͨ��7ʹ��
 #define CH6EN									  0x0040						//				 rw-- ADCͨ��6ʹ��
 #define CH5EN									  0x0020						//				 rw-- ADCͨ��5ʹ��
 #define CH4EN									  0x0010						//				 rw-- ADCͨ��4ʹ��
 #define CH3EN									  0x0008						//				 rw-- ADCͨ��3ʹ��
 #define CH2EN									  0x0004						//				 rw-- ADCͨ��2ʹ��
 #define CH1EN									  0x0002						//				 rw-- ADCͨ��1ʹ��
 #define CH0EN									  0x0001						//				 rw-- ADCͨ��0ʹ��

 #define ADC_SYSC						*(_IO  uint8 xdata *)0x4038			   // RV:  33H	ADCͨ������ʱ������

 #define ADC_CR							*(_IO  uint8 xdata *)0x4039			   // RV:  00H	ADC���ƼĴ���
 #define ADCEN									  0x80							//				 rw-- ʹ��ADC
 #define ADCBSY									  0x40							//				 rw1- ADC���� &	ADCæ��־
 #define ADCRATIO								  0x20							//				 rw-- AD14��VCC��ѹʹ�õķ�ѹ��
 #define ADCTM1									  0x10							//				 rw-- DRV����ADC����ģʽ
 #define ADCTM0									  0x08							//				 rw-- 00������01������10�½���11˫��
 #define ADCALIGN								  0x04							//				 rw-- ADC���ݴθ�λ����
 #define ADCIE									  0x02							//				 rw-- ADC�ж�ʹ��
 #define ADCIF									  0x01							//				 rw-- ADC�жϱ�־

 #define ADC0_DR						*(_I  uint16 xdata *)0x0300			   // RV:0000H	ADCͨ��0ת�����
 #define ADC1_DR						*(_I  uint16 xdata *)0x0302			   // RV:0000H	ADCͨ��1ת�����
 #define ADC2_DR						*(_I  uint16 xdata *)0x0304			   // RV:0000H	ADCͨ��2ת�����
 #define ADC3_DR						*(_I  uint16 xdata *)0x0306			   // RV:0000H	ADCͨ��3ת�����
 #define ADC4_DR						*(_I  uint16 xdata *)0x0308			   // RV:0000H	ADCͨ��4ת�����
 #define ADC5_DR						*(_I  uint16 xdata *)0x030a			   // RV:0000H	ADCͨ��5ת�����
 #define ADC6_DR						*(_I  uint16 xdata *)0x030c			   // RV:0000H	ADCͨ��6ת�����
 #define ADC7_DR						*(_I  uint16 xdata *)0x030e			   // RV:0000H	ADCͨ��7ת�����
 #define ADC8_DR						*(_I  uint16 xdata *)0x0310			   // RV:0000H	ADCͨ��8ת�����
 #define ADC9_DR						*(_I  uint16 xdata *)0x0312			   // RV:0000H	ADCͨ��9ת�����
 #define ADC10_DR						*(_I  uint16 xdata *)0x0314			   // RV:0000H	ADCͨ��10ת�����
 #define ADC11_DR						*(_I  uint16 xdata *)0x0316			   // RV:0000H	ADCͨ��11ת�����
 #define ADC12_DR						*(_I  uint16 xdata *)0x0318			   // RV:0000H	ADCͨ��12ת�����
 #define ADC13_DR						*(_I  uint16 xdata *)0x031a			   // RV:0000H	ADCͨ��13ת�����
 #define ADC14_DR						*(_I  uint16 xdata *)0x031c			   // RV:0000H	ADCͨ��14ת�����
/*****************************************************************************///DAC
 #define DAC_CR							*(_IO  uint8 xdata *)0x4035			   // RV:  00H	DAC���ƼĴ���
 #define DAC0_1EN								  0x80							//				 rw-- DAC0&1ʹ��
 #define DACMOD									  0x40							//				 rw-- DACģʽ����
 #define ADC_SYSCH3								  0x20							// ADC_SYSCH[3:0]
 #define ADC_SYSCH2								  0x10							// CH8/9/10/11/12/13����ʱ������
 #define ADC_SYSCH1								  0x08							//
 #define ADC_SYSCH0								  0x04							//

 #define DAC0_DR						 *(_IO	uint8 xdata *)0x404b				// RV:	00H	 DAC0���ֵ[8:1]
 #define DAC1_DR						 *(_IO	uint8 xdata *)0x404A				// RV:	00H	 DAC1���ֵ
 #define DAC0_DR_0								  0x80							 //	RV:	 00H  DAC0���ֵ[0]

/******************************************************************************///DMA
 #define DMA0_CR0						*(_IO  uint8 xdata *)0x403a			   // RV:  00H	DMAͨ��0���� & DMA��������
 #define DMA1_CR0						*(_IO  uint8 xdata *)0x403b			   // RV:  00H	DMAͨ��1���� & Debug����
 #define DMAEN									  0x80							//				 rw-- DMAͨ��0/1ʹ��
 #define DMABSY									  0x40							//				 rw1- DMAͨ��0/1״̬/����
 #define DMACFG2								  0x20							//				 rw-- DMAͨ��0/1�����뷽��ѡ��λ2
 #define DMACFG1								  0x10							//				 rw-- DMAͨ��0/1�����뷽��ѡ��λ1
 #define DMACFG0								  0x08							//				 rw-- DMAͨ��0/1�����뷽��ѡ��λ0
 #define DBGSW									  0x04							//				 rw-- DMAͨ��1	DBGģʽָ������
 #define DBGEN									  0x02							//				 rw-- DMAͨ��1	DBGģʽʹ��
 #define DMAIE									  0x04							//				 rw-- DMA�ж�ʹ��,λ��DMA_CR0
 #define ENDIAN									  0x02							//				 rw-- DMA���ݴ���˳��,λ��DMA_CR0
 #define DMAIF									  0x01							//				 rw0- DMAͨ��0/1�жϱ�־λ

 #define DMA0_LEN						*(_IO  uint8 xdata *)0x403c			   // RV:  00H	DMAͨ��0���䳤������
 #define DMA1_LEN						*(_IO  uint8 xdata *)0x403d			   // RV:  00H	DMAͨ��1���䳤������

 #define DMA0_BA						*(_IO uint16 xdata *)0x403e			   // RV:0000H	DMAͨ��0�����ַ����
 #define DMA1_BA						*(_IO uint16 xdata *)0x4040			   // RV:0000H	DMAͨ��1�����ַ����
/******************************************************************************///VREF & VHALF
 #define VREF_VHALF_CR					*(_IO  uint8 xdata *)0x404f			   // RV:  00H	VREF & VHALF���ƼĴ���
 #define VRVSEL1								  0x80							//				 rw-- VREF��ѹ����1
 #define VRVSEL0								  0x40							//				 rw-- VREF��ѹ����0
 #define VREFEN									  0x10							//				 rw-- VREFʹ��
 #define VHALFEN								  0x01							//				 rw-- VHALFʹ��
/******************************************************************************///AMP
 #define AMP0_GAIN						*(_IO  uint8 xdata *)0x4034			   // RV:  00H	AMP0 PGA SET
 #define AMP0_GAIN2								  0x04							//				 rw-- AMP0�Ŵ���
 #define AMP0_GAIN1								  0x02							//				 rw-- AMP0�Ŵ���
 #define AMP0_GAIN0								  0x01							//				 rw-- AMP0�Ŵ���
 
 #define AMP_CR							*(_IO  uint8 xdata *)0x404e			   // RV:  00H	�˷ſ��ƼĴ���
 #define AMP2EN									  0x04							//				 rw-- �˷�2ʹ��
 #define AMP1EN									  0x02							//				 rw-- �˷�1ʹ��
 #define AMP0EN									  0x01							//				 rw-- �˷�0ʹ��
/******************************************************************************///CMP
 //sfr	   CMP_CR0						  =	0xd5;								  // RV:  00H  �Ƚ������ƼĴ���0
 SFR(CMP_CR0, 0xd5);
 #define CMP3IM1								  0x80							//				 rw-- CMP3�ж�ģʽ����1
 #define CMP3IM0								  0x40							//				 rw-- CMP3�ж�ģʽ����0
 #define CMP2IM1								  0x20							//				 rw-- CMP2�ж�ģʽ����1
 #define CMP2IM0								  0x10							//				 rw-- CMP2�ж�ģʽ����0
 #define CMP1IM1								  0x08							//				 rw-- CMP1�ж�ģʽ����1
 #define CMP1IM0								  0x04							//				 rw-- CMP1�ж�ģʽ����0
 #define CMP0IM1								  0x02							//				 rw-- CMP0�ж�ģʽ����1
 #define CMP0IM0								  0x01							//				 rw-- CMP0�ж�ģʽ����0

 //sfr	   CMP_CR1						  =	0xd6;								  // RV:  00H  �Ƚ������ƼĴ���1
 SFR(CMP_CR1, 0xd6);
 #define HALLSEL								  0x80							//				 rw-- �����ź�����ѡ��
 #define CMP3MOD1								  0x40							//				 rw-- CMP3�������ѡ������1
 #define CMP3MOD0								  0x20							//				 rw-- CMP3�������ѡ������0
 #define CMP3EN									  0x10							//				 rw-- CMP3ʹ��
 #define CMP3HYS								  0x08							//				 rw-- CMP3����ʹ��
 #define CMP0HYS2								  0x04							//				 rw-- CMP0���͵�ѹ����2
 #define CMP0HYS1								  0x02							//				 rw-- CMP0���͵�ѹ����1
 #define CMP0HYS0								  0x01							//				 rw-- CMP0���͵�ѹ����0

 //sfr	   CMP_CR2						  =	0xda;								  // RV:  00H  �Ƚ������ƼĴ���2
 SFR(CMP_CR2, 0xda);
 #define CMP4EN									  0x80							//				 rw-- CMP4ʹ��
 #define CMP0MOD1								  0x40							//				 rw-- CMP0ģʽ����1
 #define CMP0MOD0								  0x20							//				 rw-- CMP0ģʽ����0
 #define CMP0SEL1								  0x10							//				 rw-- CMP0�˿��������1
 #define CMP0SEL0								  0x08							//				 rw-- CMP0�˿��������0
 #define CMP0CSEL1								  0x04							//				 rw-- CMP0��ѯ�ٶ�����1
 #define CMP0CSEL0								  0x02							//				 rw-- CMP0��ѯ�ٶ�����0
 #define CMP0EN									  0x01							//				 rw-- CMP0ʹ��

 //sfr	   CMP_CR3						  =	0xdc;								  // RV:  00H  �Ƚ������ƼĴ���3
 SFR(CMP_CR3, 0xdc);
 #define CMPDTEN								  0x80							//				 rw-- �Ƚ�����������ʹ��
 #define DBGSEL1								  0x40							//				 rw-- DBG�ź�����1
 #define DBGSEL0								  0x20							//				 rw-- DBG�ź�����0
 #define SAMSEL1								  0x10							//				 rw-- CMP0/1/2 & ADC ����ʱ������1
 #define SAMSEL0								  0x08							//				 rw-- CMP0/1/2 & ADC ����ʱ������0
 #define CMPSEL2								  0x04							//				 rw-- �Ƚ������ѡ������2
 #define CMPSEL1								  0x02							//				 rw-- �Ƚ������ѡ������1
 #define CMPSEL0								  0x01							//				 rw-- �Ƚ������ѡ������0

 //sfr	   CMP_CR4						  =	0xe1;								  // RV:  00H  �Ƚ������ƼĴ���4
 SFR(CMP_CR4, 0xe1);
 #define CMP4OUT								  0x80							//				 rw-- CMP5�ȽϽ��
 #define FAEN									  0x04							//				 rw-- �˲�����ϵ������ʹ��
 #define CMP0_FS								  0x02							//				 rw-- CMP1/2����ת��ʹ��

 //sfr	   CMP_SR						  =	0xd7;								  // RV:  00H  �Ƚ���״̬�Ĵ���
 SFR(CMP_SR, 0xd7);
 #define CMP3IF									  0x80							//				 rw0- CMP3�жϱ�־
 #define CMP2IF									  0x40							//				 rw0- CMP2�жϱ�־
 #define CMP1IF									  0x20							//				 rw0- CMP1�жϱ�־
 #define CMP0IF									  0x10							//				 rw0- CMP0�жϱ�־
 #define CMP3OUT								  0x08							//				 r--- CMP3�ȽϽ��
 #define CMP2OUT								  0x04							//				 r--- CMP2�ȽϽ��
 #define CMP1OUT								  0x02							//				 r--- CMP1�ȽϽ��
 #define CMP0OUT								  0x01							//				 r--- CMP0�ȽϽ��

 //sfr	   EVT_FILT						  =	0xd9;								  // RV:  00H  ������������
 SFR(EVT_FILT, 0xd9);
 #define MOEMD1									  0x10							//				 rw-- MOE�Զ���������1
 #define MOEMD0									  0x08							//				 rw-- MOE�Զ���������0
 #define EFSRC									  0x04							//				 rw-- ĸ�߱����˲�ģ��������Դ
 #define EFDIV1									  0x02							//				 rw-- ĸ�ߵ��������˲�����1
 #define EFDIV0									  0x01							//				 rw-- ĸ�ߵ��������˲�����0

 #define CMP_SAMR						*(_IO  uint8 xdata *)0x40ad			   // RV:  00H	�Ƚ�����������
/******************************************************************************///FLASH
 //sfr	   FLA_KEY						  =	0x84;								  // RV:  00H  FLASH�����Ĵ���
 SFR(FLA_KEY, 0x84);
 #define FLAKSTA1								  0x02							//				 rw-- FLASH����״̬λ1
 #define FLAKSTA0								  0x01							//				 rw-- FLASH����״̬λ0

 //sfr	   FLA_CR						  =	0x85;								  // RV:  00H  FLASH���ƼĴ���
 SFR(FLA_CR, 0x85);
 #define FLAERR									  0x10							//				 r--- FLASH�����־λ
 #define FLAACT									  0x08							//				 rw1- FLASH������ʼ
 #define FLAPRE									  0x04							//				 rw-- FLASHԤ���ʹ��
 #define FLAERS									  0x02							//				 rw-- FLASH���ʹ��
 #define FLAEN									  0x01							//				 rw-- FLASH���ʹ��
/******************************************************************************///CRC
 #define CRC_DIN						*(_O   uint8 xdata *)0x4021			   // RV:  00H	CRC��������Ĵ���

 #define CRC_CR							*(_IO  uint8 xdata *)0x4022			   // RV:	0H	CRC���ƼĴ���
 #define CRCDONE								  0x10							//				 r1-- �Զ�CRC��ɱ�־
 #define CRCDINI								  0x08							//				 r0w1 CRC��ʼ��
 #define CRCVAL									  0x04							//				 rw-- CRC��ʼ����ֵ
 #define AUTOINT								  0x02							//				 rw-- CRC�Զ�����ʹ��
 #define CRCPNT									  0x01							//				 rw-- CRC�������λ��

 #define CRC_DR							*(_IO  uint8 xdata *)0x4023			   // RV:  00H	CRC�������Ĵ���
 #define CRC_BEG						*(_IO  uint8 xdata *)0x4024			   // RV:  00H	CRC�Զ��������ʼλ��
 #define CRC_CNT						*(_IO  uint8 xdata *)0x4025			   // RV:  00H	CRC����������
/******************************************************************************///TSD
 #define TSD_CR							*(_IO  uint8 xdata *)0x402f			   // RV:	0H	TSD���ƼĴ���
 #define TSDEN									  0x80							//				 rw-- TSDʹ��
 #define TSDADJ3								  0x08							//				 rw-- TSD�¶ȵ���
 #define TSDADJ2								  0x04							//				 rw-- TSD�¶ȵ���
 #define TSDADJ1								  0x02							//				 rw-- TSD�¶ȵ���
 #define TSDADJ0								  0x01							//				 rw-- TSD�¶ȵ���
/******************************************************************************///POWER
 //sfr	   PCON							  =	0x87;								  // RV:  00H  MCU���ʿ��ƼĴ���
 SFR(PCON, 0x87);
 #define GF3									  0x20							//				 rw-- ͨ�ñ�־3
 #define GF2									  0x10							//				 rw-- ͨ�ñ�־2
 #define GF1									  0x08							//				 rw-- ͨ�ñ�־1
 #define LDOM									  0x04							//				 rw-- LDO5����ģʽѡ��
 #define STOP									  0x02							//				 rw-- MCU˯��ʹ��
 #define IDLE									  0x01							//				 rw-- MCU����ʹ��

 //sfr	   LVSR							  =	0xdb;								  // RV:  00H  ״̬�Ĵ���
 SFR(LVSR, 0xdb);
 #define EXT0CFG2								  0x20							//				 rw-- �ⲿ�ж�0�˿�����2
 #define EXT0CFG1								  0x10							//				 rw-- �ⲿ�ж�0�˿�����1
 #define EXT0CFG0								  0x08							//				 rw-- �ⲿ�ж�0�˿�����0
 #define TSDF									  0x04							//				 rw-- ���±�־λ
 #define LVWF									  0x02							//				 rw-- VCC�͵�ѹ��־
 #define LVWIF									  0x01							//				 rw-- VCC�͵�ѹ�жϱ�־


#ifdef __cplusplus
}
#endif

#endif	//__FU68XX_4_MCU_H__


/*** (C) Copyright 2022	Fortior	Technology Co.,	Ltd. ***/
