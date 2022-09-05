#pragma once

#pragma region 头文件引用

// Windows 头文件
#include <windows.h>

// C 运行时头文件
#include <stdlib.h>
#include <malloc.h>//用来开链表空间
#include <memory.h>//提供内存操作函数
#include <tchar.h>
#include <time.h>//用来计时，函数clock（）用来计算wall-clock

// 资源头文件
#include "resource.h"
#pragma comment(lib, "Msimg32.lib") //导入图像处理静态库，可使用库中位图的绘制TransparentBlt等函数

// TODO:  在此处引用程序需要的其他头文件
#include <vector>
#include <math.h>
#include "mmsystem.h"
#pragma comment(lib,"winmm.lib")

#pragma endregion

#pragma region 宏定义

#define WINDOW_TITLEBARHEIGHT	32			//标题栏高度
#define WINDOW_WIDTH			1400		//游戏窗口宽度
#define WINDOW_HEIGHT			701  		//游戏窗口高度


#define STAGE_STARTMENU			0		//开始画面的ID
#define STAGE_1					1		//第一个游戏场景的ID
#define STAGE_2                 2       //第二个游戏场景的ID
#define STAGE_3                 3       //第三个游戏场景的ID
#define STAGE_LOSE              7
#define STAGE_WIN               8
#define STAGE_OVER              9

#define UNIT_SIZE_X				64		//单位的宽度
#define UNIT_SIZE_Y				64		//单位的高度
#define POLO_SIZE_X             60
#define POLO_SIZE_Y             61
#define PD_SIZE_X               32
#define PD_SIZE_Y               32
#define PD_SPEED                6.0
#define FF_SPEED                12.0
#define Maxhealth               100     //单位的最大生命值
#define Maxenergy               100.0     //魄罗的最大蓝量
#define UNIT_LAST_FRAME			11		//单位的动画帧最大值

//单位阵营定义
#define UNIT_SIDE_RED			10000	//红方
#define UNIT_SIDE_BLUE			10001	//蓝方


//单位类型定义
#define UNIT_TYPE_REAPER		0		//收割者
#define UNIT_TYPE_CASTER		1		//魔术师
#define UNIT_TYPE_SABER			2		//剑士
#define UNIT_TYPE_SHIELDER		3		//盾卫
#define UNIT_TYPE_HOPLITE		4		//重装步兵
#define TIME_COUNT_DOWN         10000  //场景一的倒计时时长

//单位状态定义
#define UNIT_STATE_HOLD			0		//静止
#define UNIT_STATE_WALK			1		//行走
#define UNIT_STATE_ATTACK		2		//攻击
#define FIRE_TOWER              0
#define ICE_TOWER              1
//单位方向定义
#define UNIT_DIRECT_RIGHT		0		//向右
#define UNIT_DIRECT_LEFT		1		//向左

//背景
#define BG_NEW_COLUMNS          44      //背景列数
#define BG_NEW_ROWS             22      //背景行数
#define BG_NEW_CELL_WIDTH		32		//背景单格宽度
#define BG_NEW_CELL_HEIGHT		32		//背景单格高度

#define BG_TOWER_WIDTH          32      //塔的宽度
#define BG_TOWER_HEIGHT         64      //塔的高度

//其它定义
#define BUTTON_STARTGAME			1001	//开始游戏按钮ID
#define BUTTON_CONTINUE             1002    //继续游戏按钮ID
#define BUTTON_RESTART              1003    //重新开始按钮ID
#define BUTTON_INTRODUCTION         1004    //游戏说明按钮ID
#define BUTTON_MONEY                1005    //查看金币数目ID
#define BUTTON_POLO                 1006    //魄罗图标的ID
#define BUTTON_PD                   1007    //炮弹图标的ID
#define BUTTON_PDD                  1008    //炮弹CD图标的ID
#define BUTTON_NEXT                 1009    //下一关的ID
#define BUTTON_INFO1                1010
#define BUTTON_INFO2                1011
#define BUTTON_INFO3                1012
#define BUTTON_INFO4                1013
#define BUTTON_STARTGAME_WIDTH		212		//开始游戏按钮宽度
#define BUTTON_STARTGAME_HEIGHT		76		//开始游戏按钮高度

#define TIMER_GAMETIMER				1		//游戏的默认计时器ID
#define TIMER_GAMETIMER_ELAPSE		30		//默认计时器刷新间隔的毫秒数
#define UNIT_SPEED					2.0		//单位行走速度	


#pragma endregion

#pragma region 结构体声明

// 场景结构体
struct Stage {
	int stageID;		//场景编号
	HBITMAP bg;			//背景图片
	int timeCountDown;	//游戏时间倒计时
	bool timerOn;		//计时器是否运行（游戏是否被暂停）
	int money;          //玩家金币
};

struct ICE
{
	HBITMAP img;
	int x;
	int y;
	double vx;
	double vy;
};

// 按钮结构体
struct Button {
	int buttonID;	//按钮编号
	bool visible;	//按钮是否可见
	HBITMAP img;	//图片
	int x;			//坐标x
	int y;			//坐标y
	int width;		//宽度
	int height;		//高度
};

//塔结构体
struct Tower {
	HBITMAP img;		//图片

	int frame_row;		//当前显示的是图像的第几行
	int frame_column;	//当前显示的是图像的第几列

