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
    @brief        PI2用于母线限流
    @date         2022-07-14
*/
void PI2_Init(void)
{
    PI2_KP          = LimitCurrent_KP;
    PI2_KI          = LimitCurrent_KI;
    PI2_EK1         =0;
    PI2_EK          =0;
    PI2_UKH         =0;
    PI2_UKL         =0;
    PI2_UKMAX       = LimitCurrentOUTMAX;
    PI2_UKMIN       = 0;
}



/**
 * @brief     PI3初始化
 * @date      2022-09-12
 */
void PI_Init(void)
{
    PI3_KP  = SKP;
    PI3_KI  = SKI;
    PI3_UKH = 0;
    PI3_UKL = 0;
    PI3_EK  = 0;
    PI3_EK1 = 0;
    PI3_KD = 0;
    PI3_EK2 = 0;
    
  
    
    PI3_UKMAX = SOUTMAX;
   
    PI3_UKMIN = SOUTMIN;

    SetBit(PI_CR, PI3STA);               // Start PI
    
    while (ReadBit(PI_CR, PIBSY));
}
