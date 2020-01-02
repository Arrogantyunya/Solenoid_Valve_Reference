// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
    Name:       RS485_A200FrequencyConverter.ino
    Created:	2019/6/11 星期二 14:38:23
    Author:     刘家辉
*/

// Define User Types below here or use a .h file
//


// Define Function Prototypes that use User Types below here or use a .h file
//


// Define Functions below here or use other .ino or cpp files
//

// The setup() function runs once each time the micro-controller starts
#include"user_initialization.h"	//初始化函数
#include"MODBUS_RTU_CRC16.h"	//modbusCRC16校验的函数

static unsigned char YO_ON[8] = { 0x01,0x05,0x00,0x00,0xFF,0x00 };
static unsigned char YO_OFF[8] = { 0x01,0x05,0x00,0x00,0x00,0x00 };
static unsigned char Positive[8] = { 0x01,0x06,0x20,0x00,0x00,0x01 };
static unsigned char stop[8] = { 0x01,0x06,0x20,0x00,0x00,0x05 };
static unsigned char diagnosis[8] = { 0x01,0x08,0x00,0x00,0x12,0xAB };
String Y0_ON = "01050000FF00";
String str_crc;
static unsigned short length = 6;
static int modbus_CRC = 0x00;
static unsigned char RS485REceive_Data[50];
static int RS485REceive_Length = 0;


//相关函数的定义
int16_t RS485Receive_information(void);		//RS485接收函数
int16_t LORAReceive_information(void);      //LORA接收函数



void setup()
{
	Initialization();//初始化函数

	//str_crc = String(N_CRC16(YO_ON, length),HEX);
	//Serial.print("str_crc1 = ");
	//Serial.println(str_crc);

	//Serial.print("0,2 :");
	//Serial.println(str_crc.substring(0,2));//这是将String类型的字符串截取0-2的索引值

	//Serial.print("2,4 :");
	//Serial.println(str_crc.substring(2,4));//这是将String类型的字符串截取2-4的索引值
}

// Add the main program code into the continuous loop() function
void loop()
{
	RS485Receive_information();	//RS485的接收函数
	LORAReceive_information();	//LORA的接收函数
	if (digitalRead(K1) == LOW)
	{
		delay(50);//消抖
		if (digitalRead(K1) == LOW)
		{
			modbus_CRC = N_CRC16(Positive, length);//得到modbus_CRC的值
			Serial.print("modbusCRC16 = ");//输出modbus_CRC的值
			Serial.println(modbus_CRC, HEX);

			Positive[6] = modbus_CRC >> 8;
			Positive[7] = modbus_CRC;

			digitalWrite(DE_485, LOW);
			delay(500);
			Serial2.write(Positive, 8);//发送diagnosis的指令
			Serial2.flush();//等待485串口的数据发送完成
			digitalWrite(DE_485, HIGH);//高电平接收
			while (digitalRead(K1) == LOW);//为了防止按键一直按下，在这里空循环
		}
	}
	if (digitalRead(K2) == LOW)
	{
		delay(50);
		if (digitalRead(K2) == LOW)
		{
			modbus_CRC = N_CRC16(stop, length);//得到modbus_CRC的值
			Serial.print("modbusCRC16 = ");//输出modbus_CRC的值
			Serial.println(modbus_CRC, HEX);

			stop[6] = modbus_CRC >> 8;
			stop[7] = modbus_CRC;

			digitalWrite(DE_485, LOW);//低电平发送
			delay(500);
			Serial2.write(stop, 8);//发送Forward_running的指令
			Serial2.flush();//等待485串口的数据发送完成
			digitalWrite(DE_485, HIGH);//高电平接收
			while (digitalRead(K2) == LOW);//为了防止按键一直按下，在这里空循环
		}
	}
}

int16_t RS485Receive_information(void)
{
	while (Serial2.available() > 0)//RS485串口接收到数据
	{
		RS485REceive_Data[RS485REceive_Length++] = Serial2.read();
		/*RS485REceive_Length++;*/
		delay(5);
	}
	if (RS485REceive_Length > 0)
	{
		digitalWrite(LED4, HIGH);
		delay(400);
		digitalWrite(LED4, LOW);
		Serial.print("RS485REceive_Length = ");
		Serial.println(RS485REceive_Length);
		for (int i = 0; i < RS485REceive_Length; i++)
		{
			Serial.print(String("RS485REceive_Data") + "[" + i + "]");
			Serial.println(RS485REceive_Data[i], HEX);
		}
		RS485REceive_Length = 0;
	}
	return 0;

}

int16_t LORAReceive_information(void)
{
	return 0;
}