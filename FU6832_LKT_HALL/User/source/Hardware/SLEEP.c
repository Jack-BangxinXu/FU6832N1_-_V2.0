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

#if(0)
SLEEPMODE      xdata SleepSet;

/**
 * @brief     外部中断睡眠引脚设置
 * @date      2022-09-12
 */
void Sleepmode_Init(void)
{
    ClrBit(P1_OE, P11);                     // config P11 as input
    ClrBit(P1_PU, P11);                     // diasable P11 Pull Up
    ClrBit(P1_IF, P11);                     // clear P11 interrupt flag
    ClrBit(P1_IE, P11);                     // config P11 as the source of EXTI1
    IT11 = 1;
    IT10 = 0;                               // 00: posedge mode interrupt，01: negedge mode interrupt，1x: edge-change mode interrupt
    SetBit(IP0, PX11);
    SetBit(IP0, PX10);                      // 中断优先级别0，中断优先级最高
    EX1 = 1;                                // 使能外部中断1, P11位外部中断输入硬件
    EA = 1;                                 // 使能全局中断
}


/**
 * @brief     进入睡眠模式
 * @date      2022-09-12
 */
void Sleepmode(void)
{
    SleepSet.SleepDelayCout++;
    
    if (SleepSet.SleepDelayCout >= 6000) //最大65530，若要再大，需改数据类型
    {
        MotorSpeed.TargetValue = 0;
        MOE     = 0;
        /******睡眠模式初始化**********/
        Sleepmode_Init();
        ClrBit(DRV_CR, FOCEN);  //关闭FOC
        ClrBit(ADC_CR, ADCEN);
        //关闭运放
        ClrBit(AMP_CR, AMP0EN);         //AMP0 Enable
        ClrBit(AMP_CR, AMP1EN);         //AMP1 Enable
        ClrBit(AMP_CR, AMP2EN);         //AMP2 Enable
        //关闭比较器
        ClrBit(CMP_CR1, CMP3EN);    //CMP3 Enable
        //关闭VREF
        SetBit(VREF_VHALF_CR, 0x00);
        SleepSet.SleepDelayCout = 0;
        SleepSet.SleepFlag = 1;
        SetBit(P1_IE, P11);   // config P11 as the source of EXTI1
        SetBit(PCON, STOP);
    }
}

#endif
