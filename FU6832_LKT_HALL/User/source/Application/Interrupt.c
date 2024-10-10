/*  -------------------------- (C) COPYRIGHT 2022 Fortiortech ShenZhen ---------------------------*/
/**
 * @copyright (C) COPYRIGHT 2022 Fortiortech Shenzhen
 * @file      xxx.c
 * @author    Fortiortech  Appliction Team
 * @since     Create:2022-09-09
 * @date      Last modify:2022-09-09
 * @note      Last modify author is Leo.li
 * @brief
 */

#include <MyProject.h>

extern uint8 data g_1mTick;                   ///< 1ms滴答信号，每隔1ms在SYSTICK定时器被置1，需在大循环使用处清零

uint16 xdata spidebug[4] = { 0 };

/**
 * @brief        LVW_TSD_INT 芯片电压预警
 * @date         2022-08-07
 */
void LVW_TSD_INT(void) interrupt 0  //LVW & TSD interrupt
{
    if (ReadBit(LVSR, LVWIF))
    {
        if (ReadBit(LVSR, LVWF))
        {
            mcFaultSource = FaultUnderVoltageDC;
            ClrBit(DRV_CR, DRVEN);  //Driver Disable
            ClrBit(DRV_CR, FOCEN);  //FOC Disable
            MOE     = 0;
            ClrBit(LVSR, LVWF);
        }
        
        ClrBit(LVSR, LVWIF);
    }
    
    if (TSDIF)
    {
        TSDIF = 0;
    }
}

/**
 * @brief        FO_INT interrupt，硬件FO过流保护，关断输出，中断优先级最高
 * @date         2022-08-07
 */
void FO_INT(void) interrupt 1               // 硬件FO过流中断，关闭输出
{
    if (IF0)
    {
        FaultProcess();                         // 关闭输出
        mcFaultSource = FaultHardOVCurrent;     // 硬件过流保护
        IF0 = 0;                                // clear P00 interrupt flag
    }
}

/**
 * @brief        外部中断：
 * @date         2022-08-07
 */
void EXTERN_INT(void) interrupt 2
{
    if (P1_IF)
    {
	   		
        P1_IF = 0;                              // 
    }                   // 清中断标志位
}

/**
 * @brief        FOC中断(Drv中断), 可配置1 | 2 个载波周期执行一次，用于处理响应较高的程序
 * @date         2022-08-07
 */
void DRV_ISR(void) interrupt 3
{
	//GP00=0;
//	GP05=~GP05;
    if (ReadBit(DRV_SR, FGIF))
    {
        ClrBit(DRV_SR, FGIF);
    }
    
    if (ReadBit(DRV_SR, DCIF))    // 比较中断
    {
        #if(TailWind_Mode ==FOCMethod)
        {
            TailWindSpeedDetect();
        }
        #endif
        #if (DBG_MODE == DBG_SPI_SW)            //软件调试模式
        {
            spidebug[0] = FOC__THETA;
            spidebug[1] = SOFT_SPIDATA1;
            spidebug[2] = SOFT_SPIDATA2;
            spidebug[3] = SOFT_SPIDATA3;
        }
        #endif
    	DRV_SR = (DRV_SR | SYSTIF) & (~DCIF);
    }
//		GP05=1;
	//GP00=1;
}


/**
 * @brief        正反转检测(ISD)
 * @date         2022-08-07
 */
void TIM2_INT(void) interrupt 4
{
    if (ReadBit(TIM2_CR1, T2IR))
    {
        ClrBit(TIM2_CR1, T2IR);
    }
    
    if (ReadBit(TIM2_CR1, T2IP))
    {
        #if (TailWind_Mode == RSDMethod)
        RSDFRDetect();                      //RSD正反转检测
        #endif
        ClrBit(TIM2_CR1, T2IP);
    }
    
    if (ReadBit(TIM2_CR1, T2IF))            //溢出中断,用于判断静止,时间为349ms。
    {
        #if (TailWind_Mode == RSDMethod)
        {
            RSDDetect.RSDState = Static;
            RSDDetect.RSDFlag  = 1;
        }
        #endif
        ClrBit(TIM2_CR1, T2IF);
    }
}


