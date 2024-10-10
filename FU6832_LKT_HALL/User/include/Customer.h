/* --------------------------- (C) COPYRIGHT 2020 Fortiortech ShenZhen -----------------------------
    File Name      : Customer.h
    Author         : Fortiortech  Appliction Team
    Version        : V1.0
    Date           : 2020-04-10
    Description    : This file contains customer parameter used for Motor Control.
----------------------------------------------------------------------------------------------------
                                       All Rights Reserved
------------------------------------------------------------------------------------------------- */
/* Define to prevent recursive inclusion --------------------------------------------------------*/
 #ifndef __CUSTOMER_H_
 #define __CUSTOMER_H_
 #include <Develop.h>

/*芯片参数值-------------------------------------------------------------------*/
 /*PWM Parameter*/
 #define PWM_FREQUENCY                  (16.0)                                  // (kHz) 载波频率

 /*deadtime Parameter*/
 #define PWM_DEADTIME                   (0.8)                                   // (us) 死区时间
 
  /*single resistor sample Parameter*/
#define MIN_WIND_TIME                  (PWM_DEADTIME + 1.0)                   // (us) 单电阻最小采样窗口，建议值死区时间+0.9us

 /*电机参数值-------------------------------------------------------------------*/
 #define R               				(1.0)			     				    // 相电感对应系数值
 #define Pole_Pairs 			    	(2.0)					     	        // 极对数
	
 #define RS               				(0.202)			     				   // 相电阻 ,测量两根相线之间电阻/2, ohm
 #define LD               				(0.0002644)							   // D轴相电感 ,测量两根相线之间电感/2,H   0.5
 #define LQ               				(LD)							   // Q轴相电感 ,测量两根相线之间电感/2,H

 #define KeVpp                          (3.16)                                  // (V)      反电动势测量的峰峰值
 #define KeT                            (33.0)                                 // (ms)     反电动势测量的周期
 #define Ke                             (Pole_Pairs * KeVpp * KeT / 207.846)    // 反电动势常数, V/KRPM
 #define MOTOR_SPEED_BASE               (12000.0)                                // (RPM) 速度基准

/*硬件板子参数设置值------------------------------------------------------------*/

 /*电机电流采样相关硬件参数*/
 #define AMP_MODE                       (INTERNAL)                              // AMP0选择使用输入通道放大倍数来源，INTERNAL内部放大倍数  EXTERNAL外部放大倍数
 #define AMP0_VHALF                     (1)                                     // AMP0是否存在Vhalf偏置电压 1有偏置电压  0没有接偏置电压
 #define HW_RSHUNT                      (0.005)                                  // (Ω)  采样电阻
 #define HW_ADC_REF                     (5.0)                                   // (V)  ADC参考电压
 #define HW_AMPGAIN                     (16.0)                                   // 运放放大倍数
 #define CFG_AMP0GAIN                   (AMP16x)                                 // AMP0放大倍数配置
                                                                                // AMP0放大倍数：AMP2x：2倍   AMP4x：4倍    AMP8x：8倍 AMP16x：16倍  AMP32x：32倍   
/**
 * 基准电压VREF对外输出使能
 * @param (Disable)       禁止
 * @param (Enable)       使能
 */
#define VREF_OUT_EN                     (Enable)         ///< 基准电压VREF对外输出使能

/**
 * 参考电压设置
 * @param (VREF3_0)       参考电压设置为3.0V
 * @param (VREF4_0)       参考电压设置为4.0V
 * @param (VREF4_5)       参考电压设置为4.5V
 * @param (VREF5_0)       参考电压设置为5.0V
 */
#define HW_ADC_VREF                    (VREF5_0)        ///< (V)  ADC参考电压


/**
 * VHALF输出使能
 * @param (Disable)       禁止
 * @param (Enable)        使能
 */
#define VHALF_OUT_EN                    (Enable)        ///< VHALF输出使能

