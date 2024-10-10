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
 * @brief     CMP0初始化
 * @date      2022-09-12
 */	
void CMP0_Init(void)
{
    /* CMP0/1/2 端口模拟功能设置 */
    SetBit(P1_AN, PIN4);    //CMP0 Pin设置为模拟模式  +
    SetBit(P1_AN, PIN6);    //CMP1 Pin设置为模拟模式  +
    SetBit(P2_AN, PIN1);    //CMP2 Pin设置为模拟模式  +
    ClrBit(P1_PU, PIN4);    //P14上拉关闭
    ClrBit(CMP_CR0, CMP2IM1); //CMP2中断模式
    ClrBit(CMP_CR0, CMP2IM0); //00-->No Interrupt  01-->Rising  10-->Falling   11-->Rising/Falling
    ClrBit(CMP_CR0, CMP1IM1); //CMP1中断模式
    ClrBit(CMP_CR0, CMP1IM0); //00-->No Interrupt  01-->Rising  10-->Falling   11-->Rising/Falling
    ClrBit(CMP_CR0, CMP0IM1); //CMP0中断模式
    ClrBit(CMP_CR0, CMP0IM0); //00-->No Interrupt  01-->Rising  10-->Falling   11-->Rising/Falling
    SetBit(CMP_CR1, CMP0HYS2); //CMP0迟滞电压配置
    ClrBit(CMP_CR1, CMP0HYS1); //111-->±12mV   110-->+12mV   101-->-12mV   100-->±6mV
    ClrBit(CMP_CR1, CMP0HYS0); //011-->+6mV    010-->-6mV    001-->±3mV    000-->No HYS
    ClrBit(CMP_CR2, CMP0MOD1); //00-->无内置电阻3比较器             01-->有内置电阻3比较器模式
    SetBit(CMP_CR2, CMP0MOD0); //10-->3差分比较器              11-->2比较器
    ClrBit(CMP_CR2, CMP0SEL1); //00-->3比较器轮询              01-->P14+固定选择CMP0OUT
    ClrBit(CMP_CR2, CMP0SEL0); //10-->P16+固定选择CMP1OUT       11-->P21+固定选择CMP2OUT
    ClrBit(CMP_CR2, CMP0CSEL1); //00-->正常轮询（0.66us）     01-->快速轮询（0.33us）
    ClrBit(CMP_CR2, CMP0CSEL0); //10-->低速轮询（2.67us）     11-->偏低速轮询（1.33us）
    ClrBit(CMP_CR3, CMPSEL2);   //011-->P07作为CMP2输出
    SetBit(CMP_CR3, CMPSEL1);   //010-->P07作为CMP1输出
    SetBit(CMP_CR3, CMPSEL0);   //001-->P07作为CMP0输出
    ClrBit(CMP_CR4, CMP0_FS);   //CMP1/2功能转移    仅CMP0_MOD=01时有效
    SetBit(CMP_CR2, CMP0EN);    //CMP0 Enable
    PCMP1 = 0;
    PCMP0 = 0;
    /* 比较器采样设置 */
    CMP_SAMR = 0x42;    //延迟开启采样时间[7:4]&关闭采样时间[3:0]
    //延迟时间= CSOND x 41.67 x 8ns CSOND 必须>= CSOFFD
    SetBit(CMP_CR3, SAMSEL1);   //CMP0/1/2 & ADC 采样时机配置
    ClrBit(CMP_CR3, SAMSEL0);   //00-->0N&0FF采样，无延迟   01-->0FF采样，延迟CMP_SAMR
    //10-->0N采样，延迟CMP_SAMR    11-->0N&0FF采样，延迟CMP_SAMR
    ClrBit(CMP_CR3, CMPDTEN);   //比较器死区采样使能 0-->Disable 1-->Enable
    ClrBit(CMP_CR3, DBGSEL1);   //DEBUG信号选择-->输出至P01
    SetBit(CMP_CR3, DBGSEL0);   //00-->Disable          01-->方波屏蔽续流结束和检测到过零点信号
    //10-->ADC trigger信号    11-->比较器采样区间
    /* ************************************************************** */
}


/**
 * @brief     比较器3初始化,用于硬件过流保护
 * @date      2022-09-12
 */
