/*  -------------------------- (C) COPYRIGHT 2022 Fortiortech ShenZhen ---------------------------*/
/**
 * @copyright (C) COPYRIGHT 2022 Fortiortech Shenzhen
 * @file      xxx.c
 * @author    Fortiortech  Appliction Team
 * @since     Create:2022-09-09
 * @date      Last modify:2022-09-14
 * @note      Last modify author is Leo.li
 * @brief
 */
#include <MyProject.h>

FaultRecoverTypedef xdata Restart; ///< 故障恢复重启控制相关结构体变量
/**
 * @brief     保护处理函数，关闭FOC输出
 * @date      2022-07-14
 */	
void FaultProcess(void)
{
    ClrBit(DRV_CR, DRVEN);  //Driver Disable
    ClrBit(DRV_CR, FOCEN);  //FOC Disable
    MOE     = 0;
}


/**
 * @brief     过压欠压保护函数：程序每5ms判断一次，母线电压大于过压保护值时，计数器加一，计数器值超过20次，判断为过压保护，关闭输出;反之，计数器慢慢减
              同理，欠压保护。
              电机过欠压保护状态下，母线电压恢复到欠压恢复值以上，过压恢复值以下时，计数器加一，超过200次后，恢复。
 * @date      2022-07-14
 */
void Fault_OverUnderVoltage(void)
{
    if (mcFaultSource == FaultNoSource) //程序无其他保护下
    {
        //过压保护
        if (mcFocCtrl.mcDcbusFlt > OVER_PROTECT_VALUE)   //母线电压大于过压保护值时，计数，超过20次，判断为过压保护，关闭输出;反之，计数器慢慢减
        {
            mcFaultDect.OverVoltDetecCnt++;
            
            if (mcFaultDect.OverVoltDetecCnt > 10) //检测50ms
            {
                mcFaultDect.OverVoltDetecCnt = 0;
                mcFaultSource             = FaultOverVoltageDC;
            }
        }
        else if (mcFaultDect.OverVoltDetecCnt > 0)
        {
            mcFaultDect.OverVoltDetecCnt--;
        }
        
        //欠压保护
        if (mcFocCtrl.mcDcbusFlt < UNDER_PROTECT_VALUE)
        {
            mcFaultDect.UnderVoltDetecCnt++;
            
            if (mcFaultDect.UnderVoltDetecCnt > 50) //检测50ms
            {
                mcFaultDect.UnderVoltDetecCnt = 0;
                mcFaultSource              = FaultUnderVoltageDC;
            }
        }
        else if (mcFaultDect.UnderVoltDetecCnt > 0)
        {
            mcFaultDect.UnderVoltDetecCnt--;
        }
    }   
}

/**
 * @brief     电机运行或者启动时，当三相中某一相最大值大于OverCurrentValue，则OverCurCnt加1
 * @date      2022-07-14
 */
void Fault_OverCurrent(void)
{
    if ((mcState == mcRun) || (mcState == mcStart))                       // check over current in rum and open mode
    {
		mcCurVarible.Abs_ia = Abs_F16(FOC__IA);
        mcCurVarible.Abs_ib = Abs_F16(FOC__IB);
        mcCurVarible.Abs_ic = Abs_F16(FOC__IC);
		
		 if (mcCurVarible.Abs_ia >= mcCurVarible.Max_ia)
		 {
			 mcCurVarible.Max_ia = mcCurVarible.Abs_ia;
		 }
		 if (mcCurVarible.Abs_ib >= mcCurVarible.Max_ib)
		 {
			 mcCurVarible.Max_ib = mcCurVarible.Abs_ib;
		 }
		 if (mcCurVarible.Abs_ic >= mcCurVarible.Max_ic)
		 {
			 mcCurVarible.Max_ic = mcCurVarible.Abs_ic;
		 }
		 if((mcCurVarible.Max_ia>=OverSoftCurrentValue)||(mcCurVarible.Max_ib>=OverSoftCurrentValue)||(mcCurVarible.Max_ic>=OverSoftCurrentValue))	 
       
		 {
                 mcCurVarible.OverCurCnt++;
                 mcCurVarible.Max_ia=0;
			     mcCurVarible.Max_ib=0;
			     mcCurVarible.Max_ic=0;
			     mcCurVarible.OverCurCntClr=0;
			 
            if (mcCurVarible.OverCurCnt >= OverSoftCurrent_DectTime)
            {
                mcFaultSource     = FaultSoftOVCurrent;
                mcCurVarible.OverCurCnt = 0;
            }
        }
		else
		{
			 if (++mcCurVarible.OverCurCntClr > OverSoftCurrentClrTime)
            {
                mcCurVarible.OverCurCnt = 0;
                mcCurVarible.OverCurCntClr = 0;
            }
		}
	}
}


