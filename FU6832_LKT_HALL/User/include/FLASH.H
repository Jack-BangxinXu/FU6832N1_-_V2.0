/******************* (C) COPYRIGHT 2019 Fortiortech Shenzhen *******************
* File Name          : FU68xx_4_FLASH.h
* Creat Author       : Any Lin, R&D
* Modify Author      : Any Lin, R&D
* Creat Date         : 2019-06-08
* Modify Date        : 2019-06-11
* Description        :
********************************************************************************
* All Rights Reserved
*******************************************************************************/

#ifndef __FLASH_H__
#define __FLASH_H__

/******************************************************************************///Including Header Files
#include <FU68xx_4_MCU.h>
/******************************************************************************///Define Macro
/******************************************************************************///Define Type
typedef enum
{
    FLAERR_ADDR = -3,                                                           // Flash状态: 操作的地址错误
    FLAERR_KEY  = -2,                                                           // Flash状态: Flash在复位前无法执行任何操作
    FLAERR_DAT  = -1,                                                           // Flash状态: Flash编程失败
    FLA_NORMAL  =  0,                                                           // Flash状态: Flash正常
}ETypeFlashSta;
/******************************************************************************///External Symbols
/******************************************************************************///External Function
extern ETypeFlashSta FLASH_Erase   (uint16 wAddr);
extern ETypeFlashSta FLASH_Progarm (uint16 wAddr, uint8 ucDat);
extern ETypeFlashSta FLASH_Progarms(uint16 wAddr, uint8 *ucpDat, uint16 wLen);

#endif

