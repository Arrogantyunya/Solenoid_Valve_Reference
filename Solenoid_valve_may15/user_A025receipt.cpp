//user_A025receipt.cpp
/*
*版权
*
* 文件名称:user_A025receipt.cpp
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


#include"user_A025receipt.h"


//函 数 名：Receive_A012() 
//功能描述：设置区域以及组数组编号，并写入EEPROM的空间
//函数说明：A012帧的函数
//调用函数：Send_E015()
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
void Receive_A012(unsigned char * Judgement_Data, int Judgement_Length)//A012函数
{
	//--------------------------------------------------------
	//该区域为测试传输进Receive_A012函数的数据是否正确的测试代码块
	//需要测试时请取消注释
	for (int i = 0; i < Judgement_Length + 1; i++)
    {
    	Serial.print("A012Judgement_Data ");
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

    //======================================================//
    //得到查询哪一路设备的值
    if (Judgement_Data[13] == 0x01)
    {
    	Channel = 0x01;		//查询第1路的设备
    	Serial.println("查询第1路的设备");

    }
    else if (Judgement_Data[13] == 0x02)
    {
    	Channel = 0x02;		//查询第2路的设备
    	Serial.println("查询第2路的设备");
    }
    else if (Judgement_Data[13] == 0x55)
    {
    	Channel = 0x55;		//查询所有设备
    	Serial.println("查询所有设备");
    }
    else
    {
    	Channel = 0x00;		//查询的设备不存在
    	Serial.println("查询的设备不存在");
    }
    //======================================================//
    
  	EEPROM.write(3,Judgement_Data[7] );//区域
    //EEPROM.write(4,Judgement_Data[8] );//组编号数组，组ID数组第一位不改
    EEPROM.write(5,Judgement_Data[9] );
    EEPROM.write(6,Judgement_Data[10]);
    EEPROM.write(7,Judgement_Data[11]);
    EEPROM.write(8,Judgement_Data[12]);

    
    //--------------------------------------------------------
    //该区域为查看EEPROM的数据
    //使用时可以选择注释
    for (int i = 3; i < 9; ++i)
    {
        Serial.print("EEPROM_");
        Serial.print(i);
        Serial.print(":");
        Serial.println(EEPROM.read(i),HEX);
    }
    //--------------------------------------------------------

    A012_Working_parameter_setting = 0x01;
    EEPROM.write(29,A012_Working_parameter_setting);
    Serial.println("A012设置当前参数成功,已经将A012标志位写入EEPROM");

    if (A012_Working_parameter_setting = 0x01)
    {
        E015_status = AssignGroupIdArrayOk;
    }
    else
    {
        E015_status = AssignGroupIdArrayErr;
    }


    A012_Working_parameter_setting = EEPROM.read(29);
    A013_Working_parameter_setting = EEPROM.read(30);
    Serial.print("A012_Working_parameter_setting = ");
    Serial.println(A012_Working_parameter_setting,HEX);
    Serial.print("A013_Working_parameter_setting = ");
    Serial.println(A013_Working_parameter_setting,HEX);

    if (A012_Working_parameter_setting == 0x01 && A013_Working_parameter_setting == 0x01)
    {
        //当所有标志位都设置完成后，将总标志位设置写入0x01（设置完成）
        Working_parameter_setting = 0x01;
        EEPROM.write(0,Working_parameter_setting);
        Serial.println("标志位已经全部设置完成");
    }
    else
    {
        //标志位未全部设置完成，总标志位设置写入0x00（设置未完成）
        Working_parameter_setting = 0x00;
        EEPROM.write(0,Working_parameter_setting);
        Serial.println("标志位未全部设置完成，请继续进行设置或重新请求");
    }

    ////该区域的延时代码使用时请注释
    //delay(2000);

    //进行状态的回执
    Send_E015(Receive_IsBroadcast,E015_status,Channel);
    Serial.println("完成A012状态回执");
}


//函 数 名：Receive_A013() 
//功能描述：设置SN以及子设备的总路数，并写入EEPROM的空间
//函数说明：A013帧的函数
//调用函数：Send_E015()
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
void Receive_A013(unsigned char * Judgement_Data, int Judgement_Length)//A013函数
{
	//--------------------------------------------------------
	//该区域为测试传输进Receive_A013函数的数据是否正确的测试代码块
	//需要测试时请取消注释
	for (int i = 0; i < Judgement_Length + 1; i++)
    {
    	Serial.print("A013Judgement_Data ");
    	Serial.print(i,HEX);
    	Serial.print(" :");
    	Serial.println(Judgement_Data[i],HEX);
    	delay(1);
    }
    //delay(500);
    Serial.print("Judgement_Length = ");
    Serial.println(Judgement_Length);
    //--------------------------------------------------------

    //是否广播指令
    Receive_IsBroadcast = Judgement_Data[6];

    //======================================================//
    //得到查询哪一路设备的值
    if (Judgement_Data[8] == 0x01)
    {
    	Channel = 0x01;		//查询第1路的设备
    	Serial.println("查询第1路的设备");

    }
    else if (Judgement_Data[8] == 0x02)
    {
    	Channel = 0x02;		//查询第2路的设备
    	Serial.println("查询第2路的设备");
    }
    else if (Judgement_Data[8] == 0x55)
    {
    	Channel = 0x55;		//查询所有设备
    	Serial.println("查询所有设备");
    }
    else
    {
    	Channel = 0x00;		//查询的设备不存在
    	Serial.println("查询的设备不存在");
    }
    //======================================================//

    EEPROM.write( 3,Judgement_Data[7] );//所属区域
    EEPROM.write( 9,Judgement_Data[8] );//设备路数
    EEPROM.write(19,Judgement_Data[10]);//SN
    EEPROM.write(20,Judgement_Data[11]);
    EEPROM.write(21,Judgement_Data[12]);
    EEPROM.write(22,Judgement_Data[13]);
    EEPROM.write(23,Judgement_Data[14]);
    EEPROM.write(24,Judgement_Data[15]);
    EEPROM.write(25,Judgement_Data[16]);
    EEPROM.write(26,Judgement_Data[17]);
    EEPROM.write(27,Judgement_Data[18]);

    //将写入EEPRROM的数据打印，查看是否正确
    Serial.print("EEPROM_3:");
    Serial.println(EEPROM.read(3),HEX);
    Serial.print("EEPROM_9:");
    Serial.println(EEPROM.read(9),HEX);
    for (int i = 19; i < 28; ++i)
    {
        Serial.print("EEPROM_");
        Serial.print(i);
        Serial.print(":");
        Serial.println(EEPROM.read(i),HEX);
    }
    
    A013_Working_parameter_setting = 0x01;
    EEPROM.write(30,A013_Working_parameter_setting);
    Serial.println("A013设置当前参数成功,已经将A013标志位写入EEPROM");

    if (A012_Working_parameter_setting = 0x01)
    {
        E015_status = SetSnAndSlaverCountOk;
    }
    else
    {
        E015_status = SetSnAndSlaverCountErr;
    }


    A012_Working_parameter_setting = EEPROM.read(29);
    A013_Working_parameter_setting = EEPROM.read(30);
    Serial.print("A012_Working_parameter_setting = ");
    Serial.println(A012_Working_parameter_setting,HEX);
    Serial.print("A013_Working_parameter_setting = ");
    Serial.println(A013_Working_parameter_setting,HEX);

    if (A012_Working_parameter_setting == 0x01 && A013_Working_parameter_setting == 0x01)
    {
        //当所有标志位都设置完成后，将总标志位设置写入0x01（设置完成）
        Working_parameter_setting = 0x01;
        EEPROM.write(0,Working_parameter_setting);
        Serial.println("标志位已经全部设置完成");
    }
    else
    {
        //标志位未全部设置完成，总标志位设置写入0x00（设置未完成）
        Working_parameter_setting = 0x00;
        EEPROM.write(0,Working_parameter_setting);
        Serial.println("标志位未全部设置完成，请继续进行设置或重新请求");
    }

    //--------------------------------------------------------
    //该区域的延时代码使用时请注释
    /*delay(2000);*/
    //--------------------------------------------------------

    //进行状态的回执
    Send_E015(Receive_IsBroadcast,E015_status,Channel);
    Serial.println("完成A013状态回执");
}


