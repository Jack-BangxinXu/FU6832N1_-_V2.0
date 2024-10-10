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

CurrentOffset xdata mcCurOffset;



/**
 * @brief     mcInit状态下，对FOC的相关寄存器进行配置,先清理寄存器，后配置，最后使能
 * @date      2022-09-12
 */
void FOC_Init(void)//MOtor_Init
{
    /*使能FOC*/
    ClrBit(DRV_CR, FOCEN);
	ClrBit(DRV_CR, DRVEN);  //计数器使能       0-->Disable     1-->Enable
    SetBit(DRV_CR, FOCEN);
    SetBit(FOC_CR0, ESCMS);
    ClrBit(FOC_CR0, MERRS1);
    SetBit(FOC_CR0, MERRS0);
    FOC_EOMEKLPF    = 0xff;
	
    /*配置FOC寄存器*/
    FOC_CR1         = 0;                                    // 清零 FOC_CR1
    FOC_CR2         = 0;                                    // 清零 FOC_CR2
    FOC_IDREF       = 0;                                    // 清零 Id
    FOC_IQREF       = 0;                                    // 清零 Iq
    FOC__THETA      = 0;                                    // 清零 角度
    FOC_RTHEACC     = 0;                                    // 清零 爬坡函数的初始加速度
    FOC__RTHESTEP   = 0;                                    // 清零 爬坡速度
    FOC__RTHECNT     = 0;                                    // 清零 爬坡次数

    FOC__THECOMP = _Q15(-5.0 / 180.0); // SMO 估算补偿角
    FOC__THECOR      = 0x04;                                 // 误差角度补偿
    /*电流环参数配置*/
    FOC_DMAX        = DOUTMAX;
    FOC_DMIN        = DOUTMIN;
    FOC_QMAX        = QOUTMAX;
    FOC_QMIN        = QOUTMIN;
    /*位置估算参数配置*/
    FOC_EK1         = OBS_K1T;
    FOC_EK2         = OBS_K2T;
    FOC_EK3         = 0.2*OBS_K3T;
    FOC_EK4         = OBS_K4T;
    FOC_FBASE       = OBS_FBASE;
    FOC_OMEKLPF     = SPEED_KLPF;
    FOC_EBMFK       = OBS_KLPF;
    FOC_TGLI        = 0x00;
    /*********PLL或SMO**********/
    #if (EstimateAlgorithm == SMO)
    {
        ClrBit(FOC_CR2, ESEL);
        FOC_KSLIDE    = OBS_KSLIDE;
        FOC_EKLPFMIN  = OBS_EA_KS;
    }
    #elif (EstimateAlgorithm == PLL)
    {
        SetBit(FOC_CR2, ESEL);
        FOC_KSLIDE    = OBSE_PLLKP_GAIN;
        FOC_EKLPFMIN  = OBSE_PLLKI_GAIN;
    }
    #endif //end SVPMW_Mode
    SetBit(FOC_CR1, SVPWMEN);                               // SVPWM模式
    
    if (MotorSpeed.TargetFR == CW)
    {
        ClrBit(DRV_CR, DDIR);                               // 反转标志位
    }
    else
    {
        SetBit(DRV_CR, DDIR);                               // 反转标志位
    }
    
    /**过调制**/
    #if (OverModulation == 1)
    {
        SetBit(FOC_CR1, OVMDL);                             // 过调制
    }
    #endif
    #if(VOLTAGE_MODE ==INTERNAL)
    {
        SetBit(FOC_CR0, UCSEL);
    }
    #else
    {
        ClrBit(FOC_CR0, UCSEL);
    }
    #endif
    /*单电阻采样；需要最小采样窗,FOC_TRGDLY为0，七段式SVPWM方式*/
    #if (Shunt_Resistor_Mode == Single_Resistor)
    {
        SetReg(FOC_CR1, CSM0 | CSM1, 0x00);
        FOC_TSMIN  = PWM_TS_LOAD;                           // 最小采样窗口
        FOC_TRGDLY = 0x0F;                                  // 采样时刻在中点，一般考虑开关噪声影响，会设置延迟；
        // 0x0c表示延迟12个clock，提前用反码形式，如0x84表示提前12个clock。
        ClrBit(FOC_CR2, F5SEG);                             // 7段式
        SetReg(CMP_CR1, CMP3MOD0 | CMP3MOD1, 0x00);
    }
    /*双电阻采样，可设置死区补偿值，在下降沿结束前开始采样Ia，配置81*/
    #elif (Shunt_Resistor_Mode == Double_Resistor)          // double resistor sample
    {
        SetReg(FOC_CR1, CSM0 | CSM1, CSM0);
        FOC_TSMIN = PWM_DT_LOAD;                            // 死区补偿值
        FOC_TRGDLY = 0x06;                                  // ADC采样的时刻，采样时刻在计数器零点附近，83为下降沿结束前3个clock采样Ia，与单电阻不同
        // 01为上升沿开始后第一个clock开始采样。根据实际情况调整。
        FOC_TBLO = PWM_DLOWL_TIME;                          //下桥臂最小脉冲，保证采样
        SetReg(CMP_CR1, CMP3MOD0 | CMP3MOD1, 0x00);
        /*五段式或七段式选择*/
        #if (SVPMW_Mode == SVPWM_7_Segment)
        {
            ClrBit(FOC_CR2, F5SEG);                         // 7段式
        }
        #elif (SVPMW_Mode == SVPWM_5_Segment)
        {
            SetBit(FOC_CR2, F5SEG);                         // 5段式
        }
        #endif
        #if (DouRes_Sample_Mode == DouRes_1_Cycle)
        {
            ClrBit(FOC_CR2, DSS);                           // 7段式
        }
        #elif (DouRes_Sample_Mode == DouRes_2_Cycle)
        {
            SetBit(FOC_CR2, DSS);                           // 5段式
        }
        #endif //end DouRes_Sample_Mode
    }
    /*三电阻采样*/
    #elif (Shunt_Resistor_Mode == Three_Resistor)           // signel resistor sample
    {
        SetReg(FOC_CR1, CSM0 | CSM1, CSM0 | CSM1);          // 三电阻
        FOC_TSMIN  = PWM_DT_LOAD;                           // 死区补偿值
        FOC_TRGDLY = 0x06;                                  // ADC采样的时刻，采样时刻在计数器零点附近，83为下降沿结束前3个clock采样Ia，与单电阻不同。
        // 01为上升沿开始后第一个clock开始采样。根据实际情况调整。
        SetReg(CMP_CR1, CMP3MOD0 | CMP3MOD1, CMP3MOD0 | CMP3MOD1);
        FOC_TBLO = PWM_OVERMODULE_TIME;                     // 过调制电流采样处理的TB脉宽
        /*五段式或七段式选择*/
        #if (SVPMW_Mode == SVPWM_7_Segment)
        {
            ClrBit(FOC_CR2, F5SEG);                         // 7段式
        }
        #elif (SVPMW_Mode == SVPWM_5_Segment)
        {
            SetBit(FOC_CR2, F5SEG);                         // 5段式
        }
        #endif //end SVPMW_Mode
        #if (DouRes_Sample_Mode == DouRes_1_Cycle)
        {
            ClrBit(FOC_CR2, DSS);                           // 7段式
        }
        #elif (DouRes_Sample_Mode == DouRes_2_Cycle)
        {
            SetBit(FOC_CR2, DSS);                           // 5段式
        }
        #endif //end DouRes_Sample_Mode
    }
    #endif  //end Shunt_Resistor_Mode
    /* 使能电流基准校正 */
    #if (CalibENDIS == Enable)
    {
        if (mcCurOffset.OffsetFlag == 1)
        {
            #if (Shunt_Resistor_Mode == Single_Resistor)    // 单电阻校正
            {
                /*set ibus current sample offset*/
                SetReg(FOC_CR2, CSOC0 | CSOC1, 0x00);
                FOC_CSO = mcCurOffset.Iw_busOffset;         // 写入Ibus的偏置
            }
            #elif (Shunt_Resistor_Mode == Double_Resistor)  // 双电阻校正
            {
                /*set ia, ib current sample offset*/
                SetReg(FOC_CR2, CSOC0 | CSOC1, CSOC0);
                FOC_CSO  = mcCurOffset.IuOffset;            // 写入IA的偏置
            
                SetReg(FOC_CR2, CSOC0 | CSOC1, CSOC1);
                FOC_CSO  = mcCurOffset.IvOffset;            // 写入IB的偏置
            }
            #elif (Shunt_Resistor_Mode == Three_Resistor)   // 三电阻校正
            {
                /*set ibus current sample offset*/
                SetReg(FOC_CR2, CSOC0 | CSOC1, CSOC0);
                FOC_CSO = mcCurOffset.IuOffset;             // 写入IA的偏置
            
                SetReg(FOC_CR2, CSOC0 | CSOC1, CSOC1);
                FOC_CSO = mcCurOffset.IvOffset;             // 写入IB的偏置
            
                SetReg(FOC_CR2, CSOC0 | CSOC1, 0x00);
                FOC_CSO = mcCurOffset.Iw_busOffset;         // 写入IC的偏置
            }
            #endif  //end Shunt_Resistor_Mode
        }
    }
    #endif  //end CalibENDIS
    /*-------------------------------------------------------------------------------------------------
    DRV_CTL：PWM来源选择
    OCS = 0, DRV_COMR
    OCS = 1, FOC/SVPWM/SPWM
    -------------------------------------------------------------------------------------------------*/
    SetBit(DRV_CR, OCS);
	SetBit(DRV_CR, DRVEN);  //计数器使能       0-->Disable     1-->Enable
}



