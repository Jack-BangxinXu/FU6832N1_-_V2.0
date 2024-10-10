/**
 * @copyright (C) COPYRIGHT 2022 Fortiortech Shenzhen
 * @file      Parameter.h
 * @author    Leo.li
 * @note      Last modify author is Marcel He
 * @since     2022-09-04
 * @date      2022-09-04
 * @brief       
 */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __Parameter_H_
#define __Parameter_H_

#include <Develop.h>
#include <FU68xx_4_Type.h>
#include <Customer.h>

/*CPU Parameter*/
#define MCU_CLOCK                      (24.0)                                 // (MHz) 主频


/*double resistor sample Parameter*/
#define DLL_TIME                        (1.3)                                 // 双电阻最小脉宽设置(us),建议值为死区时间值+0.2us以上
/*three resistor overmodule Parameter*/
#define OVERMOD_TIME                    (2.0)                                 // 三电阻过调制时间(us)，建议值2.0
/*deadtime compensation*/
#define DT_TIME                         (0.4)                                 // 死区补偿时间(us)，适用于双电阻和三电阻，建议值是1/2死区时间
/*min pulse*/
#define GLI_TIME                        (0.5)                                 // 桥臂窄脉宽消除(us),建议值0.5

#define OverModulation                  (0)                                   // 0-禁止过调制，1-使能过调制

#define RV                              ((RV1 + RV2 ) / RV2)               ///< 分压比

/*芯片参数值------------------------------------------------------------------*/
/*CPU and PWM Parameter*/
#define PWM_CYCLE                       (1000.0 / PWM_FREQUENCY)                                      // 周期us
#define SAMP_FREQ                       (PWM_FREQUENCY * 1000)                                        // 采样频率(HZ)
#define TPWM_VALUE                      (1.0 / SAMP_FREQ)                                             // 载波周期(S)
#define PWM_VALUE_LOAD                  (uint16)(MCU_CLOCK * 1000 *2 / PWM_FREQUENCY)                 // PWM 定时器重载值 20190514修改


/*deadtime Parameter*/
#define PWM_LOAD_DEADTIME               (PWM_DEADTIME * MCU_CLOCK)                                    // 死区设置值
#define PWM_OVERMODULE_TIME             (OVERMOD_TIME * MCU_CLOCK / 2)                                // 过调制时间
#define PWM_DLOWL_TIME                  (DLL_TIME * MCU_CLOCK / 2)                                    //下桥臂最小时间
/*single resistor sample Parameter*/
#define PWM_TS_LOAD                     (uint16)(_Q16 / PWM_CYCLE * MIN_WIND_TIME / 16)               // 单电阻采样设置值
#define PWM_DT_LOAD                     (uint16)(_Q16 / PWM_CYCLE * DT_TIME / 16)                     // 死区补偿值
#define PWM_TGLI_LOAD                   (uint16)(0)  // 最小脉冲

/*硬件板子参数设置值------------------------------------------------------------------*/
/*hardware current sample Parameter*/
/*电流基准的电路参数*/
#define HW_BOARD_CURR_MAX               (HW_ADC_REF / 2 / HW_AMPGAIN / HW_RSHUNT)                     // 最大采样电流,2.702A
#define HW_BOARD_CURR_MIN               (-HW_BOARD_CURR_MAX)                                          // 最小采样电流,-2.702A
#define HW_BOARD_CURR_BASE              (HW_BOARD_CURR_MAX * 2)                                       // 电流基准//5.4A

/*hardware voltage sample Parameter*/
/*母线电压采样分压电路参数*/
#define HW_BOARD_VOLT_MAX               (HW_ADC_REF * RV)                                             // (V)  ADC可测得的最大母线电压
#define HW_BOARD_VOLTAGE_BASE           (HW_BOARD_VOLT_MAX / 1.732)                                   // 电压基准

#define ATT_COEF                        (0.85)                                  ///< 无需改动

/*硬件过流保护DAC值*///添加宏定义
#if(AMP0_VHALF == 1)
  #define DAC_OvercurrentValue            (_Q8(I_ValueX((OverHardcurrentValue))) +(0x7F))
  #define DAC_RPDCurValue                 (_Q8(I_ValueX((RPD_CurValue))) +(0x7F))