//函 数 名：Receive_A014() 
//功能描述：
//函数说明：A014帧的函数
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
void Receive_A014(unsigned char * Judgement_Data, int Judgement_Length)//A014函数
{
	//--------------------------------------------------------
	//该区域为测试传输进Receive_A014函数的数据是否正确的测试代码块
	//需要测试时请取消注释
	for (int i = 0; i < Judgement_Length + 1; i++)
	{
		Serial.print("A014Judgement_Data ");
		Serial.print(i, HEX);
		Serial.print(" :");
		Serial.println(Judgement_Data[i], HEX);
		delay(1);
	}
	delay(500);
	Serial.print("Judgement_Length = ");
	Serial.println(Judgement_Length);
	//--------------------------------------------------------


	//是否广播指令
	Receive_IsBroadcast = Judgement_Data[6];

	//得到查询哪一路设备的值
	if (Judgement_Data[8] == 0x01)
	{
		Inquire_channel = 0x01;		//查询第1路的设备
		Serial.println("查询第1路的设备");

	}
	else if (Judgement_Data[8] == 0x02)
	{
		Inquire_channel = 0x02;		//查询第2路的设备
		Serial.println("查询第2路的设备");
	}
	else if (Judgement_Data[8] == 0x55)
	{
		Inquire_channel = 0x55;		//查询所有设备
		Serial.println("查询所有设备");
	}
	else
	{
		Inquire_channel = 0x00;		//查询的设备不存在
		Serial.println("查询的设备不存在");
	}



	//先判断是否出厂模式
	if (EEPROM.read(0) == 0x00)
	{
		E014_status = FactoryMode;//出厂模式
		KCZJ1_E014_status = E014_status;
		KCZJ2_E014_status = E014_status;
	}
	else
	{
		//     //再判断是否是低电压
		//     if (Get_voltage() <= 10)
		//     {
				 //E014_status = LOW_POWER;//低电压异常
				 //KCZJ1_E014_status = E014_status;
				 //KCZJ2_E014_status = E014_status;
		//     }
			 //else
			 //{
				 //然后判断设备1是否工作
		if (digitalRead(KCZJ1) == LOW)
		{
			KCZJ1_E014_status = RUN_OK;//设备运行中
		}
		else
		{
			KCZJ1_E014_status = CLOSE_OK;//设备关闭
		}


		//然后判断设备2是否工作
		if (digitalRead(KCZJ2) == LOW)
		{
			KCZJ2_E014_status = RUN_OK;//设备运行中
		}
		else
		{
			KCZJ2_E014_status = CLOSE_OK;//设备关闭
		}
		//}
	}

	// CurrentOpenRatio = 0x000000;
	// TotalWorkSec = 0x000000;

	//进行状态的回执
	Send_E014();
	Serial.println("完成A014状态回执");
	digitalWrite(LED1, HIGH);
	delay(300);
	digitalWrite(LED1, LOW);
}