/*电机驱动母线电压采样相关硬件参数*/
 #define VOLTAGE_MODE                   (INTERNAL)                              // 母线电压选择使用分压通道，INTERNAL内部分压  EXTERNAL外部分压
 #define RV1                            (5.5)                                  // (kΩ) 母线电压分压电阻1
 #define RV2                            (1.0)                                   // (kΩ) 母线电压分压电阻2
/* ---RV分压比例系数  Ratio_12 ：母线分压系数为1:12，   Ratio_6_5 ：母线分压系数为1:6.5-----    ((RV1 + RV2 + RV3) / RV3)  */
 #define VOLTAGE_SCALE                  (Ratio_6_5) 

/**
 * 电流采样模式选择
 * @param (Single_Resistor)       单电阻电流采样模式
 * @param (Double_Resistor)       双电阻电流采样模式
 * @param (Three_Resistor)        三电阻电流采样模式
 */
#define Shunt_Resistor_Mode            (Single_Resistor)    ///< 电流采样模式选择

 /**
 * 电流采样模式选择
 * @param (PLL)       锁相环
 * @param (SMO)       滑膜
 */
 #define EstimateAlgorithm              (SMO)     

/**
 * 模式选择设置值
 * @param (IPMtest)          硬件测试模式，MCU输出固定占空比
 * @param (NormalRun)        正常运行
 */
 #define IPMState                       (NormalRun)

/* 正常运行时估算算法的参数设置值  */
 #define OBS_KSLIDE                     _Q15(0.85)       ///< SMO算法里的滑膜增益值
 #define E_BW                           (450.0)          ///< PLL算法里的反电动势滤波值

/*时间设置值-------------------------------------------------------------------*/
 #define Charge_Time                    (20)                                  	// (ms) 预充电时间，单位：ms
 
 /**
 * 顺逆风检测方式
 * @param (NoTailWind)      无逆风顺风判断
 * @param (BEMFMethod)      BEMF比较器方法
 * @param (FOCMethod)       FOC计算方法
 */
#define TailWind_Mode                  (NoTailWind) 
 
 /*-----逆风判断时的估算算法设置值-----*/
 #define TailWind_Time                   (200)                                   // (ms) 顺逆风检测时间
 #define ATO_BW_Wind                     (100)                                    // 逆风判断观测器带宽的滤波值，经典值为8.0-100.0
 #define SPD_BW_Wind                     (20.0)                                  // 逆风判断速度带宽的滤波值，经典值为5.0-40.0
 /*--- 逆风顺风状态下的KP、KI ---*/
 #define DQKP_TailWind                   _Q12(1.5)                               //_Q12(1.0)-PLL , _Q12(1.5)-smo
 #define DQKI_TailWind                   _Q15(0.2)                              //_Q15(0.08)-PLL ,_Q15(0.2)-smo
 /*顺风启动电流值*/
 #define IQ_TailWind_CURRENT            I_Value(0.4)                           // (A) Q轴运行电流

 /**
 * 预定位模式选择
 * @param (0)         正常预定位
 * @param (1)         测试模式，可用于手动测试电机极对数
 */
 #define AlignTestMode                  (0)                                     // 预定位测试模式
 #define Align_Time                     (50)                                  	// (ms) 预定位时间，单位：ms
 #define Align_Angle                    (0.0)                                 // (°) 预定位角度

 /***预定位的Kp、Ki****/
 #define DQKP_Alignment                 _Q12(0.8)                               // 预定位的KP
 #define DQKI_Alignment                 _Q15(0.1)                              // 预定位的KI
 #define ID_Align_CURRENT               I_Value(0.0)                            // (A) D轴定位电流
 #define IQ_Align_CURRENT               I_Value(0.15)                          	// (A) Q轴定位电流


