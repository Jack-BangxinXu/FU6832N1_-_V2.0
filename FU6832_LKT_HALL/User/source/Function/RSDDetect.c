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
 
/* Includes -------------------------------------------------------------------------------------*/
#include <Myproject.h>

#if(TailWind_Mode == RSDMethod)
MotorRSDTypeDef xdata   RSDDetect;

/**
 * @brief     RSD初始化
 * @date      2022-09-12
 */		
void RSDDetectInit(void)
{
    MOE = 0;
    RSDDetect.RSDStepTime[0] = 0;
    RSDDetect.RSDStepTime[1] = 0;
    RSDDetect.RSDStepTime[2] = 0;
    RSDDetect.RSDStepTime[3] = 0;
    RSDDetect.RSDTimes       = 0;
    RSDDetect.RSDPeriod      = 0;
    RSDDetect.RSDCount       = 0;
    RSDDetect.RSDState       = Static;
    RSDDetect.RSDSpeed       = 0;
    RSDDetect.RSDDir         = 0;
    RSDDetect.RSDFlag        = 0;
    RSDDetect.RSDStep        = 0;
    RSDDetect.RSDBRFlag      = 0;
    ClrBit(DRV_CR, FOCEN);   // 关闭FOC
    CMP_RSD_Init();
    Time2_RSD_Init();        // RSD用的是Time2
}


/**
 * @brief     RSD对CMP的初始化
 * @date      2022-09-12
 */	
void CMP_RSD_Init(void)
{
    /*  -------------------------------------------------------------------------------------------------
        CMP Input Pin Mode
        P1.4--CMP0_IN+, P1.6--CMP1_IN+, P2.1--CMP2_IN+
        P1.5--CMP0_IN-, P1.7--CMP1_IN-, P2.2--CMP2_IN-
        P1.3--CMP1P2
        -------------------------------------------------------------------------------------------------*/
    SetBit(P1_AN, P14 | P15 | HBMOD);
    ClrBit(P1_OE, P13);
    /*  -------------------------------------------------------------------------------------------------
        CMP0_MOD：
        00： 无内置虚拟中心点电阻的BEMF模式
        01： 内置虚拟中心点电阻的BEMF模式
        10： 3差分比较器模式
        11： 2比较器模式RSD
        -------------------------------------------------------------------------------------------------*/
    SetReg(CMP_CR2, CMP0MOD0 | CMP0MOD1, CMP0MOD0 | CMP0MOD1);
    /*  -------------------------------------------------------------------------------------------------
        比较器输出选择配置，与CMP0_MOD配合使用
        CMP0_SEL[1:0]=00，比较器0工作在2比较器轮询模式，正端在CMP0P、CMP1P2之间自动轮流选择，负端固定接CMP0M，
                      其输出结果分别送至CMP0_OUT、CMP1_OUT
        CMP0_SEL[1:0]=01，比较器0选择CMP0对应的端口组合，即正端接CMP0P，负端接CMP0M，输出接CMP0_OUT
        CMP0_SEL[1:0]=10，比较器0选择CMP1对应的端口组合，即正端接CMP1P2，负端接CMP0M，输出接CMP1_OUT
        -----------------------------------------------------------------------------*/
    SetReg(CMP_CR2, CMP0SEL0 | CMP0SEL1, 0x00);
    /*  -------------------------------------------------------------------------------------------------
        比较器迟滞电压选择
        000: 无迟滞     001: ±2.5mV   010: -5mV   011: +5mV
        100: +-5mV   101: -10mV   110: +10mV   111: +-10mV
        -------------------------------------------------------------------------------------------------*/
    SetReg(CMP_CR1, CMP0HYS0 | CMP0HYS1 , CMP0HYS0);
    /*  -------------------------------------------------------------------------------------------------
        CMP0的轮询时间设置
        -------------------------------------------------------------------------------------------------*/
    SetReg(CMP_CR1, CMP0CSEL0 | CMP0CSEL1, 0x00);
    EA = 0;
    /** ------------------------------------------------------
        使能比较器CMP0,CMP1,CMP2和ADC在pwm on/off采样功能
    
        00：在on和off均采样，没有延迟采样开启
        01：只在off采样，根据CMP_SAMR延迟采样开启
        10：只在on采样，根据CMP_SAMR延迟采样开启
        11：在on和off均采样，根据CMP_SAMR延迟采样开启
        ---------------------------------------------------------**/
    //SetReg(CMP_CR3, SAMSEL0 | SAMSEL1, SAMSEL1);
    /**采样延迟设置**/
    CMP_SAMR = 0x10;
    SetBit(CMP_CR2, CMP0EN); //使能比较器
}