//函 数 名：Receive_A025() 
//功能描述：
//函数说明：A025帧的函数
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
void Receive_A025(unsigned char * Judgement_Data, int Judgement_Length)//A025函数
{

	//这段代码是为了读取EEPROM的值
	/*if(A025_flag == 0)
	{
		Serial.println("A025_flag = 0");
		A025_flag = 1;
		Serial.println("A025_flag = 1");
		A025_ZoneId = EEPROM.read(3);
		A025_GroupIdArray1 = 0x01;
		A025_GroupIdArray2 = EEPROM.read(5);
		A025_GroupIdArray3 = EEPROM.read(6);
		A025_GroupIdArray4 = EEPROM.read(7);
		A025_GroupIdArray5 = EEPROM.read(8);
		A025_channel = EEPROM.read(9);
	}*/

	//--------------------------------------------------------
	//该区域为测试传输进Receive_A025函数的数据是否正确的测试代码块
	//需要测试时请取消注释
	for (int i = 0; i < Judgement_Length + 1; i++)
    {
    	Serial.print("A025Judgement_Data ");
    	Serial.print(i,HEX);
    	Serial.print(" :");
    	Serial.println(Judgement_Data[i],HEX);
    	delay(1);
    }
    Serial.print("Judgement_Length = ");
    Serial.println(Judgement_Length);
    //--------------------------------------------------------
   	
   	Receive_IsBroadcast = Judgement_Data[6];
   	
   	/*//--------------------------------------------------------
   	//接受到信息时回执一次
   	Send_E015(Receive_IsBroadcast,E015_status);
    Serial.println("完成A015接收状态回执");
    //--------------------------------------------------------*/

   	//判断所属区域
	if (Judgement_Data[7] == EEPROM.read(3))
	{
		//判断组ID
		if (Judgement_Data[8] == 0x01 || Judgement_Data[8] == 0x55
		 || Judgement_Data[8] == EEPROM.read(6) || Judgement_Data[8] == EEPROM.read(7) 
		 || Judgement_Data[8] == EEPROM.read(8)	|| Judgement_Data[8] == EEPROM.read(9))//这里是将发送的组ID与设置的组ID数组进行比对
		{
			//判断设备路数
			if (Judgement_Data[9] == 0x01 && Judgement_Data[9] <= A025_channel)//
			{
				//判断开度
				if(Judgement_Data[10] == 0x00 && Judgement_Data[11] == 0x00 && Judgement_Data[12] == 0x64)
				{
					//这里代表01区01组01的设备路数开
					rd1   = KCZJ1_ON;
					rd[0] = rd1;

					//决定在这里赋时间值，先赋持续时间的值到数组
                    Duration_time = Judgement_Data[13]*0x1000+Judgement_Data[14]*0x100+Judgement_Data[15];
                  	duration[0]   = Duration_time;
                  	Serial.print("Duration_time=");
                  	Serial.println(Duration_time);
                  	Serial.print("duration[i]=");
                  	Serial.println(duration[i]);

                  	//然后赋旧时间的值到数组
                  	oldtime = millis();
                  	ot[0]   = oldtime;
                  	Serial.print("oldtime=");
                  	Serial.println(oldtime);
                  	Serial.print("ot[i]=");
                  	Serial.println(ot[i]);

                  	Inquire_channel = 0x01;//得到查询路数

                  	//============该段为了回复通用状态=================
                  	//判断参数是否设置成功
					if(rd[0] == KCZJ1_ON)
					{
						E015_status = SetParamsOk;//设置参数成功
						KCZJ1_E015_status = E015_status;
					}
					else
					{
						E015_status = SetParamsErr;//设置参数失败
						KCZJ1_E015_status = E015_status;
					}

					Channel = 0x01;

					//接受到信息时回执一次
				   	Send_E015(Receive_IsBroadcast,E015_status,Channel);
				    Serial.println("完成A025通用状态回执");
				    //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


				    //==========该段为了回执实时状态============================
				    //在这里直接调用一次
					forswitch();
				    

				    //设置的开度
				    KCZJ1_E014_CurrentOpenRatio1 = Judgement_Data[10];
				    KCZJ1_E014_CurrentOpenRatio2 = Judgement_Data[11];
				    KCZJ1_E014_CurrentOpenRatio3 = Judgement_Data[12];
					//设置的工作时长
					KCZJ1_E014_TotalWorkSec1 = Judgement_Data[13];
					KCZJ1_E014_TotalWorkSec2 = Judgement_Data[14];
					KCZJ1_E014_TotalWorkSec3 = Judgement_Data[15];


				    if(digitalRead(KCZJ1) == LOW)
				    {
				    	KCZJ1_E014_status = RUN_OK;//设备运行中
				    }
				    else if(digitalRead(KCZJ1) == HIGH)
				    {
				    	KCZJ1_E014_status = OPEN_EXCEPTION;//打开设备异常
				    }

				    //进行开启的状态的回执，回复实时状态（E014）
				    Send_E014();
				    Serial.println("完成A025实时状态回执");
				    //=========================================================	
				}
				else if (Judgement_Data[10] == 0x00 && Judgement_Data[11] == 0x00 && Judgement_Data[12] == 0x00)
				{
					//代表关1区1组1继电器关
					rd1   = Stateless;
					rd[0] = rd1;
					digitalWrite(KCZJ1,HIGH);
					Serial.println("设备路数1：KCZJ1关");

					Inquire_channel = 0x01;//得到查询路数

					//============该段为了回复通用状态=================
                  	//判断参数是否设置成功
					if(rd[0] == Stateless)
					{
						E015_status = SetParamsOk;//设置参数成功
					}
					else
					{
						E015_status = SetParamsErr;//设置参数失败
					}

					Channel = 0x01;

					//接受到信息时回执一次
				   	Send_E015(Receive_IsBroadcast,E015_status,Channel);
				    Serial.println("完成A025通用状态回执");
				    //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
				    

				    //==========该段为了回执实时状态============================
				    //在这里直接调用一次
					forswitch();
				    

				    //设置的开度
				    KCZJ1_E014_CurrentOpenRatio1 = Judgement_Data[10];
				    KCZJ1_E014_CurrentOpenRatio2 = Judgement_Data[11];
				    KCZJ1_E014_CurrentOpenRatio3 = Judgement_Data[12];
					//设置的工作时长
					KCZJ1_E014_TotalWorkSec1 = Judgement_Data[13];
					KCZJ1_E014_TotalWorkSec2 = Judgement_Data[14];
					KCZJ1_E014_TotalWorkSec3 = Judgement_Data[15];


				    if(digitalRead(KCZJ1) == HIGH)
				    {
				    	KCZJ1_E014_status = CLOSE_OK;//设备关闭
				    }
				    else if(digitalRead(KCZJ1) == LOW)
				    {
				    	KCZJ1_E014_status = CLOSE_EXCEPTION;//关闭设备异常
				    }

					KCZJ1_E014_TotalWorkSec1 = 0x00;	//KCZJ1_E014设置的工作时长1完成清零
					KCZJ1_E014_TotalWorkSec2 = 0x00;	//KCZJ1_E014设置的工作时长2完成清零
					KCZJ1_E014_TotalWorkSec3 = 0x00;	//KCZJ1_E014设置的工作时长3完成清零
					KCZJ1_E014_CurrentWorkSec1 = 0x00;	//KCZJ1_E014_CurrentWorkSec1已工作时间完成清零
					KCZJ1_E014_CurrentWorkSec2 = 0x00;	//KCZJ1_E014_CurrentWorkSec1已工作时间完成清零
					KCZJ1_E014_CurrentWorkSec3 = 0x00;	//KCZJ1_E014_CurrentWorkSec1已工作时间完成清零
					KCZJ1_CurrentWorkSec = 0;			//KCZJ1_CurrentWorkSec已工作时间完成清零

				    //进行关闭的状态的回执，回复实时状态（E014）
				    Send_E014();
				    Serial.println("完成A025实时状态回执");
				    //=========================================================
				}
				else
				{
					//不存在的开度类型
                    Serial.println("Nonexistent_opening_type不存在的开度类型");
				}
			}
			//第二个的设备路数
			else if (Judgement_Data[9] == 0x02 && Judgement_Data[9] <= A025_channel)
			{
				//判断开度
				if(Judgement_Data[10] == 0x00 && Judgement_Data[11] == 0x00 && Judgement_Data[12] == 0x64)
				{
					//第二个的设备路数
					rd1   = KCZJ2_ON;
	              	rd[1] = rd1;

	              	//决定在这里赋时间值，先赋持续时间的值到数组
	              	Duration_time = Judgement_Data[13]*0x1000+Judgement_Data[14]*0x100+Judgement_Data[15];
	              	duration[1]   = Duration_time;

	              	//然后赋旧时间的值到数组
	              	oldtime = millis();
	              	ot[1]   = oldtime;

	              	Inquire_channel = 0x02;//得到查询路数

	              	//==========该段为了回执通用状态============================
	              	//判断参数是否设置成功
					if(rd[1] == KCZJ2_ON)
					{
						E015_status = SetParamsOk;//设置参数成功
					}
					else
					{
						E015_status = SetParamsErr;//设置参数失败
					}

					Channel = 0x02;

					//接受到信息时回执一次
				   	Send_E015(Receive_IsBroadcast,E015_status,Channel);
				    Serial.println("完成A025通用状态回执");
				    //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


				    //==========该段为了回执实时状态============================
				    //在这里直接调用一次
					forswitch();

					//设置的开度
				    KCZJ2_E014_CurrentOpenRatio1 = Judgement_Data[10];
				    KCZJ2_E014_CurrentOpenRatio2 = Judgement_Data[11];
				    KCZJ2_E014_CurrentOpenRatio3 = Judgement_Data[12];
					//设置的工作时长
					KCZJ2_E014_TotalWorkSec1 = Judgement_Data[13];
					KCZJ2_E014_TotalWorkSec2 = Judgement_Data[14];
					KCZJ2_E014_TotalWorkSec3 = Judgement_Data[15];
				    
				    if(digitalRead(KCZJ2) == LOW)
				    {
				    	KCZJ2_E014_status = RUN_OK;//设备运行中
				    }
				    else if(digitalRead(KCZJ2) == HIGH)
				    {
				    	KCZJ2_E014_status = OPEN_EXCEPTION;//打开设备异常
				    }

				    //进行完成的状态的回执，回复实时状态（E014）
				    Send_E014();
				    Serial.println("完成A025实时状态回执");
				    //=========================================================
	            }
	            else if (Judgement_Data[10] == 0x00 && Judgement_Data[11] == 0x00 && Judgement_Data[12] == 0x00)
				{
					//代表关1区1组2继电器关
					rd1   = Stateless;
	              	rd[1] = rd1;
	              	digitalWrite(KCZJ2,HIGH);
	              	Serial.println("设备路数2：KCZJ2关");


	              	Inquire_channel = 0x02;//得到查询路数

	              	//============该段为了回复通用状态=================
                  	//判断参数是否设置成功
					if(rd[1] == Stateless)
					{
						E015_status = SetParamsOk;//设置参数成功
					}
					else
					{
						E015_status = SetParamsErr;//设置参数失败
					}

					Channel = 0x02;

					//接受到信息时回执一次
				   	Send_E015(Receive_IsBroadcast,E015_status,Channel);
				    Serial.println("完成A025通用状态回执");
				    //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
				    

				    //==========该段为了回执实时状态============================
				    //在这里直接调用一次
					forswitch();
				    

				    //设置的开度
				    KCZJ2_E014_CurrentOpenRatio1 = Judgement_Data[10];
				    KCZJ2_E014_CurrentOpenRatio2 = Judgement_Data[11];
				    KCZJ2_E014_CurrentOpenRatio3 = Judgement_Data[12];
					//设置的工作时长
					KCZJ2_E014_TotalWorkSec1 = Judgement_Data[13];
					KCZJ2_E014_TotalWorkSec2 = Judgement_Data[14];
					KCZJ2_E014_TotalWorkSec3 = Judgement_Data[15];


				    if(digitalRead(KCZJ2) == HIGH)
				    {
				    	KCZJ2_E014_status = CLOSE_OK;//设备关闭
				    }
				    else if(digitalRead(KCZJ2) == LOW)
				    {
				    	KCZJ2_E014_status = CLOSE_EXCEPTION;//关闭设备异常
				    }

					KCZJ2_E014_TotalWorkSec1 = 0x00;	//KCZJ2_E014设置的工作时长1完成清零
					KCZJ2_E014_TotalWorkSec2 = 0x00;	//KCZJ2_E014设置的工作时长2完成清零
					KCZJ2_E014_TotalWorkSec3 = 0x00;	//KCZJ2_E014设置的工作时长3完成清零
					KCZJ2_E014_CurrentWorkSec1 = 0x00;	//KCZJ2_E014_CurrentWorkSec1已工作时间完成清零
					KCZJ2_E014_CurrentWorkSec2 = 0x00;	//KCZJ2_E014_CurrentWorkSec1已工作时间完成清零
					KCZJ2_E014_CurrentWorkSec3 = 0x00;	//KCZJ2_E014_CurrentWorkSec1已工作时间完成清零
					KCZJ2_CurrentWorkSec = 0;			//KCZJ2_CurrentWorkSec已工作时间完成清零

				    //进行关闭的状态的回执，回复实时状态（E014）
				    Send_E014();
				    Serial.println("完成A025实时状态回执");
				    //=========================================================
				}
				else
				{
					//不存在的开度类型
                    Serial.println("Nonexistent_opening_type不存在的开度类型");
                    delay(500);
                    Serial.println("该条指令被无视");
				}
			}
			//所有的设备路数
			else if (Judgement_Data[9] == 0x55)
			{
				//判断开度
				if(Judgement_Data[10] == 0x00 && Judgement_Data[11] == 0x00 && Judgement_Data[12] == 0x64)
				{
					//所有的设备路数

	              	//决定在这里赋时间值，先赋持续时间的值到数组
	              	Duration_time = Judgement_Data[13]*0x1000+Judgement_Data[14]*0x100+Judgement_Data[15];
	              	duration[0]   = Duration_time;
	              	duration[1]   = Duration_time;

	              	//然后赋旧时间的值到数组
	              	oldtime = millis();
	              	ot[0]   = oldtime;
	              	ot[1]   = oldtime;

	              	//一旦判断了为EQUIPMENT_ALL_ON设备路数全开，将数组的其他位的状态值都改为开            	
	              	rd[0] = KCZJ1_ON;
	              	rd[1] = KCZJ2_ON;


	              	Inquire_channel = 0x55;//得到查询路数
	              	
	              	//==========该段为了回执通用状态============================
	              	//判断参数是否设置成功
					if(rd[0] == KCZJ1_ON && rd[1] == KCZJ2_ON)
					{
						E015_status = SetParamsOk;//设置参数成功
					}
					else
					{
						E015_status = SetParamsErr;//设置参数失败
					}

					Channel = 0x55;

					//接受到信息时回执一次
				   	Send_E015(Receive_IsBroadcast,E015_status,Channel);
				    Serial.println("完成A025通用状态回执");
				    //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


				    //==========该段为了回执实时状态============================
				    //在这里直接调用一次
					forswitch();
				    //设置的开度
				    KCZJ1_E014_CurrentOpenRatio1 = Judgement_Data[10];
				    KCZJ1_E014_CurrentOpenRatio2 = Judgement_Data[11];
				    KCZJ1_E014_CurrentOpenRatio3 = Judgement_Data[12];
					//设置的工作时长
					KCZJ1_E014_TotalWorkSec1 = Judgement_Data[13];
					KCZJ1_E014_TotalWorkSec2 = Judgement_Data[14];
					KCZJ1_E014_TotalWorkSec3 = Judgement_Data[15];
					//设置的开度
				    KCZJ2_E014_CurrentOpenRatio1 = Judgement_Data[10];
				    KCZJ2_E014_CurrentOpenRatio2 = Judgement_Data[11];
				    KCZJ2_E014_CurrentOpenRatio3 = Judgement_Data[12];
					//设置的工作时长
					KCZJ2_E014_TotalWorkSec1 = Judgement_Data[13];
					KCZJ2_E014_TotalWorkSec2 = Judgement_Data[14];
					KCZJ2_E014_TotalWorkSec3 = Judgement_Data[15];

				    if(digitalRead(KCZJ1) == LOW)
				    {
				    	KCZJ1_E014_status = RUN_OK;//设备1运行中
				    }
					else if (digitalRead(KCZJ1) == HIGH)
					{
						KCZJ1_E014_status = OPEN_EXCEPTION;//打开设备1异常
					}
					if (digitalRead(KCZJ2) == LOW)
					{
						KCZJ2_E014_status = RUN_OK;//设备2运行中
					}
					else if (digitalRead(KCZJ2) == HIGH)
					{
						KCZJ2_E014_status = OPEN_EXCEPTION;//打开设备2异常
					}

				    //进行完成的状态的回执，回复实时状态（E014）
				    Send_E014();
				    Serial.println("完成A025实时状态回执");
				    //=========================================================
	            }
	            else if (Judgement_Data[10] == 0x00 && Judgement_Data[11] == 0x00 && Judgement_Data[12] == 0x00)
				{
					//一旦判断了为EQUIPMENT_ALL_OFF设备路数全关，将数组的其他位的状态值都改为为无状态
					rd[0] = Stateless;
	              	rd[1] = Stateless;

	              	digitalWrite(KCZJ1,HIGH);
					digitalWrite(KCZJ2,HIGH);

					Inquire_channel = 0x55;//得到查询路数

					//==========该段为了回执通用状态============================
	              	//判断参数是否设置成功
					if(rd[0] == Stateless && rd[1] == Stateless)
					{
						E015_status = SetParamsOk;//设置参数成功
					}
					else
					{
						E015_status = SetParamsErr;//设置参数失败
					}

					Channel = 0x55;

					//接受到信息时回执一次
				   	Send_E015(Receive_IsBroadcast,E015_status,Channel);
				    Serial.println("完成A025通用状态回执");
				    //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


				    //==========该段为了回执实时状态============================
				    //在这里直接调用一次
					forswitch();
				    
				    if(digitalRead(KCZJ1) == HIGH)
				    {
						KCZJ1_E014_status = CLOSE_OK;//设备1关闭
				    }
					else if (digitalRead(KCZJ1) == LOW)
					{
						KCZJ1_E014_status = CLOSE_EXCEPTION;//关闭设备1异常
					}
					if (digitalRead(KCZJ2) == HIGH)
					{
						KCZJ2_E014_status = CLOSE_OK;//设备2关闭
					}
					else if (digitalRead(KCZJ2) == LOW)
					{
						KCZJ2_E014_status = CLOSE_EXCEPTION;//关闭设备2异常
					}

					KCZJ1_E014_TotalWorkSec1 = 0x00;	//KCZJ1_E014设置的工作时长1完成清零
					KCZJ1_E014_TotalWorkSec2 = 0x00;	//KCZJ1_E014设置的工作时长2完成清零
					KCZJ1_E014_TotalWorkSec3 = 0x00;	//KCZJ1_E014设置的工作时长3完成清零
					KCZJ1_E014_CurrentWorkSec1 = 0x00;	//KCZJ1_E014_CurrentWorkSec1已工作时间完成清零
					KCZJ1_E014_CurrentWorkSec2 = 0x00;	//KCZJ1_E014_CurrentWorkSec1已工作时间完成清零
					KCZJ1_E014_CurrentWorkSec3 = 0x00;	//KCZJ1_E014_CurrentWorkSec1已工作时间完成清零
					KCZJ1_CurrentWorkSec = 0;			//KCZJ1_CurrentWorkSec已工作时间完成清零

					KCZJ2_E014_TotalWorkSec1 = 0x00;	//KCZJ2_E014设置的工作时长1完成清零
					KCZJ2_E014_TotalWorkSec2 = 0x00;	//KCZJ2_E014设置的工作时长2完成清零
					KCZJ2_E014_TotalWorkSec3 = 0x00;	//KCZJ2_E014设置的工作时长3完成清零
					KCZJ2_E014_CurrentWorkSec1 = 0x00;	//KCZJ2_E014_CurrentWorkSec1已工作时间完成清零
					KCZJ2_E014_CurrentWorkSec2 = 0x00;	//KCZJ2_E014_CurrentWorkSec1已工作时间完成清零
					KCZJ2_E014_CurrentWorkSec3 = 0x00;	//KCZJ2_E014_CurrentWorkSec1已工作时间完成清零
					KCZJ2_CurrentWorkSec = 0;			//KCZJ2_CurrentWorkSec已工作时间完成清零

				    //进行完成的状态的回执，回复实时状态（E014）
				    Send_E014();
				    Serial.println("完成A025实时状态回执");
				    //=========================================================
				}
				else
				{
					//不存在的开度类型
                    Serial.println("Nonexistent_opening_type不存在的开度类型");
                    delay(500);
                    Serial.println("该条指令被无视");
				}
			}
			//不存在的设备路数
			else
			{
				//不存在的设备路数
				Serial.println("不存在的设备路数");
			}
		}
		else
		{
			//不是自己的组
			Serial.println("不属于该组");
		}
	}
	else
	{
		//不是自己的区域
		Serial.println("不属于该区域");
	}
}