/**
 * @brief     启动与堵转检测
 * @date      2022-07-14
 */
void Fault_Stall(void)
{
	
    if (mcState == mcRun)
    {
        if (mcFaultDect.StallDelayCnt <= 3000) //5s
        {
            mcFaultDect.StallDelayCnt++;
			
			 mcFaultDect.StartDelay++;
            
            if (mcFaultDect.StartDelay >= 1000)               // 1.5s
            {
                mcFaultDect.StartDelay = 1000;
                
                if ((mcFocCtrl.EsValue < 800))
                {
                    mcFaultDect.StartESCount++;
                    
                    if (mcFaultDect.StartESCount >= 10)
                    {
                        mcFaultSource = FaultStall;
                        mcProtectTime.SecondStartTimes++;
                        mcFaultDect.StartDelay     = 0;
                        mcFaultDect.StartESCount   = 0;
                        mcProtectTime.StallFlag = 1;
                    }
                }
                else
                {
                    if (mcFaultDect.StartESCount > 0)
                    {
                        mcFaultDect.StartESCount--;
                    }
                }
            }

        }
        else
        {
			mcFaultDect.StartESCount = 0;
            //method 1，判断反电动势太小或当反电动势太小，转速太大
            if ((mcFocCtrl.EsValue < 1500) || ((FOC__EOME > _Q15(2500.0 / MOTOR_SPEED_BASE)) && (mcFocCtrl.EsValue < 4000)))
            {
                mcFaultDect.StallDectEs++;  
                
                if (mcFaultDect.StallDectEs >= 50)
                {
                    mcFaultDect.StallDectEs = 0;
                    mcFaultSource        = FaultStall;
                    mcProtectTime.StallFlag = 2;
                }
            }
            else
            {
                if ( mcFaultDect.StallDectEs > 0)
                {
                    mcFaultDect.StallDectEs--;
                }
            }
            
            //method 2，判断速度低于堵转最小值或者超过堵转最大值
            if ((mcFocCtrl.SpeedFlt < MOTOR_SPEED_STAL_MIN_RPM) || (mcFocCtrl.SpeedFlt > MOTOR_SPEED_STAL_MAX_RPM))
            {
                mcFaultDect.StallDectSpeed++;
                
                if (mcFaultDect.StallDectSpeed >= 30)
                {
                    mcFaultDect.StallDectSpeed = 0;
                    mcFaultSource           = FaultStall;
                    mcProtectTime.StallFlag = 3;
                }
            }
            else
            {
                if (mcFaultDect.StallDectSpeed > 0)
                {
                    mcFaultDect.StallDectSpeed--;
                }
            }
            
			  // 判断速度低于堵转最小值或者超过堵转最大值
            if ((mcFocCtrl.SpeedFlt) > (uint16)(mcFocCtrl.EsValue*2))
            {
                mcFaultDect.StallSpeedAndEsCnt++;
                
                if (mcFaultDect.StallSpeedAndEsCnt > 50)
                {
                    mcFaultDect.StallSpeedAndEsCnt = 0;
                    mcFaultSource         = FaultStall;
                    mcProtectTime.StallFlag = 4;
                }
            }
            else
            {
                if (mcFaultDect.StallSpeedAndEsCnt > 0)
                { mcFaultDect.StallSpeedAndEsCnt--; }
            }
		
        }
		
			//通用检测method2 : 长时间在MODE0
			if (mcFocCtrl.CtrlMode == 0)   
            {
                mcFaultDect.StartFocmode++;
             
                if (mcFaultDect.StartFocmode >= 2000)
                {
                  mcFaultDect.StartFocmode = 0;
                  mcFaultSource         = FaultStall;
                  mcProtectTime.SecondStartTimes++;
                  mcProtectTime.StallFlag = 5;
                }
            }	
    }
}

