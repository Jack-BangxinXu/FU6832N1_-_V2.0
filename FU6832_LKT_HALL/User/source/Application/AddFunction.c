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

/* Private variables ---------------------------------------------------------*/
FaultStateType             mcFaultSource;
PWMINPUTCAL        xdata   mcPwmInput;
FaultVarible       xdata   mcFaultDect;
CurrentVarible     mcCurVarible;
ProtectVarible     xdata   mcProtectTime;

FOCCTRL            xdata   mcFocCtrl;
ONVarible          ONOFFTest;
MCRAMP             xdata   MotorSpeed;
uint16 xdata Power_Currt;

FGFAULTFEEDBACK xdata FGFault_feedback; ///< FG故障反馈结构体变量
float feedbackTtime = 0; // 故障反馈拉低时间s

/*  -------------------------------------------------------------------------------------------------
    Function Name  : Abs_F32
    Description    : 对变量取32位的绝对值
    Date           : 2020-04-10
    Parameter      : value: [输入/出]
    ------------------------------------------------------------------------------------------------- */
uint32 Abs_F32(int32 value)
{
    if (value < 0)
    {
        return (-value);
    }
    else
    {
        return (value);
    }
}


uint16 Abs_F16(int16 value)
{
    if (value < 0)
    {
        return (-value);
    }
    else
    {
        return (value);
    }
}
/* -------------------------------------------------------------------------------------------------
    Function Name  : PWMInputCapture
    Description    : 输入PWM处理
    Date           : 2020-04-10
    Parameter      : None
------------------------------------------------------------------------------------------------- */
void PWMInputCapture(void)
{
     uint16 MotorSpeedVSP;
    
    if (mcPwmInput.PwmUpdateFlag == 1) // 有新的duty更新
    {
        if ((Abs_F32(mcPwmInput.PwmCompare - mcPwmInput.PwmCompareOld) < 500) // 两次比较值相近，减少读错率
            && (Abs_F32(mcPwmInput.PwmArrOld - mcPwmInput.PwmArr) < 500)      // 两次周期值相近，减少读错率
            && (mcPwmInput.PwmDivFlag == 0) && (mcPwmInput.PwmDealFlag == 0))
        {
            mcPwmInput.PwmFlag          = 1;                           // PwmFlag置1期间，不读取TIM3__DR和TIM3__ARR;，防止出错
            mcPwmInput.PwmCompareUpdate = (mcPwmInput.PwmCompare >> 1);// 对其乘以32768
            mcPwmInput.PwmArrUpdate     = mcPwmInput.PwmArr;
            mcPwmInput.PwmDivFlag       = 1;                           // 启动除法
            mcPwmInput.PwmFlag          = 0;
            mcPwmInput.PwmDealFlag      = 1;                           // 更新PWM后必须进过一次PWM判断才能重新进入
        }
		
		if ((mcPwmInput.PwmDivFlag == 0) && (mcPwmInput.PwmDealFlag == 1))
        {
            mcPwmInput.PwmDealFlag    = 0;
            /***速度随PWM增大而增大***/
            #if (PWMDUTY_Choose == NegaPWMDUTY)
            {
                MotorSpeedVSP = 32768 - mcPwmInput.PwmDuty;
            }
            /***速度随PWM增大而减小***/
            #elif (PWMDUTY_Choose == PosiPWMDUTY)
            {
                MotorSpeedVSP = mcPwmInput.PwmDuty;
            }
            #endif
            if ( (mcPwmInput.PwmArr>=759) && (mcPwmInput.PwmArr<=18750) ) //分频375KHZ,频率范围500HZ-20HZ
			{
				if (((MotorSpeedVSP >= _Q15(0.118)) &&(MotorSpeedVSP <= _Q15(1.0) ))||((MotorSpeedVSP > _Q15(0.0098)) &&(MotorSpeedVSP < _Q15(0.07) )))
				{
					MotorSpeed.FlagONOFF = 1;
				}
				else if (((MotorSpeedVSP < _Q15(0.115)) && (MotorSpeedVSP >= _Q15(0.07)))||(MotorSpeedVSP <= _Q15(0.0098)))
				{
					MotorSpeed.FlagONOFF = 0;
				}
				//转速曲线计算
				if (MotorSpeed.FlagONOFF == 1)
				{
					#if (Motor_Speed_Control_Mode == SPEED_LOOP_CONTROL)
					{
						if ((MotorSpeedVSP <= _Q15(0.07)) || (MotorSpeedVSP >= _Q15(0.85)))   //最大转速运行
						{
							MotorSpeed.TargetValue = MOTOR_LOOP_MAX;
						}
						else if ((MotorSpeedVSP >= _Q15(0.13)) && (MotorSpeedVSP < _Q15(0.85))) //调速曲线
						{
							MotorSpeed.TargetValue = MOTOR_LOOP_MIN + LOOP_K  * (MotorSpeedVSP - MINPWMDuty);
						}
                        else if((MotorSpeedVSP < _Q15(0.13))) //最小转速运行
                        {
                            MotorSpeed.TargetValue = MOTOR_LOOP_MIN;
                        }
                                
					}
				   #endif
				}
				else
				{
					MotorSpeed.TargetValue = 0;
				}
		}
        else //不在设定频率范围内
        {
           MotorSpeed.FlagONOFF = 1;
           if (MotorSpeed.FlagONOFF == 1)
           {   
              MotorSpeed.TargetValue = MOTOR_LOOP_MAX;
           }
        }
   }
        
        mcPwmInput.PwmUpdateFlag = 0;
        mcPwmInput.PwmCompareOld = mcPwmInput.PwmCompare;//将此次比较值赋值给上次比较值
        mcPwmInput.PwmArrOld     = mcPwmInput.PwmArr;//将此次周期值赋值给上次周期值
		
		
	}

}
// FG拉低
void FG_OUT(float htime)
{
    FGFault_feedback.CycleTime = htime * 1000 + 2000; // 周期=拉低时间+放开时间
    FGFault_feedback.CycleTimeCnt++;
    if (FGFault_feedback.CycleTimeCnt < FGFault_feedback.CycleTime)
    {
        if (FGFault_feedback.LowlevelCnt < htime * 1000) // 按时间拉低
        {
            FGFault_feedback.LowlevelCnt++;
            GP01 = 1; // 拉低
        }
        else
        {
            GP01 = 0; // 释放
        }
    }
    else if (FGFault_feedback.CycleTimeCnt >= FGFault_feedback.CycleTime)
    {
        FGFault_feedback.CycleTimeCnt = 0;
        FGFault_feedback.LowlevelCnt = 0;
    }
}
// 确认故障信息
void PWM_OUT(void)
{
    // 堵转重启大于五次开始反馈
    if ((mcFaultSource == FaultStall) && (Restart.Stall_Times > 5))
    {
		Restart.StallFeedbackFlag = 1;
    }


    // 过流重启大于三次开始反馈
    if (((mcFaultSource == FaultHardOVCurrent) || (mcFaultSource == FaultSoftOVCurrent)) && (Restart.OverCurrent_Times > 3))
    {
		Restart.CurrentPretectFeedbackFlag = 1;
    }

    // 过压
    if (mcFaultSource == FaultOverVoltageDC)
    {
        Restart.OverVolFeedbackFlag = 1;
    }


    // 欠压
    if (mcFaultSource == FaultUnderVoltageDC)
    {
        Restart.UnderVolFeedbackFlag = 1;
    }


    // 过温
//    if ((mcFaultSource == FaultNtcOTErr) || (mcFaultSource == FaultTSD))
    if ((mcFaultSource == FaultNtcOTErr))
    {
        Restart.TempProtectFeedbackFlag = 1;
    }



    // 故障反馈完整周期后更新故障类型
    if (FGFault_feedback.CycleTimeCnt == 0)
    {
        if(Restart.StallFeedbackFlag == 1)
        {
            feedbackTtime = 1.5;
        }
        else if (Restart.CurrentPretectFeedbackFlag == 1)
        {
            feedbackTtime = 1.5;
        }
        else if(Restart.UnderVolFeedbackFlag == 1)
        {
            feedbackTtime = 2.0;
        }
        else if(Restart.OverVolFeedbackFlag == 1)
        {
            feedbackTtime = 2.5;
        }
		else if(Restart.TempProtectFeedbackFlag == 1)
        {
            feedbackTtime = 3.0;
        }
        else
        {
            feedbackTtime = 0;
        }
    }


	// 开始反馈
    FG_OUT(feedbackTtime);

    // 正常运行超过15S，清除所有故障次数与时间
    if ((mcState == mcRun) && (mcFocCtrl.CtrlMode == 1))
    {
        if (Restart.AllReCnt < 15000)
        {
            Restart.AllReCnt++;
        }
        else
        {
            memset(&Restart, 0, sizeof(FaultRecoverTypedef));
        }
    }
    
}