//函 数 名：Receive_E015() 
//功能描述：
//函数说明：E015帧的函数
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
unsigned char Send_E015(int Receive_IsBroadcast,int E015_status,int Channel)//E015函数
{
    E015_IsBroadcast = Receive_IsBroadcast;
    E015_channel = Channel;
    E015_init();
    
    E015[0]  = E015_FrameHead;
    E015[1]  = E015_FrameId1;
    E015[2]  = E015_FrameId2;
    E015[3]  = E015_DataLen;
    E015[4]  = E015_DeviceTypeID1;
    E015[5]  = E015_DeviceTypeID2;
    E015[6]  = E015_IsBroadcast;
    E015[7]  = E015_ZoneId;
    E015[8]  = E015_channel;
    E015[9]  = E015_status;
    E015[10] = E015_Allocate1;
    E015[11] = E015_Allocate2;
    E015[12] = E015_Allocate3;
    E015[13] = E015_Allocate4;
    E015[14] = E015_Allocate5;
    E015[15] = E015_Allocate6;
    E015[16] = E015_Allocate7;
    E015[17] = E015_Allocate8;

    //--------------------------------------------------------
    //将Receive_Data的值处理得到Check_Data
    for (int i = 4; i <= E015_DataLen + 0x03; i++)
    {
        Check_Data[Check_Length] = E015[i];
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
        E015_CRC8 = GetCrc8(Check_Data,Check_Length);
        Serial.print("E015_CRC8 = 0x");
        Serial.println(E015_CRC8,HEX);
        Check_Length = 0;
    }
    E015[18] = E015_CRC8;
    E015[19] = E015_FrameEnd1;
    E015[20] = E015_FrameEnd2;
    E015[21] = E015_FrameEnd3;
    E015[22] = E015_FrameEnd4;
    E015[23] = E015_FrameEnd5;
    E015[24] = E015_FrameEnd6;

    //--------------------------------------------------------
    //该区域为串口查看E015回执的数据
    //使用时可以注释
    for (int i = 0; i < 25; i++)
    {
        Serial.print(i);
        Serial.print("/");
        Serial.println(E015[i],HEX);
        delay(1);
    }
    //--------------------------------------------------------
    Serial3.write(E015,25);
    //delay(1000);
    Serial.println("已经发送E015，等待服务器回应");
    return 0;
}

