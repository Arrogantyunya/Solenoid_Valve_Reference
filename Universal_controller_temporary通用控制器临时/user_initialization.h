//user_initialization.h
/*
*版权
*
* 文件名称:user_initialization.h
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


#ifndef USER_INITIALIZATION_H	//防止头文件user_initialization.h被重复调用
#define USER_INITIALIZATION_H
#include<arduino.h>	//引用标准库的头文件
#include<EEPROM.h>
#include"user_lorainit.h"
#include"user_A025receipt.h"



//引脚定义
#define K1			PC0		//按键1
#define K2			PC1		//按键2
#define A01			PC2		//模拟输出1
#define A02			PC3		//模拟输出2
#define VIN1		PA0		//模拟输入1
#define VIN2		PA1		//模拟输入2
#define TX_485		PA2		//485TX
#define	RX_485		PA3		//485RX
#define	DI1			PA6		//数字输入1
#define	DI2			PA7		//数字输入2
#define	DO1			PC4		//数字输出1
#define	DO2			PC5		//数字输出2
#define	KCZJ1		PB0		//继电器1
#define	KCZJ2		PB1		//继电器2
#define	BOOT1		PB2		//boot1
#define	LORA_RX		PB10	//LORA_TX
#define	LORA_TX		PB11	//LORA_RX
#define	LED4		PB12	//LED4
#define	LED3		PB13	//LED3
#define	LED2		PB14	//LED2
#define	LED1		PB15	//LED1
#define	MCU_TX		PA9		//MCU_TX
#define	MCU_RX		PA10	//MCU_RX
#define	USBDM		PA11	//USB接口
#define	USBDP		PA12	//USB接口
#define	SWDIO		PA13	//程序下载接口
#define SWCLK		PA14	//程序下载接口
#define	RESETN		PC12	//LORA模块RESETn
#define	WAKE_UP		PD2		//LORA模块Wake_UP
#define	AT_CMD		PB3		//LORA模块AT_CMD
#define	LORA_PWR	PB4		//LORA模块LORA_PWR
#define	WP			PB5		//FLASH模块WP
#define	EEPROM_SCL	PB6		//FLASH模块EEPROM_SCL
#define	EEPROM_SDA	PB7		//FLASH模块EEPROM_SDA
#define	BOOT0		BOOT0	//BOOT0


//全局函数声明
void Initialization(void);//初始化函数


//全局变量
static unsigned char Working_parameter_setting = 0x00; //工作参数设置标志位，为0为未设置，为1为已设置
static unsigned char Receive_Working_parameter_setting = 0x00; //接收参数设置标志位


//类结构声明



#endif