/* -------------------------------------------------------------------------------------------------
    Function Name  : SCLKInputCapture
    Description    : 输入PWM频率处理
    Date           : 2020-04-10
    Parameter      : None
------------------------------------------------------------------------------------------------- */
void SCLKInputCapture(void)
{
    if (mcPwmInput.PwmUpdateFlag == 1) // 有新的duty更新
    {
        if (Abs_F32(mcPwmInput.PwmArrOld - mcPwmInput.PwmArr) < 100)  // 两次周期值相近，减少读错率
        {
            DivQ_L_MDU(TIM3_FreH, TIM3_FreL, mcPwmInput.PwmArr, mcPwmInput.PwmSclk);
            
            if ((mcPwmInput.PwmSclk > ONPWMSclk) && (mcPwmInput.PwmSclk <= (OFFPWMSclkHigh + 1)))
            {
                MotorSpeed.FlagONOFF = 1;
            }
            else if (mcPwmInput.PwmSclk < OFFPWMSclk)
            {
                MotorSpeed.FlagONOFF = 0;
            }
            
            //转速曲线计算
            if (MotorSpeed.FlagONOFF == 1)
            {
                if (mcPwmInput.PwmSclk <= MINPWMSclk)
                {
                    MotorSpeed.TargetValue = MOTOR_LOOP_MIN;
                }
                else if (mcPwmInput.PwmSclk < MAXPWMSclk)
                {
                    MotorSpeed.TargetValue = SCLK_SPEED_K * mcPwmInput.PwmSclk;
                }
                else                    //最大转速运行
                {
                    MotorSpeed.TargetValue = MOTOR_LOOP_MAX;
                }
            }
            else
            {
                MotorSpeed.TargetValue = 0;
            }
        }
        
        mcPwmInput.PwmUpdateFlag = 0;
        mcPwmInput.PwmArrOld     = mcPwmInput.PwmArr;//将此次周期值赋值给上次周期值
    }
}