/**
 * @brief     缺相保护检测
 * @date      2022-07-14
 */
void Fault_PhaseLoss(void)
{
    if (mcState == mcRun)
    {
        if (mcFaultDect.DectCycleCnt < 4000)
        {
            mcFaultDect.DectCycleCnt++;
        }
        else
        {
            mcCurVarible.Max_ia = FOC__IAMAX;
            mcCurVarible.Max_ib = FOC__IBMAX;
            mcCurVarible.Max_ic = FOC__ICMAX;
            
            if (((mcCurVarible.Max_ia > (mcCurVarible.Max_ib << 2)) || (mcCurVarible.Max_ia > (mcCurVarible.Max_ic << 2)))
                && (mcCurVarible.Max_ia > PhaseLossCurrentValue))
            {
                mcFaultDect.AOpencnt++;
            }
            else
            {
                if (mcFaultDect.AOpencnt > 0)
                {
                    mcFaultDect.AOpencnt --;
                }
            }
            
            if (((mcCurVarible.Max_ib > (mcCurVarible.Max_ia << 2)) || (mcCurVarible.Max_ib > (mcCurVarible.Max_ic << 2)))
                && (mcCurVarible.Max_ib > PhaseLossCurrentValue))
            {
                mcFaultDect.BOpencnt++;
            }
            else
            {
                if (mcFaultDect.BOpencnt > 0)
                {
                    mcFaultDect.BOpencnt --;
                }
            }
            
            if (((mcCurVarible.Max_ic > (mcCurVarible.Max_ia << 2)) || (mcCurVarible.Max_ic > (mcCurVarible.Max_ib << 2)))
                && (mcCurVarible.Max_ic > PhaseLossCurrentValue))
            {
                mcFaultDect.COpencnt++;
            }
            else
            {
                if (mcFaultDect.COpencnt > 0)
                {
                    mcFaultDect.COpencnt --;
                }
            }
            
            mcCurVarible.Max_ia = 0;
            mcCurVarible.Max_ib = 0;
            mcCurVarible.Max_ic = 0;
            SetBit(FOC_CR2, ICLR);
            
            if ((mcFaultDect.AOpencnt > 20) || (mcFaultDect.BOpencnt > 20) || (mcFaultDect.COpencnt > 20))
            {
				mcProtectTime.LossPHTimes++;
                mcFaultSource = FaultPhaseLost;
            }
        }
    }
}

/**
    @brief     NTC过温检测
    @date      2022-07-14
*/
void Fault_NTCTemperature(void)
{
    if (mcFaultSource == FaultNoSource)
    {
        if (mcFocCtrl.NTCTempFlt <= OVER_Temperature) // 过温保护
        {
            if (mcFaultDect.NTCDetecCnt < TemperatureProtectTime)
            {
                mcFaultDect.NTCDetecCnt++;
            }
            else
            {
                mcFaultDect.NTCDetecCnt = 0;
                mcFaultSource = FaultNtcOTErr;
            }
        }
        else
        {
           mcFaultDect.NTCDetecCnt = 0;
        }
    }
}



