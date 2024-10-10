/**************************** (C) COPYRIGHT 2018 Fortiortech Shenzhen ******************************
* File Name          : UART_Debug.c
* Author             : Any Lin
* Version            : V1.0
* Date               : 2018-07-01
* Description        : Based on ANOT
****************************************************************************************************
* All Rights Reserved
***************************************************************************************************/



/**************************************************************************************************///Including Header Files
#include <UART_Debug.h>
/**************************************************************************************************///Define Macro
#define BUFFLEN                         128
/**************************************************************************************************///Define Global Symbols
static unsigned char xdata sg_ucUartDbgData[BUFFLEN] = {0xaa, 0xaa};
static char                sg_cUartDataLen;
static unsigned char       sg_ucUartDataSum;
/**************************************************************************************************///Function Subject
/**
 * 初始化缓存区内容
 *
 * @param Type 输出的指令
 */
void InitBuff_UARTDBG(unsigned char Type)
{
    sg_ucUartDbgData[2] = Type;

    sg_cUartDataLen = 4;

    sg_ucUartDataSum = 0x54 + Type;
}

/**
 * 装载16位数据
 *
 * @param Data 要装载的数据
 */
void LoadBuff16_UARTDBG(unsigned short Data)
{
    union
    {
        unsigned short m_w;
        unsigned char  m_uc[2];
    }uChange;

    uChange.m_w = Data;

    sg_ucUartDbgData[sg_cUartDataLen++] = uChange.m_uc[0];
    sg_ucUartDbgData[sg_cUartDataLen++] = uChange.m_uc[1];

    sg_ucUartDataSum += uChange.m_uc[0] + uChange.m_uc[1];
}

/**
 * 装载8位数据
 *
 * @param Data 要装载数据
 */
void LoadBuff8_UARTDBG(unsigned char Data)
{
    sg_ucUartDbgData[sg_cUartDataLen++] = Data;

    sg_ucUartDataSum += Data;
}

/**
 * 发送前的准备
 *
 * @return  将要发送的字节数
 */
unsigned char SendReady_UARTDBG(void)
{
    sg_ucUartDbgData[3] = sg_cUartDataLen - 4;

    sg_ucUartDataSum += sg_ucUartDbgData[3];

    sg_ucUartDbgData[sg_cUartDataLen] = sg_ucUartDataSum;

    return sg_cUartDataLen;
}

/**
 * 获取缓存区的地址
 *
 * @return  缓存区地址
 */
unsigned char* GetAddr_UARTDBG(void)
{
    return &sg_ucUartDbgData;
}