/*  -------------------------------------------------------------------------------------------------
    Function Name  : VSPSample
    Description    : VSP采样
    Date           : 2020-04-10
    Parameter      : None
    ------------------------------------------------------------------------------------------------- */
void VSPSample(void)
{
    static uint16 MotorSpeedVSP;
    static uint16 MotorSpeedVSP_LSB;
    /*****VREF的采样获取值并滤波******/
    LPF_MDU(ADC7_DR, 30, MotorSpeedVSP, MotorSpeedVSP_LSB);   //低通滤波

    if ((MotorSpeedVSP > ONPWMDuty))  //在ONPwmDuty-OFFPwmDutyHigh之间，电机有转速运行
    {
    	MotorSpeed.FlagONOFF = 1;
    }
    else if ((MotorSpeedVSP < OFFPWMDuty)) //电机停机
    {
    	MotorSpeed.FlagONOFF = 0;
    }

    /* -----转速曲线计算----- */
    if (MotorSpeed.FlagONOFF == 1)                        //
    {
    	#if (Motor_Speed_Control_Mode == SPEED_LOOP_CONTROL)
                {
                	
                    if (MotorSpeedVSP <= MINPWMDuty)   //最小转速运行
                    {
                        MotorSpeed.TargetValue = MOTOR_LOOP_MIN;
                    }
                    else if (MotorSpeedVSP < MAXPWMDuty) //调速
                    {
                        MotorSpeed.TargetValue = MOTOR_LOOP_MIN + LOOP_K * (MotorSpeedVSP - MINPWMDuty);
                    }
                    else                    //最大转速运行
                    {
                  
                    	  MotorSpeed.TargetValue = MOTOR_LOOP_MAX;
           
                    }
                }
                #elif (Motor_Speed_Control_Mode == POWER_LOOP_CONTROL)
                {
                    if (MotorSpeedVSP <= MINPWMDuty)   //最小转速运行
                    {
                        MotorSpeed.TargetValue = Motor_Min_Power;
                    }
                    else if (MotorSpeedVSP < MAXPWMDuty) //调速
                    {
                        MotorSpeed.TargetValue = Motor_Min_Power + POWER_K * (MotorSpeedVSP - MINPWMDuty);
                    }
                    else             //最大转速运行
                    {
                        MotorSpeed.TargetValue = Motor_Max_Power;
                    }
                }
                #elif (Motor_Speed_Control_Mode == CURRENT_LOOP_CONTROL)
                {
                    if (MotorSpeedVSP <= MINPWMDuty)   //最小转矩
                    {
                        MotorSpeed.TargetValue     = Motor_Min_Current;
                    }
                    else if (MotorSpeedVSP < MAXPWMDuty) //调转矩
                    {
                        MotorSpeed.TargetValue     = Motor_Min_Current + CURRENT_K * (MotorSpeedVSP - MINPWMDuty);
                    }
                    else                    //最大转矩
                    {
                        MotorSpeed.TargetValue     = Motor_Max_Current;
                    }
                }
				
                #endif
    }
    else
    {
    	MotorSpeed.TargetValue = 0;
    }
}