#else
  #define DAC_OvercurrentValue            (_Q8(I_ValueX((OverHardcurrentValue))))
  #define DAC_RPDCurValue                 (_Q8(I_ValueX((RPD_CurValue))))
#endif


#define BASE_FREQ                       ((MOTOR_SPEED_BASE / 60) * Pole_Pairs)                        // 基准频率

/*保护参数值------------------------------------------------------------------*/
/* protect value */
#define OVER_PROTECT_VALUE              _Q15(Over_Protect_Voltage  / HW_BOARD_VOLT_MAX)
#define UNDER_PROTECT_VALUE             _Q15(Under_Protect_Voltage / HW_BOARD_VOLT_MAX)
#define OVER_RECOVER_VALUE              _Q15(Over_Recover_Vlotage  / HW_BOARD_VOLT_MAX)
#define UNDER_RECOVER_VALUE             _Q15(Under_Recover_Vlotage / HW_BOARD_VOLT_MAX)

/* motor speed set value */
#define Motor_Open_Ramp_ACC             _Q15(MOTOR_OPEN_ACC     / MOTOR_SPEED_BASE)
#define Motor_Open_Ramp_Min             _Q15(MOTOR_OPEN_ACC_MIN / MOTOR_SPEED_BASE)


#define Motor_Speed_Inc                 _Q15(SPEED_INC / MOTOR_SPEED_BASE)
#define Motor_Speed_Dec                 _Q15(SPEED_DEC / MOTOR_SPEED_BASE)

#define LOOP_K                         ((float)(MOTOR_LOOP_MAX-MOTOR_LOOP_MIN)/(float)(MAXPWMDuty-MINPWMDuty))

//#define LOOP_K2                        ((float)(MOTOR_LOOP_MAX2 - MOTOR_LOOP_MAX) / (float)(OFFPWMDutyHigh - MAXPWMDuty))

//#define LOOP_K3                         ((float)(_Q15(0.17)-_Q15(0.99))/(float)(MAXPWMDuty - MINPWMDuty))

/* obsever parameter set value */
#define MAX_BEMF_VOLTAGE                ((MOTOR_SPEED_BASE*Ke)/(1000.0))
#define MAX_OMEG_RAD_SEC                ((float)(_2PI*BASE_FREQ))
#define OBS_K1T                         _Q15(LD/(LD+RS*TPWM_VALUE))

#define OBS_K2T                         _Q13(1.732*(TPWM_VALUE/(LD+RS*TPWM_VALUE))*(HW_BOARD_VOLTAGE_BASE/HW_BOARD_CURR_BASE))
#define OBS_K3T                         _Q15((TPWM_VALUE/(LD+RS*TPWM_VALUE))*(MAX_BEMF_VOLTAGE/HW_BOARD_CURR_BASE))
#define OBS_K4T                         _Q15(((LD-LQ)*TPWM_VALUE*MAX_OMEG_RAD_SEC)/(LD+RS*TPWM_VALUE))

#define OBSW_KP_GAIN                    _Q12(2*_2PI*ATT_COEF*ATO_BW/BASE_FREQ)
#define OBSW_KI_GAIN                    _Q15(_2PI*ATO_BW*ATO_BW*TPWM_VALUE/BASE_FREQ)

#define OBSW_KP_GAIN_RUN                _Q12(2*_2PI*ATT_COEF*ATO_BW_RUN/BASE_FREQ)
#define OBSW_KI_GAIN_RUN                _Q15(_2PI*ATO_BW_RUN*ATO_BW_RUN*TPWM_VALUE/BASE_FREQ)

#define OBSW_KP_GAIN_RUN1               _Q12(2*_2PI*ATT_COEF*ATO_BW_RUN1/BASE_FREQ)
#define OBSW_KI_GAIN_RUN1               _Q15(_2PI*ATO_BW_RUN1*ATO_BW_RUN1*TPWM_VALUE/BASE_FREQ)

#define OBSW_KP_GAIN_RUN2               _Q12(2*_2PI*ATT_COEF*ATO_BW_RUN2/BASE_FREQ)
#define OBSW_KI_GAIN_RUN2               _Q15(_2PI*ATO_BW_RUN2*ATO_BW_RUN2*TPWM_VALUE/BASE_FREQ)