/**
    @brief      偏置电压检测
*/
void Fault_GetCurrentOffset(void)
{
    if (mcCurOffset.OffsetFlag == 1)
    {
        #if (VHALF_OUT_EN == Enable)                                              //有加VHALF偏置，理论值为16383
        {
            #if (Shunt_Resistor_Mode == Single_Resistor)                   //单电阻模式
            {
                if ((mcCurOffset.Iw_busOffset < (16383 - GetCurrentOffsetValue)) || (mcCurOffset.Iw_busOffset > (16383 + GetCurrentOffsetValue)))
                {
                    mcFaultSource = FaultOffset;
                }
            }
            #elif (Shunt_Resistor_Mode == Double_Resistor)                 //双电阻模式
            {
                if ((mcCurOffset.IuOffset < (16383 - GetCurrentOffsetValue)) || (mcCurOffset.IuOffset > (16383 + GetCurrentOffsetValue))
                    || (mcCurOffset.IvOffset < (16383 - GetCurrentOffsetValue)) || (mcCurOffset.IvOffset > (16383 + GetCurrentOffsetValue)))
                {
                    mcFaultSource = FaultOffset;
                }
            }
            #elif (Shunt_Resistor_Mode == Three_Resistor)                 //三电阻模式
            {
                if ((mcCurOffset.IuOffset < (16383 - GetCurrentOffsetValue)) || (mcCurOffset.IuOffset > (16383 + GetCurrentOffsetValue))
                    || (mcCurOffset.IvOffset < (16383 - GetCurrentOffsetValue)) || (mcCurOffset.IvOffset > (16383 + GetCurrentOffsetValue))
                    || (mcCurOffset.Iw_busOffset < (16383 - GetCurrentOffsetValue)) || (mcCurOffset.Iw_busOffset > (16383 + GetCurrentOffsetValue)))
                {
                    mcFaultSource = FaultOffset;
                }
            }
            #endif
        }
        #else                                                              //没加VHALF偏置,理论值在0
        {
            #if (Shunt_Resistor_Mode == Single_Resistor)                   //单电阻模式
            {
                if (mcCurOffset.Iw_busOffset > GetCurrentOffsetValue)
                {
                    mcFaultSource = FaultOffset;
                }
        
            }
            #elif (Shunt_Resistor_Mode == Double_Resistor)                 //双电阻模式
            {
                if ((mcCurOffset.IuOffset > GetCurrentOffsetValue) || (mcCurOffset.IvOffset > GetCurrentOffsetValue))
                {
                    mcFaultSource = FaultOffset;
                }
            }
            #elif (Shunt_Resistor_Mode == Three_Resistor)                 //三电阻模式
            {
                if ((mcCurOffset.IuOffset > GetCurrentOffsetValue) || (mcCurOffset.IvOffset > GetCurrentOffsetValue) || (mcCurOffset.Iw_busOffset > GetCurrentOffsetValue))
                {
                    mcFaultSource = FaultOffset;
                }
            }
            #endif
        }
        #endif
    }
}

/**
 * @brief     保护函数汇总处理 
 * @date      2022-07-14
 */		