/**
 * @brief     RSD对应Time2的初始化
 * @date      2022-09-12
 */	
void Time2_RSD_Init(void)
{
    /*  -------------------------------------------------------------------------------------------------
        先停止计数，配置完寄存器后，最后启动计数
        -------------------------------------------------------------------------------------------------*/
    ClrBit(TIM2_CR1, T2CEN);        // 0，停止计数；1,使能计数
    /*  -------------------------------------------------------------------------------------------------
        时钟分频设置(T2PSC)
        000:cpuclk(24MHz)         001:cpuclk/2^1(12MHz)   010:cpuclk/2^2(6MHz)    011:cpuclk/2^3(3MHz)
        100:cpuclk/2^4(1.5MHz)    101:cpuclk/2^5(750KHz)  110:cpuclk/2^6(375KHz)  111:cpuclk/2^7(187.5KHz)
        -------------------------------------------------------------------------------------------------*/
    SetReg(TIM2_CR0, T2PSC0 | T2PSC1 | T2PSC2,  T2PSC0 | T2PSC1 | T2PSC2);
    /*  -------------------------------------------------------------------------------------------------
        /模式选择
        T2MODE1，T2MODE0
        00--输入Timer模式；01--输出模式
        10--输入Count模式；11--QEP或者RSD模式
        -------------------------------------------------------------------------------------------------*/
    SetReg(TIM2_CR0, T2MOD0 | T2MOD1, T2MOD0 | T2MOD1);
     ClrBit(TIM2_CR1, T2FE);                               // 滤波使能
    /*  -------------------------------------------------------------------------------------------------
        清除中断标志位
        禁止PWM周期检测中断使能
        使能计数器上溢中断使能
        -------------------------------------------------------------------------------------------------*/
    ClrBit(TIM2_CR1, T2IR | T2IF | T2IP);  // 清除中断标志位
    ClrBit(TIM2_CR0, T2CES | T2IRE);       // 清零脉冲计数器不使能
    SetBit(TIM2_CR1, T2IPE | T2IFE);       // 输入有效边沿变化中断使能和基本计数器上溢使能
    /*  -------------------------------------------------------------------------------------------------
        定时器2中断优先级配置及芯片中断总使能
        PTIM231-PTIM230，中断优先级控制值从0-3依次表示优先级从最低到最高，共4级优化级控制
        EA,芯片中断总使能
        -------------------------------------------------------------------------------------------------*/
//    PTIM21 = 1;
//    PTIM20 = 0;// TIM2/2中断优先级别为2
    SetBit(IP1, PTIM21 );       // 输入有效边沿变化中断使能和基本计数器上溢使能
    SetBit(IP1, PTIM20 );   
    EA = 1;
    /*  -------------------------------------------------------------------------------------------------
        配置周期值、比较值、计数值
        -------------------------------------------------------------------------------------------------*/
    TIM2__CNTR = 0;
    /*-----------启动计数------------------------------------------------*/
    SetBit(TIM2_CR1, T2CEN);            //启动计数
}

/**
 * @brief     RSD检测，判断正转还是反转
 * @date      2022-09-12
 */
