//user_initialization.cpp
/*
*版权
*
* 文件名称:user_initialization.cpp
* 文件标识:配置管理计划书
* 摘要:对引脚进行初始化
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


#include"user_initialization.h"	//引用头文件

//函 数 名：Initialization() 
//功能描述：初始化的函数
//函数说明：
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
void Initialization()//初始化函数
{
    //初始化引脚
    afio_cfg_debug_ports(AFIO_DEBUG_SW_ONLY);//因为引脚复用
    pinMode(RESETN,OUTPUT);//复位电路，给高电平进行复位
    pinMode(KCZJ1,OUTPUT);//继电器1
    pinMode(KCZJ2,OUTPUT);//继电器2
    pinMode(LED1,OUTPUT);//LED1
    pinMode(LED2,OUTPUT);//LED2
    pinMode(LED3,OUTPUT);//LED3
    pinMode(LED4,OUTPUT);//LED4
    pinMode(A01,OUTPUT);//模拟输出1
    pinMode(A02,OUTPUT);//模拟输出2
    pinMode(K1,INPUT);//按键1
    pinMode(K2,INPUT);//按键2
    pinMode(LORA_PWR,OUTPUT);//LORA电源
    pinMode(RESETN,OUTPUT);//LORA复位
    pinMode(AT_CMD,OUTPUT);//LORA设置
    pinMode(WAKE_UP,OUTPUT);//LORA唤醒
	pinMode(VIN1,INPUT_ANALOG);//模拟输入电压1
	pinMode(VIN2,INPUT_ANALOG);//模拟输入电压2
	pinMode(A01, OUTPUT);//模拟输出1
	pinMode(A02, OUTPUT);//模拟输出2
	pinMode(DI1, INPUT_PULLDOWN);//数字输入1
	pinMode(DI2, INPUT_PULLDOWN);//数字输入2
	pinMode(DO1, OUTPUT);//数字输出1
	pinMode(DO2, OUTPUT);//数字输出2

    
    //初始化串口
    Serial.begin(9600);		//USB串口
	Serial2.begin(9600);	//485的串口
    Serial3.begin(9600);	//LORA的串口
    //继电器初始化//
    digitalWrite(KCZJ1,HIGH);
    digitalWrite(KCZJ2,HIGH);

    //LED初始化
    digitalWrite(LED1,LOW);
    digitalWrite(LED2,LOW);
    digitalWrite(LED3,LOW);
    digitalWrite(LED4,LOW);
    
    //lora相关初始化//
    digitalWrite(LORA_PWR,HIGH);
    digitalWrite(RESETN,HIGH);
    digitalWrite(AT_CMD,LOW);

    //-------------------------------------------
    //======测试时所用代码块，实际使用请注释=====
    //将所有的标志位都清为0
	//EEPROM.write(0, 0x00);//全部设置完成的标志位
	//EEPROM.write(29, 0x00);//A012设置完成的标志位
	//EEPROM.write(30, 0x00);//A013设置完成的标志位
	//EEPROM.write(31, 0x00);//Receive设置完成的标志位
	//EEPROM.write(32, 0x00);//LORA设置完成的标志位
	//EEPROM.write(33, 0x00);//EEPR0M初始化设置完成的标志位
    //-------------------------------------------

    //设置EEPROM的初始化
    if(EEPROM.read(33) == 0x01)
    {
    	//说明进行过EEPROM的初始化
    	delay(1500);
    	Serial.println("进行过EEPROM的初始化");
    }
    else
    {
    	delay(1500);
    	Serial.println("进行EEPROM存储空间的初始化");
    	//则需要进行EEPROM的初始化
		EEPROM.write(1,0xC0);//设备类型初始化
		EEPROM.write(2,0x02);
    	EEPROM.write(3,0x00);//区域值初始化
    	EEPROM.write(4,0x01);//组数组的第一位
    	for (int i = 5; i <= 8; ++i)
    	{
    		EEPROM.write(i,0x00);//组数组初始化
    	}
		EEPROM.write(9, 0x02);//设备路数的初始化
		for (int i = 10; i <= 27; ++i)
		{
			EEPROM.write(i, 0x00);//采集时间间隔、RTC、SN初始化
		}
		EEPROM.write(28,0x01);//A011设置的标志位，没有实际用途
    	EEPROM.write(33,0x01);
    	Serial.println("EEPROM存储空间的初始化完成");
    }

    //这里就读取LORA标志位是否设置完成，未设置完成就进行LORA模块的设置
	if (EEPROM.read(32) == 0x01)
	{
		Serial.println("LORA进行过初始化设置");
	}
	else
    {
        Serial.println("LORA未进行初始化设置，开始进行LORA模块的初始化");
        //进入LORA设置的函数
        LORA_Initialization();
    }

    //读取A012、A013的标志位，看看是否设置完成
    A012_Working_parameter_setting = EEPROM.read(29);
    A013_Working_parameter_setting = EEPROM.read(30);

    if (A012_Working_parameter_setting == 0x01 && A013_Working_parameter_setting == 0x01)
    {
        //当所有标志位都设置完成后，将总标志位设置写入0x01（设置完成）
        Working_parameter_setting = 0x01;
        EEPROM.write(0,Working_parameter_setting);
        Receive_Working_parameter_setting = 0x01;
        EEPROM.write(31,Receive_Working_parameter_setting);
        Serial.println("标志位已经全部设置完成");
    }
    else
    {
        //标志位未全部设置完成，总标志位设置写入0x00（设置未完成）
        Working_parameter_setting = 0x00;
        EEPROM.write(0,Working_parameter_setting);
        Receive_Working_parameter_setting = 0x00;
        EEPROM.write(31,Receive_Working_parameter_setting);
        Serial.println("标志位未全部设置完成，请重新请求设置");
    }

    //-------------------------------------------
    //这里可以注释，自行选择保留
    //输出总标志位的状态
    Serial.print("总标志位：");
    Serial.println(EEPROM.read(0),HEX);
   	//-------------------------------------------
}
