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
/******************************************************************************///Define Macro
#define FLASH_DON_TOCH_SECTOR_ADDR      0x3f80
/******************************************************************************///Define Global Symbols
/******************************************************************************///Function Subject


/**
 * @brief     
 * @date      2022-09-12
 */	
static bool _FLASH_Ctrl(uint16 wAddr, uint8 ucCmd, uint8 ucDat)
{
    FLA_CR = FLAEN | ucCmd;
    FLA_KEY = 0x5a;
    FLA_KEY = 0x1f;
    *(uint8 xdata *)wAddr = ucDat;
    FLA_CR |= FLAACT;
    
    if ((FLA_CR & FLAERR) == FLAERR)
    {
        return false;
    }
    
    return true;
}


/**
 * @brief     
 * @date      2022-09-12
 */
ETypeFlashSta FLASH_Erase(uint16 wAddr)
{
    bool bEATmp;
    bool bError;
    
    if (wAddr >= FLASH_DON_TOCH_SECTOR_ADDR)
    {
        return FLAERR_ADDR;
    }
    
    if (FLA_KEY == 0x02)
    {
        return FLAERR_KEY;
    }
    
    bEATmp = EA;
    EA = 0;
    bError = !_FLASH_Ctrl(wAddr, FLAPRE, 0x00) || !_FLASH_Ctrl(wAddr, FLAERS, 0x00);
    EA = bEATmp;
    return bError ? FLAERR_DAT : FLA_NORMAL;
}


/**
 * @brief     
 * @date      2022-09-12
 */
ETypeFlashSta FLASH_Program(uint16 wAddr, uint8 ucDat)
{
    bool bEATmp;
    bool bError;
    
    if (wAddr >= FLASH_DON_TOCH_SECTOR_ADDR)
    {
        return FLAERR_ADDR;
    }
    
    if (FLA_KEY == 0x02)
    {
        return FLAERR_KEY;
    }
    
    bEATmp = EA;
    EA = 0;
    bError = _FLASH_Ctrl(wAddr, 0x00, ucDat);
    EA = bEATmp;
    return bError ? FLA_NORMAL : FLAERR_DAT;
}


/**
 * @brief     
 * @date      2022-09-12
 */
ETypeFlashSta FLASH_Programs(uint16 wAddr, uint8 * ucpDat, uint16 wLen)
{
    bool bEATmp;
    bool bError;
    uint16 w;
    
    if (wAddr >= FLASH_DON_TOCH_SECTOR_ADDR)
    {
        return FLAERR_ADDR;
    }
    
    if (FLA_KEY == 0x02)
    {
        return FLAERR_KEY;
    }
    
    bEATmp = EA;
    EA = 0;
    bError = true;
    
    for (w = 0; w != wLen; w++)
    {
        bError = _FLASH_Ctrl(wAddr + w, 0x00, *(ucpDat + w));       // 不直接break, 目的是均衡磨损
    }
    
    EA = bEATmp;
    return bError ? FLA_NORMAL : FLAERR_DAT;
}