/*  -------------------------------------------------------------------------------------------------
    Function Name  : ONOFF_Starttest
    Description    : 启动测试
    Date           : 2020-04-10
    Parameter      : h_test: [输入/出]
    ------------------------------------------------------------------------------------------------- */
void ONOFF_Starttest(void)
{
    if (ONOFFTest.ONOFF_Flag == 1)
    {
        ONOFFTest.ON_Count++;
        
        if (ONOFFTest.ON_Count > StartON_Time)
        {
            ONOFFTest.ON_Count        = 0;
            ONOFFTest.ONOFF_Times++;
            ONOFFTest.ONOFF_Flag      = 0;
            MotorSpeed.FlagONOFF   = 0;
            MotorSpeed.TargetValue = 0;
        }
    }
    else
    {
        if (mcState != mcFault)
        {
            ONOFFTest.OFF_Count++;
            
            if (ONOFFTest.OFF_Count > StartOFF_Time)
            {
                ONOFFTest.OFF_Count       = 0;
                ONOFFTest.ONOFF_Flag      = 1;
                MotorSpeed.FlagONOFF   = 1;
                MotorSpeed.TargetValue = MOTOR_LOOP_MAX ;
            }
        }
    }
}

/*  -------------------------------------------------------------------------------------------------
    Function Name  : Speed_response
    Description    : 速度响应函数，可根据需求加入控制环，如恒转矩控制、恒转速控制、恒功率控制
    Date           : 2020-04-10
    Parameter      : None
    ------------------------------------------------------------------------------------------------- */