/**
 * @brief        CMP0/1/2：顺逆风判断
 * @date         2022-08-07
 */
void CMP_ISR(void) interrupt 7
{
    if (ReadBit(CMP_SR, CMP0IF) || ReadBit(CMP_SR, CMP1IF) || ReadBit(CMP_SR, CMP2IF)) //当检测到比较器中断时
    {
        #if (TailWind_Mode == BEMFMethod)
        {
            /* -----通过BEMF做顺风启动功能----- */
            BEMFDetectFunc();
        }
        #endif
        ClrBit(CMP_SR, CMP0IF | CMP1IF | CMP2IF);
    }
}

/**
 * @brief        Capture PWM ，用于PWM调速
 * @date         2022-08-07
 */
void TIM3_INT(void) interrupt 9
{
    if (ReadBit(TIM3_CR1, T3IR))
    {
        ClrBit(TIM3_CR1, T3IR);
    }
    
    if (ReadBit(TIM3_CR1, T3IP))//周期中断
    {
        if (mcPwmInput.PwmFlag != 1) //若正在计算占空比则不更新
        {
            mcPwmInput.PwmCompare    = TIM3__DR;
            mcPwmInput.PwmArr        = TIM3__ARR;
            mcPwmInput.PwmUpdateFlag = 1;
        }
        
        ClrBit(TIM3_CR1, T3IP);
    }
    
    if (ReadBit(TIM3_CR1, T3IF))
    {
        if (ReadBit(P1, PIN1))//PWM 100%输出
        {
            mcPwmInput.PwmCompare = 400;
            mcPwmInput.PwmArr     = 400;
        }
        else//PWM 为0%
        {
            mcPwmInput.PwmCompare = 0;
            mcPwmInput.PwmArr     = 400;
        }
        
        mcPwmInput.PwmUpdateFlag = 1;
        ClrBit(TIM3_CR1, T3IF);
    }
	
}

/**
 * @brief        1ms定时器中断（SYS TICK中断），用于处理附加功能，如控制环路响应、各种保护等。
 * @date         2022-08-07
 */
void SYStick_INT(void) interrupt 10
{
    if (ReadBit(DRV_SR, SYSTIF))          // SYS TICK中断
    {
        SetBit(ADC_CR, ADCBSY);           //使能ADC的DCBUS采样
        g_1mTick = 1;
        DRV_SR = (DRV_SR | DCIF) & (~SYSTIF);               // 清零标志位
    }
}



/**
 * @brief        CMP3：硬件比较器过流保护，关断输出，中断优先级最高
 * @date         2022-08-07
 */
void CMP3_INT(void)  interrupt 12
{
    if (ReadBit(CMP_SR, CMP3IF))
    {
        if (mcState != mcPosiCheck)
        {
            FaultProcess();                                                                   // 关闭输出
            mcFaultSource = FaultHardOVCurrent;                                               // 硬件过流保护
        }
        else
        {
        }        
        ClrBit(CMP_SR, CMP3IF);
    }
}

/**
 * @brief        TIM4会用到FG输出，如果TIM4用作基本定时器需要注意
 * @date         2022-08-07
 */
void TIM4_INT(void) interrupt 11
{
    /*TIM4 Interrupt*/
    if (ReadBit(TIM4_CR1, T4IR))
    {
        ClrBit(TIM4_CR1, T4IR);
    }
    
    if (ReadBit(TIM4_CR1, T4IP)) //周期中断
    {
        ClrBit(TIM4_CR1, T4IP);
    }
    
    if (ReadBit(TIM4_CR1, T4IF))
    {
        ClrBit(TIM4_CR1, T4IF);
    }
}
