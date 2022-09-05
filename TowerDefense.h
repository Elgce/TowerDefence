#pragma once

#pragma region ͷ�ļ�����

// Windows ͷ�ļ�
#include <windows.h>

// C ����ʱͷ�ļ�
#include <stdlib.h>
#include <malloc.h>//����������ռ�
#include <memory.h>//�ṩ�ڴ��������
#include <tchar.h>
#include <time.h>//������ʱ������clock������������wall-clock

// ��Դͷ�ļ�
#include "resource.h"
#pragma comment(lib, "Msimg32.lib") //����ͼ����̬�⣬��ʹ�ÿ���λͼ�Ļ���TransparentBlt�Ⱥ���

// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�
#include <vector>
#include <math.h>
#include "mmsystem.h"
#pragma comment(lib,"winmm.lib")

#pragma endregion

#pragma region �궨��

#define WINDOW_TITLEBARHEIGHT	32			//�������߶�
#define WINDOW_WIDTH			1400		//��Ϸ���ڿ��
#define WINDOW_HEIGHT			701  		//��Ϸ���ڸ߶�


#define STAGE_STARTMENU			0		//��ʼ�����ID
#define STAGE_1					1		//��һ����Ϸ������ID
#define STAGE_2                 2       //�ڶ�����Ϸ������ID
#define STAGE_3                 3       //��������Ϸ������ID
#define STAGE_LOSE              7
#define STAGE_WIN               8
#define STAGE_OVER              9

#define UNIT_SIZE_X				64		//��λ�Ŀ��
#define UNIT_SIZE_Y				64		//��λ�ĸ߶�
#define POLO_SIZE_X             60
#define POLO_SIZE_Y             61
#define PD_SIZE_X               32
#define PD_SIZE_Y               32
#define PD_SPEED                6.0
#define FF_SPEED                12.0
#define Maxhealth               100     //��λ���������ֵ
#define Maxenergy               100.0     //���޵��������
#define UNIT_LAST_FRAME			11		//��λ�Ķ���֡���ֵ

//��λ��Ӫ����
#define UNIT_SIDE_RED			10000	//�췽
#define UNIT_SIDE_BLUE			10001	//����


//��λ���Ͷ���
#define UNIT_TYPE_REAPER		0		//�ո���
#define UNIT_TYPE_CASTER		1		//ħ��ʦ
#define UNIT_TYPE_SABER			2		//��ʿ
#define UNIT_TYPE_SHIELDER		3		//����
#define UNIT_TYPE_HOPLITE		4		//��װ����
#define TIME_COUNT_DOWN         10000  //����һ�ĵ���ʱʱ��

//��λ״̬����
#define UNIT_STATE_HOLD			0		//��ֹ
#define UNIT_STATE_WALK			1		//����
#define UNIT_STATE_ATTACK		2		//����
#define FIRE_TOWER              0
#define ICE_TOWER              1
//��λ������
#define UNIT_DIRECT_RIGHT		0		//����
#define UNIT_DIRECT_LEFT		1		//����

//����
#define BG_NEW_COLUMNS          44      //��������
#define BG_NEW_ROWS             22      //��������
#define BG_NEW_CELL_WIDTH		32		//����������
#define BG_NEW_CELL_HEIGHT		32		//��������߶�

#define BG_TOWER_WIDTH          32      //���Ŀ��
#define BG_TOWER_HEIGHT         64      //���ĸ߶�

//��������
#define BUTTON_STARTGAME			1001	//��ʼ��Ϸ��ťID
#define BUTTON_CONTINUE             1002    //������Ϸ��ťID
#define BUTTON_RESTART              1003    //���¿�ʼ��ťID
#define BUTTON_INTRODUCTION         1004    //��Ϸ˵����ťID
#define BUTTON_MONEY                1005    //�鿴�����ĿID
#define BUTTON_POLO                 1006    //����ͼ���ID
#define BUTTON_PD                   1007    //�ڵ�ͼ���ID
#define BUTTON_PDD                  1008    //�ڵ�CDͼ���ID
#define BUTTON_NEXT                 1009    //��һ�ص�ID
#define BUTTON_INFO1                1010
#define BUTTON_INFO2                1011
#define BUTTON_INFO3                1012
#define BUTTON_INFO4                1013
#define BUTTON_STARTGAME_WIDTH		212		//��ʼ��Ϸ��ť���
#define BUTTON_STARTGAME_HEIGHT		76		//��ʼ��Ϸ��ť�߶�

#define TIMER_GAMETIMER				1		//��Ϸ��Ĭ�ϼ�ʱ��ID
#define TIMER_GAMETIMER_ELAPSE		30		//Ĭ�ϼ�ʱ��ˢ�¼���ĺ�����
#define UNIT_SPEED					2.0		//��λ�����ٶ�	


#pragma endregion

#pragma region �ṹ������

// �����ṹ��
struct Stage {
	int stageID;		//�������
	HBITMAP bg;			//����ͼƬ
	int timeCountDown;	//��Ϸʱ�䵹��ʱ
	bool timerOn;		//��ʱ���Ƿ����У���Ϸ�Ƿ���ͣ��
	int money;          //��ҽ��
};

