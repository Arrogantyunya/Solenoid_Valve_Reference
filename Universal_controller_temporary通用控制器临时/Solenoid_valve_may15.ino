/* LORA控制的远程水泵V3.0.0
*
*版本说明：开度增加为3个字节，回执信息增加设置的开度、设置的工作时间、已工作的时间
*分为01继电器和02继电器。
*所使用的指令参考文件夹内的各种指令以及通用的协议帧
*A015指令被取消。A014指令取消组ID。
*设计说明查看文件夹内的电磁阀设计说明       
*作者：刘家辉
*日期：2019.05.18
*
*/
#include "user_filter.h"
#include <arduino.h>
#include <EEPROM.h> 
#include "user_initialization.h"
#include "user_crc8.h"
#include "user_judgement.h"
#include "user_A011_E011.h"
#include "user_A025receipt.h"
#include "user_Character.h"		//
#include "user_test.h"			//
#include "user_HEXtoDEC.h"		//
#include "user_DECtoHEX.h"		//
#include "MODBUS_RTU_CRC16.h"	//modbusCRC16校验的函数
#include "user_DECtoHEX.h"		//

//相关函数的定义
int16_t Receive_information_lora(void);		//lora接收函数
int16_t Receive_information_485(void);		//485接收函数


//全局变量
static unsigned char Receive_Data[50];//用来存放接收到的数据
static int Receive_Length = 0;//接收数据的长度
static int CRC_Check_num  = 0x00;//CRC校验的数值
volatile long numm = 0;//中断的计数函数

static unsigned char Positive_rotation[8] = { 0x01,0x06,0x20,0x00,0x00,0x01,0x43,0xCA };//正转
static unsigned char Reversal[8] = { 0x01, 0x06, 0x20, 0x00, 0x00, 0x02, 0x03, 0xCB };//反转
static unsigned char frequency[8] = { 0x01, 0x06, 0x10, 0x00, 0x13, 0x88, 0x80, 0x5C };//设置变频器的频率
static unsigned char Shutdown[8] = { 0x01, 0x06, 0x20, 0x00, 0x00, 0x05, 0x42, 0x09 };//停机



//函 数 名：Receive_information_lora() 
//功能描述：负责接收LORA接收到的信息然后传给Judgement_function()
//函数说明：
//调用函数：Judgement_function()
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
int16_t Receive_information_lora(void)
{
    while(Serial3.available() > 0)//接收串口收到的数据
    {
       Receive_Data[Receive_Length++] = Serial3.read();
       delay(5);
    }
    //Serial.println("检测中...");
    if(Receive_Length > 0)
    {
        //Serial.write(Receive_Data,Receive_Length);//发16进制，自动转成ASCII码
        Judgement_Length = 0;//收到新消息清空判断数组的长度值
        Check_Length = 0;//收到新消息清空校验数组的长度值
        digitalWrite(LED4,HIGH);//LED4闪烁代表成功接收到信息
        delay(400);
        digitalWrite(LED4,LOW);
        Serial.print("Receive_Length = ");
        Serial.println(Receive_Length);

        //--------------------------------------------------------
        //将Receive_Data的值处理得到judgement_Data
        for (int i = 0; i < Receive_Length; i++)
        {
        	Judgement_Length = i;
        	Judgement_Data[Judgement_Length] = Receive_Data[i];

        	//====================================================
        	Serial.print("Judgement_Data ");
        	Serial.print(Judgement_Length,HEX);
        	Serial.print(" :");
        	Serial.println(Judgement_Data[Judgement_Length],HEX);
        	delay(5);
        	//====================================================
  			
        }
        Serial.print("Judgement_Length = ");
        Serial.println(Judgement_Length);
        //--------------------------------------------------------


        //--------------------------------------------------------
        //将Receive_Data的值处理得到Check_Data
        for (int i = 4; i < Receive_Length - 0x07; i++)
        {
        	Check_Data[Check_Length] = Receive_Data[i];
        	Serial.print("Check_Data ");
        	Serial.print(i);
        	Serial.print(" :");
        	Serial.println(Check_Data[i],HEX);
        	Check_Length++;
        	delay(5);
        }
        Serial.print("Check_Length = ");
        Serial.println(Check_Length);
        //--------------------------------------------------------

        if(Check_Length > 0)
        {
        	Serial.print("CRC8计算的值为：0x");
          	Serial.println(GetCrc8(Check_Data,Check_Length),HEX);
          	CRC_Check_num = GetCrc8(Check_Data,Check_Length);
          	/*Serial.print("CRC_Check_num = 0x");
          	Serial.println(CRC_Check_num,HEX);*/
        }
        Receive_Length = 0;
        Check_Length = 0;

        //--------------------------------------------------------
        //-------//
        // CRC_Check_num = 0xD6;//这行代码是为了不让我每次都计算CRC，实际使用请注释
        //-------//
        //--------------------------------------------------------
        
        Judgement_function(Judgement_Data,Judgement_Length,CRC_Check_num);//判断函数
    }
    return 0;
}