void RSDFRDetect(void)
{
    RSDDetect.RSDCount = TIM2__CNTR;//注意RSDCount需为IDATA数据类型
    
    if (RSDDetect.RSDCount < -7) //正转
    {
        RSDDetect.RSDPeriod = (RSDDetect.RSDStepTime[0] + RSDDetect.RSDStepTime[1] + RSDDetect.RSDStepTime[2] + RSDDetect.RSDStepTime[3]) >> 2;
        RSDDetect.RSDDir    = ReadBit(TIM2_CR1, T2DIR);
        ClrBit(TIM2_CR1, T2CEN);     //关掉定时器2
        RSDDetect.RSDState = Forward;
        RSDDetect.RSDFlag  = 1;
    }
    else if (RSDDetect.RSDCount > 7) //反转
    {
        RSDDetect.RSDPeriod = (RSDDetect.RSDStepTime[0] + RSDDetect.RSDStepTime[1] + RSDDetect.RSDStepTime[2] + RSDDetect.RSDStepTime[3]) >> 2;
        RSDDetect.RSDDir    = ReadBit(TIM2_CR1, T2DIR);
        ClrBit(TIM2_CR1, T2CEN);     //关掉定时器2
        RSDDetect.RSDState = Reverse;
        RSDDetect.RSDFlag  = 1;
    }
    else//多次判断
    {
        RSDDetect.RSDStepTime[RSDDetect.RSDStep] = TIM2__ARR;//将比较器的读值给RSDStep
        RSDDetect.RSDStep++;
        
        if (RSDDetect.RSDStep > 3)
        {
            RSDDetect.RSDStep = 0;
        }
    }
    
    RSDDetect.RSDTimes++;//多次中断，但又没有跳入正反转
    
    if (RSDDetect.RSDTimes > 15)
    {
        RSDDetect.RSDState = Static;
        RSDDetect.RSDFlag  = 1;
    }
}

/**
 * @brief     RSD处理方式
 * @date      2022-09-12
 */	
void RSDDealwith(void)
{
    if (RSDDetect.RSDFlag == 1)
    {
        if (RSDDetect.RSDState != Static)//处理速度
        {
            RSDDetect.RSDSpeedBase  = RSDSpeedBaseStep;
            RSDDetect.RSDPeriod    += 1;
            DivQ_L_MDU(((RSDDetect.RSDSpeedBase) >> 16), RSDDetect.RSDSpeedBase, RSDDetect.RSDPeriod, RSDDetect.RSDSpeed);
        }
        
        if (((RSDDetect.RSDState == Reverse)
                && (RSDDetect.RSDDir == 0x00))
            && (RSDDetect.RSDSpeed > _Q15(80.0 / MOTOR_SPEED_BASE))
            && (RSDDetect.RSDCCWTimes < 4))//反转超过一定速度，且刹车次数小于4次时，进入
        {
            mcFocCtrl.State_Count            = 1000;
            McStaSet.SetFlag.TailWindSetFlag = 0;
            MOE = 0;
            DRV_DR   = DRV_ARR + 1;
            DRV_CMR &= 0xFFC0;
            DRV_CMR |= 0x015;                         // 三相下桥臂通，刹车
            ClrBit(DRV_CR, OCS);//OCS = 0, DRV_COMR;OCS = 1, FOC/SVPWM/SPWM
            MOE = 1;
            
            if (RSDDetect.RSDSpeed > _Q15(200.0 / MOTOR_SPEED_BASE)) //速度超过一定值时，刹车，且置标志位，在启动时，根据不同速度设置不同启动电流
            {
                mcFocCtrl.State_Count = 1500;
                RSDDetect.RSDCCWFlag  = 1;
            }
            else
            {
                mcFocCtrl.State_Count = 800;
                
                if (RSDDetect.RSDCCWFlag == 0)
                {
                    RSDDetect.RSDCCWFlag = 2;
                }
            }
            
            RSDDetect.RSDCCWTimes++;
            ClrBit(CMP_CR2, CMP0EN);                              //关闭比较器
            ClrBit(TIM2_CR1, T2CEN);                               // 0，停止计数；1,使能计数
        }
        else if ((RSDDetect.RSDState == Forward) && (RSDDetect.RSDDir == 0x01))//正转
        {
            RSDFOCCloseLoopStart();
            ClrBit(CMP_CR2, CMP0EN);                               // 关闭比较器
            ClrBit(TIM2_CR1, T2CEN);                                // 0，停止计数；1,使能计数
        }
        else//其他，如静止
        {
            ClrBit(CMP_CR2, CMP0EN);                               // 关闭比较器
            ClrBit(TIM2_CR1, T2CEN);                               // 0，停止计数；1,使能计数
            
            if (RSDDetect.RSDCCWFlag != 0)
            {
                if (RSDDetect.RSDBRFlag == 0)                      // 刹车400ms，用以提高逆风情况下的成功率
                {
                    RSDDetect.RSDCCWSBRCnt = 400;
                    MOE = 0;
                    DRV_DR   = DRV_ARR + 1;
                    DRV_CMR &= 0xFFC0;
                    DRV_CMR |= 0x015;                              // 三相下桥臂通，刹车
                    ClrBit(DRV_CR, OCS);                           // OCS = 0, DRV_COMR;OCS = 1, FOC/SVPWM/SPWM
                    MOE = 1;
                    RSDDetect.RSDBRFlag = 1;
                }
            }
            
            if ((RSDDetect.RSDCCWFlag == 0) || (RSDDetect.RSDCCWSBRCnt == 0))
            {
                MOE = 0;
               // mcState                           = mcPosiCheck;
                McStaSet.SetFlag.PosiCheckSetFlag = 0;
                mcFocCtrl.mcPosCheckAngle         = 32767;         // 角度赋初值
				mcFocCtrl.WindFlag = Wind_STATIC;
            }
        }
    }
}