/**
 * @brief     预充电，当一直处于预充电状态下，不接电机，可用于验证IPM或者Mos。
                     预充电分三步，第一步是对U相进行预充电，第二步是对U,V两相进行预充电;第三步是对U、V、W三相进行预充电。
 * @date      2022-09-12
 */
void Motor_Charge(void)
{
    if (McStaSet.SetFlag.ChargeSetFlag == 0)
    {
        McStaSet.SetFlag.ChargeSetFlag = 1;
        DRV_DR = 0.1 * DRV_ARR;              //下桥臂10% duty
        /*-------------------------------------------------------------------------------------------------
        DRV_CTL：PWM来源选择
        OCS = 0, DRV_COMR
        OCS = 1, FOC/SVPWM/SPWM
        -------------------------------------------------------------------------------------------------*/
        ClrBit(DRV_CR, OCS);
        DRV_CMR &= 0xFFc0;
        DRV_CMR |= 0x3F;                         // U相输出
        MOE = 1;
    }
}


/**
 * @brief     预定位函数，当无逆风判断时，采用预定位固定初始位置;当有逆风判断时，采用预定位刹车
 * @date      2022-09-12
 */
void Motor_Align(void)
{
    if (McStaSet.SetFlag.AlignSetFlag == 0)
    {
        McStaSet.SetFlag.AlignSetFlag = 1;
        /* -----FOC初始化----- */
        FOC_Init();
        /*配置预定位的电压、KP、KI*/
        FOC_IQREF = IQ_Align_CURRENT;
        FOC_IDREF = IQ_Align_CURRENT;               //定义电压
        FOC_DQKP  = DQKP_Alignment;
        FOC_DQKI  = DQKI_Alignment;
        FOC_EKP   = OBSW_KP_GAIN;
        FOC_EKI   = OBSW_KI_GAIN;
        /*配置预定位角度*/
        FOC__THETA  = mcFocCtrl.mcPosCheckAngle;
		
		 #if (AlignTestMode==1)
        {
            FOC__THETA      = Align_Theta;
        }
        #else
        {
            #if (PosCheckEnable==1)
            {
                FOC__THETA    = mcFocCtrl.mcPosCheckAngle;
            }
            #else
            {
                FOC__THETA      = Align_Theta;
            }
            #endif
        }
        #endif
        /*********PLL或SMO**********/
        #if (EstimateAlgorithm == SMO)
        {
            FOC__ETHETA   = FOC__THETA - 4096;
        }
        #elif (EstimateAlgorithm == PLL)
        {
            FOC__ETHETA   = FOC__THETA;
        }
        #endif //end    EstimateAlgorithm
        mcFocCtrl.State_Count = Align_Time;
        ClrBit(FOC_CR2, UDD);
        ClrBit(FOC_CR2, UQD);
        /*使能输出*/
        DRV_CMR |= 0x3F;                         // U、V、W相输出
        MOE = 1;
    }
}