//函 数 名：Receive_information_485() 
//功能描述：负责接收485接收到的信息然后传给Judgement_function()
//函数说明：
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
int16_t Receive_information_485(void)
{
	while (Serial2.available() > 0)//接收串口收到的数据
	{
		Receive_Data[Receive_Length++] = Serial2.read();
		delay(5);
	}
	//Serial.println("检测中...");
	if (Receive_Length > 0)
	{
		//Serial.write(Receive_Data,Receive_Length);//发16进制，自动转成ASCII码
		Judgement_Length = 0;//收到新消息清空判断数组的长度值
		Check_Length = 0;//收到新消息清空校验数组的长度值
		digitalWrite(LED4, HIGH);//LED4闪烁代表成功接收到信息
		delay(400);
		digitalWrite(LED4, LOW);
		Serial.print("485Receive_Length = ");
		Serial.println(Receive_Length);
	}
	for (size_t i = 0; i < Receive_Length; i++)
	{
		Serial.print(String("485Receive_Data[ ")+String(i)+String(" ]= "));
		Serial.println(Receive_Data[i]);
	}
	return 0;
}

//函 数 名：COUNT() 
//功能描述：中断调用的计数函数
//函数说明：
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
void COUNT(void)
{
	numm++;
	Serial.println(String("numm = ")+String(numm));
	//Serial.println(numm);
}

//函 数 名：setup() 
//功能描述：起始代码
//函数说明：
//调用函数：Send_E011()、
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
void setup()
{
    Initialization();//初始化函数
  //  Working_parameter_setting = EEPROM.read(0);
  //  Receive_Working_parameter_setting = EEPROM.read(31);
  //  delay(500);

  //  Serial.println("启动中...");
  //  while(EEPROM.read(0) == 0x00 && EEPROM.read(31) == 0x00)
  //  {
  //      //代表未设置工作参数
  //      Serial.println("未设置工作参数,如需要设置工作参数，请长按按键1");
		//digitalWrite(LED3, HIGH);
		//delay(750);
		//digitalWrite(LED3, LOW);
		//delay(750);
  //      //等待按键1按下
  //      if(digitalRead(K1) == LOW)
  //      {
  //          delay(2000);
  //          if(digitalRead(K1) == LOW)
  //          {
  //              Serial.println("K1按下");
  //              Serial.println("本设备开始上报当前的设置参数");
  //              //进入E011函数上报请求当前参数
  //              Send_E011(Receive_IsBroadcast);//这里的Receive_IsBroadcast是否有值？
  //              Receive_Working_parameter_setting = 0x01;
  //              EEPROM.write(31,Receive_Working_parameter_setting);//请求过就将Receive的标志位置1
  //          }
  //      }
  //  }
  //  if(EEPROM.read(0) == 0x01 && EEPROM.read(31) == 0x01)
  //  {
  //      //已经设置好了工作参数
  //      Serial.println("工作参数已设置完成");
  //      delay(1500);
  //  }
  //  else if(EEPROM.read(0) == 0x00 && EEPROM.read(31) == 0x01)
  //  {
  //  	//未设置好工作参数，但是请求了参数，允许接收
  //  	Serial.println("等待服务器设置中...");
  //      delay(1500);
  //  }
  //  else
  //  {
  //  	//出现了未知错误
  //  	Serial.println("出现了未知错误");
  //  }
}

//函 数 名：loop() 
//功能描述：循环执行的代码
//函数说明：循环执行的代码
//调用函数：Receive_information()、forswitch()、Initialization()、setup()、Receive_information_485()
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
void loop()
{
	/*if (digitalRead(DI1) == HIGH)
	{
		if (digitalRead(DI1) == LOW)
		{
			Serial.println("............");
			delay(100);
		}
	}*/
    Receive_information_lora();	//LORA的接收函数
	Receive_information_485();	//485的接收函数
    forswitch();				//forswitch
    //这是重新设置所有的配置信息
    if(digitalRead(K1) == LOW)
    {
        delay(2000);
        if (digitalRead(K1) == LOW)
        {
            //-------------------------------------------
            //======测试时所用代码块，实际使用请注释=====
            //将所有的标志位都清为0
            EEPROM.write(0 ,0x00);//总标志位
            //EEPROM.write(28,0x00);//A011设置的标志位
            EEPROM.write(29,0x00);//A012设置的标志位
            EEPROM.write(30,0x00);//A013设置的标志位
            EEPROM.write(31,0x00);//Receive的标志位
			//EEPROM.write(32,0x00);//LORA设置的标志位
			EEPROM.write(33,0x00);//EEPROM设置的标志位
            //-------------------------------------------
			Serial.println("重新请求分号");

			for (size_t i = 0; i < 3; i++)//代表清号成功
			{
				digitalWrite(LED1, HIGH);
				digitalWrite(LED2, LOW);
				delay(300);
				digitalWrite(LED1, LOW);
				digitalWrite(LED2, HIGH);
				delay(300);
			}

            Initialization();
            setup();


            /*Serial.println("K1按下");
            Serial.println("本设备开始上报当前的设置参数");
            //进入E011函数上报请求当前参数
            Send_E011(Receive_IsBroadcast);//这里的Receive_IsBroadcast是否有值？
            Receive_Working_parameter_setting = 0x01;
            EEPROM.write(31,Receive_Working_parameter_setting);*/
        }
    }
    //这是强制启动继电器
    if(digitalRead(K2) == LOW)
    {
        delay(500);
        if (digitalRead(K2) == LOW)
        {
            digitalWrite(KCZJ1,LOW);
            digitalWrite(KCZJ2,LOW);
			/*Serial2.write(Positive_rotation, 8);
			delay(3000);
			Serial2.write(Shutdown, 8);*/
        }
        else
        {
            digitalWrite(KCZJ1,HIGH);
            digitalWrite(KCZJ2,HIGH);
        }
    }
}