void Fault_Detection(void)
{
	#if (OverSoftCurrentProtectEnable)      //过流保护使能
	{        
        Fault_OverCurrent();                //软件过流保护
    }
	#endif
    #if (VoltageProtectEnable == 1)         //过压保护使能
    {
        Fault_OverUnderVoltage();
    }
    #endif
    
    #if (StallProtectEnable == 1)           //堵转保护使能
    {
        Fault_Stall();
    }
    #endif
    #if (PhaseLossProtectEnable == 1)        //缺相保护使能
    {
        Fault_PhaseLoss();
    }
    #endif
    #if (OverTPProtectEn == 1)
    {
        Fault_NTCTemperature();
    }
#endif
    #if (ProtectRecoveryEn == 1)        //保护恢复
    {
        Fault_Recovery();
    }
#endif
}
/* -------------------------------------------------------------------------------------------------
    Function Name  : Fault_Recovery
    Description    : 故障恢复，条件满足只清除故障码，状态跳转由状态机执行
    Date           : 2022-07-01
    Parameter      : None
------------------------------------------------------------------------------------------------- */
void Fault_Recovery(void)
{
    if (mcState == mcFault)
    {
#if (OV_RecoveryTimes) /* DC电压保护恢复 */

        if (((mcFocCtrl.mcDcbusFlt > UNDER_PROTECT_VALUE) && (mcFocCtrl.mcDcbusFlt < OVER_PROTECT_VALUE)) && (mcFaultSource == FaultUnderVoltageDC || mcFaultSource == FaultOverVoltageDC))
        {
            if (Restart.OV_Times <= OV_RecoveryTimes)
            {
                if (Restart.DC_DelayTcnt < OV_RecoveryDelayTime)
                {
                    Restart.DC_DelayTcnt++;
                }
                else
                {
                    Restart.OV_Times++;
                    Restart.DC_DelayTcnt = 0;
                    mcFaultSource = FaultNoSource;
                }
            }
        }
        else
        {
            Restart.DC_DelayTcnt = 0;
        }

#endif
#if (OT_RecoveryTimes)

//        /* TSD过温保护恢复 */
//        if (mcFaultSource == FaultTSD)
//        {
//            if (mcFocCtrl.MCU_TEMP <= TempRecoverValue)
//            {
//                if (Restart.OT_Times < OT_RecoveryTimes)
//                {
//                    if (Restart.OT_DelayTcnt < OT_RecoveryDelayTime)
//                    {
//                        Restart.OT_DelayTcnt++;
//                    }
//                    else
//                    {
//                        Restart.OT_Times++;
//                        Restart.OT_DelayTcnt = 0;
//                        mcFaultSource = FaultNoSource;
//                    }
//                }
//            }
//        }
        /* NTC过温保护恢复 */
        if (mcFaultSource == FaultNtcOTErr)
        {
            if (mcFocCtrl.NTCTempFlt >= UNDER_Temperature)
            {
                if (Restart.OT_Times < OT_RecoveryTimes)
                {
                    if (Restart.OT_DelayTcnt < OT_RecoveryDelayTime)
                    {
                        Restart.OT_DelayTcnt++;
                    }
                    else
                    {
                        Restart.OT_Times++;
                        Restart.OT_DelayTcnt = 0;
                        mcFaultSource = FaultNoSource;
                    }
                }
            }
        }

#endif
#if (LP_RecoveryTimes)

        /* 缺相保护恢复 */
        if (mcFaultSource == FaultPhaseLost)
        {
            if (Restart.LP_Times < LP_RecoveryTimes)
            {
                if (Restart.LP_DelayTcnt < LP_RecoveryDelayTime)
                {
                    Restart.LP_DelayTcnt++;
                }
                else
                {
                    Restart.LP_Times++;
                    Restart.LP_DelayTcnt = 0;
                    mcFaultSource = FaultNoSource;
                }
            }
        }

#endif
#if (Stall_RecoveryTimes)
        /* 堵转保护恢复 */
        if (mcFaultSource == FaultStall)
        {

            if (Restart.Stall_Times < 5) // 次数小于5次，每次1S重启
            {
                if (Restart.Stall_DealyTcnt < Stall_RecoveryDelayTime)
                {
                    Restart.Stall_DealyTcnt++;
                }
                else
                {
                    Restart.Stall_Times++;
                    Restart.Stall_DealyTcnt = 0;
                    mcFaultSource = FaultNoSource;
                }
            }
            else // 大于5次，每次30S重启
            {
                if (Restart.Stall_DealyTcnt < Stall_RecoveryDelayTime2)
                {
                    Restart.Stall_DealyTcnt++;
                }
                else
                {
                    Restart.Stall_Times = 10;
                    Restart.Stall_DealyTcnt = 0;
                    mcFaultSource = FaultNoSource;
                }
            }
        }

#endif

#if (WL_RecoveryTimes)
//        /* 离水保护恢复 */
//        if (mcFaultSource == FaultWaterLost)
//        {
//            if (Restart.WL_Times < WL_RecoveryTimes)
//            {
//                if (Restart.WL_DelayTcnt < WL_RecoveryDelayTime)
//                {
//                    Restart.WL_DelayTcnt++;
//                }
//                else
//                {
//                    Restart.WL_Times++;
//                    Restart.WL_DelayTcnt = 0;
//                    mcFaultSource = FaultNoSource;
//                }
//            }
//        }

#endif

#if (OC_RecoveryTimes)
        /* 软件硬件过流恢复   30s 重启一次*/
        if (mcFaultSource == FaultSoftOVCurrent || mcFaultSource == FaultHardOVCurrent)
        {
            if (Restart.OverCurrent_Times < OC_RecoveryTimes)
            {
                if (Restart.OverCurrent_DelayTcnt < OC_RecoveryDelayTime)
                {
                    Restart.OverCurrent_DelayTcnt++;
                }
                else
                {
                    Restart.OverCurrent_Times++;
                    Restart.OverCurrent_DelayTcnt = 0;
                    mcFaultSource = FaultNoSource;
                }
            }
        }

#endif
    }
}