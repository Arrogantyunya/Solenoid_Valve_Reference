//user_A025receipt.h
/*
*版权
*
* 文件名称:user_A025receipt.h
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


#ifndef USER_A025RECEIPT_H	//防止头文件user_A025receipt.h被重复调用
#define USER_A025RECEIPT_H


#include<arduino.h>	//引用标准库的头文件
#include<EEPROM.h>//
#include"user_initialization.h"//初始化
#include"user_crc8.h"//CRC校验
#include"user_judgement.h"//判断
#include"user_filter.h"//滤波



//引脚定义



//全局变量
static unsigned char A012_Working_parameter_setting;	//A012设置的标志位
static unsigned char A013_Working_parameter_setting;	//A013设置的标志位
// static unsigned char A012_Set = 0x00;  					//
// static unsigned char A013_Set = 0x00;					//
static unsigned char Receive_IsBroadcast; 				//是否广播指令
static unsigned char E015[25];//用来存放E015发送出去的数组
static unsigned char E014[37];//用来存放E014发送出去的数组
static int LORA_Query_parameters[20];//用来存放LORA查询的参数

static int E015_FrameHead = 0xFE;		//E015的帧头

static int E015_FrameId1 = 0xE0;		//E015的帧ID1
static int E015_FrameId2 = 0x15;		//E015的帧ID2

static int E015_DataLen = 0x0E;			//E015的数据长度

static int E015_DeviceTypeID1 = 0xC0;	//E015的设备类型1
static int E015_DeviceTypeID2 = 0x03;	//E015的设备类型2

static int E015_IsBroadcast = 0x00;		//E015的是否广播指令

static int E015_ZoneId = 0x01;			//E015的区域

static int E015_channel = 0x02;			//E015的设备路数

static int KCZJ1_E015_status = 0x00;    //KCZJ1_E015的设备状态
static int KCZJ2_E015_status = 0x00;    //KCZJ2_E015的设备状态

static int E015_Allocate1 = 0x00;		//E015的预留字段1
static int E015_Allocate2 = 0x00;		//E015的预留字段2
static int E015_Allocate3 = 0x00;		//E015的预留字段3
static int E015_Allocate4 = 0x00;		//E015的预留字段4
static int E015_Allocate5 = 0x00;		//E015的预留字段5
static int E015_Allocate6 = 0x00;		//E015的预留字段6
static int E015_Allocate7 = 0x00;		//E015的预留字段7
static int E015_Allocate8 = 0x00;		//E015的预留字段8

static int E015_CRC8 = 0xD6;			//E015的CRC8校验码

static int E015_FrameEnd1 = 0x0D;		//E015的帧尾1
static int E015_FrameEnd2 = 0x0A;		//E015的帧尾2
static int E015_FrameEnd3 = 0x0D;		//E015的帧尾3
static int E015_FrameEnd4 = 0x0A;		//E015的帧尾4
static int E015_FrameEnd5 = 0x0D;		//E015的帧尾5
static int E015_FrameEnd6 = 0x0A;		//E015的帧尾6

//============================分割线======================================//
static int E014_FrameHead = 0xFE;		//E014的帧头

static int E014_FrameId1 = 0xE0;		//E014的帧ID1
static int E014_FrameId2 = 0x14;		//E014的帧ID2

static int E014_DataLen = 0x1A;			//E014的数据长度

static int E014_DeviceTypeID1 = 0xC0;	//E014的设备类型1
static int E014_DeviceTypeID2 = 0x03;	//E014的设备类型2

static int E014_IsBroadcast = 0x00;		//E014的是否广播指令

static int E014_ZoneId = 0x01;			//E014的区域

static int E014_channel = 0x02;			//E014的设备路数


static int KCZJ1_E014_status = 0x00;    //KCZJ1_E014的设备状态
static int KCZJ2_E014_status = 0x00;    //KCZJ2_E014的设备状态


static int E014_Vol1 = 0x00;            //E014的电压1
static int E014_Vol2 = 0x00;            //E014的电压2

static int E014_Rssi = 0x00;            //E014的信噪比

static int E014_Csq = 0x00;             //E014的信号强度

static int KCZJ1_E014_CurrentOpenRatio1 = 0x00;//KCZJ1_E014设置的开度1
static int KCZJ1_E014_CurrentOpenRatio2 = 0x00;//KCZJ1_E014设置的开度2
static int KCZJ1_E014_CurrentOpenRatio3 = 0x00;//KCZJ1_E014设置的开度3
static int KCZJ2_E014_CurrentOpenRatio1 = 0x00;//KCZJ2_E014设置的开度1
static int KCZJ2_E014_CurrentOpenRatio2 = 0x00;//KCZJ2_E014设置的开度2
static int KCZJ2_E014_CurrentOpenRatio3 = 0x00;//KCZJ2_E014设置的开度3

static int KCZJ1_E014_TotalWorkSec1 = 0x00;//KCZJ1_E014设置的工作时长1
static int KCZJ1_E014_TotalWorkSec2 = 0x00;//KCZJ1_E014设置的工作时长2
static int KCZJ1_E014_TotalWorkSec3 = 0x00;//KCZJ1_E014设置的工作时长3
static int KCZJ2_E014_TotalWorkSec1 = 0x00;//KCZJ2_E014设置的工作时长1
static int KCZJ2_E014_TotalWorkSec2 = 0x00;//KCZJ2_E014设置的工作时长2
static int KCZJ2_E014_TotalWorkSec3 = 0x00;//KCZJ2_E014设置的工作时长3

static int KCZJ1_E014_CurrentWorkSec1 = 0x00;//KCZJ1_E014当前已工作时长1
static int KCZJ1_E014_CurrentWorkSec2 = 0x00;//KCZJ1_E014当前已工作时长2
static int KCZJ1_E014_CurrentWorkSec3 = 0x00;//KCZJ1_E014当前已工作时长3
static int KCZJ2_E014_CurrentWorkSec1 = 0x00;//KCZJ2_E014当前已工作时长1
static int KCZJ2_E014_CurrentWorkSec2 = 0x00;//KCZJ2_E014当前已工作时长2
static int KCZJ2_E014_CurrentWorkSec3 = 0x00;//KCZJ2_E014当前已工作时长3

static int KCZJ1_WaterPressure1 = 0x00;		//KCZJ1_E014的水压1
static int KCZJ1_WaterPressure2 = 0x00;		//KCZJ1_E014的水压2
static int KCZJ1_WaterPressure3 = 0x00;		//KCZJ1_E014的水压3
static int KCZJ1_WaterPressure4 = 0x00;		//KCZJ1_E014的水压4
static int KCZJ2_WaterPressure1 = 0x00;		//KCZJ2_E014的水压1
static int KCZJ2_WaterPressure2 = 0x00;		//KCZJ2_E014的水压2
static int KCZJ2_WaterPressure3 = 0x00;		//KCZJ2_E014的水压3
static int KCZJ2_WaterPressure4 = 0x00;		//KCZJ2_E014的水压4

static int E014_Allocate5 = 0x00;		//E014的预留字段5
static int E014_Allocate6 = 0x00;		//E014的预留字段6
static int E014_Allocate7 = 0x00;		//E014的预留字段7

static int E014_CRC8 = 0xD6;			//E014的CRC8校验码

static int E014_FrameEnd1 = 0x0D;		//E014的帧尾1
static int E014_FrameEnd2 = 0x0A;		//E014的帧尾2
static int E014_FrameEnd3 = 0x0D;		//E014的帧尾3
static int E014_FrameEnd4 = 0x0A;		//E014的帧尾4
static int E014_FrameEnd5 = 0x0D;		//E014的帧尾5
static int E014_FrameEnd6 = 0x0A;		//E014的帧尾6

static float Voltage_value;				//映射的电压值
static float Water_value1;				//映射的水压值1
static float Water_value2;				//映射的水压值2
static float Water_sum1;				//水压的总和1
static float Water_sum2;				//水压的总和2
static float Water_valueData1[10];		//水压数组1
static int Water_valueData1_length;		//水压数组1的长度
static float Water_valueData2[10];		//水压数组2
static int Water_valueData2_length;		//水压数组1的长度
static unsigned char Re_Data[50];		//接收的数组
static int Re_Length = 0;				//数组的长度

static unsigned char CurrentOpenRatio;	//设置的开度
static unsigned long TotalWorkSec; 		//设置的时间
static unsigned long CurrentWorkSec;	//当前已工作时长

static unsigned char Inquire_channel;	//查询路数
//=========================分割线==========================================
static int A025_flag = 0;
static int A025_ZoneId = 0x01;
static int A025_GroupIdArray1 = 0x01;
static int A025_GroupIdArray2 = 0x00;
static int A025_GroupIdArray3 = 0x00;
static int A025_GroupIdArray4 = 0x00;
static int A025_GroupIdArray5 = 0x00;
static int A025_channel = 0x02;

static unsigned char rd[6];                     //用来存放状态值rd1
static unsigned long duration[6];               //用来存放持续时间值Duration_time
static unsigned long remaining[6];              //用来存放剩余时间值Remaining
static unsigned long ot[6];                     //用来存放旧时间值oldtime

static unsigned long oldtime  = 0;              //旧时间

static unsigned char i;                         //循环变量，写在这里其实不合适

static unsigned long time_huns;                           //时间百位
static unsigned long time_tens;                           //时间十位
static unsigned long time_ones;                           //时间个位

static unsigned long Duration_time;                      //持续时间

static unsigned long Remaining;                          //剩余时间

static unsigned long KCZJ1_CurrentWorkSec;				//KCZJ1的已工作时长
static unsigned long KCZJ2_CurrentWorkSec;				//KCZJ2的已工作时长

static int IsBroadcast;							//是否是广播指令
// static int ZoneID;								//区域ID
// static int GroupID;								//组ID
static int Channel;								//设备路数 


//全局函数声明
void Receive_A012(unsigned char * Judgement_Data, int Judgement_Length);		//A012函数
unsigned char Send_E015(int Receive_IsBroadcast,int E015_status,int Channel);	//E015函数
unsigned char E015_init();														//E015初始化函数
unsigned char Send_E014();														//E014函数
unsigned char E014_init();														//E014初始化函数
void E014_easy();																//E014的剩余函数
unsigned char Report_information(float Voltage_value);							//信息上报函数
unsigned char Get_voltage();													//获取电压值函数
unsigned char Water_pressure1();												//水压测量函数
unsigned char Water_pressure2();												//水压测量函数
unsigned char Signal_query();													//信号查询函数
void Receive_A013(unsigned char * Judgement_Data, int Judgement_Length);  		//A013函数
void Receive_A014(unsigned char * Judgement_Data, int Judgement_Length);  		//A014函数
void Receive_A025(unsigned char * Judgement_Data, int Judgement_Length);  		//A025函数
void forswitch();


//类结构声明


//LORA开关型设备的通用回执状态(结构类型，枚举)
static enum Device_status
{
	FactoryMode_E015		= 0x00,//出厂模式
	AskUploadParamsOk 		= 0x01,//查询LORA设备参数成功
	AskUploadParamsErr 		= 0x02,//查询LORA设备参数失败
	AssignGroupIdArrayOk 	= 0x03,//设置组ID成功
	AssignGroupIdArrayErr 	= 0x04,//设置组ID失败
	SetSnAndSlaverCountOk 	= 0x05,//设置SN以及设备路数成功
	SetSnAndSlaverCountErr	= 0x06,//设置SN以及设备路数失败
	TrunOffOk 				= 0x07,//强制停止设备成功
	TrunOffErr 				= 0x08,//强制停止设备失败
	SetParamsOk 			= 0x09,//设置参数成功
	SetParamsErr 			= 0x0A //设置参数失败
}E015_status = FactoryMode_E015;

//LORA开关型设备的实时状态(结构类型，枚举)
static enum Real_time_Status
{
	FactoryMode = 0x00,		//出厂模式
	RUN_OK = 0x01,			//设备运行中
	CLOSE_OK = 0x02,		//设备关闭
	OPEN_EXCEPTION = 0x03,	//打开设备异常
	CLOSE_EXCEPTION = 0x04,	//关闭设备异常
	LOW_POWER = 0x05,		//低电压异常
	SENSOR_EXCEPTION = 0x06,//传感器异常
	Unknown_anomaly = 0x07	//未知异常
}E014_status = FactoryMode;

//继电器的状态(结构类型，枚举)
static enum RD1S
{
	KCZJ1_ON  = 1,//继电器1开
	KCZJ2_ON  = 2,//继电器2开
	LED2_ON	  = 3,//LED2开								
	Stateless = 0//无状态指令
}rd1 = Stateless;


#endif