void Speed_response(void)
{
	static int16 temp=0;
	 temp=FOC_EK3;
	
	//static int16 temp2=0;
	
    if ((mcState == mcRun) || (mcState == mcStop))
    {
        switch (mcFocCtrl.CtrlMode)
        {
            case 0:
            {
				GP21 = 0;
                if (mcFocCtrl.SpeedFlt > MOTOR_LOOP_RPM) //>=MOTOR_LOOP_RPM
                {
                    mcFocCtrl.CtrlMode = 1;
                    FOC_DQKP = DQKP;
                    FOC_DQKI = DQKI;
                    FOC_IDREF   = 0;
                    ClrBit(FOC_CR2, UQD);
                    PI_Init();                                    // PI初始化
                    PI2_Init();                                  //用以限制电流
                    MotorSpeed.ActualValue = mcFocCtrl.SpeedFlt;
                    mcFocCtrl.LoopTime = SPEED_LOOP_TIME;
                    MotorSpeed.IncValue = SPEED_INC;
                    MotorSpeed.DecValue = SPEED_DEC;
					GP21 = 1;
                    #if (Motor_Speed_Control_Mode == UQ_LOOP_CONTROL)
                   {
                       SetBit(FOC_CR2, UQD); 
                       MotorSpeed.ActualValue = FOC__UQ;
                    }
                    #else
                    {
                       mcFocCtrl.mcIqref = FOC_IQREF;
                    }
                   #endif
                    PI3_UKH = mcFocCtrl.mcIqref;
					
                }
                else
                {
                    
                    
                    if (FOC_IQREF < IQ_RUN_CURRENT)
                    {
                        mcFocCtrl.mcIqref += 1;
                        FOC_IQREF = mcFocCtrl.mcIqref;
                    }
                }
            }
            break;
            
            case 1:
            {
	            
                mcFocCtrl.LoopTime++;
                if (mcFocCtrl.LoopTime >= SPEED_LOOP_TIME)
                {
                        mcFocCtrl.LoopTime = 0;
                       /*速度环控制*/
                         Motor_Ramp(); //速度环控制速度爬坡
                     #if (Motor_Speed_Control_Mode == SPEED_LOOP_CONTROL)
                     {
                         
						  if((temp>=0.01*OBS_K3T)&&(temp<1.0*OBS_K3T))
					   {
						    temp=temp+1;
						    if(temp<=(1.0*OBS_K3T))
							{
						        FOC_EK3=temp; 
							}
							
						}
					   
						mcFocCtrl.IqSpeedRef = HW_One_PI(MotorSpeed.ActualValue - mcFocCtrl.SpeedFlt);
						mcFocCtrl.IqADCCurrentRef = HW_One_PI2(Motor_Max_ADCCurrentbus - mcFocCtrl.mcADCCurrentbus);//限制最大电流
                            #if (ADCCurrentbusLitmitEn == Disable)
                            {
                                  mcFocCtrl.IqRef = mcFocCtrl.IqSpeedRef;
                            }
                            #else
                            {
                                if (mcFocCtrl.IqSpeedRef >=  mcFocCtrl.IqADCCurrentRef) // 二者取其小
                                {
                                    mcFocCtrl.IqRef = mcFocCtrl.IqADCCurrentRef;
                                }
                                else
                                {
                                    mcFocCtrl.IqRef = mcFocCtrl.IqSpeedRef;
                                }
                            }
                            #endif
                     }
                    #elif (Motor_Speed_Control_Mode == POWER_LOOP_CONTROL)
                    {
                        mcFocCtrl.mcIqref = HW_One_PI(MotorSpeed.ActualValue - mcFocCtrl.Powerlpf);
                      
                    }
                    #elif (Motor_Speed_Control_Mode == CURRENT_LOOP_CONTROL)
                    {
                        mcFocCtrl.mcIqref = HW_One_PI(MotorSpeed.ActualValue - FOC_IQREF);
                    }
                   
                    #endif
                     FOC_IQREF = mcFocCtrl.IqRef;                                       //Q轴电流参考值,FOC控制
                   
                }
            }
            break;
        }
    }
}

