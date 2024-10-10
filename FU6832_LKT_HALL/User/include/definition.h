/**
 * @copyright (C) COPYRIGHT 2022 Fortiortech Shenzhen
 * @file      definition.h
 * @author    Leo.li
 * @note      Last modify author is Marcel He
 * @since     2022-09-04
 * @date      2022-09-04
 * @brief       
 */
 

#ifndef __DEFINITION_H_
#define __DEFINITION_H_

#define SystemPowerUpTime               (15000)                                                       // ??????,cpu????
#define Calib_Time                     (1000)                                  //< 校正次数，固定1000次，单位:次

/* Q format define ---------------------------------------------------------------------------------*/
#define _Q7(A)                          (int8) ((A) * 0x7f)         ///< Q7 format
#define _Q8(A)                          (int16)((A) * 0xff)         ///< Q8 format
#define _Q9(A)                          (int16)((A) * 0x1ff)        ///< Q9 format
#define _Q10(A)                         (int16)((A) * 0x3ff)        ///< Q10 format
#define _Q11(A)                         (int16)((A) * 0x07ff)       ///< Q11 format
#define _Q12(A)                         (int16)((A) * 0x0fff)       ///< Q12 format
#define _Q13(A)                         (int16)((A) * 0x1fff)       ///< Q13 format
#define _Q14(A)                         (int16)((A) * 0x3fff)       ///< Q14 format
#define _Q15(A)                         (int16)((A) * 0x7fff)       ///< Q15 format
#define _Q16                            (65535.0)                   ///< Q16 format value
#define _2PI                            (3.1415926 * 2)             ///< 2 PI value

#define I_ValueX(Curr_Value)            ((Curr_Value) * (HW_RSHUNT) * (HW_AMPGAIN) / (HW_ADC_REF))
#define I_Value(Curr_Value)             _Q15(I_ValueX(Curr_Value))
#define S_Value(SpeedValue)             _Q15((float)(SpeedValue) / MOTOR_SPEED_BASE)
#define SAcc_Value(SpeedValue)          ((float)32767.0*(SpeedValue*SPEED_LOOP_TIME/1000.0) / MOTOR_SPEED_BASE)
#define I_Bus_ValueX(Curr_Value)            (I_LimitiBus_K*Curr_Value * HW_RSHUNT * HW_AMPGAIN / (HW_ADC_REF))
#define I_Bus_Value(Curr_Value)             _Q15(I_Bus_ValueX(Curr_Value))


/* 使能定义 */
#define Disable                         (0)                              
#define Enable                          (1)

/* 转向定义 */
#define CW                              (0)             ///<正转
#define CCW                             (1)             ///<反转

/* ADC参考电压配置 */
#define VREF3_0                         (0xA0)          ///< 0XA0 远离实际值  减少直接填写数值导致错误，其他同理
#define VREF4_0                         (0xB0)
#define VREF4_5                         (0xC0)
#define VREF5_0                         (0xD0)

/* 运放模式选择 */
#define AMP_NOMAL                       (0xA0)          ///< 外部放大
#define AMP_PGA_DUAL                    (0xB0)          ///< 内部PGA 双端差分输入

/* 内部PGA放大倍数选择 */
#define AMP2x                           (2)           
#define AMP4x                           (4)
#define AMP8x                           (8)
#define AMP16x                          (16)
#define AMP32x                          (32)

#define INTERNAL                        (0xA0)   
#define EXTERNAL                        (0xB0)   

#define Ratio_12                        (0xA0)  
#define Ratio_6_5                       (0xB0)

/***正PWMduty or 负PWMduty Choose***/
#define PosiPWMDUTY                     (0xA0)                                     // 正PWMduty
#define NegaPWMDUTY                     (0xB0)                                     // 负PWMduty

#define ALIGN_DSIABLE                   (0xA0)          ///< 禁止 
#define ALIGN_NOMAL                     (0xB0)          ///< 正常预定位 
#define ALIGN_TEST                      (0xC0)          ///< 测试模式，可用于手动测试电机极对数 


/* 闭环模式 */
#define CURRENT_LOOP_CONTROL            (0xA0)          ///< 电流环
#define POWER_LOOP_CONTROL              (0xB0)          ///< 恒功率
#define SPEED_LOOP_CONTROL              (0xC0)          ///< 恒转速
#define UQ_LOOP_CONTROL                 (0xD0)          ///< UQ闭环
#define OTHERS_LOOP_CONTROL             (0xE0)          ///< 其他环路，自定义


/* 调速模式 */
#define NONEMODE                        (0xA0)          ///< 直接给定值，不调速
#define PWMMODE                         (0xB0)          ///< PWM调速
#define SREFMODE                        (0xC0)          ///< 模拟调速
#define ONOFFTEST                       (0xD0)          ///< 启停测试工具
#define SCLKMODE                        (0xE0)          ///< SCLK 调速  
#define OTHERS                          (0xF0)          ///< 其他调速方式   

/* 估算器模式选择 */
#define SMO                             (0xA0)          ///< SMO ,滑膜估算
#define PLL                             (0xB0)          ///< PLL ,锁相环

/*模式选择设置值----------------------------------------------------------------*/
#define IPMtest                         (0xA0)                                    // IPM测试或者MOS测试，MCU输出固定占空比
#define NormalRun                       (0xB0)                                    // 正常按电机状态机运行


/* 顺逆风判断设置 */
#define NoTailWind                      (0xA0)          ///< 无逆风顺风判断
#define RSDMethod                       (0xB0)          ///< RSD比较器方法
#define FOCMethod                       (0xC0)          ///< FOC计算方法
#define BEMFMethod                      (0xD0)          ///< BEMF比较器方法


/* 静止启动 强拖模式选择 */
#define Open_Start                      (0xA0)          ///< 开环强拖启动
#define Omega_Start                     (0xB0)          ///< Omega启动
#define Open_Omega_Start                (0xC0)          ///< 先开环启，后Omega启动


/* 电流采样模式 */
#define Single_Resistor                 (0xA0)          ///< 单电阻电流采样模式
#define Double_Resistor                 (0xB0)          ///< 双电阻电流采样模式
#define Three_Resistor                  (0xC0)          ///< 三电阻电流采样模式


/* -----初始位置检查参数----- */
#define PosCheckEnable                 (0)                                                                              ///< 初始位置使能,目前程序中没添加此功能 20220616
#define AlignEnable                    (0)                                                                              ///< 预定位使能

/* -----电机顺逆风状态----- */
#define  Wind_FORWARD                           (1)
#define  Wind_REVERSE                           (2)
#define  Wind_STATIC                            (3)
#define  Wind_DETECTING                         (0)

#endif