void CMP3_Init(void)
{
    /******CMP3 端口模拟功能设置*******/
    #if (Shunt_Resistor_Mode == Single_Resistor)
    {
        SetBit(P2_AN, P27);                           //CMP3 Pin设置为模拟模式  +
        ClrBit(CMP_CR1, CMP3MOD1);                    //00-->P27-单比较器模式    01-->P20/P23-双比较器模式
        ClrBit(CMP_CR1, CMP3MOD0);                    //1X-->P20/P23/P27-三比较器模式
    }
    #elif (Shunt_Resistor_Mode == Double_Resistor)
    {
        SetBit(P2_AN, P27);                           //CMP3 Pin设置为模拟模式  +
        ClrBit(CMP_CR1, CMP3MOD1);                    //00-->P27-单比较器模式    01-->P20/P23-双比较器模式
        ClrBit(CMP_CR1, CMP3MOD0);                    //1X-->P20/P23/P27-三比较器模式
    }
    #elif (Shunt_Resistor_Mode == Three_Resistor)
    {
        SetBit(P2_AN, P27 | P23 | P20);               //CMP3 Pin设置为模拟模式  +
        SetBit(CMP_CR1, CMP3MOD1);                    //00-->P27-单比较器模式    01-->P20/P23-双比较器模式
        ClrBit(CMP_CR1, CMP3MOD0);                    //1X-->P20/P23/P27-三比较器模式
    }
    #endif  //end Shunt_Resistor_Mode
    #if (Compare_Mode == Compare_Hardware)
    {
        /**P2.6使能其模拟功能，使能数字输出**/
        SetBit(P2_AN, P26);
        ClrBit(P2_OE, P26);
        ClrBit(DAC_CR, DAC0_1EN);
    }
    #else
    {
        /**P2.6使能其模拟功能，使能数字输出**/
        SetBit(P2_AN, P26);
        SetBit(P2_OE, P26);
        /******************************
            0: 正常模式，DAC输出电压范围为0到VREF
            1: 半电压转换模式，DAC输出电压范围为VHALF到VREF
        ****************************/
        ClrBit(DAC_CR, DACMOD);
    
        /**********设置DAC过流值*****************/
        SetBit(DAC1_DR, DAC0_DR_0);   //舍弃最后一位精度
    
        DAC0_DR = DAC_OvercurrentValue;
        /**********DAC0 Enable******************/
        SetBit(DAC_CR, DAC0_1EN);
    }
    #endif                                               //end Compare_Mode
    SetBit(CMP_CR1, CMP3HYS);                            // CMP3 Hysteresis voltage Enable
    /*  ---------------------------------------------------------------------------------
        选择母线电流保护触发信号源，外部中断0或者比较器3中断。
        0-CMP3,1-INT0
        ---------------------------------------------------------------------------------*/
    ClrBit(EVT_FILT, EFSRC);
    /*  ---------------------------------------------------------------------------------
        触发硬件保护后硬件关闭驱动输出MOE配置
        00--MOE不自动清零
        01--MOE自动清零
        ----------------------------------------------------------------------------------*/
    ClrBit(EVT_FILT, MOEMD1);
    SetBit(EVT_FILT, MOEMD0);
    /*  ----------------------------------------------------------------------------------
        母线电流保护时间滤波宽度
        00-不滤波
        01-4cpu clock
        10-8cpu clock
        11-16cpu clock
        -----------------------------------------------------------------------------------*/
    SetBit(EVT_FILT, EFDIV1);
    SetBit(EVT_FILT, EFDIV0);
    SetBit(CMP_CR1, CMP3EN);                               //CMP3 Enable
	
	
}


/**
 * @brief     CMP3中断配置
 * @date      2022-09-12
 */
void CMP3_Interrupt_Init(void)
{
    ClrBit(CMP_SR, CMP3IF);
    /*  ------------------------------------------------------------------------
        比较器中断模式配置
        00: 不产生中断
        01: 上升沿产生中断
        10: 下降沿产生中断
        11: 上升/下降沿产生中断
        ------------------------------------------------------------------------ */
    ClrBit(CMP_CR0, CMP3IM1);
    SetBit(CMP_CR0, CMP3IM0);
	
    PCMP31 = 1;
    PCMP30 = 1;                 // 中断优先级别3
}



