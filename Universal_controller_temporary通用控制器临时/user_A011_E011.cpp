//user_A011_E011.cpp
/*
*版权
*
* 文件名称:user_A011_E011.cpp
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


#include"user_A011_E011.h"	//引用头文件


//函 数 名：Receive_A011() 
//功能描述：
//函数说明：A011帧的函数
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
void Receive_A011(unsigned char * Judgement_Data, int Judgement_Length)//A011函数
{

	//--------------------------------------------------------
	//该区域为测试传输进Receive_A011函数的数据是否正确的测试代码块
	//需要测试时请取消注释
	for (int i = 0; i < Judgement_Length + 1; i++)
    {
    	Serial.print("A011Judgement_Data ");
    	Serial.print(i,HEX);
    	Serial.print(" :");
    	Serial.println(Judgement_Data[i],HEX);
    	delay(1);
    }
    delay(500);
    Serial.print("Judgement_Length = ");
    Serial.println(Judgement_Length);
    //--------------------------------------------------------
    
    //是否广播指令
    Receive_IsBroadcast = Judgement_Data[6];
    
    
    if (Judgement_Data[8] == 0x00)
    {
        /*//--------------------------------------------------------
        //此区域无效
        //不请求只设置参数
        
        Serial.print("EEPROM_3:");
        Serial.println(EEPROM.read(3),HEX);
        //--------------------------------------------------------*/


        /*//--------------------------------------------------------
        //该区域为查看EEPROM空间的数据
        //使用时可以选择注释
        for (int i = 10; i < 19; ++i)
        {
            Serial.print("EEPROM_");
            Serial.print(i);
            Serial.print(":");
            Serial.println(EEPROM.read(i),HEX);
        }
        //--------------------------------------------------------*/
    }
    else if(Judgement_Data[8] == 0x55)
    {
        //重新请求
        Serial.println("服务器要求重新请求");
        Serial.println("本设备开始上报当前的设置参数");
        Send_E011(Receive_IsBroadcast);//这里的是否广播指令数值是否正确以及逻辑是否正确
    }
        
	/*//---------------------------------------------------
    A012_Working_parameter_setting = EEPROM.read(29);
    A013_Working_parameter_setting = EEPROM.read(30);
    Serial.print("A012_Working_parameter_setting = ");
    Serial.println(A012_Working_parameter_setting,HEX);
    Serial.print("A013_Working_parameter_setting = ");
    Serial.println(A013_Working_parameter_setting,HEX);
    //---------------------------------------------------*/

    
    /*//------------------------------
    //该区域的延时代码使用时请注释
    delay(2000);
    //------------------------------*/
    

    //进行状态的回执
    Send_E011(Receive_IsBroadcast);
    Serial.println("完成A011状态回执");
	digitalWrite(LED1, HIGH);
	delay(300);
	digitalWrite(LED1, LOW);
}


//函 数 名：Receive_A011() 
//功能描述：
//函数说明：E011帧的函数
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
unsigned char Send_E011(int Receive_IsBroadcast)//E011函数
{
    E011_IsBroadcast = Receive_IsBroadcast;//E011的是否广播指令

    E011_init();

    E011[0]  = E011_FrameHead;
    E011[1]  = E011_FrameId1;
    E011[2]  = E011_FrameId2;
    E011[3]  = E011_DataLen;
    E011[4]  = 0xC0;
    E011[5]  = 0x02;
    E011[6]  = E011_IsBroadcast;
    E011[7]  = E011_ZoneId;
    E011[8]  = E011_GroupIdArray1;
    E011[9]  = E011_GroupIdArray2;
    E011[10] = E011_GroupIdArray3;
    E011[11] = E011_GroupIdArray4;
    E011[12] = E011_GroupIdArray5;
    E011[13] = E011_DeviceSN1;
    E011[14] = E011_DeviceSN2;
    E011[15] = E011_DeviceSN3;
    E011[16] = E011_DeviceSN4;
    E011[17] = E011_DeviceSN5;
    E011[18] = E011_DeviceSN6;
    E011[19] = E011_DeviceSN7;
    E011[20] = E011_DeviceSN8;
    E011[21] = E011_DeviceSN9;
    E011[22] = E011_channel;
    E011[23] = E011_Interval1;
    E011[24] = E011_Interval2;
    E011[25] = E011_NewTime1;
    E011[26] = E011_NewTime2;
    E011[27] = E011_NewTime3;
    E011[28] = E011_NewTime4;
    E011[29] = E011_NewTime5;
    E011[30] = E011_NewTime6;
    E011[31] = E011_NewTime7;
    E011[32] = E011_Allocate1;
    E011[33] = E011_Allocate2;
    E011[34] = E011_Allocate3;
    E011[35] = E011_Allocate4;
    E011[36] = E011_Allocate5;
    E011[37] = E011_Allocate6;
    E011[38] = E011_Allocate7;
    E011[39] = E011_Allocate8;

    //--------------------------------------------------------
    //将Receive_Data的值处理得到Check_Data
    for (int i = 4; i <= E011_DataLen + 0x03; i++)
    {
        Check_Data[Check_Length] = E011[i];
        // Check_Data[Check_Length] = 0x55;
        Serial.print("Check_Data ");
        Serial.print(Check_Length);
        Serial.print(" :");
        Serial.println(Check_Data[Check_Length],HEX);
        Check_Length++;
        delay(1);
    }
    Serial.print("Check_Length = ");
    Serial.println(Check_Length);
    //--------------------------------------------------------

    if(Check_Length > 0)
    {
        Serial.print("CRC8计算的值为：0x");
        Serial.println(GetCrc8(Check_Data,Check_Length),HEX);
        E011_CRC8 = GetCrc8(Check_Data,Check_Length);
        Serial.print("E011_CRC8 = 0x");
        Serial.println(E011_CRC8,HEX);
        Check_Length = 0;
    }
    E011[40] = E011_CRC8;
    E011[41] = E011_FrameEnd1;
    E011[42] = E011_FrameEnd2;
    E011[43] = E011_FrameEnd3;
    E011[44] = E011_FrameEnd4;
    E011[45] = E011_FrameEnd5;
    E011[46] = E011_FrameEnd6;

    //--------------------------------------------------------
    //该区域为串口查看E011回执的信息
    for (int i = 0; i < 47; i++)
    {
        Serial.print(i);
        Serial.print("/");
        Serial.println(E011[i],HEX);
        delay(1);
    }
    //--------------------------------------------------------
    Serial3.write(E011,47);
    //delay(1000);
    Serial.println("已发送回执信息E011，等待服务器回应");
	digitalWrite(LED1, HIGH);
	delay(300);
	digitalWrite(LED1, LOW);
    return 0;
}