unsigned char E015_init()
{
    E015_FrameHead = 0xFE;                  //E015的帧头

    E015_FrameId1 = 0xE0;                   //E015的帧ID1
    E015_FrameId2 = 0x15;                   //E015的帧ID2

    E015_DataLen = 0x0E;                    //E015的数据长度

	E015_DeviceTypeID1 = 0xC0;				//E015的设备类型1
	E015_DeviceTypeID2 = 0x03;				//E015的设备类型2

    //E015_IsBroadcast = 0x00;                //E015的是否广播指令

    E015_ZoneId = EEPROM.read(3);           //E015的区域

    // E015_channel = EEPROM.read(9);          //E015的设备路数

    //E015_status = FactoryMode_E015;         //E015的设备状态

    E015_Allocate1 = 0x00;                  //E015的预留字段1
    E015_Allocate2 = 0x00;                  //E015的预留字段2
    E015_Allocate3 = 0x00;                  //E015的预留字段3
    E015_Allocate4 = 0x00;                  //E015的预留字段4
    E015_Allocate5 = 0x00;                  //E015的预留字段5
    E015_Allocate6 = 0x00;                  //E015的预留字段6
    E015_Allocate7 = 0x00;                  //E015的预留字段7
    E015_Allocate8 = 0x00;                  //E015的预留字段8

    E015_CRC8 = 0xD6;                       //E015的CRC8校验码

    E015_FrameEnd1 = 0x0D;                  //E015的帧尾1
    E015_FrameEnd2 = 0x0A;                  //E015的帧尾2
    E015_FrameEnd3 = 0x0D;                  //E015的帧尾3
    E015_FrameEnd4 = 0x0A;                  //E015的帧尾4
    E015_FrameEnd5 = 0x0D;                  //E015的帧尾5
    E015_FrameEnd6 = 0x0A;                  //E015的帧尾6
}


//函 数 名：Receive_E014() 
//功能描述：
//函数说明：E014帧的函数
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
unsigned char Send_E014()//E014函数
{
    E014_IsBroadcast = Receive_IsBroadcast;//E014的是否广播指令

    E014_init();//初始化函数

    E014[0]  = E014_FrameHead;					//E014的帧头
    E014[1]  = E014_FrameId1;					//E014的帧ID
    E014[2]  = E014_FrameId2;
    E014[3]  = E014_DataLen;					//E014的数据长度
    E014[4]  = E014_DeviceTypeID1;				//E014的设备类型
    E014[5]  = E014_DeviceTypeID2;
    E014[6]  = E014_IsBroadcast;				//E014的是否广播指令
    E014[7]  = E014_ZoneId;						//E014的区域
    // E014[8]  = E014_channel;					//E014的路数
    // E014[9]  = KCZJ1_E014_status;				//继电器1的E014状态
    E014[10] = E014_Vol1;						//E014的电压
    E014[11] = E014_Vol2;
    E014[12] = E014_Rssi;						//E014的信噪比
    E014[13] = E014_Csq;						//E014的信号强度
    //E014[14] = KCZJ1_E014_CurrentOpenRatio1;	//继电器1的E014开度
    //E014[15] = KCZJ1_E014_CurrentOpenRatio2;
    //E014[16] = KCZJ1_E014_CurrentOpenRatio3;
    //E014[17] = KCZJ1_E014_TotalWorkSec1;		//继电器1的工作时长
    //E014[18] = KCZJ1_E014_TotalWorkSec2;     E014[19] = KCZJ1_E014_TotalWorkSec3;
    //E014[20] = KCZJ1_E014_CurrentWorkSec1;		//继电器1的已工作时长
    //E014[21] = KCZJ1_E014_CurrentWorkSec2;
    //E014[22] = KCZJ1_E014_CurrentWorkSec3;
    //E014[23] = E014_Allocate1;					//E014的预留字段
    //E014[24] = E014_Allocate2;
    //E014[25] = E014_Allocate3;
    //E014[26] = E014_Allocate4;
    E014[27] = E014_Allocate5;
    E014[28] = E014_Allocate6;
    E014[29] = E014_Allocate7;

    if (Inquire_channel == 0x01)
    {
    	E014[8]  = 0x01;							//E014的路数
    	E014[9]  = KCZJ1_E014_status;				//继电器1的E014状态
    	E014[14] = KCZJ1_E014_CurrentOpenRatio1;	//继电器1的E014开度
	    E014[15] = KCZJ1_E014_CurrentOpenRatio2;
	    E014[16] = KCZJ1_E014_CurrentOpenRatio3;
	    E014[17] = KCZJ1_E014_TotalWorkSec1;		//继电器1的工作时长
	    E014[18] = KCZJ1_E014_TotalWorkSec2;
	    E014[19] = KCZJ1_E014_TotalWorkSec3;
	    E014[20] = KCZJ1_E014_CurrentWorkSec1;		//继电器1的已工作时长
	    E014[21] = KCZJ1_E014_CurrentWorkSec2;
	    E014[22] = KCZJ1_E014_CurrentWorkSec3;
		E014[23] = KCZJ1_WaterPressure1;			//继电器1的水压
		E014[24] = KCZJ1_WaterPressure2;
		E014[25] = KCZJ1_WaterPressure3;
		E014[26] = KCZJ1_WaterPressure4;
	    E014_easy();//剩余部分
	    Serial.println("完成设备路数1的回执");
    }
    else if (Inquire_channel == 0x02)
    {
    	E014[8]  = 0x02;							//E014的路数
    	E014[9]  = KCZJ2_E014_status;				//继电器2的E014状态
    	E014[14] = KCZJ2_E014_CurrentOpenRatio1;	//继电器2的E014开度
	    E014[15] = KCZJ2_E014_CurrentOpenRatio2;
	    E014[16] = KCZJ2_E014_CurrentOpenRatio3;
	    E014[17] = KCZJ2_E014_TotalWorkSec1;		//继电器2的工作时长
	    E014[18] = KCZJ2_E014_TotalWorkSec2;
	    E014[19] = KCZJ2_E014_TotalWorkSec3;
	    E014[20] = KCZJ2_E014_CurrentWorkSec1;		//继电器2的已工作时长
	    E014[21] = KCZJ2_E014_CurrentWorkSec2;
	    E014[22] = KCZJ2_E014_CurrentWorkSec3;
		E014[23] = KCZJ2_WaterPressure1;			//继电器2的水压
		E014[24] = KCZJ2_WaterPressure2;
		E014[25] = KCZJ2_WaterPressure3;
		E014[26] = KCZJ2_WaterPressure4;
	    E014_easy();//剩余部分
	    Serial.println("完成设备路数2的回执");
    }
    else if(Inquire_channel == 0x55)
    {
    	E014[8]  = 0x01;							//E014的路数
    	E014[9]  = KCZJ1_E014_status;				//继电器1的E014状态
    	E014[14] = KCZJ1_E014_CurrentOpenRatio1;	//继电器1的E014开度
	    E014[15] = KCZJ1_E014_CurrentOpenRatio2;
	    E014[16] = KCZJ1_E014_CurrentOpenRatio3;
	    E014[17] = KCZJ1_E014_TotalWorkSec1;		//继电器1的工作时长
	    E014[18] = KCZJ1_E014_TotalWorkSec2;
	    E014[19] = KCZJ1_E014_TotalWorkSec3;
	    E014[20] = KCZJ1_E014_CurrentWorkSec1;		//继电器1的已工作时长
	    E014[21] = KCZJ1_E014_CurrentWorkSec2;
	    E014[22] = KCZJ1_E014_CurrentWorkSec3;
		E014[23] = KCZJ1_WaterPressure1;			//继电器1的水压
		E014[24] = KCZJ1_WaterPressure2;
		E014[25] = KCZJ1_WaterPressure3;
		E014[26] = KCZJ1_WaterPressure4;
	    E014_easy();//剩余部分
	    Serial.println("完成设备路数1的回执");


	    delay(1500);//这段延时暂时不要去除,怕LORA的发送接收反应不过来


	    E014[8]  = 0x02;							//E014的路数
	    E014[9]  = KCZJ2_E014_status;				//继电器2的E014状态
    	E014[14] = KCZJ2_E014_CurrentOpenRatio1;	//继电器2的E014开度
	    E014[15] = KCZJ2_E014_CurrentOpenRatio2;
	    E014[16] = KCZJ2_E014_CurrentOpenRatio3;
	    E014[17] = KCZJ2_E014_TotalWorkSec1;		//继电器2的工作时长
	    E014[18] = KCZJ2_E014_TotalWorkSec2;
	    E014[19] = KCZJ2_E014_TotalWorkSec3;
	    E014[20] = KCZJ2_E014_CurrentWorkSec1;		//继电器2的已工作时长
	    E014[21] = KCZJ2_E014_CurrentWorkSec2;
	    E014[22] = KCZJ2_E014_CurrentWorkSec3;
		E014[23] = KCZJ2_WaterPressure1;			//继电器2的水压
		E014[24] = KCZJ2_WaterPressure2;
		E014[25] = KCZJ2_WaterPressure3;
		E014[26] = KCZJ2_WaterPressure4;
	    E014_easy();//剩余部分
	    Serial.println("完成设备路数2的回执");
    }
    else
    {
    	Serial.println("这里是E014预留的未知错误信息....");
    }
    
    return 0;
}