struct ICE
{
	HBITMAP img;
	int x;
	int y;
	double vx;
	double vy;
};

// ��ť�ṹ��
struct Button {
	int buttonID;	//��ť���
	bool visible;	//��ť�Ƿ�ɼ�
	HBITMAP img;	//ͼƬ
	int x;			//����x
	int y;			//����y
	int width;		//���
	int height;		//�߶�
};

//���ṹ��
struct Tower {
	HBITMAP img;		//ͼƬ

	int frame_row;		//��ǰ��ʾ����ͼ��ĵڼ���
	int frame_column;	//��ǰ��ʾ����ͼ��ĵڼ���

	int height;			//���ĸ߶�
	int width;			//���Ŀ��

	int x;				//����x
	int y;				//����y

	int type;			//������
	int distance;		//������Χ
	int attack;         //�����˺�
	int level;
	int yes;
	//Unit* victim=NULL;       //���������˹����Ķ���
};

// ��λ�ṹ��
struct Unit {
	HBITMAP img;	//ͼƬ

	int frame_row;			//��ǰ��ʾ����ͼ��ĵڼ���
	int frame_column;		//��ǰ��ʾ����ͼ��ĵڼ���

	int* frame_sequence;		//��ǰ��֡����
	int frame_count;		//֡���еĳ���
	int frame_id;			//��ǰ��ʾ����֡���еĵڼ���


	int side;		//��λ��Ӫ
	int type;		//��λ����
	int state;		//��λ״̬
	int direction;	//��λ����
	int condition;
	int x;			//����x
	int y;			//����y
	double vx;		//�ٶ�x
	double vy;		//�ٶ�y
	int health;		//����ֵ
	int maxhealth;  //��ʼ����ֵ
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
	//int frame_number;//��ǰ��ʾ����ͼ��ĵڼ���
	int *frame_sequence;//��ǰ��֡����
	int frame_count;//֡���еĳ���
	int frame_id;//��ǰ��ʾ����֡���еĵڼ���
	int x;//��λ��ʾ��x����
	int y;//��λ��ʾ��y����
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

//TODO: �����Ϸ��Ҫ�ĸ��������ݣ����ש��ȣ�


#pragma endregion

#pragma region �¼�����������


// ��ʼ����Ϸ���庯��
void InitGame(HWND hWnd, WPARAM wParam, LPARAM lParam);

// ���̰����¼�������
void KeyDown(HWND hWnd, WPARAM wParam, LPARAM lParam);

// �����ɿ��¼�������
void KeyUp(HWND hWnd, WPARAM wParam, LPARAM lParam);

// ����ƶ��¼�������
void MouseMove(HWND hWnd, WPARAM wParam, LPARAM lParam);

// �����������¼�������
void LButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam);

void RButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam);
// �������ɿ��¼�������
void LButtonUp(HWND hWnd, WPARAM wParam, LPARAM lParam);
void RButtonUp(HWND hWnd, WPARAM wParam, LPARAM lParam);
// ��ʱ���¼�������
void TimerUpdate(HWND hWnd, WPARAM wParam, LPARAM lParam);

void drawdistance(int distance, int x, int y);
#pragma endregion

#pragma region ������Ϸ״̬����������

// ��Ӱ�ť����
Button* CreateButton(int buttonID, HBITMAP img, int width, int height, int x, int y);

// ��ӵ�λ����
Unit* CreateUnit(int side, int type, int x, int y, int health);

// ��ӷ���������
void CreateTowers(HWND hWnd, int x, int y, int type,int row,int column,int attack,int distance);
F* CreateF(int x, int y);
TD* CreateTD(int x, int y);
POLO* CreatePOLO(int x, int y, int health);
PD* CreatePD(int x, int y);
MIST* Createmist(int x, int y);
FOG* Createfog(int x, int y);
FF* CreateFF(int x, int y);
ICE* CreateICE(int x, int y);
// ��ʼ����������
void InitStage(HWND hWnd, int stageID);

// ˢ�µ�λ״̬����
void UpdateUnits(HWND hWnd);
void Drawmoney(int x, int y);
void DrawDeadline(int x, int y);

//��λ��Ϊ����
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
//TODO: �����Ϸ��Ҫ�ĸ��ຯ��


#pragma endregion

#pragma region ��ͼ��������

// ��ͼ����
void Paint(HWND hWnd);
void DrawTDHealthLine(int midx, int midy, int health, int maxhealth);
void DrawHealthLine(int midx, int midy, int health,int maxhealth);
void DrawPOLOLine(int midx, int midy, int health,int energy);
void DrawattackLine(int xbx, int xby, int towerx, int towery);
// ��ͼ��ƺ���
int** GetMap(int k);

// ��ʼ����������
HBITMAP InitBackGround(HWND hWnd, HBITMAP bmp_src,HBITMAP bmp_src1, HBITMAP bmp_tower);

#pragma endregion