/**
 * @brief     开环启动的参数配置
 * @date      2022-09-12
 */
void Motor_Open(void)
{   
	#if (AlignTestMode == 0)
	{
		DRV_CMR|=0x3F;
		MOE=1;
    }
	#endif
    #if (Open_Start_Mode == Open_Start)
    static uint8 OpenRampCycles = 0;
    #endif
    
    if (McStaSet.SetFlag.StartSetFlag == 0)
    {
        McStaSet.SetFlag.StartSetFlag = 1;
        FOC_Init();
        FOC__UD = 0;
        FOC__UQ = _Q15(0.01);                                //Uq给一个初始值，防止IQ给定瞬间电流太大
        ClrBit(FOC_CR2, UDD);
        ClrBit(FOC_CR2, UQD);
        /****启动初始角度赋值****/
        FOC__THETA  =  mcFocCtrl.mcPosCheckAngle;
		
		 #if (PosCheckEnable)
        {
            FOC__THETA  = mcFocCtrl.mcPosCheckAngle;                                                // 有初始位置检测，则用初始位置角
        }
        #else
        {
            FOC__THETA  = Align_Theta;                                                              // 无初始位置检测，则用预定位角
        }
        #endif
        /*启动电流、KP、KI、FOC_EKP、FOC_EKI*/
        FOC_IDREF = ID_Start_CURRENT;                         // D轴启动电流
        mcFocCtrl.mcIqref = IQ_Start_CURRENT;                 // Q轴启动电流
        FOC_DQKP = DQKPStart;
        FOC_DQKI = DQKIStart;
        FOC_EKP  = OBSW_KP_GAIN;
        FOC_EKI  = OBSW_KI_GAIN;
        /*启动方式选择*/
        #if (Open_Start_Mode == Omega_Start)              // Omega 启动
        {
            FOC_EFREQACC  = Motor_Omega_Ramp_ACC;
            FOC_EFREQMIN  = MOTOR_OMEGA_RAMP_MIN;
            FOC_EFREQHOLD = MOTOR_OMEGA_RAMP_END;
            SetReg(FOC_CR1, EFAE | RFAE | ANGM, EFAE | ANGM);
        }
        #elif (Open_Start_Mode == Open_Start)
        {
            FOC_RTHEACC      = Motor_Open_Ramp_ACC;      // 爬坡函数的初始加速度
            FOC__RTHESTEP    = Motor_Open_Ramp_Min;      // 0.62 degree acce speed
            FOC_RTHECNT      = MOTOR_OPEN_ACC_CNT;       // acce time
            SetReg(FOC_CR1, EFAE | RFAE | ANGM, RFAE);
        }
        #elif (Open_Start_Mode == Open_Omega_Start)
        {
            FOC_RTHEACC   = Motor_Open_Ramp_ACC;         // 爬坡函数的初始加速度
            FOC__RTHESTEP = Motor_Open_Ramp_Min;         // 0.62 degree acce speed
            FOC__RTHECNT  = MOTOR_OPEN_ACC_CNT;          // acce time
            FOC_EFREQACC  = Motor_Omega_Ramp_ACC;
            FOC_EFREQMIN  = Motor_Omega_Ramp_Min;
            FOC_EFREQHOLD = Motor_Omega_Ramp_End;
            SetReg(FOC_CR1, EFAE | RFAE | ANGM, EFAE | RFAE | ANGM);
        }
        #endif //end Open_Start_Mode
    }
    
    /*不同启动方式下，切换到MCRUN状态*/
    #if (Open_Start_Mode == Open_Start)         //OPEN状态启动时拖动多次
    {
        if (OpenRampCycles < (MOTOR_OPEN_ACC_CYCLE - 1))
        {
            if (!ReadBit(FOC_CR1, RFAE))
            {
                SetBit(FOC_CR1, RFAE);
                OpenRampCycles++;
            }
        }
        else
        {
            mcFocCtrl.State_Count = 2;
            SetBit(FOC_CR1, ANGM);
        }
        
        FOC_EKP = OBSW_KP_GAIN_RUN4;                            // 估算器里的PI的KP
        FOC_EKI = OBSW_KI_GAIN_RUN4;                            // 估算器里的PI的KI
    }
    #elif (Open_Start_Mode == Open_Omega_Start)
    {
        mcFocCtrl.State_Count = 2600;
    }
    #elif (Open_Start_Mode == Omega_Start)
    {
        /*********PLL或SMO**********/
        #if (EstimateAlgorithm == SMO)
        {
            mcFocCtrl.State_Count = 2780;
        }
        #elif (EstimateAlgorithm == PLL)
        {
            mcFocCtrl.State_Count = 1680;
            FOC_EKP = OBSW_KP_GAIN_RUN4;                       // 估算器里的PI的KP
            FOC_EKI = OBSW_KI_GAIN_RUN4;                       // 估算器里的PI的KI
        }
        #endif
    }
    #endif
    FOC_IQREF = mcFocCtrl.mcIqref;                          // Q轴启动电流
}