unsigned char E014_init()
{
    E014_FrameHead = 0xFE;                  //E014的帧头

    E014_FrameId1 = 0xE0;                   //E014的帧ID1
    E014_FrameId2 = 0x14;                   //E014的帧ID2

    E014_DataLen = 0x1A;                    //E014的数据长度

	E014_DeviceTypeID1 = 0xC0;				//E014的设备类型1
	E014_DeviceTypeID2 = 0x03;				//E014的设备类型2

    /*------
    E014_IsBroadcast = 0x00;                //E014的是否广播指令
    */

    E014_ZoneId = EEPROM.read(3);           //E014的区域

    // E014_channel = EEPROM.read(9);          //E014的设备路数

    E014_status = FactoryMode;  //E014的设备状态

    Get_voltage();//得到电压值
    Report_information(Voltage_value);//得到电流值
	Water_pressure1();//得到水压值1
	Water_pressure2();//得到水压值2
    // E014_Vol1 = 0x00;           //E014的电压1
    // E014_Vol2 = 0x00;           //E014的电压2

    Signal_query();
    // E014_Rssi = 0x00;           //E014的信噪比
    // E014_Csq = 0x00;            //E014的信号强度

    //E014_Allocate1 = 0x00;      //E014的预留字段1
    //E014_Allocate2 = 0x00;      //E014的预留字段2
    //E014_Allocate3 = 0x00;      //E014的预留字段3
    //E014_Allocate4 = 0x00;      //E014的预留字段4
    E014_Allocate5 = 0x00;      //E014的预留字段5
    E014_Allocate6 = 0x00;      //E014的预留字段6
    E014_Allocate7 = 0x00;      //E014的预留字段7

    E014_CRC8 = 0xD6;           //E014的CRC8校验码

    E014_FrameEnd1 = 0x0D;      //E014的帧尾1
    E014_FrameEnd2 = 0x0A;      //E014的帧尾2
    E014_FrameEnd3 = 0x0D;      //E014的帧尾3
    E014_FrameEnd4 = 0x0A;      //E014的帧尾4
    E014_FrameEnd5 = 0x0D;      //E014的帧尾5
    E014_FrameEnd6 = 0x0A;      //E014的帧尾6

}

unsigned char Get_voltage()
{
    Voltage_value = map(analogRead(VIN1),0,1129,0,1000);//这里需要换测量的引脚
    Voltage_value = Voltage_value/100;
    return Voltage_value;
}

unsigned char Water_pressure1()
{
	pinMode(VIN1, INPUT_ANALOG);
	for (int i = 0; i < 10; i++)
	{
		if (analogRead(VIN1) <= 2)
		{
			Water_valueData1[i] = 0.00;
		}
		else
		{
			Water_valueData1[i] = float(analogRead(VIN1) * 1000) / 569;//这里是水压测量的引脚VIN2，靠近继电器端子的V引脚
		}
		Water_valueData1_length++;
		Serial.print("Water_valueData1 -");
		Serial.print(i);
		Serial.print(" ->:");
		Serial.println(Water_valueData1[i]);
		delay(5);
	}
	if (Water_valueData1_length > 0)
	{
		Water_value1 = Filter(Water_valueData1,Water_valueData1_length);
		Water_valueData1_length = 0;
	}
	Serial.print("Water_value1 = ");
	Serial.print(Water_value1);
	Serial.println("kpa");
	if ((Water_value1 <= 99) && (Water_value1 >= 0))
	{
		KCZJ1_WaterPressure1 = 0;
		KCZJ1_WaterPressure2 = floor(Water_value1);
		KCZJ1_WaterPressure3 = (Water_value1 - KCZJ1_WaterPressure2) * 100;
		KCZJ1_WaterPressure4 = 0xE2;
	}
	else if ((Water_value1 > 99) && (Water_value1 <= 9999))
	{
		KCZJ1_WaterPressure1 = Water_value1 / 100;
		KCZJ1_WaterPressure2 = floor(Water_value1 - (KCZJ1_WaterPressure1 * 100));
		KCZJ1_WaterPressure3 = (Water_value1 - (KCZJ1_WaterPressure1 * 100) - KCZJ1_WaterPressure2) * 100;
		KCZJ1_WaterPressure4 = 0xE2;
	}
	//E014[23] = KCZJ1_WaterPressure1;
	//E014[24] = KCZJ1_WaterPressure2;
	//E014[25] = KCZJ1_WaterPressure3;
	//E014[26] = KCZJ1_WaterPressure4;
	return Water_value1;
}