/**
 * @brief     闭环启动
 * @date      2022-09-12
 */	
void RSDFOCCloseLoopStart(void)
{
    /*FOC初始化*/
    FOC_Init();
    /*启动电流、KP、KI*/
    FOC_IDREF         = ID_Start_CURRENT;                      // D轴启动电流
    mcFocCtrl.mcIqref = IQ_Start_CURRENT;                      // Q轴启动电流
    FOC_IQREF         = mcFocCtrl.mcIqref;                     // Q轴启动电流
    FOC_DQKP = DQKP;
    FOC_DQKI = DQKI;
    FOC_EFREQACC  = Motor_Omega_Ramp_ACC;
    FOC_EFREQMIN  = MOTOR_OMEGA_RAMP_MIN;
    FOC_EFREQHOLD = MOTOR_OMEGA_RAMP_END;
    SetBit(FOC_CR1, ANGM);                                     // 估算模式
    ClrBit(FOC_CR1, RFAE);                                     // 禁止强拉
    SetBit(FOC_CR1, EFAE);                                     // 估算器强制输出
    FOC__EOME = RSDDetect.RSDSpeed;
       
    #if (EstimateAlgorithm == SMO)
    
    //根据不同转速确启动的ATO_BW值
    if (RSDDetect.RSDSpeed > _Q15(360.0 / MOTOR_SPEED_BASE))
    {
        FOC_EKP               = OBSW_KP_GAIN_RUN4;
        FOC_EKI               = OBSW_KI_GAIN_RUN4;
        mcFocCtrl.mcIqref     = IQ_RUN_CURRENT;
        mcFocCtrl.State_Count = 100;
    }
    else if (RSDDetect.RSDSpeed > _Q15(160.0 / MOTOR_SPEED_BASE))
    {
        FOC_EKP               = OBSW_KP_GAIN_RUN3;
        FOC_EKI               = OBSW_KI_GAIN_RUN3;
        mcFocCtrl.mcIqref     = IQ_RUN_CURRENT;
        mcFocCtrl.State_Count = 100;
    }
    else
    {
        FOC_EKP               = OBSW_KP_GAIN_RUN2;
        FOC_EKI               = OBSW_KI_GAIN_RUN2;
        mcFocCtrl.mcIqref     = IQ_RUN_CURRENT;
        mcFocCtrl.State_Count = 100;
    }
    
    #elif (EstimateAlgorithm == PLL)
    FOC_EKP           = OBSW_KP_GAIN_RUN4;
    FOC_EKI           = OBSW_KI_GAIN_RUN4;
    mcFocCtrl.mcIqref = IQ_RUN_CURRENT;
    #endif //end    EstimateAlgorithm
    FOC_OMEKLPF        = SPEED_KLPF;
//    mcState            = mcRun;
    mcFocCtrl.CtrlMode = 0;
    /*使能输出*/
    DRV_CMR |= 0x3F;                         // U、V、W相输出
    MOE = 1;
    EA = 1;
	mcFocCtrl.WindFlag = Wind_FORWARD;
}
#endif