/**
 * @brief     顺风逆风参数配置函数
 * @date      2022-09-12
 */
void Motor_TailWind(void)
{
    if (mcFocCtrl.State_Count == 0)
    {
        if (McStaSet.SetFlag.TailWindSetFlag  == 0) //初始化
        {
            McStaSet.SetFlag.TailWindSetFlag = 1;
            #if (TailWind_Mode ==RSDMethod)
            {
                RSDDetectInit();
            }
            #elif (TailWind_Mode ==BEMFMethod)
            {
                BEMFDetectInit();
            }
            #elif (TailWind_Mode ==FOCMethod)
            {
                FOCTailWindInit();
            }
            #endif
        }
		
		
		 if (McStaSet.SetFlag.TailWindSetFlag == 1)
        {
            #if (TailWind_Mode==RSDMethod)
            {
                RSDDealwith();
            }
            #elif (TailWind_Mode==BEMFMethod)
            {
                BEMFDealwith();
            }          
            #elif (TailWind_Mode==FOCMethod)
            {
                TailWindDealwith();
            }            
            #endif
        }
    }
}

/**
 * @brief     Motor_Stop电机停止控制
 * @date      2022-09-12
 */
void Motor_Stop(void)
{
    if ((mcFocCtrl.SpeedFlt < S_Value(12000.0)) || (mcFocCtrl.State_Count == 0))
    {
        #if (StopBrake_Enble == 0)
        {
            mcState = mcReady;
            FOC_CR1 = 0x00;
            ClrBit(DRV_CR, FOCEN);   //关闭FOC
            ClrBit(DRV_CR, DRVEN);
            MOE = 0;
           // mcFocCtrl.State_Count = 100;
        }
        #else
        {
            if (mcFocCtrl.SpeedFlt < MOTOR_LOOP_MIN)
            {
                ClrBit(DRV_CR, DRVEN);
                FOC_CR1 = 0x00;
                ClrBit(DRV_CR, FOCEN);
                MOE = 0;
                DRV_DR   = DRV_ARR + 1;
                DRV_CMR  = 0x00;
                DRV_CMR |= 0x015;     // 三相下桥臂通，刹车
                ClrBit(DRV_CR, OCS);  // OCS = 0, DRV_COMR;OCS = 1, FOC/SVPWM/SPWM
                SetBit(DRV_CR, DRVEN);
                MOE = 1;
                mcState  = mcBrake;
                mcFocCtrl.State_Count = StopWaitTime;
            }
            else
            {
                FOC_IQREF = 0;
            }
        }
        #endif
    }
    else if (MotorSpeed.FlagONOFF)
    {
    	if (mcFocCtrl.SpeedFlt < S_Value(100.0))
    	{
    		mcState = mcReady;
    		FOC_CR1 = 0x00;
    		ClrBit(DRV_CR, FOCEN);   //关闭FOC
    		ClrBit(DRV_CR, DRVEN);
    		MOE = 0;
    		//mcFocCtrl.State_Count = 100;
    	}
    	else
    	{
    		mcState = mcRun;
    		mcFocCtrl.CtrlMode = 1;
    	}
    }
}