/**
 * 开环启动模式选择
 * @param (Open_Start)          开环强拖启动
 * @param (Omega_Start)         Omega启动
 * @param (Open_Omega_Start)    Open_Omega_Start 启动
 */
 #define Open_Start_Mode               (Omega_Start)       ///< 开环启动模式选择

 /***静止启动电流****/
 #define ID_Start_CURRENT               I_Value(0.0)                            // (A) D轴启动电流
 #define IQ_Start_CURRENT               I_Value(4.0)                            // (A) Q轴启动电流

 /***运行电流****/
 #define ID_RUN_CURRENT                 I_Value(0.0)                            // (A) D轴运行电流
 #define IQ_RUN_CURRENT                 I_Value(0.0)                            // (A) Q轴运行电流
 

 /*************Omega启动的参数***************/
 #define ATO_BW                         (0.0)                                  // 观测器带宽的滤波值，经典值为1.0-200.0

 #define ATO_BW_RUN                     (0.0)
 #define ATO_BW_RUN1                    (0.0)
 #define ATO_BW_RUN2                    (20.0)
 #define ATO_BW_RUN3                    (30.0)
 #define ATO_BW_RUN4                    (60.0)
 #define ATO_BW_RUN5                    (80.0) 

 #define SPD_BW                         (40.0)                                  // 速度带宽的滤波值，经典值为5.0-40.0

 /* OMEGA启动参数 */
 #define Motor_Omega_Ramp_ACC            (10)                                    ///< omega启动的增量（每个载波递增值）
 #define MOTOR_OMEGA_RAMP_MIN            S_Value(50.0)                          ///< (RPM) omega启动的最小切换转速
 #define MOTOR_OMEGA_RAMP_END            S_Value(200.0)                          ///< (RPM) omega启动的限制转速
 
 #define MOTOR_SPEED_SMOMIN_RPM          (120.0)                                 ///< (RPM) SMO运行最小转速影响启动

 #define MOTOR_LOOP_RPM                  S_Value(300.0)                          ///< (RPM) 启动后电流环切入外部环路转速阈值
 
 /*******运行时的参数*****************/
/*电流环参数设置值--------------------------------------------------------------*/
 #define DQKPStart                      _Q12(2.5)                               // 启动DQ轴KP
 #define DQKIStart                      _Q15(0.02)                              // 启动DQ轴KI

 #define DQKP                           _Q12(2.5)                               // 运行DQ轴KP
 #define DQKI                           _Q15(0.02)                             // 运行DQ轴KI
 /* D轴参数设置 */
 #define DOUTMAX                        _Q15(0.6)                               // D轴最大限幅值，单位：输出占空比
 #define DOUTMIN                        _Q15(-0.6)                              // D轴最小限幅值，单位：输出占空比
 /* Q轴参数设置 */
 #define QOUTMAX                        _Q15(0.99)                               // Q轴最大限幅值，单位：输出占空比
 #define QOUTMIN                        _Q15(-0.99)                              // Q轴最小限幅值，单位：输出占空比
 
/*外环参数设置值----------------------------------------------------------------*/
#define SPEED_LOOP_TIME                  (1)                                    // (ms) 速度环调节周期 风扇速度环50，功率环5

#define SKP                            _Q12(1.0)                               // 外环KP
#define SKI                             _Q15(0.008)                              // 外环KI

#define SOUTMAX                         I_Value(15.0)                            // (A) 外环最大限幅值
#define SOUTMIN                        I_Value(-2.0)                            // (A) 外环最小限幅值

 
 /**
 * 环路控制范围 （目标控制 转速，电流，输出占空比，功率）
 * @MOTOR_LOOP_MIN_RPM      最小值
 * @MOTOR_LOOP_MAX_RPM      最大值
 */
 #define MOTOR_LOOP_MIN                 S_Value(1000.0)                               	// 环路控制最大值
 #define MOTOR_LOOP_MAX                 S_Value(6400.0)                                 // 环路控制最小值

 
 #define MOTOR_SPEED_LIMIT_RPM          S_Value(4050.0)
 #define MOTOR_SPEED_STOP_RPM           S_Value(1000.0)                                 // (RPM) 运行最小转速


 /**
 * 闭环方式选择
 * @param (CURRENT_LOOP_CONTROL)       电流环
 * @param (SPEED_LOOP_CONTROL)         速度环
 * @param (POWER_LOOP_CONTROL)         功率环
 */
 #define Motor_Speed_Control_Mode       (SPEED_LOOP_CONTROL) 

