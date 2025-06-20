#include <REGX52.H>
#include "Delay.h"
#include "Timer0.h"

//蜂鸣器端口定义
sbit Buzzer=P2^5;

//播放速度，值为四分音符的时长(ms)
#define SPEED	250

//音符与索引对应表，P：休止符，L：低音，M：中音，H：高音，下划线：升半音符号#
#define P	0
#define L1	1
#define L1_	2
#define L2	3
#define L2_	4
#define L3	5
#define L4	6
#define L4_	7
#define L5	8
#define L5_	9
#define L6	10
#define L6_	11
#define L7	12
#define M1	13
#define M1_	14
#define M2	15
#define M2_	16
#define M3	17
#define M4	18
#define M4_	19
#define M5	20
#define M5_	21
#define M6	22
#define M6_	23
#define M7	24
#define H1	25
#define H1_	26
#define H2	27
#define H2_	28
#define H3	29
#define H4	30
#define H4_	31
#define H5	32
#define H5_	33
#define H6	34
#define H6_	35
#define H7	36

//索引与频率对照表
unsigned int FreqTable[]={
	0,
	63628,63731,63835,63928,64021,64103,64185,64260,64331,64400,64463,64528,
	64580,64633,64684,64732,64777,64820,64860,64898,64934,64968,65000,65030,
	65058,65085,65110,65134,65157,65178,65198,65217,65235,65252,65268,65283,
};

//乐谱
unsigned char code Music[]={
	//音符,时值,
   L7,3,P,1,
   L7,2,
   L7,2,
   M2_,2,
   M2_,2,
   M1_,2,
   M1_,2,
   M1_,8,
   L7,3,P,1,
   L7,3,P,1,
   L7,2,
   L7,2,
   M2_,2,
   M2_,2,
   M1_,3,P,1,
   M1_,8,P,4,
   L6,1,P,1,
   L7,3,P,1,
   L7,3,P,1,
   L7,2,P,1,
   L7,2,P,1,
   M2_,2,P,1,
   M2_,2,P,1,
   L7,1,
   M1_,3,P,1,
   M1_,8,P,4,
   L7,3,P,1,
   L7,3,P,1,
   L7,2,P,1,
   L7,2,P,1,
   M2_,2,P,1,
   M2_,2,P,1,
   L7,1,
   M1_,3,
   L7,1,
   M1_,7,

   0xFF	//终止标志
};

unsigned char FreqSelect,MusicSelect;

void main()
{
	Timer0Init();
	while(1)
	{
		if(Music[MusicSelect]!=0xFF)	//如果不是停止标志位
		{
			FreqSelect=Music[MusicSelect];	//选择音符对应的频率
			MusicSelect++;
			Delay(SPEED/4*Music[MusicSelect]);	//选择音符对应的时值
			MusicSelect++;
			TR0=0;
			Delay(0.1);	//音符间短暂停顿
			TR0=1;
		}
		else	//如果是停止标志位
		{
			TR0=0;
			while(1);
		}
	}
}

void Timer0_Routine() interrupt 1
{
	if(FreqTable[FreqSelect])	//如果不是休止符
	{
		/*取对应频率值的重装载值到定时器*/
		TL0 = FreqTable[FreqSelect]%256;		//设置定时初值
		TH0 = FreqTable[FreqSelect]/256;		//设置定时初值
		Buzzer=!Buzzer;	//翻转蜂鸣器IO口
	}
}
