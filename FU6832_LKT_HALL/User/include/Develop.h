/*  -------------------------- (C) COPYRIGHT 2020 Fortiortech ShenZhen ---------------------------*/
/*  File Name      : Develop.h
/*  Author         : Fortiortech  Appliction Team
/*  Version        : V1.0
/*  Date           : 2020-08-31
/*  Description    : This file contains Advanced Applications parameter used for Motor Control.
/*  ----------------------------------------------------------------------------------------------*/
/*                                     All Rights Reserved
/*  ----------------------------------------------------------------------------------------------*/

/*  Define to prevent recursive inclusion --------------------------------------------------------*/
#ifndef __DEVELOP_H_
#define __DEVELOP_H_
#include <Customer.h>


/* 电机启动参数值 */
//open 算法启动参数
#define MOTOR_OPEN_ACC                  (1)                                 // 强拖启动的增量(每载波周期加一次)
#define MOTOR_OPEN_ACC_MIN              (1)                                   // 强拖启动的初始速度
#define MOTOR_OPEN_ACC_CNT              (4)                                  // 强拖启动的执行次数(MOTOR_OPEN_ACC_CNT*256)
#define MOTOR_OPEN_ACC_CYCLE            (10)                                   // 强拖启动循环拖动的次数


#endif