/**
 * @brief        控制变量初始化清零,包括保护参数的初始化、电机状态初始化
 * @date         2022-09-04
 */
void MotorcontrolInit(void)
{
    /* -----保护参数初始化----- */
    memset(&mcFaultDect, 0, sizeof(FaultVarible));        // FaultVarible变量清零
    /* -----保护次数初始化----- */
    memset(&mcProtectTime, 0, sizeof(ProtectVarible));    // ProtectVarible保护次数清零
    /* -----过流保护----- */
    memset(&mcCurVarible, 0, sizeof(CurrentVarible));     // 电流保护的变量清零
    /* -----电流偏置校准变量初始化----- */
    memset(&mcCurOffset, 0, sizeof(CurrentOffset));        // mcCurOffset变量清零
    
    memset(&FGFault_feedback, 0, sizeof(FGFAULTFEEDBACK));//故障反馈变量清零
    memset(&Restart, 0, sizeof(FaultRecoverTypedef));//重启变量清零
    #if(SPEED_MODE == ONOFFTEST)
    {
        /* -----启停测试参数初始化----- */
        memset(&ONOFFTest, 0, sizeof(ONVarible));
    }
    #endif
    /*****电机状态机时序变量***********/
    McStaSet.SetMode                   = 0;
    /**********电机目标方向*************/
    #if (FRMODE == CW)
    {
        MotorSpeed.TargetFR                 = CW;
    }
    #else
    {
        MotorSpeed.TargetFR                 = CCW;
    }
    #endif
    mcCurOffset.IuOffsetSum            = 16383;
    mcCurOffset.IvOffsetSum            = 16383;
    mcCurOffset.Iw_busOffsetSum        = 16383;
}


