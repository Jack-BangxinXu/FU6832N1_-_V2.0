/********************************************************************************

 **** Copyright (C), 2019, Fortior Technology Co., Ltd.                      ****

 ********************************************************************************
 * File Name     : FU68xx_4_DMA.h
 * Author        : Bruce HW&RD
 * Date          : 2019-03-27
 * Description   : .C file function description
 * Version       : 1.0
 * Function List :
 * 
 * Record        :
 * 1.Date        : 2019-03-27
 *   Author      : Bruce HW&RD
 *   Modification: Created file

********************************************************************************/

#ifndef __FU68XX_4_DMA_H__
#define __FU68XX_4_DMA_H__

// Include external	header file.
#include "FU68xx_4_MCU.h"

#ifdef __cplusplus
extern "C" {
#endif
// DMA Pipe Config
 #define DMA_PIPE        (DMACFG2 | DMACFG1 | DMACFG0)
 #define UART1_XDATA     0x00                                         // DMA管道--UART1-->XDATA
 #define XDATA_UART1     (DMACFG0)                                    // DMA管道--UART1<--XDATA
 #define I2C_XDATA       (DMACFG1)                                    // DMA管道--I2C  -->XDATA
 #define XDATA_I2C       (DMACFG0 | DMACFG1)                          // DMA管道--I2C  <--XDATA
 #define SPI_XDATA       (DMACFG2)                                    // DMA管道--SPI  -->XDATA
 #define XDATA_SPI       (DMACFG2 | DMACFG0)                          // DMA管道--SPI  <--XDATA
 #define UART2_XDATA     (DMACFG2 | DMACFG1)                          // DMA管道--UART2-->XDATA
 #define XDATA_UART2     (DMACFG2 | DMACFG1 | DMACFG0)                // DMA管道--UART2<--XDATA

// DMA IE config
 #define DMA_IE_EN       DMAIE                                        // 使能DMA中断
 #define DMA_IE_DIS      0x00                                         // 禁能DMA中断

// DMA transmission order
 #define DMA_FHSB        ENDIAN                                       // DMA先发高8位
 #define DMA_FLSB        0x00                                         // DMA先发低8位
/**************************************************************************************************///Define Global Symbols
/**************************************************************************************************///Function Subject
#define Wait_DMA(a)       while (ReadBit(*(&DMA0_CR0 + a), DMABSY))
#define Switch_DMA(a)     SetBit(*(&DMA0_CR0 + a), DMAEN | DMABSY)

extern void Init_DMA(uint8 DMAIrq, uint8 DMAFMod);
extern void Conf_DMA(uint8 DMAx, uint8 DMAPipe, uint16 DMAAddr, uint8 DMALen);
//extern void Set_DBG_DMA(uint16 DMAAddr);

#ifdef __cplusplus
}
#endif

#endif	//__FU68XX_4_DMA_H__


/*** (C) Copyright 2022	Fortior	Technology Co.,	Ltd. ***/
