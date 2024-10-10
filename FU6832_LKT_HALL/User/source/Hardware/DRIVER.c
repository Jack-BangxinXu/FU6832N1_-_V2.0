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
 * @brief     Driver初始化配置
 * @date      2022-09-12
 */	
void Driver_Init(void)
{
    DRV_ARR = PWM_VALUE_LOAD - 1;       // 载波频率的周期值
    DRV_DTR = PWM_LOAD_DEADTIME - 1;    // 死区时间
    DRV_DR  = 0;
    DRV_CMR &= 0x003f;  //UH/VH/WH UL/VL/WL High level active
    DRV_OUT &= 0x80;    //UH/VH/WH UL/VL/WL Idle level is 0
    ClrBit(DRV_SR, FGIE);   //FG中断使能            0-->Disable     1-->Enable
    /*清中断标志位，使能中断，配置比较值，设置中断优先级*/
    ClrBit(DRV_SR, DCIF);   //清除DRV中断标志位
    /**************************************************
        DRV比较匹配中断模式
        当计数值等于DRV_COMR时，根据DCIM的设置判断是否产生中断标记
        00：不产生中断        01：上升方向
        10：下降方向         11：上升/下降方向
    *************************************************/
    SetBit(DRV_SR, DCIM1);
    ClrBit(DRV_SR, DCIM0);
    /*设置DRV计数器的比较匹配值，当DRV计数值与COMR相等时，根据DRV_SR寄存器的DCIM是否产生比较匹配事件*/
    DRV_COMR = (PWM_VALUE_LOAD >> 3);
    PDRV1 = 1;// 中断优先级设置为2，优先级低于FO硬件过流
    PDRV0 = 0;
    ClrBit(DRV_SR, DCIP);   //0-->1个计数周期产生中断  1-->2个计数周期产生中断
    ClrBit(DRV_CR, FOCEN);
	
    /*  MESEL为0，ME模块工作在BLDC模式
        MESEL为1，ME模块工作在FOC/SVPWM/SPWM模式*/		
    SetBit(DRV_CR, MESEL);
    SetBit(DRV_CR, DRVEN);  //计数器使能       0-->Disable     1-->Enable
    ClrBit(DRV_CR, DRPE);   //计数器比较值预装载使能 0-->Disable             1-->Enable
    SetBit(DRV_CR, DRVOE);  //Driver输出使能0-->Disable     1-->Enable
    MOE = 1;
}