/**
 * @brief        初始化电机参数
 * @date         2022-09-04
 */
void VariablesPreInit(void)
{
    mcFaultSource = 0;
    /* -----保护参数初始化----- */
    memset(&mcFaultDect, 0, sizeof(FaultVarible));                                                                 // FaultVarible变量清零
    /* -----外部控制环参数初始化----- */
    memset(&mcFocCtrl, 0, sizeof(FOCCTRL));                                                                // mcFocCtrl变量清零
    /*****电机状态机时序变量***********/
    McStaSet.SetMode                  = 0x01;   //电流校准标志位置1，其它置0
    mcFocCtrl.State_Count = 0;
}


/**
 * @brief        上电时，先对硬件电路的电流进行采集，写入对应的校准寄存器中。
                     调试时，需观察mcCurOffset结构体中对应变量是否在范围内。采集结束后，OffsetFlag置1。
 * @date         2022-09-04
 */
void GetCurrentOffset(void)
{
    if (!mcCurOffset.OffsetFlag)
    {
        SetBit(ADC_CR, ADCBSY);             // 使能ADC
        
        while (ReadBit(ADC_CR, ADCBSY));
        
        #if (Shunt_Resistor_Mode == Single_Resistor)                   //单电阻模式
        {
            mcCurOffset.Iw_busOffsetSum += ((ADC4_DR & 0x7ff8));
            mcCurOffset.Iw_busOffset     = mcCurOffset.Iw_busOffsetSum >> 4;
            mcCurOffset.Iw_busOffsetSum -= mcCurOffset.Iw_busOffset;		
        }
        #elif (Shunt_Resistor_Mode == Double_Resistor)                 //双电阻模式
        {
            mcCurOffset.IuOffsetSum     += ((ADC0_DR & 0x7ff8));
            mcCurOffset.IuOffset         = mcCurOffset.IuOffsetSum >> 4;
            mcCurOffset.IuOffsetSum     -= mcCurOffset.IuOffset;
            mcCurOffset.IvOffsetSum     += ((ADC1_DR & 0x7ff8));
            mcCurOffset.IvOffset         = mcCurOffset.IvOffsetSum >> 4;
            mcCurOffset.IvOffsetSum     -= mcCurOffset.IvOffset;
            mcCurOffset.Iw_busOffsetSum += ((ADC4_DR & 0x7ff8));
            mcCurOffset.Iw_busOffset     = mcCurOffset.Iw_busOffsetSum >> 4;
            mcCurOffset.Iw_busOffsetSum -= mcCurOffset.Iw_busOffset;
        }
        #elif (Shunt_Resistor_Mode == Three_Resistor)                 //三电阻模式
        {
            mcCurOffset.IuOffsetSum     += ((ADC0_DR & 0x7ff8));
            mcCurOffset.IuOffset         = mcCurOffset.IuOffsetSum >> 4;
            mcCurOffset.IuOffsetSum     -= mcCurOffset.IuOffset;
            mcCurOffset.IvOffsetSum     += ((ADC1_DR & 0x7ff8));
            mcCurOffset.IvOffset         = mcCurOffset.IvOffsetSum >> 4;
            mcCurOffset.IvOffsetSum     -= mcCurOffset.IvOffset;
            mcCurOffset.Iw_busOffsetSum += ((ADC4_DR & 0x7ff8));
            mcCurOffset.Iw_busOffset     = mcCurOffset.Iw_busOffsetSum >> 4;
            mcCurOffset.Iw_busOffsetSum -= mcCurOffset.Iw_busOffset;
        }
        #endif
        mcCurOffset.OffsetCount++;
        
        if (mcCurOffset.OffsetCount > Calib_Time)
        {
            mcCurOffset.OffsetFlag = 1;
			#if (OffsetProtectEn)
			{
				Fault_GetCurrentOffset();
			}
			#endif
        }
    }
}


