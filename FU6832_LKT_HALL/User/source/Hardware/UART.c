/*  -------------------------- (C) COPYRIGHT 2022 Fortiortech ShenZhen ---------------------------*/
/**
 * @copyright (C) COPYRIGHT 2022 Fortiortech Shenzhen
 * @file      xxx.c
 * @author    Fortiortech  Appliction Team
 * @since     Create:2022-09-12
 * @date      Last modify:2022-09-14
 * @note      Last modify author is Leo.li
 * @brief
 */
 
#include <MyProject.h>

/**
 * @brief     UART2的参数设置
 * @date      2022-09-12
 */	
void UART2_Init(void)
{
    SetBit(PH_SEL, UART2EN);    //P3[6]as UART2_RXD; P3[7]as UART2_TXD
    #if 0
    ClrBit(P3_OE, P36);         //输入使能
    SetBit(P3_PU, P36);         //上拉电阻
    SetBit(P3_OE, P37);         //输出使能
    SetBit(P3_PU, P37);         //上拉电阻
    #endif
    ClrBit(UT2_CR, UT2MOD1);    //00-->单线制8bit        01-->8bit uart(波特率可设置)
    SetBit(UT2_CR, UT2MOD0);    //10-->单线制9bit        11-->9bit uart(波特率可设置)
    ClrBit(UT2_CR, UT2SM2);     //0-->单机通讯          1-->多机通讯；
    SetBit(UT2_CR, UT2REN);     //0-->不允许串行输入 1-->允许串行输入，软件清0;
    ClrBit(UT2_CR, UT2TB8);     //模式2/3下数据发送第9位，在多机通信中，可用于判断当前数据帧的数据是地址还是数据，TB8=0为数据，TB8=1为地址
    ClrBit(UT2_CR, UT2RB8);     //模式2/3下数据接收第9位，若SM2=0,作为停止位
    PSPI_UT21 = 0;              //中断优先级时最低
    PSPI_UT20 = 0;
    ClrBit(UT2_BAUD, BAUD2_SEL); //倍频使能0-->Disable  1-->Enable
    ClrBit(UT2_BAUD, UART2CH);   //UART2端口功能转移使能0：P36->RXD P37->TXD 1:P01->RXD P00->TXD
    ClrBit(UT2_BAUD, UART2IEN);  //UART2中断使能0-->Disable  1-->Enable
    UT2_BAUD = 0x000c;           //波特率可设置 = 24000000/(16/(1+ UT_BAUD[BAUD_SEL]))/(UT_BAUD+1)
    //9B-->9600 0x000c-->115200 0x0005-->256000
}


/**
 * @brief     UART1的参数设置
 * @date      2022-09-12
 */	
void UART1_Init(void)
{
    SetBit(PH_SEL , UART1EN);   // P0[6]as UART2_RXD; P0[5]as UART2_TXD
    UT_MOD1 = 0;                // 8bit波特率可变UART模式
    UT_MOD0 = 1;		
    SM2     = 0;                // 
    REN     = 1;		        // 使能接收
    ES0 = 0;                    // 发送/接受中断使能
    UT_BAUD = 0x000C;     
}



/******************************************************
Function	:UartSendChar
Input		:byte-data
Output		:N/A
Return		:N/A
Description	:串口发送字节数据
Note		:这里借助于变量previousStatus先来记住ES的值，
			然后使用轮询法发送字节数据后，再将ES还原到之
			前的状态，这里的previousStatus是非常有必要的。
******************************************************/
void UartSendChar(char dataCode)
{
	bit previousStatus = ES0 ;
	
	ES0 = 0 ;
	
	UT_DR = dataCode ;
	while( !TI ) ;
	TI = 0 ;
	
	ES0 = previousStatus ;
}



#if  1
char putchar(char c)
{
	UartSendChar(c);
	return c; 
}
#endif

void UartSendString( uint8 *str)
{	
	while(*str != '\0') 
	{
		UartSendChar(*str) ;	
			str++;					
	}
}