/*  -------------------------------------------------------------------------------------------------
    Function Name  : mc_ramp
    Description    :
    Date           : 2020-04-10
    Parameter      : Speedramp: [输入/出]
    ------------------------------------------------------------------------------------------------- */
 void Motor_Ramp(void)
{
    if (MotorSpeed.ActualValue < MotorSpeed.TargetValue)
    {
        if (MotorSpeed.ActualValue + MotorSpeed.IncValue < MotorSpeed.TargetValue)
        {
            MotorSpeed.ActualValue += MotorSpeed.IncValue;
        }
        else
        {
            MotorSpeed.ActualValue = MotorSpeed.TargetValue;
        }
    }
    else
    {
        if (MotorSpeed.ActualValue - MotorSpeed.DecValue > MotorSpeed.TargetValue)
        {
            MotorSpeed.ActualValue -= MotorSpeed.DecValue;
        }
        else
        {
            MotorSpeed.ActualValue = MotorSpeed.TargetValue;
        }
    }
}

/*  -------------------------------------------------------------------------------------------------
    Function Name  : HW_One_PI
    Description    : PI控制
    Date           : 2020-04-10
    Parameter      : Xn1: [输入/出]
    ------------------------------------------------------------------------------------------------- */
int16 HW_One_PI(int16 Xn1)
{
    PI3_EK = Xn1;          //填入EK
    SetBit(PI_CR, PI3STA); // Start PI
    
    while (ReadBit(PI_CR, PIBSY));
    
    return PI3_UKH;
}
/*  -------------------------------------------------------------------------------------------------
    Function Name : int16 HW_One_PI2(int16 Xn1, int16 Yn0, int16 Xn2)
    Description   : PI控制
    Input         : Xn1--E(K)
    Output        : PI_UK--当前PI输出值,执行时间us
    -------------------------------------------------------------------------------------------------*/
int16 HW_One_PI2(int16 Xn1)
{
    PI2_EK = Xn1;          //填入EK
    SetBit(PI_CR, PI2STA); // Start PI
    
    while (ReadBit(PI_CR, PIBSY));
    
    return PI2_UKH;
}

/*  -------------------------------------------------------------------------------------------------
    Function Name  : StarRampDealwith
    Description    :
    Date           : 2020-04-10
    Parameter      : None
    ------------------------------------------------------------------------------------------------- */
void StarRampDealwith(void)
{
    if ((mcState == mcRun))
    {
        if (mcFocCtrl.State_Count == 2700) //2300
        {
            FOC_EKP = OBSW_KP_GAIN_RUN;              // 估算器里的PI的KP
            FOC_EKI = OBSW_KI_GAIN_RUN;              // 估算器里的PI的KI
        }
        else if (mcFocCtrl.State_Count == 2500) //2000
        {
            FOC_EKP = OBSW_KP_GAIN_RUN1;             // 估算器里的PI的KP
            FOC_EKI = OBSW_KI_GAIN_RUN1;             // 估算器里的PI的KI
        }
        else if (mcFocCtrl.State_Count == 2300) //1600
        {
            FOC_EKP = OBSW_KP_GAIN_RUN2;             // 估算器里的PI的KP
            FOC_EKI = OBSW_KI_GAIN_RUN2;             // 估算器里的PI的KI
        }
        else if (mcFocCtrl.State_Count == 2100) //1200
        {
            FOC_EKP = OBSW_KP_GAIN_RUN3;             // 估算器里的PI的KP
            FOC_EKI = OBSW_KI_GAIN_RUN3;             // 估算器里的PI的KI
        }
        else if (mcFocCtrl.State_Count == 2000) //1200
        {
            FOC_EKP = OBSW_KP_GAIN_RUN4;             // 估算器里的PI的KP
            FOC_EKI = OBSW_KI_GAIN_RUN4;             // 估算器里的PI的KI
        }
        else if (mcFocCtrl.State_Count == 1900)
        {
            FOC_EKP = OBSW_KP_GAIN_RUN5;             // 估算器里的PI的KP
            FOC_EKI = OBSW_KI_GAIN_RUN5;             // 估算器里的PI的KI
        }
    }
}


