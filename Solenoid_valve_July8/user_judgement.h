//user_judgement.h
/*
*版权
*
* 文件名称:user_judgement.h
* 文件标识:配置管理计划书
* 摘要:
*
* 当前版本:V1.0
* 作者:刘家辉
* 完成日期:
* 修改者:
* 修改日期:
*
* 取代版本:
* 原作者:刘家辉
* 完成日期:
 */

#ifndef USER_JUDGEMENT_H	                      //防止头文件user_initialization.h被重复调用
#define USER_JUDGEMENT_H	

#include<arduino.h>	                            //引用标准库的头文件
#include<EEPROM.h>
#include"user_initialization.h"	                //引用非标准库的头文件
#include"user_crc8.h"

//全局变量
static unsigned char Judgement_Data[50];   	//用来存放接收到的数据
static int Judgement_Length = 0;
static int Judgement_flag = 0;
static int Judgement_DeviceTypeID1 = 0xC0;	//这里设置了设备类型
static int Judgement_DeviceTypeID2 = 0x03;


//全局函数声明
unsigned char Judgement_function(unsigned char * Judgement_Data, int Judgement_Length, int CRC_Check_num);


//类结构声明


#endif