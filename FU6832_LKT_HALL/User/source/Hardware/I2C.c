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
/*
    void I2C_Init_Master(void)
    {
    SetBit(P0_PU , P00);
    SetBit(P0_PU , P01);
    // I2C initial
    SetBit(I2C_CR , I2CMS);     //主从模式选择    0-->Slave Mode  1-->Host Mode
    ClrBit(I2C_CR , I2CSPD1);   //00-->100kHz       01-->400kHz
    SetBit(I2C_CR , I2CSPD0);   //10-->1MHz         11-->RSV
    ClrBit(I2C_CR , I2CIE);     //中断使能         0-->Disable 1-->Enable
    I2C_ID = 0xD0;
    SetBit(I2C_ID , GC);    //广播呼叫使能    0-->Disable 1-->Enable
    SetBit(I2C_CR , I2CEN); //I2C使能     0-->Disable 1-->Enable
    }

    void I2C_ID_Start(bool rw)
    {
    if(rw)
        SetBit(I2C_SR , DMOD);
    else
        ClrBit(I2C_SR , DMOD);
    SetBit(I2C_SR , I2CSTA);    //1-->发送START或RESTART和地址字节
    while(!ReadBit(I2C_SR , STR));
    ClrBit(I2C_SR , STR);
    }

    void I2C_Addr_Write(unsigned char addr,unsigned char wdata)
    {
    I2C_ID_Start(0);    // ID write

    I2C_DR = addr;      // Slave reg addr.
    while(!ReadBit(I2C_SR , STR));
    ClrBit(I2C_SR , STR);

    I2C_DR = wdata;     // Slave reg data.
    while(!ReadBit(I2C_SR , STR));
    ClrBit(I2C_SR , STR);
    SetBit(I2C_SR , I2CSTP);    //1-->发送STOP
    }

    unsigned char I2C_Addr_Read(char addr)
    {
    unsigned char rd_data;
    //write process
    I2C_ID_Start(0);  // write+ID
    I2C_DR = addr;   // write reg. addr
    while(!ReadBit(I2C_SR , STR));
    ClrBit(I2C_SR , STR);
    //    SetBit(I2C_SR , I2CSTP);  //1-->发送STOP

    //read process
    I2C_ID_Start(1);  // read+ID
    while(!ReadBit(I2C_SR , STR));
    ClrBit(I2C_SR , STR);
    rd_data = (unsigned char)(I2C_DR); // read data
    SetBit(I2C_SR , NACK);      //第9位发送NACK
    SetBit(I2C_SR , I2CSTP);    //1-->发送STOP
    return(rd_data);
    }*/
