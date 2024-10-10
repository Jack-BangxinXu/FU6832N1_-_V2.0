/**
 * @file	 FU68xx_4_Type.h
 * @version	 V1.0.0
 * @author	 FortiorTech Hardware Team
 * @date	 2021-07-15	22:22:21
 * @brief	 This file contains	...
 * 
 * @copyright Copyright(C) 2022, Fortior Technology	Co., Ltd. All rights reserved.
 */

#ifndef	__FU68XX_4_TYPE_H__
#define	__FU68XX_4_TYPE_H__

// Include external	header file.
#include <ctype.h> 

#ifdef __cplusplus
extern "C" {
#endif


#define	_I								volatile const
#define	_O								volatile
#define	_IO								volatile

//#define bool							  bit
//#define false							  (0)
//#define true							  (!false)

typedef	unsigned char					uint8;
typedef	unsigned short					uint16;
typedef	unsigned long					uint32;
typedef	long							int32;
typedef	short							int16;
typedef	char							int8;

typedef	enum{false = 0,	true}			bool;
typedef	enum{DISABLE = 0, ENABLE}		ebool;


#ifdef __cplusplus
}
#endif

#endif	//__FU68XX_4_TYPE_H__


/*** (C) Copyright 2022	Fortior	Technology Co.,	Ltd. ***/