unsigned char Water_pressure2()
{
	pinMode(VIN2, INPUT_ANALOG);
	for (int i = 0; i < 10; i++)
	{
		if (analogRead(VIN2) <= 2)
		{
			Water_valueData1[i] = 0.00;
		}
		else
		{
			Water_valueData2[i] = (float(analogRead(VIN2)) * 1000) / 569;//这里是水压测量的引脚VIN2，靠近继电器端子的V引脚
		}
		Water_valueData2_length++;
		Serial.print("Water_valueData2 -");
		Serial.print(i);
		Serial.print(" ->:");
		Serial.println(Water_valueData2[i]);
		delay(5);
	}
	if (Water_valueData2_length > 0)
	{
		Water_value2 = Filter(Water_valueData2, Water_valueData2_length);
		Water_valueData2_length = 0;
	}
	Serial.print("Water_value2 = ");
	Serial.print(Water_value2);
	Serial.println("kpa");
	if ((Water_value2 <= 99) && (Water_value2 >= 0))
	{
		KCZJ2_WaterPressure1 = 0;
		KCZJ2_WaterPressure2 = floor(Water_value2);
		KCZJ2_WaterPressure3 = (Water_value2 - KCZJ2_WaterPressure2) * 100;
		KCZJ2_WaterPressure4 = 0xE2;
	}
	else if ((Water_value2 > 99) && (Water_value2 <= 9999))
	{
		KCZJ2_WaterPressure1 = Water_value2 / 100;
		KCZJ2_WaterPressure2 = floor(Water_value2 - (KCZJ2_WaterPressure1 * 100));
		KCZJ2_WaterPressure3 = (Water_value2 - (KCZJ2_WaterPressure1 * 100) - KCZJ2_WaterPressure2) * 100;
		KCZJ2_WaterPressure4 = 0xE2;
	}
	//E014[23] = KCZJ2_WaterPressure1;
	//E014[24] = KCZJ2_WaterPressure2;
	//E014[25] = KCZJ2_WaterPressure3;
	//E014[26] = KCZJ2_WaterPressure4;
	return Water_value2;
}

unsigned char Report_information(float Voltage_value)//信息上报函数
{
    Serial.print("经过处理读取到的电压值1为：");
    Serial.print( Voltage_value,2);
    Serial.println("V");
    //delay(500);//使用请注释
    E014_Vol1 = floor(Voltage_value);               //E014的电压1,floor函数向下取整
    E014_Vol2 = (Voltage_value - E014_Vol1)*100;    //E014的电压2
    Serial.print("E014_Vol1 = ");
    Serial.println(E014_Vol1);
    Serial.print("E014_Vol2 = ");
    Serial.println(E014_Vol2);
    return 0;
}

unsigned char Signal_query()        //信号查询函数
{
    Serial.println("AT_CMD,HIGH");
    digitalWrite(AT_CMD,HIGH);      //外部输入高电平到AT引脚，模块即可进入AT配置模式
    delay(500);//此处延时不能删
    Serial3.print("AT+CSQ?\r\n");   //查询信号质量
    delay(500);//此处延时不能删
    while(Serial3.available() > 0)
    {
        Re_Data[Re_Length++] = Serial3.read();
        delay(1);
    }
    if(Re_Length > 0)
    {
        Serial.write(Re_Data,Re_Length);
        delay(100);
        for (int i = 0; i < Re_Length; ++i)
        {
            Serial.print(i);
            Serial.print(":");
            Serial.println(Re_Data[i]);
            delay(1);
        }
        Re_Length = 0;
    }

    //这里得到信号强度以及信噪比的10进制
    if(Re_Data[6] == 58 && Re_Data[8] == 44)//第6位是冒号以及第8位是逗号说明信号强度为1位
    {
        E014_Csq = Re_Data[7] - 48;         //E014的信号强度

        //这里得到信噪比的10进制
        if(Re_Data[11] == 13)//结合前面的条件以及第11位是\r说明信噪比为1位
        {
            E014_Rssi = Re_Data[10] - 48;
        }
        else if(Re_Data[12] == 13)//结合前面的条件以及第12位是\r说明信噪比为2位
        {
            E014_Rssi = ((Re_Data[10] - 48)* 10) + (Re_Data[11] - 48);
        }
        else if(Re_Data[13] == 13)//结合前面的条件以及第13位是\r说明信噪比为3位
        {
            E014_Rssi = ((Re_Data[10] - 48)* 100) + (Re_Data[11] - 48)* 10 + (Re_Data[12] - 48);
        }
    }
    else if(Re_Data[6] == 58 && Re_Data[9] == 44)//第6位是冒号以及第9位是逗号说明信号强度为2位
    {
        E014_Csq = (Re_Data[7] - 48)* 10 + (Re_Data[8] - 48);         //E014的信号强度

        //这里得到信噪比的10进制
        if(Re_Data[12] == 13)//结合前面的条件以及第12位是\r说明信噪比为1位
        {
            E014_Rssi = Re_Data[11] - 48;
        }
        else if(Re_Data[13] == 13)//结合前面的条件以及第13位是\r说明信噪比为2位
        {
            E014_Rssi = ((Re_Data[11] - 48)* 10) + (Re_Data[12] - 48);
        }
        else if(Re_Data[14] == 13)//结合前面的条件以及第14位是\r说明信噪比为3位
        {
            E014_Rssi = ((Re_Data[11] - 48)* 100) + (Re_Data[12] - 48)* 10 + (Re_Data[13] - 48);
        }
    }
    else if (Re_Data[6] == 58 && Re_Data[10] == 44)//第6位是冒号以及第10位是逗号说明信号强度为3位
    {
        E014_Csq = (Re_Data[7] - 48)* 100 + (Re_Data[8] - 48)* 10 + (Re_Data[9] - 48); 

        //这里得到信噪比的10进制
        if(Re_Data[13] == 13)//结合前面的条件以及第12位是\r说明信噪比为1位
        {
            E014_Rssi = Re_Data[12] - 48;
        }
        else if(Re_Data[14] == 13)//结合前面的条件以及第13位是\r说明信噪比为2位
        {
            E014_Rssi = ((Re_Data[12] - 48)* 10) + (Re_Data[13] - 48);
        }
        else if(Re_Data[15] == 13)//结合前面的条件以及第14位是\r说明信噪比为3位
        {
            E014_Rssi = ((Re_Data[12] - 48)* 100) + (Re_Data[13] - 48)* 10 + (Re_Data[14] - 48);
        }
    }
    Serial.print("E014_Csq = ");
    Serial.println(E014_Csq);
    Serial.print("E014_Rssi = ");
    Serial.println(E014_Rssi);
    //delay(500);
    digitalWrite(AT_CMD,LOW);       //外部输入低电平即可进入透传模式
    Serial.println("AT_CMD,LOW");
    delay(500);
    return 0;
}

void E014_easy()
{
	//--------------------------------------------------------
    //将Receive_Data的值处理得到Check_Data
    for (int i = 4; i <= E014_DataLen + 0x03; i++)
    {
        Check_Data[Check_Length] = E014[i];
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
        E014_CRC8 = GetCrc8(Check_Data,Check_Length);
        Serial.print("E014_CRC8 = 0x");
        Serial.println(E014_CRC8,HEX);
        Check_Length = 0;
    }
    E014[30] = E014_CRC8;
    E014[31] = E014_FrameEnd1;
    E014[32] = E014_FrameEnd2;
    E014[33] = E014_FrameEnd3;
    E014[34] = E014_FrameEnd4;
    E014[35] = E014_FrameEnd5;
    E014[36] = E014_FrameEnd6;

    for (int i = 0;i < 37;i++)
    {
        Serial.print(i);
        Serial.print("/");
        Serial.println(E014[i],HEX);
        delay(1);
    }

    Serial3.write(E014,37);
    Serial.println("已发送E014，等待服务器回应");
}