	int height;			//塔的高度
	int width;			//塔的宽度

	int x;				//坐标x
	int y;				//坐标y

	int type;			//塔类型
	int distance;		//攻击范围
	int attack;         //攻击伤害
	int level;
	int yes;
	//Unit* victim=NULL;       //防御塔单人攻击的对象
};

// 单位结构体
struct Unit {
	HBITMAP img;	//图片

	int frame_row;			//当前显示的是图像的第几行
	int frame_column;		//当前显示的是图像的第几列

	int* frame_sequence;		//当前的帧序列
	int frame_count;		//帧序列的长度
	int frame_id;			//当前显示的是帧序列的第几个


	int side;		//单位阵营
	int type;		//单位类型
	int state;		//单位状态
	int direction;	//单位方向
	int condition;
	int x;			//坐标x
	int y;			//坐标y
	double vx;		//速度x
	double vy;		//速度y
	int health;		//生命值
	int maxhealth;  //初始生命值
};
struct F
{
	HBITMAP img;
	int x;
	int y;
};
struct FOG
{
	HBITMAP img;
	int *frame_sequence;
	int frame_count;
	int frame_id;
	int x; int y;
};
struct MIST
{
	HBITMAP img;
	//int frame_number;//当前显示的是图像的第几个
	int *frame_sequence;//当前的帧序列
	int frame_count;//帧序列的长度
	int frame_id;//当前显示的是帧序列的第几个
	int x;//单位显示的x坐标
	int y;//单位显示的y坐标
};

struct POLO
{
	HBITMAP img;
	int x;
	int y;
	int health;
	int vx;
	int vy;
	int ax;
	int ay;
	int state;
	double energy;
};
struct PD
{
	HBITMAP img;
	int x;
	int y;
	double vx;
	double vy;
};
struct TD
{
	HBITMAP img;
	int x;
	int y;
	int health;
};
struct FF
{
	HBITMAP img;
	int x;
	int y;
	double vx;
	double vy;
};

//TODO: 添加游戏需要的更多种数据（地物、砖块等）


#pragma endregion

#pragma region 事件处理函数声明


// 初始化游戏窗体函数
void InitGame(HWND hWnd, WPARAM wParam, LPARAM lParam);

// 键盘按下事件处理函数
void KeyDown(HWND hWnd, WPARAM wParam, LPARAM lParam);

// 键盘松开事件处理函数
void KeyUp(HWND hWnd, WPARAM wParam, LPARAM lParam);

// 鼠标移动事件处理函数
void MouseMove(HWND hWnd, WPARAM wParam, LPARAM lParam);

// 鼠标左键按下事件处理函数
void LButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam);

void RButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam);
// 鼠标左键松开事件处理函数
void LButtonUp(HWND hWnd, WPARAM wParam, LPARAM lParam);
void RButtonUp(HWND hWnd, WPARAM wParam, LPARAM lParam);
// 定时器事件处理函数
void TimerUpdate(HWND hWnd, WPARAM wParam, LPARAM lParam);

void drawdistance(int distance, int x, int y);
#pragma endregion

#pragma region 其它游戏状态处理函数声明

// 添加按钮函数
Button* CreateButton(int buttonID, HBITMAP img, int width, int height, int x, int y);

// 添加单位函数
Unit* CreateUnit(int side, int type, int x, int y, int health);

// 添加防御塔函数
void CreateTowers(HWND hWnd, int x, int y, int type,int row,int column,int attack,int distance);
F* CreateF(int x, int y);
TD* CreateTD(int x, int y);
POLO* CreatePOLO(int x, int y, int health);
PD* CreatePD(int x, int y);
MIST* Createmist(int x, int y);
FOG* Createfog(int x, int y);
FF* CreateFF(int x, int y);
ICE* CreateICE(int x, int y);
// 初始化场景函数
void InitStage(HWND hWnd, int stageID);

// 刷新单位状态函数
void UpdateUnits(HWND hWnd);
void Drawmoney(int x, int y);
void DrawDeadline(int x, int y);

//单位行为函数
void UnitBehaviour_1(Unit* unit);
void UnitBehaviour_2(Unit* unit);
void POLOBehaviour(POLO* polo);
void PDBehaviour(PD* pd,double vx,double vy);
void MISTBehaviour(MIST* mist);
void UnitBehaviour_stage1(Unit* unit,HWND hwnd);
void UnitBehaviour_stage2(Unit* unit, HWND hwnd);
void FOGBehaviour(FOG* fog);
void FFBehaviour(FF* ff, double vx, double vy);
void TDBehaviour(TD* td);
void ICEBehaviour(ICE* ice, double vx, double vy);
//TODO: 添加游戏需要的更多函数


#pragma endregion

#pragma region 绘图函数声明

// 绘图函数
void Paint(HWND hWnd);
void DrawTDHealthLine(int midx, int midy, int health, int maxhealth);
void DrawHealthLine(int midx, int midy, int health,int maxhealth);
void DrawPOLOLine(int midx, int midy, int health,int energy);
void DrawattackLine(int xbx, int xby, int towerx, int towery);
// 地图设计函数
int** GetMap(int k);

// 初始化背景函数
HBITMAP InitBackGround(HWND hWnd, HBITMAP bmp_src,HBITMAP bmp_src1, HBITMAP bmp_tower);

#pragma endregion