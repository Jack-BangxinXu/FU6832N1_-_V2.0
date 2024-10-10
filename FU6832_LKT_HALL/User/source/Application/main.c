/**
 * @copyright (C) COPYRIGHT 2022 Fortiortech Shenzhen
 * @file      main.c
 * @author    Fortiortech  Appliction Team
 * @since     Create:2022-09-04
 * @date      Last modify:2022-09-14
 * @note      Last modify author is Leo li
 * @brief     包含主函数，软硬件初始化函数，VRER配置函数,Debug小工具
 */

/*-------------------------------------------------------------------------------
    Header Definition
-------------------------------------------------------------------------------*/
#include <MyProject.h>

uint8 data g_1mTick = 0;  ///< 1ms滴答信号，每隔1ms在SYSTICK定时器被置1，需在大循环使用处清零

void HardwareInit(void);
void SoftwareInit(void);
void VREFConfigInit(void);


/**
 * @brief        SPI Debug调试小工具
 * @date         2022-09-04
 */
void DebugSet(void)
{
	/* -----硬件外设初始化----- */
#if (DBG_MODE == DBG_SPI_HW)        // 硬件调试模式
	{
		SPI_Init();
		Set_DBG_DMA(&HARD_SPIDATA);
	}
#elif (DBG_MODE == DBG_SPI_SW)      // 软件调试模式
	{
		SPI_Init();
		Set_DBG_DMA(spidebug);
	}
#elif (DBG_MODE == DBG_UART)        // UART调试模式
	{
		UART2_Init();
		SetPipe_DMA0(DRAM_UART2);
	}
#endif
	/* Observation signal Select */
	SetReg(CMP_CR3, DBGSEL0 | DBGSEL1, GP01_DBG_Conf);
	SetReg(CMP_CR3, CMPSEL0 | CMPSEL1 | CMPSEL2, GP07_DBG_Conf);

}


/**
 * @brief     硬件初始化，初始化需要使用的硬件设备配置，FOC必须配置的是运放电压、运放初始化、ADC初始化、Driver初始化
 *            其他的可根据实际需求加。
 * @date      2022-09-04
 */
void HardwareInit(void)
{
    /*----- 为提高芯片的抗干扰能力，降低芯片功耗，请在具体项目时，将不需要用的GPIO默认都配置为输入上拉。
     具体配置可在GPIO_Default_Init设置。------*/
    // GPIO_Default_Init();
    /*----- ADC参考电压电压配置 ------*/
    VREFConfigInit();
    /*----- 硬件过流，比较器初始化，用于硬件过流比较保护 ------*/
    CMP3_Init();
    GPIO_Init();
	ADC_Init();
    Driver_Init();
    AMP_Init();
    #if defined (SPI_DBG_SW) | defined (SPI_DBG_HW)   // 调试模式
    SPI_Init();                    //调试模式下，占用SPI端口的NSS(GP04),MOSI(GP05),SCK(GP06)
    #endif
    /* -----比较器中断配置----- */
    CMP3_Interrupt_Init();
    Timer3_Init();
//    Timer4_Init();
    /* -----SYSTICK定时器配置----- */
    SetBit(DRV_SR, SYSTIE);
    /*----- 总中断使能 -----*/
    EA = 1;
}

/**
 * @brief        部分变量初始化，上电运行一次
 * @date         2022-07-14
 */
void SoftwareInit(void)
{
    MotorcontrolInit();
    mcState       = mcReady;
    mcFaultSource = FaultNoSource;
}


/**
 * @brief        参考电压，偏置电压配置
 * @date         2022-09-04
 */
void VREFConfigInit(void)
{
    /* ***********************VREF&VHALF Config*********************** */
    #if (HW_ADC_VREF == VREF3_0)
    {
        SetBit(VREF_VHALF_CR, VRVSEL1);             //00-->4.5V   01-->VDD5
        ClrBit(VREF_VHALF_CR, VRVSEL0);             //10-->3.0V   11-->4.0V
    }
    #elif (HW_ADC_VREF == VREF4_0)
    {
        SetBit(VREF_VHALF_CR, VRVSEL1);             //00-->4.5V   01-->VDD5
        SetBit(VREF_VHALF_CR, VRVSEL0);             //10-->3.0V   11-->4.0V
    }
    #elif (HW_ADC_VREF == VREF4_5)
    {
        ClrBit(VREF_VHALF_CR, VRVSEL1);             //00-->4.5V   01-->VDD5
        ClrBit(VREF_VHALF_CR, VRVSEL0);             //10-->3.0V   11-->4.0V
    }
    #elif (HW_ADC_VREF == VREF5_0)
    {
        ClrBit(VREF_VHALF_CR, VRVSEL1);             //00-->4.5V   01-->VDD5
        SetBit(VREF_VHALF_CR, VRVSEL0);             //10-->3.0V   11-->4.0V
    }
    #else
    {
#error " VHALF MODE Err "
    }
    #endif
    #if (VREF_OUT_EN)
    SetBit(P3_AN, PIN5);                         //VREF Voltage -->P35 Output 是否输出到P35引脚，需同步配置输出
    SetBit(P3_OE, PIN5);                         //VREF Voltage -->P35 Output 是否输出到P35引脚
    SetBit(VREF_VHALF_CR, VREFEN);
    #endif
    #if (VHALF_OUT_EN)
    SetBit(P3_AN, P32);
    SetBit(VREF_VHALF_CR, VHALFEN);
    #endif
	//配置VHALEN
	SetBit(VREF_VHALF_CR, VHALFEN);
}


/**
 * @brief        主函数，大循环运行偏置电流采集函数，电机状态机控制函数，以及环路响应函数
 * @date         2022-09-04
 */
void main(void)
{
    uint16 PowerUpCnt = 0;
    
    /*********上电等待*********/
    for (PowerUpCnt = 0; PowerUpCnt < SystemPowerUpTime; PowerUpCnt++);
    
    /* ----- 部分变量初始化 ----- */
    SoftwareInit();
    /* ----- 硬件初始化，配置MCU外设 ----- */
    HardwareInit();
    #if (DBG_MODE !=  DBG_DISABLE)      // 调试小工具
    /* -----debug配置(SPI调试)，量产程序可以删除----- */
    DebugSet();
    #endif
    
    while (1)
    {
//		GP05 = 1;
        /* -----获取电流采样偏置电压----- */
        if (!mcCurOffset.OffsetFlag)
        {
            GetCurrentOffset();
        }
        else
        {
            /* -----电机控制状态机----- */
            MC_Control();
        }
        
        if (g_1mTick)
        {
            TickCycle_1ms();
            g_1mTick = 0;
        }
		
//		GP05=0;
    }
}