/***
 *
 *
 *          .,:,,,                                        .::,,,::.
 *        .::::,,;;,                                  .,;;:,,....:i:
 *        :i,.::::,;i:.      ....,,:::::::::,....   .;i:,.  ......;i.
 *        :;..:::;::::i;,,:::;:,,,,,,,,,,..,.,,:::iri:. .,:irsr:,.;i.
 *        ;;..,::::;;;;ri,,,.                    ..,,:;s1s1ssrr;,.;r,
 *        :;. ,::;ii;:,     . ...................     .;iirri;;;,,;i,
 *        ,i. .;ri:.   ... ............................  .,,:;:,,,;i:
 *        :s,.;r:... ....................................... .::;::s;
 *        ,1r::. .............,,,.,,:,,........................,;iir;
 *        ,s;...........     ..::.,;:,,.          ...............,;1s
 *       :i,..,.              .,:,,::,.          .......... .......;1,
 *      ir,....:rrssr;:,       ,,.,::.     .r5S9989398G95hr;. ....,.:s,
 *     ;r,..,s9855513XHAG3i   .,,,,,,,.  ,S931,.,,.;s;s&BHHA8s.,..,..:r:
 *    :r;..rGGh,  :SAG;;G@BS:.,,,,,,,,,.r83:      hHH1sXMBHHHM3..,,,,.ir.
 *   ,si,.1GS,   sBMAAX&MBMB5,,,,,,:,,.:&8       3@HXHBMBHBBH#X,.,,,,,,rr
 *   ;1:,,SH:   .A@&&B#&8H#BS,,,,,,,,,.,5XS,     3@MHABM&59M#As..,,,,:,is,
 *  .rr,,,;9&1   hBHHBB&8AMGr,,,,,,,,,,,:h&&9s;   r9&BMHBHMB9:  . .,,,,;ri.
 *  :1:....:5&XSi;r8BMBHHA9r:,......,,,,:ii19GG88899XHHH&GSr.      ...,:rs.
 *  ;s.     .:sS8G8GG889hi.        ....,,:;:,.:irssrriii:,.        ...,,i1,
 *  ;1,         ..,....,,isssi;,        .,,.                      ....,.i1,
 *  ;h:               i9HHBMBBHAX9:         .                     ...,,,rs,
 *  ,1i..            :A#MBBBBMHB##s                             ....,,,;si.
 *  .r1,..        ,..;3BMBBBHBB#Bh.     ..                    ....,,,,,i1;
 *   :h;..       .,..;,1XBMMMMBXs,.,, .. :: ,.               ....,,,,,,ss.
 *    ih: ..    .;;;, ;;:s58A3i,..    ,. ,.:,,.             ...,,,,,:,s1,
 *    .s1,....   .,;sh,  ,iSAXs;.    ,.  ,,.i85            ...,,,,,,:i1;
 *     .rh: ...     rXG9XBBM#M#MHAX3hss13&&HHXr         .....,,,,,,,ih;
 *      .s5: .....    i598X&&A&AAAAAA&XG851r:       ........,,,,:,,sh;
 *      . ihr, ...  .         ..                    ........,,,,,;11:.
 *         ,s1i. ...  ..,,,..,,,.,,.,,.,..       ........,,.,,.;s5i.
 *          .:s1r,......................       ..............;shs,
 *          . .:shr:.  ....                 ..............,ishs.
 *              .,issr;,... ...........................,is1s;.
 *                 .,is1si;:,....................,:;ir1sr;,
 *                    ..:isssssrrii;::::::;;iirsssssr;:..
 *                         .,::iiirsssssssssrri;;:.
 *
 *
 *
 */