//函 数 名：E011_init() 
//功能描述：
//函数说明：E011初始化函数
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
unsigned char E011_init()
{
    E011_FrameHead = 0xFE;                  //E011的帧头

    E011_FrameId1 = 0xE0;                   //E011的帧ID1
    E011_FrameId2 = 0x11;                   //E011的帧ID2

    E011_DataLen = 0x24;                    //E011的数据长度

    E011_DeviceTypeID1 = 0xC0;				//E011的设备类型1
    E011_DeviceTypeID2 = 0x03;				//E011的设备类型2

    // E011_IsBroadcast = Receive_IsBroadcast;//E011的是否广播指令

    E011_ZoneId = EEPROM.read(3);           //E011的区域

    E011_GroupIdArray1 = 0x01;    			//E011的组数组1
    E011_GroupIdArray2 = EEPROM.read(5);    //E011的组数组2
    E011_GroupIdArray3 = EEPROM.read(6);    //E011的组数组3
    E011_GroupIdArray4 = EEPROM.read(7);    //E011的组数组4
    E011_GroupIdArray5 = EEPROM.read(8);    //E011的组数组5

    E011_DeviceSN1 = EEPROM.read(19);       //E011的SN1
    E011_DeviceSN2 = EEPROM.read(20);       //E011的SN2
    E011_DeviceSN3 = EEPROM.read(21);       //E011的SN3
    E011_DeviceSN4 = EEPROM.read(22);       //E011的SN4
    E011_DeviceSN5 = EEPROM.read(23);       //E011的SN5
    E011_DeviceSN6 = EEPROM.read(24);       //E011的SN6
    E011_DeviceSN7 = EEPROM.read(25);       //E011的SN7
    E011_DeviceSN8 = EEPROM.read(26);       //E011的SN8
    E011_DeviceSN9 = EEPROM.read(27);       //E011的SN9

    E011_channel = 0x02;          			//E011的设备路数

    E011_Interval1 = EEPROM.read(10);       //E011的设备采集时间1
    E011_Interval2 = EEPROM.read(11);       //E011的设备采集时间2

    E011_NewTime1 = EEPROM.read(12);        //E011的RTC时间1
    E011_NewTime2 = EEPROM.read(13);        //E011的RTC时间2
    E011_NewTime3 = EEPROM.read(14);        //E011的RTC时间3
    E011_NewTime4 = EEPROM.read(15);        //E011的RTC时间4
    E011_NewTime5 = EEPROM.read(16);        //E011的RTC时间5
    E011_NewTime6 = EEPROM.read(17);        //E011的RTC时间6
    E011_NewTime7 = EEPROM.read(18);        //E011的RTC时间7

    E011_Allocate1 = 0x00;                  //E011的预留字段1
    E011_Allocate2 = 0x00;                  //E011的预留字段2
    E011_Allocate3 = 0x00;                  //E011的预留字段3
    E011_Allocate4 = 0x00;                  //E011的预留字段4
    E011_Allocate5 = 0x00;                  //E011的预留字段5
    E011_Allocate6 = 0x00;                  //E011的预留字段6
    E011_Allocate7 = 0x00;                  //E011的预留字段7
    E011_Allocate8 = 0x00;                  //E011的预留字段8

    E011_CRC8 = 0xD6;                       //E011的CRC8校验码

    E011_FrameEnd1 = 0x0D;                  //E011的帧尾1
    E011_FrameEnd2 = 0x0A;                  //E011的帧尾2
    E011_FrameEnd3 = 0x0D;                  //E011的帧尾3
    E011_FrameEnd4 = 0x0A;                  //E011的帧尾4
    E011_FrameEnd5 = 0x0D;                  //E011的帧尾5
    E011_FrameEnd6 = 0x0A;                  //E011的帧尾6
}