//函 数 名：forswitch()
//功能描述：并行控制继电器的代码
//函数说明：
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
void forswitch()
{
	if(rd[0] == Stateless && rd[1] == Stateless)
	{

	}
	else
	{
		for (int i = 0; i < 2; i++)
	    {
	        switch (rd[i]) 
	        {
	          	/*状态：无状态
	             *在此状态中需要不断检测接收的值，
	             *接收到值后进行判断进入下一个状态。*/
	            case Stateless:
	              	//无状态
	              	//无状态指令
	              	//--------------------------------------
	                delay(200);
	                Serial.print(i);
	                Serial.println("进入case：Stateless");
	                //--------------------------------------
	                break;
	  
	            /*状态：继电器1开
	            *在此状态中需要不断检测接收的值，
	            *接收到值后进行判断进入下一个状态。*/
	            case KCZJ1_ON:
	            	//--------------------------------------
	              	delay(500);
	                Serial.print(i);
	                Serial.println("进入case：KCZJ1_ON");
	                //--------------------------------------
	                digitalWrite(KCZJ1,LOW);

	                KCZJ1_CurrentWorkSec = (millis() - ot[i])/1000;//得到设备路数2的已工作时长
	                Serial.print("KCZJ1_CurrentWorkSec:");
	                Serial.println(KCZJ1_CurrentWorkSec);

	                //-----------------------------------这一段代码将已工作的数值拆位-------------------------------------------------------------------------------
	                if (KCZJ1_CurrentWorkSec <= 0xFF)
	                {
	                	KCZJ1_E014_CurrentWorkSec1 = 0x00;
						KCZJ1_E014_CurrentWorkSec2 = 0x00;
						KCZJ1_E014_CurrentWorkSec3 = KCZJ1_CurrentWorkSec;
	                }
	                else if (KCZJ1_CurrentWorkSec > 0xFF && KCZJ1_CurrentWorkSec <= 0xFFFF)
	                {
	                	KCZJ1_E014_CurrentWorkSec1 = 0x00;
						KCZJ1_E014_CurrentWorkSec2 = KCZJ1_CurrentWorkSec/0x100;
						KCZJ1_E014_CurrentWorkSec3 = (KCZJ1_CurrentWorkSec - KCZJ1_E014_CurrentWorkSec2*0x100);
	                }
	                else if (KCZJ1_CurrentWorkSec > 0xFFFF)
	                {
	                	KCZJ1_E014_CurrentWorkSec1 = KCZJ1_CurrentWorkSec/0x10000;
						KCZJ1_E014_CurrentWorkSec2 = KCZJ1_CurrentWorkSec - (KCZJ1_E014_CurrentWorkSec1*0x10000)/0x100;
						KCZJ1_E014_CurrentWorkSec3 = KCZJ1_CurrentWorkSec - (KCZJ1_E014_CurrentWorkSec1*0x10000) - (KCZJ1_E014_CurrentWorkSec2*0x100);
	                }
	                //-------------------------------------------------------------------------------------------------------------------------------------------


	                if (millis() - ot[i] >= duration[i]*1000)
	                {
	                    //时间到了需要清空这个数组的东西
	                    Serial.println("继电器1设定的时间到了呀");
	                    digitalWrite(KCZJ1,HIGH);
	                    rd[i] = Stateless;
	                    if(digitalRead(KCZJ1) == HIGH)
	                    {
	                    	KCZJ1_E014_status = CLOSE_OK;
	                    }
	                    else
	                    {
	                    	KCZJ1_E014_status = CLOSE_EXCEPTION;
	                    }
	                    //进行完成的状态的回执，成时回复实时状态（E014）
	                    Inquire_channel = 0x01;//这是为了只回执设备路数1完成
				    	Send_E014();

				    	KCZJ1_E014_TotalWorkSec1 = 0x00;	//KCZJ1_E014设置的工作时长1完成清零
						KCZJ1_E014_TotalWorkSec2 = 0x00;	//KCZJ1_E014设置的工作时长2完成清零
						KCZJ1_E014_TotalWorkSec3 = 0x00;	//KCZJ1_E014设置的工作时长3完成清零
						KCZJ1_E014_CurrentWorkSec1 = 0x00;	//KCZJ1_E014_CurrentWorkSec1已工作时间完成清零
						KCZJ1_E014_CurrentWorkSec2 = 0x00;	//KCZJ1_E014_CurrentWorkSec1已工作时间完成清零
						KCZJ1_E014_CurrentWorkSec3 = 0x00;	//KCZJ1_E014_CurrentWorkSec1已工作时间完成清零
						KCZJ1_CurrentWorkSec = 0;			//KCZJ1_CurrentWorkSec已工作时间完成清零
	                }
	                break;
	  	  
	            /*状态：继电器2开
	            *在此状态中需要不断检测接收的值，
	            *接收到值后进行判断进入下一个状态。*/
	            case KCZJ2_ON:
	            	//--------------------------------------
	              	delay(500);
	                Serial.print(i);
	                Serial.println("进入case：KCZJ2_ON");
	                //--------------------------------------
	                digitalWrite(KCZJ2,LOW);

	                KCZJ2_CurrentWorkSec = (millis() - ot[i])/1000;//得到设备路数2的已工作时长//得到设备路数2的已工作时长
	                Serial.print("KCZJ2_CurrentWorkSec:");
	                Serial.println(KCZJ2_CurrentWorkSec);
	                //-----------------------------------这一段代码将已工作的数值拆位-------------------------------------------------------------------------------
	                if (KCZJ2_CurrentWorkSec <= 0xFF)
	                {
	                	KCZJ2_E014_CurrentWorkSec1 = 0x00;
						KCZJ2_E014_CurrentWorkSec2 = 0x00;
						KCZJ2_E014_CurrentWorkSec3 = KCZJ2_CurrentWorkSec;
	                }
	                else if (KCZJ2_CurrentWorkSec > 0xFF && KCZJ2_CurrentWorkSec <= 0xFFFF)
	                {
	                	KCZJ2_E014_CurrentWorkSec1 = 0x00;
						KCZJ2_E014_CurrentWorkSec2 = KCZJ2_CurrentWorkSec/0x100;
						KCZJ2_E014_CurrentWorkSec3 = (KCZJ2_CurrentWorkSec - KCZJ2_E014_CurrentWorkSec2*0x100);
	                }
	                else if (KCZJ2_CurrentWorkSec > 0xFFFF)
	                {
	                	KCZJ2_E014_CurrentWorkSec1 = KCZJ2_CurrentWorkSec/0x10000;
						KCZJ2_E014_CurrentWorkSec2 = KCZJ2_CurrentWorkSec - (KCZJ2_E014_CurrentWorkSec1*0x10000)/0x100;
						KCZJ2_E014_CurrentWorkSec3 = KCZJ2_CurrentWorkSec - (KCZJ2_E014_CurrentWorkSec1*0x10000) - (KCZJ2_E014_CurrentWorkSec2*0x100);
	                }
	                //-------------------------------------------------------------------------------------------------------------------------------------------


	                if (millis() - ot[i] >= duration[i]*1000)
	                {
	                    //时间到了需要清空这个数组的东西
	                    Serial.println("继电器2设定的时间到了呀");
	                    digitalWrite(KCZJ2,HIGH);
	                    rd[i] = Stateless;
	                    if(digitalRead(KCZJ2) == HIGH)
	                    {
	                    	KCZJ2_E014_status = CLOSE_OK;
	                    }
	                    else
	                    {
	                    	KCZJ2_E014_status = CLOSE_EXCEPTION;
	                    }
	                    //进行完成的状态的回执，成时回复实时状态（E014）
	                    Inquire_channel = 0x02;//这是为了只回执设备路数2完成
				    	Send_E014();

				    	KCZJ2_E014_TotalWorkSec1 = 0x00;	//KCZJ2_E014设置的工作时长1完成清零
						KCZJ2_E014_TotalWorkSec2 = 0x00;	//KCZJ2_E014设置的工作时长2完成清零
						KCZJ2_E014_TotalWorkSec3 = 0x00;	//KCZJ2_E014设置的工作时长3完成清零
						KCZJ2_E014_CurrentWorkSec1 = 0x00;	//KCZJ2_E014_CurrentWorkSec1已工作时间完成清零
						KCZJ2_E014_CurrentWorkSec2 = 0x00;	//KCZJ2_E014_CurrentWorkSec1已工作时间完成清零
						KCZJ2_E014_CurrentWorkSec3 = 0x00;	//KCZJ2_E014_CurrentWorkSec1已工作时间完成清零
						KCZJ2_CurrentWorkSec = 0;			//KCZJ2_CurrentWorkSec已工作时间完成清零
	                }
	                break;
	            default:
	            	//--------------------------------------
	                delay(500);
	                Serial.println("Instruction error指令错误");
	                //--------------------------------------
	                break;
	        }
	    }
	}
}