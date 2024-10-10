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
 * @brief     AMP初始化配置,使能运放电压VHALF，配置运放的电流采样正向输入，反向输入和输出，包括I_BUS,I_U,I_V
                    并使能对应的运放
 * @date      2022-09-12
 */
void AMP_Init(void)
{
    #if (Shunt_Resistor_Mode == Single_Resistor)
    {
        /*****AMP 端口模拟功能设置******/
        SetBit(P3_AN, P31);             //AMP0 Pin设置为模拟模式  +
        SetBit(P3_AN, P30);             //AMP0 Pin设置为模拟模式  -
        SetBit(P2_AN, P27);             //AMP0 Pin设置为模拟模式  O
        
        SetBit(AMP_CR, AMP0EN);         //AMP0 Enable
    }
    #elif (Shunt_Resistor_Mode == Double_Resistor)
    {
        /*****AMP 端口模拟功能设置******/
        SetBit(P3_AN, P31);             //AMP0 Pin设置为模拟模式  +
        SetBit(P3_AN, P30);             //AMP0 Pin设置为模拟模式  -
        SetBit(P2_AN, P27);             //AMP0 Pin设置为模拟模式  O
    
        SetBit(P1_AN, P16);             //AMP1 Pin设置为模拟模式  +
        SetBit(P1_AN, P17);             //AMP1 Pin设置为模拟模式  -
        SetBit(P2_AN, P20);             //AMP1 Pin设置为模拟模式  O
    
        SetBit(P2_AN, P21);             //AMP2 Pin设置为模拟模式  +
        SetBit(P2_AN, P22);             //AMP2 Pin设置为模拟模式  -
        SetBit(P2_AN, P23);             //AMP2 Pin设置为模拟模式  O
        ClrBit(P2_OE, P23);             //P23_OE需要强制为0，禁止DA1输出至PAD
    
        SetBit(AMP_CR, AMP0EN);         //AMP0 Enable
        SetBit(AMP_CR, AMP1EN);         //AMP1 Enable
        SetBit(AMP_CR, AMP2EN);         //AMP2 Enable
    }
    #elif (Shunt_Resistor_Mode == Three_Resistor)
    {
        SetBit(P3_AN, P31);             //AMP0 Pin设置为模拟模式  +
        SetBit(P3_AN, P30);             //AMP0 Pin设置为模拟模式  -
        SetBit(P2_AN, P27);             //AMP0 Pin设置为模拟模式  O
    
        SetBit(P1_AN, P16);             //AMP1 Pin设置为模拟模式  +
        SetBit(P1_AN, P17);             //AMP1 Pin设置为模拟模式  -
        SetBit(P2_AN, P20);             //AMP1 Pin设置为模拟模式  O
    
        SetBit(P2_AN, P21);             //AMP2 Pin设置为模拟模式  +
        SetBit(P2_AN, P22);             //AMP2 Pin设置为模拟模式  -
        SetBit(P2_AN, P23);             //AMP2 Pin设置为模拟模式  O
        ClrBit(P2_OE, P23);             //P23_OE需要强制为0，禁止DA1输出至PAD
    
        SetBit(AMP_CR, AMP0EN);         //AMP0 Enable
        SetBit(AMP_CR, AMP1EN);         //AMP1 Enable
        SetBit(AMP_CR, AMP2EN);         //AMP2 Enable
    }
    #endif
    #if(AMP_MODE ==INTERNAL)
    {
        //000-->Genaral AMP 001-->2X 010-->4X 011-->8X 100-->16X 101-->32X Others-->32X
        /**********AMP0 PGA SET************/
        #if (CFG_AMP0GAIN ==AMP2x)
        {
            ClrBit(AMP0_GAIN, AMP0_GAIN2); //0x80
            ClrBit(AMP0_GAIN, AMP0_GAIN1);  //0x40
            SetBit(AMP0_GAIN, AMP0_GAIN0);  //0x20
        }
        #elif (CFG_AMP0GAIN ==AMP4x)
        {
            ClrBit(AMP0_GAIN, AMP0_GAIN2);  //0x80
            SetBit(AMP0_GAIN, AMP0_GAIN1);  //0x40
            ClrBit(AMP0_GAIN, AMP0_GAIN0);  //0x20
        }
        #elif (CFG_AMP0GAIN ==AMP8x)
        {
            ClrBit(AMP0_GAIN, AMP0_GAIN2);  //0x80
            SetBit(AMP0_GAIN, AMP0_GAIN1);  //0x40
            SetBit(AMP0_GAIN, AMP0_GAIN0);  //0x20
        }
        #elif (CFG_AMP0GAIN ==AMP16x)
        {
            SetBit(AMP0_GAIN, AMP0_GAIN2);  //0x80
            ClrBit(AMP0_GAIN, AMP0_GAIN1);  //0x40
            ClrBit(AMP0_GAIN, AMP0_GAIN0);  //0x20
        }
        #elif (CFG_AMP0GAIN ==AMP32x)
        {
            SetBit(AMP0_GAIN, AMP0_GAIN2);  //0x80
            ClrBit(AMP0_GAIN, AMP0_GAIN1);  //0x40
            SetBit(AMP0_GAIN, AMP0_GAIN0);  //0x20
        }
        #else
        {
            ClrBit(AMP0_GAIN, AMP0_GAIN2);  //0x80
            SetBit(AMP0_GAIN, AMP0_GAIN1);  //0x40
            SetBit(AMP0_GAIN, AMP0_GAIN0);  //0x20
        }
        #endif
    }
    #else
    {
        ClrBit(AMP0_GAIN, AMP0_GAIN2);  //0x80
        ClrBit(AMP0_GAIN, AMP0_GAIN1);  //0x40
        ClrBit(AMP0_GAIN, AMP0_GAIN0);  //0x20
    }
    #endif
}