#define OBSW_KP_GAIN_RUN3               _Q12(2*_2PI*ATT_COEF*ATO_BW_RUN3/BASE_FREQ)
#define OBSW_KI_GAIN_RUN3               _Q15(_2PI*ATO_BW_RUN3*ATO_BW_RUN3*TPWM_VALUE/BASE_FREQ)

#define OBSW_KP_GAIN_RUN4               _Q12(2*_2PI*ATT_COEF*ATO_BW_RUN4/BASE_FREQ)
#define OBSW_KI_GAIN_RUN4               _Q15(_2PI*ATO_BW_RUN4*ATO_BW_RUN4*TPWM_VALUE/BASE_FREQ)

#define OBSW_KP_GAIN_RUN5               _Q12(2*_2PI*ATT_COEF*ATO_BW_RUN5/BASE_FREQ)
#define OBSW_KI_GAIN_RUN5               _Q15(_2PI*ATO_BW_RUN4*ATO_BW_RUN5*TPWM_VALUE/BASE_FREQ)


#define OBS_FBASE                       _Q15(BASE_FREQ*TPWM_VALUE)                                    // Fbase*Tpwm*32768
#define OBS_KLPF                        _Q15(_2PI*BASE_FREQ*TPWM_VALUE)                               // 2PI*Fbase*Tpwm
#define SPEED_KLPF                      _Q15(_2PI*SPD_BW*TPWM_VALUE)                                  // 2PI*SPD_BW*Tpwm
#define OBS_EA_KS                       _Q15((2*MOTOR_SPEED_SMOMIN_RPM*_2PI*BASE_FREQ*TPWM_VALUE)/MOTOR_SPEED_BASE)     // SMO的最小速度


/*逆风判断时的估算算法设置值------------------------------------------------------------*/
#define SPEED_KLPF_WIND                 _Q15(_2PI*SPD_BW_Wind*TPWM_VALUE)               // 2PI*SPD_BW_Wind*Tpwm
#define OBSW_KP_GAIN_WIND               _Q12(2*_2PI*ATT_COEF*ATO_BW_Wind/BASE_FREQ)
#define OBSW_KI_GAIN_WIND               _Q15(_2PI*ATO_BW_Wind*ATO_BW_Wind*TPWM_VALUE/BASE_FREQ)//


#define OBSE_PLLKP_GAIN                 _Q11(((2*ATT_COEF*_2PI*E_BW*LD - RS)*HW_BOARD_CURR_BASE)/HW_BOARD_VOLTAGE_BASE)
#define OBSE_PLLKI_GAIN                 _Q11((_2PI*E_BW*_2PI*E_BW*LD*TPWM_VALUE*HW_BOARD_CURR_BASE)/HW_BOARD_VOLTAGE_BASE)


/*Current Calib:enable or disable*/
#define Disable                         (0)
#define Enable                          (1)
#define CalibENDIS                      (Enable)

/*SVPWM mode*/
#define SVPWM_5_Segment                 (0)                                    // 五段式SVPWM
#define SVPWM_7_Segment                 (1)                                    // 七段式SVPWM
#define SVPMW_Mode                      (SVPWM_7_Segment)

/*double resistor sample mode*/
#define DouRes_1_Cycle                  (0)                                    // 1 周期采样完 ia, ib
#define DouRes_2_Cycle                  (1)                                    // 交替采用ia, ib, 2周期采样完成
#define DouRes_Sample_Mode              (DouRes_1_Cycle)

/*FG输出方式设置值----------------------------------------------------------------*/
#define DISABLE_FG_OUTPUT               (0xA0)                                     ///< 不反馈FG
#define HARD_TIMFG_OUTPUT               (0xC0)                                     ///< 通过硬件定时器输出FG信号
#define THETA_FG_OUTPUT                 (0xD0)                                     ///< 通过角度输出FG信号

#define Align_Theta                     _Q15((float)Align_Angle / 180.0)

/* -----过温保护值设置----- */
#define   Tempera_Value(NTC_Value) 		_Q15((5.0*NTC_Value/(10.0+NTC_Value))/HW_ADC_REF)									    ///< 10K上拉电阻时，NTC阻值对应Q15_AD值，单位：KΩ

#endif