/*环路爬坡增量----*/

 #if (Motor_Speed_Control_Mode==CURRENT_LOOP_CONTROL)
 #define SPEED_INC                        I_Value(0.1)                           // 电流环增量
 #define SPEED_DEC                        I_Value(0.1)                           // 电流环减量
 #else
 #define SPEED_INC                     SAcc_Value(7500) // (RPM/s)切环后速度环增量
 #define SPEED_DEC                     SAcc_Value(7500) // (RPM/s)切环后速度环减量
 #endif
 /**
 * 调速模式
 * @param (ONOFFTEST)       启停测试模式
 * @param (NONEMODE)       不调速
 * @param (PWMMODE)        PWM调速
 * @param (SREFMODE)       VSP调速
 * @param (SCLKMODE)       SCLK调速
 */
#define SPEED_MODE                     (PWMMODE)                              

/**
 * PWM调速 PWM极性选择
 * @param (PosiPWMDUTY)      正逻辑
 * @param (NegaPWMDUTY)      反逻辑
 */
 #define PWMDUTY_Choose                 (PosiPWMDUTY)
 
 /* motor ON/0FF value */
 #define OFFPWMDuty                     _Q15(0.13)           ///< 关机PWM占空比，小于该占空比关机
#define OFFPWMDutyHigh                 _Q15(0.07)            ///< 关机PWM占空比，大于该占空比关机
#define ONPWMDuty                      _Q15(0.13)           ///< 开机PWM占空比，大于该占空比时开机
#define MINPWMDuty                     _Q15(0.13)           ///< 速度曲线上最小PWM占空比
#define MAXPWMDuty                     _Q15(0.85)           ///< 速度曲线上最大PWM占空比
 


 /*******SCLK模式下motor ON/0FF value*****************/
 #define OFFPWMSclk                     (40)                                    // 关机PWM频率，小于该频率关机                                                
 #define OFFPWMSclkHigh                 (500)                                   // 关机PWM频率，大于该频率关机
 #define ONPWMSclk                      (45)                                    // 开机PWM频率，大于该频率时开机
 #define MINPWMSclk                     (42)                                    // 速度曲线上最小PWM频率
 #define MAXPWMSclk                     (400)                                   // 速度曲线上最大PWM频率
 #define Speed_PerFre                   (4.0)                                   // 目标转速与输入频率的比例系数  例：Speed_PerFre = 4，Fre = 75;则目标转速为300
 #define SCLK_SPEED_K                   _Q15(Speed_PerFre / MOTOR_SPEED_BASE)
                                                                                   
 /*正反转模式，正转为 CW ，反转为 CCW */
 #define FRMODE                         (CCW)

/**
 * 母线电流限流使能
 * @param (Disable)       禁止
 * @param (Enable)        使能
 */
#define ADCCurrentbusLitmitEn         (Enable)               	// 限流功能使能
#define ADCCurrentbusPort              ADC1_DR              	///<(A) 母线电流采样端口，需使能相应ADC通道 
#define Motor_Max_ADCCurrentbus        I_Bus_Value(5.0)     	///< (A) 母线电流限流值,电源显示5.0
#define I_LimitiBus_K                  (1.0)               		///< (A) 系数K，调整限流值
#define LimitCurrent_KP                _Q12(5.0)             	///< 限流环KP     
#define LimitCurrent_KI                _Q15(0.05)            	///< 限流环KI
#define LimitCurrentOUTMAX             I_Bus_Value(15.0)       ///< 限流环限幅

 /******启停测试参数******/
 #define StartON_Time                   (5000)                                  // (ms) 启动运行时间
 #define StartOFF_Time                  (5000)                                 // (ms) 停止时间

 #define StopBrake_Enble                (0)
 #define StopWaitTime                   (2000)                                  // (ms) 刹车等待时间

#endif

