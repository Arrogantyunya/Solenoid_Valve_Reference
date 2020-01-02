//user_lorainit.cpp
/*
*版权
*
* 文件名称:user_lorainit.cpp
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


#include"user_lorainit.h"	//引用头文件

//函 数 名：LORA_Initialization() 
//功能描述：
//函数说明：LORA初始化的函数
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
void LORA_Initialization()//LORA初始化函数
{
	delay(3000);
	//对未设置过的LORA进行设置
	//更改TFREQ，RFREQ、TSF，RSF
	
	//先设置LORA引脚的初始化
	// digitalWrite(LORA_PWR,HIGH);		//开启LORA的电源
	// digitalWrite(RESETN,HIGH);			//防止LORA进行复位
	// digitalWrite(AT_CMD,LOW);			//将LORA设置为透传

    Serial.println("开始设置M-HL9：LORA的初始化配置");
    delay(500);
    digitalWrite(AT_CMD,HIGH);
    delay(500);

	//先测试AT指令是否OK
	delay(500);
	lora_len = 0;
	Serial3.print("AT\r\n");
	while(Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data,lora_len);
		delay(500);
		lora_len = 0;
		// if (lora_data[2] == 79 && lora_data[3] == 75)
		// {
		// 	Serial.println("AT设置成功");
		// }
		// else
		// {
		// 	Serial.println("AT设置失败");
		// }
	} 
	//然后设置NET
	//00为	Node to Node;	01为	Node to Gateway
	delay(500);
	Serial3.print("AT+NET=01\r\n");
	while(Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data,lora_len);
		lora_len = 0;
		delay(500);
		if (lora_data[2] == 79 && lora_data[3] == 75)
		{
			Serial.println("NET设置成功");
		}
		else
		{
			Serial.println("NET设置失败");
		}
	}
	//然后设置TFREQ、RFREQ发送频点以及接收频点
	delay(500);
	Serial3.print("AT+TFREQ=1C578DE0\r\n");
	while(Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data,lora_len);
		lora_len = 0;
		delay(500);
		if (lora_data[2] == 79 && lora_data[3] == 75)
		{
			Serial.println("TFREQ设置成功");
		}
		else
		{
			Serial.println("TFREQ设置失败");
		}
	}
	//设置RRFREQ
	delay(500);
	Serial3.print("AT+RFREQ=1C03A180\r\n");
	while(Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data,lora_len);
		lora_len = 0;
		delay(500);
		if (lora_data[2] == 79 && lora_data[3] == 75)
		{
			Serial.println("RFREQ设置成功");
		}
		else
		{
			Serial.println("RFREQ设置失败");
		}
	}
	//设置发送功率
	//14为20dbm
	delay(500);
	Serial3.print("AT+POW=14\r\n");
	while(Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data,lora_len);
		lora_len = 0;
		delay(500);
		if (lora_data[2] == 79 && lora_data[3] == 75)
		{
			Serial.println("POW设置成功");
		}
		else
		{
			Serial.println("POW设置失败");
		}
	}
	//设置调制带宽
	//07为125KHZ
	delay(500);
	Serial3.print("AT+BW=07\r\n");
	while(Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data,lora_len);
		lora_len = 0;
		delay(500);
		if (lora_data[2] == 79 && lora_data[3] == 75)
		{
			Serial.println("BW设置成功");
		}
		else
		{
			Serial.println("BW设置失败");
		}
	}
	//设置TSF发送扩频
	//09代表09
	delay(500);
	Serial3.print("AT+TSF=09\r\n");
	while(Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data,lora_len);
		lora_len = 0;
		delay(500);
		if (lora_data[2] == 79 && lora_data[3] == 75)
		{
			Serial.println("TSF设置成功");
		}
		else
		{
			Serial.println("TSF设置失败");
		}
	}

	//设置RSF接收扩频
	//09代表09
	delay(500);
	Serial3.print("AT+RSF=09\r\n");
	while(Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data,lora_len);
		lora_len = 0;
		delay(500);
		if (lora_data[2] == 79 && lora_data[3] == 75)
		{
			Serial.println("RSF设置成功");
		}
		else
		{
			Serial.println("RSF设置失败");
		}
	}

	//设置CR编码速率
	//01代表4/5
	delay(500);
	Serial3.print("AT+CR=01\r\n");
	while(Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data,lora_len);
		lora_len = 0;
		delay(500);
		if (lora_data[2] == 79 && lora_data[3] == 75)
		{
			Serial.println("CR设置成功");
		}
		else
		{
			Serial.println("CR设置失败");
		}
	}

	//设置MODE调制方式
	//01为LORA调制方式
	delay(500);
	Serial3.print("AT+MODE=01\r\n");
	while(Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data,lora_len);
		lora_len = 0;
		delay(500);
		if (lora_data[2] == 79 && lora_data[3] == 75)
		{
			Serial.println("MODE设置成功");
		}
		else
		{
			Serial.println("MODE设置失败");
		}
	}

	//设置SYNC同步字
	//12代表0x12
	delay(500);
	Serial3.print("AT+SYNC=12\r\n");
	while(Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data,lora_len);
		lora_len = 0;
		delay(500);
		if (lora_data[2] == 79 && lora_data[3] == 75)
		{
			Serial.println("SYNC设置成功");
		}
		else
		{
			Serial.println("SYNC设置失败");
		}
	}

	/*//-------------------------------------------------------
	//这里PREM设置不了，回复ER00
	//设置PREM前导码
	//08代表默认值
	Serial3.print("AT+PREM=08\r\n");
	while(Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data,lora_len);
		lora_len = 0;
		delay(500);
		if (lora_data[2] == 79 && lora_data[3] == 75)
		{
			Serial.println("是否设置成功");
		}
	}
	//-------------------------------------------------------*/

	//设置CRC硬件CRC
	//01代表有CRC校验
	delay(500);
	Serial3.print("AT+CRC=01\r\n");
	while(Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data,lora_len);
		lora_len = 0;
		delay(500);
		if (lora_data[2] == 79 && lora_data[3] == 75)
		{
			Serial.println("CRC设置成功");
		}
		else
		{
			Serial.println("CRC设置失败");
		}
	}

	//设置TIQ发送反转
	//00为不反转
	delay(500);
	Serial3.print("AT+TIQ=00\r\n");
	while(Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data,lora_len);
		lora_len = 0;
		delay(500);
		if (lora_data[2] == 79 && lora_data[3] == 75)
		{
			Serial.println("TIQ设置成功");
		}
		else
		{
			Serial.println("TIQ设置失败");
		}
	}

	//设置RIQ接收反转
	//00为不反转
	delay(500);
	Serial3.print("AT+RIQ=00\r\n");
	while(Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data,lora_len);
		lora_len = 0;
		delay(500);
		if (lora_data[2] == 79 && lora_data[3] == 75)
		{
			Serial.println("RIQ设置成功");
		}
		else
		{
			Serial.println("RIQ设置失败");
		}
	}

	//设置SEQ数据包编号、设置IP模块地址功能
	//01为带地址不带包序
	delay(500);
	Serial3.print("AT+SIP=01\r\n");
	while(Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data,lora_len);
		lora_len = 0;
		delay(500);
		if (lora_data[2] == 79 && lora_data[3] == 75)
		{
			Serial.println("SIP设置成功");
		}
		else
		{
			Serial.println("SIP设置失败");
		}
	}
	
	/*//-------------------------------------------------------
	//设置不成功
	//设置AES模块AES通信加密
	//
	Serial3.print("AT+AES=00000000000000000000000000000000\r\n");
	while(Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data,lora_len);
		lora_len = 0;
		delay(500);
		if (lora_data[2] == 79 && lora_data[3] == 75)
		{
			Serial.println("是否设置成功");
		}
	}
	//-------------------------------------------------------*/
	
	//设置ACK数据包应答功能
	//00代表不应答
	delay(500);
	Serial3.print("AT+ACK=00\r\n");
	while(Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data,lora_len);
		lora_len = 0;
		delay(500);
		if (lora_data[2] == 79 && lora_data[3] == 75)
		{
			Serial.println("ACK设置成功");
		}
		else
		{
			Serial.println("ACK设置失败");
		}
	}
	//设置LDR低速率优化
	//00代表AUTO
	delay(500);
	Serial3.print("AT+LDR=00\r\n");
	while(Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data,lora_len);
		lora_len = 0;
		delay(500);
		if (lora_data[2] == 79 && lora_data[3] == 75)
		{
			Serial.println("LDR设置成功");
		}
		else
		{
			Serial.println("LDR设置失败");
		}
	}

	//查询CFG
	delay(500);
	Serial3.print("AT+TFREQ?\r\n");
	while(Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data,lora_len);
		lora_len = 0;
		delay(500);
	}
	delay(500);
	Serial3.print("AT+RFREQ?\r\n");
	while(Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data,lora_len);
		lora_len = 0;
		delay(500);
	}
	delay(500);
	Serial3.print("AT+SYNC?\r\n");
	while(Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data,lora_len);
		lora_len = 0;
		delay(500);
	}
	delay(500);
	Serial3.print("AT+POW?\r\n");
	while(Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data,lora_len);
		lora_len = 0;
		delay(500);
	}
	delay(500);
	Serial3.print("AT+BW?\r\n");
	while(Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data,lora_len);
		lora_len = 0;
		delay(500);
	}
	delay(500);
	Serial3.print("AT+CR?\r\n");
	while(Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data,lora_len);
		lora_len = 0;
		delay(500);
	}
	delay(500);
	Serial3.print("AT+CRC?\r\n");
	while(Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data,lora_len);
		lora_len = 0;
		delay(500);
	}
	delay(500);
	Serial3.print("AT+TSF?\r\n");
	while(Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data,lora_len);
		lora_len = 0;
		delay(500);
	}
	delay(500);
	Serial3.print("AT+RSF?\r\n");
	while(Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data,lora_len);
		lora_len = 0;
		delay(500);
	}
	digitalWrite(AT_CMD,LOW);		//将LORA设置为透传
	delay(10);
    LORA_Working_parameter_setting = 0x01;
    EEPROM.write(32,0x01);//将EEPROM的标志位设置为0x01已设置
    Serial.println("LORA初始化设置完成");
}