/**
 * @brief        默认1ms周期服务函数，运行信号采样，调速信号处理，闭环控制，故障检测,ATO爬坡函数
 *               该函数运行于大循环中，由SYSTICK定时器间隔1ms触发运行。
 * @date         2022-09-13
 */
void  TickCycle_1ms(void)
{
//	GP00=~GP00;
	//GP00=0;

//	GP21 = ~GP21;//测试1ms用
    mcFocCtrl.QoutValue     = FOC__UQ;
    mcFocCtrl.DoutValue     = FOC__UD;
    
    if (mcState == mcRun)
    {
        /*----- 功率滤波 -----*/
        LPF_MDU(FOC__POW, 10, mcFocCtrl.Powerlpf, mcFocCtrl.Powerlpf_LSB);    //注意低通滤波器系数范围为0---127
    }
    else
    {
        mcFocCtrl.Powerlpf = 0;
    }
    
    if ((mcState != mcInit) && (mcState != mcReady))
    {
        /* -----速度滤波----- */
        LPF_MDU(FOC__EOME, 30, mcFocCtrl.SpeedFlt, mcFocCtrl.SpeedFlt_LSB);
    }
    else
    {
        mcFocCtrl.SpeedFlt = 0;
    }
	    /* -----母线电流值采样----- */
    Power_Currt = (ADCCurrentbusPort);
    
    if (Power_Currt > mcCurOffset.Iw_busOffset)
    {
        Power_Currt   = Power_Currt - mcCurOffset.Iw_busOffset;
    }
    else
    {
        Power_Currt   = 0;
    }
    
	LPF_MDU(Power_Currt, 30, mcFocCtrl.mcADCCurrentbus, mcFocCtrl.mcADCCurrentbus_LSB); /* -----母线电流值滤波----- */
    /*----- DCbus的采样获取值并滤波 -----*/
    LPF_MDU((ADC14_DR), 30, mcFocCtrl.mcDcbusFlt, mcFocCtrl.mcDcbusFlt_LSB);
    mcFocCtrl.NTCTempFlt = ADC12_DR;                                                    /* -----NTC电压值滤波----- */
    Atan_Us_MDU(FOC__EALP, FOC__EBET, mcFocCtrl.EsValue);
    /*----- 获取调速信号，不同调速模式(PWMMODE,NONEMODE,SREFMODE,KEYSCANMODE)的目标值修改 -----*/
    TargetSpeed_Colletion();
   
    /*----- 环路响应，如速度环、转矩环、功率环等 -----*/
    Speed_response();
    /* -----故障保护函数功能，如过欠压保护、启动保护、缺相、堵转等----- */
    Fault_Detection();
    
    /*----- 电机状态机的时序处理 -----*/
    if (mcFocCtrl.State_Count > 0)
    {
        mcFocCtrl.State_Count--;
    }
	
	#if(TailWind_Mode ==BEMFMethod)
	{
		if(BEMFDetect.BEMFTimeCount > 0)
		{
			BEMFDetect.BEMFTimeCount--;
		}
	}
	#endif
	
    /* -----电机启动ATO爬坡函数处理----- */
    StarRampDealwith();
    #if(TailWind_Mode ==FOCMethod)
    {
        FOCTailWindTimeLimit();
    }
    #endif
  
}
/*  -------------------------------------------------------------------------------------------------
    Function Name  : APP_DIV
    Description    : 将所有用到除法的地方，放在同一个中断，以避免中断串扰
    Date           : 2020-04-10
    Parameter      : None
    ------------------------------------------------------------------------------------------------- */
void APP_DIV(void)
{
    if ( mcPwmInput.PwmDivFlag == 1)
    {
        DivQ_L_MDU(mcPwmInput.PwmCompareUpdate, 0x0000, mcPwmInput.PwmArrUpdate, mcPwmInput.PwmDuty);
        mcPwmInput.PwmDivFlag = 0;
    }
}

