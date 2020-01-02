//user_lorainit.h
/*
*版权
*
* 文件名称:user_lorainit.h
* 文件标识:配置管理计划书
* 摘要:定义了需要初始化的引脚
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
#ifndef USERLORA_INIT_H	//防止头文件user_initialization.h被重复调用
#define USERLORA_INIT_H
#include<arduino.h>	//引用标准库的头文件
#include<EEPROM.h>
#include"user_initialization.h"	//引用头文件



//引脚定义


//全局函数声明
void LORA_Initialization(void);//初始化函数
//全局变量
static unsigned char LORA_Working_parameter_setting;
static unsigned char lora_data[500];
static unsigned char lora_len = 0;


//类结构声明



#endif