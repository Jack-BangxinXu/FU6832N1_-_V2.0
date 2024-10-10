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
 * @brief     Timer1的参数设置
 * @date      2022-09-12
 */	
void Timer1_Init(void)
{
}
/**
 * @brief     Timer2的参数设置
 * @date      2022-09-12
 */
void Timer2_Init(void)
{
    SetBit(PH_SEL, T2SEL);           //P10
    SetBit(PH_SEL, T2SSEL);          //P07
    ClrBit(TIM2_CR0, T2PSC2);        //计数器时钟分频选择
    ClrBit(TIM2_CR0, T2PSC1);        //000-->24M        001-->12M       010-->6M    011-->3M
    ClrBit(TIM2_CR0, T2PSC0);        //100-->1.5M   101-->750K      110-->375K  111-->187.5K
    ClrBit(TIM2_CR0, T2OCM);
    SetBit(TIM2_CR0, T2IRE);         //比较匹配中断/脉宽检测中断0-->Disable  1-->Enable
    ClrBit(TIM2_CR0, T2CES);
    ClrBit(TIM2_CR1, T2IPE);         //输入Timer PWM周期检测中断使能 0-->Disable  1-->Enable
    ClrBit(TIM2_CR1, T2IFE);         //计数器上溢中断使能 0-->Disable  1-->Enable
    ClrBit(TIM2_CR1, T2FE);          //输入噪声滤波使能，小于4个时钟周期脉宽滤除
    ClrBit(TIM2_CR1, T2DIR);         //QEP&ISD&步进模式专用：当前的方向 0-->正向  1-->反向
    TIM2__DR = 1200;
    TIM2__ARR = 2400;
    ClrBit(TIM2_CR0, T2MOD1);        //00-->输入Timer模式           01-->输出模式
    SetBit(TIM2_CR0, T2MOD0);        //10-->输入Counter模式         11-->QEP&ISD&步进模式
    SetBit(TIM2_CR1, T2CEN);         //TIM2使能   0-->Disable  1-->Enable
}
/**
 * @brief     Timer3的参数设置
 * @date      2022-09-12
 */	
void Timer3_Init(void)
{
    SetBit(PH_SEL, T3SEL);            //Timer3端口使能
    ClrBit(PH_SEL1, T3CT);            //默认端口为P11,功能转移后为P01,需TIMER4转移到P00
	
    SetBit(TIM3_CR0, T3PSC2);         //计数器时钟分频选择
    SetBit(TIM3_CR0, T3PSC1);         //000-->24M       001-->12M       010-->6M    011-->3M
    ClrBit(TIM3_CR0, T3PSC0);         //100-->1.5M  101-->750K      110-->375K  111-->187.5K
	
    ClrBit(TIM3_CR0, T3OCM);
    ClrBit(TIM3_CR0, T3IRE);          //比较匹配中断/脉宽检测中断0-->Disable  1-->Enable
    ClrBit(TIM3_CR0, T3OPM);          //0-->计数器不停止      1-->单次模式
    SetBit(TIM3_CR1, T3IPE);          //输入Timer PWM周期检测中断使能 0-->Disable  1-->Enable
    SetBit(TIM3_CR1, T3IFE);          //计数器上溢中断使能 0-->Disable  1-->Enable
    ClrBit(TIM3_CR1, T3NM1);          //输入噪声脉宽选择
    ClrBit(TIM3_CR1, T3NM0);          //00-->不滤波  01-->4cycles    10-->8cycles  11-->16cycles
    ClrBit(TIM3_CR0, T3MOD);           //0-->Timer模式       1-->输出模式
    SetBit(TIM3_CR1, T3EN);            //TIM3使能    0-->Disable  1-->Enable
}
/**
 * @brief     Timer4的参数设置
 * @date      2022-09-12
 */	
void Timer4_Init(void)
{
    SetBit(PH_SEL, T4SEL);               //Timer4端口使能
	
	ClrBit(PH_SEL1, T4CT);
	SetReg(TIM4_CR0, T3PSC2 | T3PSC1 | T3PSC0, T3PSC2);
	SetBit(TIM4_CR0, T4OCM);

	ClrBit(TIM4_CR0, T4IRE);             //比较匹配中断/脉宽检测中断0-->Disable  1-->Enable
	ClrBit(TIM4_CR0, T4OPM);             //0-->计数器不停止       1-->单次模式
	ClrBit(TIM4_CR1, T4IPE);             //输入Timer PWM周期检测中断使能 0-->Disable  1-->Enable
	ClrBit(TIM4_CR1, T4IFE);             //计数器上溢中断使能 0-->Disable  1-->Enable
	ClrBit(TIM4_CR1, T4NM1);             //输入噪声脉宽选择
	ClrBit(TIM4_CR1, T4NM0);             //00-->不滤波   01-->4cycles  10-->8cycles  11-->16cycles

	TIM4__ARR = 65535;
	SetBit(TIM4_CR0, T4MOD);             //0-->Timer模式  1-->输出模式
	SetBit(TIM4_CR1, T4EN);              //TIM4使能   0-->Disable  1-->Enable

}
