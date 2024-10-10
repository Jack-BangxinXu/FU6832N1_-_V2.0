/*  -------------------------- (C) COPYRIGHT 2022 Fortiortech ShenZhen ---------------------------*/
/**
 * @copyright (C) COPYRIGHT 2022 Fortiortech Shenzhen
 * @file      main.c
 * @author    Fortiortech  Appliction Team
 * @since     Create:2022-07-14
 * @date      Last modify:2022-07-14
 * @note      Last modify author is Leo.li
 * @brief     包含主函数，软硬件初始化函数，VRER配置函数
 */

#include <MyProject.h>
/* Private variables ----------------------------------------------------------------------------*/
MotStaType mcState;
MotStaM    McStaSet;

/**
 * @brief        主函数，大循环运行偏置电流采集函数，电机状态机控制函数，以及环路响应函数
 * @date         2022-07-14
 */
void MC_Control(void)
{
    
    
    switch (mcState)
    {
        case mcReady:
            Motor_Ready();
            if (mcFaultSource != FaultNoSource)
            {
                      mcState = mcFault;
            }
            else if ((mcCurOffset.OffsetFlag == 1) && (MotorSpeed.FlagONOFF == 1))
            {
                mcState = mcInit;
                mcCurOffset.OffsetFlag = 0;
                mcCurOffset.OffsetCount = 0;    //偏置电压采集计数
   
            }
            
            break;
            
        case mcInit:
			if (mcFaultSource != FaultNoSource)
            {
                      mcState = mcFault;
            }
			else if(MotorSpeed.FlagONOFF == 0)
			{
				   mcState                 = mcStop;
                    mcFocCtrl.State_Count   = 10;
			}
            else if (mcCurOffset.OffsetFlag == 1)
            {
                Motor_Init();
                #if (IPMState == IPMtest)                           // 正常按电机状态机运行
                {
                    mcState                 = mcCharge;
                    mcFocCtrl.State_Count   = Charge_Time;
                }
                #else
                {
                    
					 #if (TailWind_Mode == NoTailWind)
                     #if (PosCheckEnable == 1)
                     mcState                           = mcPosiCheck;
                     McStaSet.SetFlag.PosiCheckSetFlag = 0;
                     mcFocCtrl.mcPosCheckAngle         = 0xffff;                     // 角度赋初值
                     #elif (AlignEnable == 1)
                     mcFocCtrl.mcPosCheckAngle = Align_Angle;
                     mcState = mcAlign;
                     mcFocCtrl.State_Count = Align_Time;
                     #else
                     mcState = mcStart;
                     #endif
					 #else
                    mcFocCtrl.State_Count   = 0;                                     //顺逆风判断时间
                    mcState                 = mcTailWind;
                     #endif
                 }
                 #endif
            }
            
            break;
            
        case mcCharge:
			if (mcFaultSource != FaultNoSource)
            {
                      mcState = mcFault;
            }
			else if(MotorSpeed.FlagONOFF == 0)
			{
				   mcState                 = mcStop;
                    mcFocCtrl.State_Count   = 10;
			}
			else
			{
                      Motor_Charge();
			}
            break;
			
          #if (TailWind_Mode != NoTailWind)
          case mcTailWind:
			if (mcFaultSource != FaultNoSource)
            {
                      mcState = mcFault;
            }
			else if(MotorSpeed.FlagONOFF == 0)
			{
				   mcState                 = mcStop;
                    mcFocCtrl.State_Count   = 10;
			}
			else
			{	
                
                  Motor_TailWind();
				
				   if (mcFocCtrl.WindFlag == Wind_STATIC)
                {
                    #if (PosCheckEnable == 1)
                    mcState                           = mcPosiCheck;
                    McStaSet.SetFlag.PosiCheckSetFlag = 0;
                    mcFocCtrl.mcPosCheckAngle         = 0xffff;                     // 角度赋初值
                    #elif (AlignEnable == 1)
                    mcFocCtrl.mcPosCheckAngle = Align_Angle;
                    mcState = mcAlign;
                    mcFocCtrl.State_Count = Align_Time;
                    #else
                    mcState = mcStart;
                    #endif
                }
                 if (mcFocCtrl.WindFlag == Wind_FORWARD)
                {                    
                          mcState = mcRun;
                }
		 
		   }
            break;
           #endif
		   
		    #if (PosCheckEnable == 1)
            case mcPosiCheck:
			if (mcFaultSource != FaultNoSource)
            {
                      mcState = mcFault;
            }
			else if(MotorSpeed.FlagONOFF == 0)
			{
				   mcState                 = mcStop;
                    mcFocCtrl.State_Count   = 10;
			}
			else
			{
//                 mcFocCtrl.mcPosCheckAngle = 0;
//                 mcState = mcAlign;
//                 mcFocCtrl.State_Count = Align_Time;
			}
            break;
            #endif
			
		  #if (AlignEnable == 1)	
          case mcAlign:
			if (mcFaultSource != FaultNoSource)
            {
                      mcState = mcFault;
            }
			else if(MotorSpeed.FlagONOFF == 0)
			{
				   mcState                 = mcStop;
                    mcFocCtrl.State_Count   = 10;
			}
			else
			{
                Motor_Align();
                #if (AlignTestMode == 1)
                {
                    while (1);
                }
               #else
                {
                    if (mcFocCtrl.State_Count == 0)
                   {
                      mcState = mcStart;
                    }
                }
               #endif
		    }
            break;
            #endif
            
        case mcStart:
			if (mcFaultSource != FaultNoSource)
            {
                      mcState = mcFault;
            }
			else if(MotorSpeed.FlagONOFF == 0)
			{
				   mcState                 = mcStop;
                    mcFocCtrl.State_Count   = 10;
			}
			else
			{
               Motor_Open();
               mcState   = mcRun;
			}
            break;
            
        case mcRun:
			if (mcFaultSource != FaultNoSource)
            {
                      mcState = mcFault;
            }
			else if(MotorSpeed.FlagONOFF == 0)
			{
				   mcState                 = mcStop;
                    mcFocCtrl.State_Count   = 10;
			}
			
            
            break;
            
        case mcStop:
			if (mcFaultSource != FaultNoSource)
            {
                      mcState = mcFault;
            }
			else 
			{
				   Motor_Stop();         
			}
			
             
            break;
            
        case mcBrake:
			if (mcFaultSource != FaultNoSource)
            {
                      mcState = mcFault;
            }
			else if(MotorSpeed.FlagONOFF == 0)
			{
				   mcState                 = mcStop;
                    mcFocCtrl.State_Count   = 10;
			}
            else if (mcFocCtrl.State_Count == 0)
            {
                mcState = mcReady;
                ClrBit(DRV_CR, DRVEN);
                MOE = 0;
                ClrBit(DRV_CR, FOCEN);
            }
            
            break;
            
        case mcFault:
            if (mcFaultSource == FaultNoSource)   //保护清零后关闭输出，软件重新运行
            {
                mcState   = mcReady;
            }
            else
            {
                FaultProcess();
            }
            
            break;
            
        default:
            break;
    }
}

