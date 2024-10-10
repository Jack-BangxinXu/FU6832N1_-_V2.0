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
 * @brief     GPIO初始化配置,可将I/O口配置成输入或输出模式，上拉还是不上拉，模拟输出还是数字输出
 * @date      2022-09-12
 */
void GPIO_Init(void)
{
	SetBit(P2_OE, P21);//TX测试用
    GP21 = 1;
    SetBit(P0_OE , P01);//FG
    GP01 = 1;		
    
    SetBit(P2_OE , P20);//NTC_POWER
    SetBit(P2_PU , P20);//NTC_POWER
    GP20 = 1;	

}