/**
 * @brief        变量初始化
 * @date         2022-09-04
 */
void Motor_Ready(void)
{
    if (McStaSet.SetFlag.CalibFlag == 0)
    {
        McStaSet.SetFlag.CalibFlag = 1;
        ClrBit(DRV_CR, FOCEN);
        ClrBit(DRV_CR, DRVEN);
        MOE = 0;
    }
}


/**
 * @brief        对电机相关变量、PI进行初始化设置
 * @date         2022-09-04
 */
void Motor_Init(void)
{
    VariablesPreInit();                           // 电机相关变量初始化
    SetBit(DRV_CR, DRVEN);
}



/**
 * @brief        获取控制的目标值
 * @date         2022-09-04
 */
void TargetSpeed_Colletion(void)
{
    #if (SPEED_MODE == PWMMODE)
    {   
        /* PWM调速曲线  */
        PWMInputCapture();
		APP_DIV();
    
        /* PWM故障反馈  */
        PWM_OUT();
    }
    #elif (SPEED_MODE == NONEMODE)
    {
        MotorSpeed.FlagONOFF   = 1;                                  //启动标志
        MotorSpeed.TargetValue =	MOTOR_LOOP_MAX;     //固定转速赋值
    }
    #elif (SPEED_MODE == SREFMODE)
    {
        VSPSample();
    }
    #elif (SPEED_MODE == SCLKMODE)
    {
        SCLKInputCapture();
    }
    #elif (SPEED_MODE == ONOFFTEST)
    {
        ONOFF_Starttest();
    }
    #endif
}

///**
// * @brief        FR控制逻辑
// * @date         2022-09-04
// */
//void  FRControl(void)
//{
//    static uint16 CWCCWDelay = 0;
//    
//    if ((FRPin != MotorSpeed.TargetFR ) && (MotorSpeed.FlagFR == 0)) //CCW
//    {
//        if (CWCCWDelay ++ == 500)
//        {
//            CWCCWDelay = 0;
//            mcFocCtrl.State_Count = 10000;
//            MotorSpeed.FlagFR = 1;
//        }
//    }
//    
//    if (MotorSpeed.FlagFR)
//    {
//        mcState = mcStop;
//        FOC_IQREF = 0;                           //6832关闭桥区会可能会出现刹车的情况
//        MotorSpeed.FlagONOFF = 0;
//        
//        if (mcFocCtrl.SpeedFlt < _Q15(150.0 / MOTOR_SPEED_BASE))
//        {
//            MotorSpeed.FlagFR = 0;
//            mcState  = mcBrake;
//            MotorSpeed.TargetFR = FRPin;
//            mcFocCtrl.State_Count = 2500;
//        }
//    }
//}
