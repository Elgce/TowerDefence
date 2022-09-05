// TowerDefense.cpp : 定义应用程序的入口点。


#include "TowerDefense.h"

using namespace std;



#pragma region 全局变量

#define MAX_LOADSTRING 100



// 全局变量:句柄=指针？
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名



HBITMAP bmp_Map;			//地图图像资源
HBITMAP bmp_Tower;          //塔图像资源
HBITMAP bmp_StartButton;	//开始按钮图像资源
HBITMAP bmp_Unit_Red;		//红方主角图像资源
HBITMAP bmp_Unit_Blue;		//蓝方主角图像资源
HBITMAP bmp_F;              //地火图标

HBITMAP bmp_Background;		//生成的背景图像
HBITMAP bmp_BackLOSE;       //生成失败背景图像
HBITMAP bmp_BackWIN;        //生成成功背景图像
HBITMAP bmp_CONTINUE;       //生成的继续游戏图标
HBITMAP bmp_BackRound2;     //生成第二关的背景图像
HBITMAP bmp_Back;
HBITMAP bmp_RESTART;        //生成重新开始的图标
HBITMAP bmp_INTRODUCTION;   //生成游戏说明的图标
HBITMAP bmp_Map1;           //生成瓦罗兰大陆背景
HBITMAP bmp_MAP2;           //生成诺手背景
HBITMAP bmp_MONEY;          //生成金币图标
HBITMAP bmp_POLOL;          //生成面朝左边的魄罗
HBITMAP bmp_PD;             //生成炮弹
HBITMAP bmp_FF;             //生成火花小普攻
HBITMAP bmp_ICE;
HBITMAP bmp_PDD;            //炮弹CD图片
HBITMAP bmp_MIST;           //烟雾图片
HBITMAP bmp_FOG;            //被炸图片
HBITMAP bmp_LOSE;           //you lose图片
HBITMAP bmp_WIN;            //you win图片
HBITMAP bmp_NEXT;            //下一关的图片
HBITMAP bmp_TOMATO;         //生成土豆图片
HBITMAP bmp_MENU;
HBITMAP bmp_INFO1;           //生成防御塔信息图片
HBITMAP bmp_INFO2;
HBITMAP bmp_INFO3;
HBITMAP bmp_INFO4;
Stage* currentStage = NULL; //当前场景状态
vector<Unit*> units;		//单位
vector<Button*> buttons;	//按钮   使用buttons.size()可以求出用了多少个button
vector<Tower*> towers;      //塔
vector<POLO*> polos;        //魄罗
vector<PD*> pds;
vector<TD*> tds;
vector<double> polox;
vector<double> poloy;
vector<double> mousex;
vector<double> mousey;//记录发射炮弹时鼠标POlo位置
vector<double> poloX;
vector<double> poloY;
vector<double> mousexx;
vector<double> mouseyy;
vector<double> mousx;
vector<double> mousy;
vector<double> px;
vector<double> py;
//记录发射普攻时鼠标位置
vector<MIST*> mists;
vector<FOG*> fogs;
vector<FF*> ffs;
vector<F*> fs;
vector<ICE*> ices;
int mouseX = 0;
int mouseY = 0;
int pass = 0;
int pdCountdown = TIME_COUNT_DOWN+151;
int ffCountdown = TIME_COUNT_DOWN + 8;
bool mouseDown = false;
bool mouseRdown = false;
bool keyUpDown = false;
bool keyDownDown = false;
bool keyLeftDown = false;
bool keyRightDown = false;
bool keyEscDown = false;
bool keyWDown = false;
bool keySDown = false;
bool keyADown = false;
bool keyDDown = false;
bool keyRDown = false;
bool keyGDown = false;
bool SpaceDown = false;
bool keyHDown = false;

//帧
int FRAMES_HOLD[] = { 0 };
int FRAMES_HOLD_COUNT = 1;
int FRAMES_WALK[] = { 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2 };
int FRAMES_WALK_COUNT = 16;
int FRAMES_ATTACK[] = { 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 };
int FRAMES_ATTACK_COUNT = 24;
int FRAMES_MIST[] = { 1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12,12 };
int FRAMES_MIST_COUNT = 24;
int FRAMES_FOG[] = { 1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12,12,13,13,14,14,15,15,16,16 };
int FRAMES_FOG_COUNT = 32;
int mapp[22][44];

// TODO: 在此添加其它全局变量

HDC HDC_MEMORY; // -> hdc_memBuf
HPEN hbBck = CreatePen(PS_SOLID, 4, RGB(200, 200, 200));
HPEN hbBar = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
HPEN hbBar1 = CreatePen(PS_SOLID, 8, RGB(255, 0, 0));
HPEN hbBlue1 = CreatePen(PS_SOLID, 8, RGB(0, 0, 255));
HPEN hbBlue = CreatePen(PS_SOLID, 3, RGB(0, 0, 255));
HPEN hbBck1 = CreatePen(PS_SOLID, 9, RGB(200, 200, 200));
HPEN hbyel = CreatePen(PS_SOLID, 4, RGB(255, 0, 255));
HPEN hbll = CreatePen(PS_SOLID, 2, RGB(255, 239, 213));
double const PI = acos(double(-1));
//函数“acos(X)”即return arccosx;




#pragma endregion

#pragma region Win32程序框架



// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此处放置代码。

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_TOWERDEFENSE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TOWERDEFENSE));

    MSG msg;

    // 主消息循环:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_TOWERDEFENSE);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

	return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)//在WIN32中由于内存区域分隔，故模块句柄等价于实例句柄，均使用hInstance表示
{
   hInst = hInstance; // 将实例句柄存储在全局变量中

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, //szWincowClass:窗口类名称;szTitle:窗口标题；
	   WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX, // 设置窗口样式，不可改变大小，不可最大化（API函数CreateWindowW中只可以固定窗口大小）
	   CW_USEDEFAULT, //初始x坐标
	   CW_USEDEFAULT, //初始y坐标 如果该参数被设为 CW_USEDEFAULT 则系统为窗口选择缺省的左上角坐标并忽略 y 参数，CW_USEDEFAULT 只对层叠窗口有效，如果为弹出式窗口或子窗口设定，则 x 和 y 参数被设为零。
	   WINDOW_WIDTH, //初始x方向尺寸
	   WINDOW_HEIGHT + WINDOW_TITLEBARHEIGHT, //初始y方向尺寸
	   nullptr, //hWndParent父窗口句柄
	   nullptr,//hMenu窗口菜单句柄
	   hInstance,//程序实例句柄
	   nullptr);//创建参数

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_CREATE:
		// 初始化游戏窗体
		InitGame(hWnd, wParam, lParam);
		break;
	case WM_KEYDOWN:
		// 键盘按下事件
		KeyDown(hWnd, wParam, lParam);
		break;
	case WM_KEYUP:
		// 键盘松开事件
		KeyUp(hWnd, wParam, lParam);
		break;
	case WM_MOUSEMOVE:
		// 鼠标移动事件
		MouseMove(hWnd, wParam, lParam);
		break;
	case WM_LBUTTONDOWN:
		// 鼠标左键按下事件
		LButtonDown(hWnd, wParam, lParam);
		break;
	case WM_RBUTTONDOWN:
		RButtonDown(hWnd, wParam, lParam);
		break;
	case WM_LBUTTONUP:
		// 鼠标左键松开事件
		LButtonUp(hWnd, wParam, lParam);
		break;
	case WM_TIMER:
		// 定时器事件
		if (currentStage != NULL && currentStage->timerOn) TimerUpdate(hWnd, wParam, lParam);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_PAINT: {
		Paint(hWnd);

		break;
	}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


#pragma endregion



#pragma region 事件处理函数
// 初始化游戏窗体函数：加载图像资源；添加按钮；初始化背景；初始化开始场景；初始化主计时器；键盘按下松开处理函数；鼠标移动；按钮；建塔；
void InitGame(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	//加载图像资源
	bmp_Map = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_MAP));
	bmp_Map1 = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_MAP1));
	bmp_Tower = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_TOWER));
	bmp_StartButton = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_START));
	bmp_Unit_Red = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_RED));
	bmp_Unit_Blue = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_BLUE));
	bmp_CONTINUE = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_CONTINUE));
	bmp_RESTART = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_RESTART));
	bmp_INTRODUCTION = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_INTRODUCTION));
	bmp_MAP2 = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_MAP2));
	bmp_MENU = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_MENU));
	bmp_MONEY= LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_MONEY));
	bmp_POLOL = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_POLOL));
	bmp_PD = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_PD));
	bmp_FF = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_FIRE));
	bmp_PDD = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_PDD));
	bmp_MIST= LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_MIST));
	bmp_FOG = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_FOG));
	bmp_LOSE= LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_LOSE));
	bmp_WIN = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_WIN));
	bmp_NEXT = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_NEXT));
	bmp_TOMATO = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_TOMATO));
	bmp_F = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_FF));
	bmp_INFO1= LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP1));
	bmp_INFO2 = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP2));
	bmp_INFO3 = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP3));
	bmp_INFO4 = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP4));
	bmp_ICE = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_ICE));
	//添加按钮

	Button* startButton = CreateButton(BUTTON_STARTGAME, bmp_StartButton, BUTTON_STARTGAME_WIDTH, BUTTON_STARTGAME_HEIGHT,
		(WINDOW_WIDTH - BUTTON_STARTGAME_WIDTH) / 2, (WINDOW_HEIGHT - BUTTON_STARTGAME_HEIGHT) / 2);//BUTTON_STARTGAME_WIDTH为游戏开始的按钮高度
	buttons.push_back(startButton);
	//操作此处参数可以实现“Start”按钮位置的移动
	Button* startButton1 = CreateButton(BUTTON_CONTINUE, bmp_CONTINUE, 300, 106,
		(WINDOW_WIDTH - 300) / 2, (WINDOW_HEIGHT - 106) / 4);
    buttons.push_back(startButton1);
	//BUTTON_STARTGAME_WIDTH为游戏开始的按钮高度
	Button* startButton2 = CreateButton(BUTTON_RESTART, bmp_RESTART, 300, 106,
		(WINDOW_WIDTH - 300) / 2, 2*(WINDOW_HEIGHT - 106) / 4);
	buttons.push_back(startButton2);
	Button* startButton3 = CreateButton(BUTTON_INTRODUCTION, bmp_INTRODUCTION, 300, 106,
		(WINDOW_WIDTH - 300) / 2, 3 * (WINDOW_HEIGHT - 106) / 4);
	buttons.push_back(startButton3);
	Button* startButton4 = CreateButton(BUTTON_MONEY, bmp_MONEY, 40, 38,
		(0),(WINDOW_HEIGHT-50));
	buttons.push_back(startButton4);
	Button* startButton5 = CreateButton(BUTTON_POLO, bmp_POLOL, 60, 61,
		(WINDOW_WIDTH - 120), (10));
	buttons.push_back(startButton5);
	Button* startButton6 = CreateButton(BUTTON_PD, bmp_PD, 32, 32,
		(WINDOW_WIDTH - 120), (100));
	buttons.push_back(startButton6);
	Button* startButton7 = CreateButton(BUTTON_PDD, bmp_PDD, 32, 32,
		(WINDOW_WIDTH - 120), (100));
	buttons.push_back(startButton7);
	Button* startButton8 = CreateButton(BUTTON_NEXT, bmp_NEXT, 300, 106,
		(WINDOW_WIDTH - 300), (WINDOW_HEIGHT - 106));
	buttons.push_back(startButton8);
	Button* startButton9 = CreateButton(BUTTON_INFO1, bmp_INFO1, 353, 386,
		(0), ((WINDOW_HEIGHT - 386) / 2)+100);
	buttons.push_back(startButton9);
	Button* startButton10 = CreateButton(BUTTON_INFO2, bmp_INFO2, 353, 386,
		(0), ((WINDOW_HEIGHT - 386) / 2) + 100);
	buttons.push_back(startButton10);
	Button* startButton11 = CreateButton(BUTTON_INFO3, bmp_INFO3, 353, 386,
		(0), ((WINDOW_HEIGHT - 386) / 2) + 100);
	buttons.push_back(startButton11);
	Button* startButton12 = CreateButton(BUTTON_INFO4, bmp_INFO4, 353, 386,
		(0), ((WINDOW_HEIGHT - 386) / 2) + 100);
	buttons.push_back(startButton12);
	//通过上文复制，可以实现在新的位置出现“Start按钮”

	//初始化背景
	bmp_Background = InitBackGround(hWnd, bmp_Map, bmp_Map1, bmp_Tower);//InitBackGround用于初始化背景
	bmp_BackLOSE = InitBackGround(hWnd, bmp_Map, bmp_LOSE, bmp_Tower);
	bmp_BackWIN = InitBackGround(hWnd, bmp_Map, bmp_WIN, bmp_Tower);
	bmp_Back = InitBackGround(hWnd, bmp_Map, bmp_MENU, bmp_Tower);
	bmp_BackRound2 = InitBackGround(hWnd, bmp_Map, bmp_MAP2, bmp_Tower);
	//初始化开始场景
	InitStage(hWnd, STAGE_STARTMENU);
	//初始化主计时器
	SetTimer(hWnd, TIMER_GAMETIMER, TIMER_GAMETIMER_ELAPSE, NULL);//hWnd表示窗口句柄；TIMER_GAMETIMER表示计时器的ID（此处#define =1）；TIMER_GAMETIMER_ELAPSE为过多少ms跳转一次（=30）；NULL默认；
}

// 键盘按下事件处理函数
void KeyDown(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	switch (wParam) {
	case VK_UP:
		keyUpDown = true;
		break;
	case VK_DOWN:
		keyDownDown = true;
		break;
	case VK_LEFT:
		keyLeftDown = true;
		break;
	case VK_RIGHT:
		keyRightDown = true;
		break;
	case VK_ESCAPE:
		keyEscDown = true;
		if (currentStage->stageID != STAGE_STARTMENU)//此为开始画面的ID
		{
			for (int i = 0; i < buttons.size(); i++)
			{
				Button* button = buttons[i];
				if (button->buttonID == BUTTON_CONTINUE || button->buttonID == BUTTON_RESTART || button->buttonID==BUTTON_INTRODUCTION)
					button->visible = true;
				else button->visible = false;
			}
		}
		break;
	case 0x57://0x57表示按钮W
		keyWDown = true;
		break;
	case 0x41://表示按钮A
		keyADown = true;
		break;
	case 0x53://按钮S
		keySDown = true;
		break;
	case 0x44://按钮D
		keyDDown = true;
		break;
	case 0x52:
		keyRDown = true;
		break;
	case 0x47:
		keyGDown = true;
		break;
	case VK_SPACE:
		SpaceDown = true;
		break;
	case 0x48:
		keyHDown = true;
		break;
	default:
		break;
	}
}

// 键盘松开事件处理函数
void KeyUp(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	// TODO
	switch (wParam) {
	case VK_UP:
		keyUpDown = false;
		break;
	case VK_DOWN:
		keyDownDown = false;
		break;
	case VK_LEFT:
		keyLeftDown = false;
		break;
	case VK_RIGHT:
		keyRightDown = false;
		break;
	case VK_ESCAPE:
		keyEscDown = false;
		PlaySound(NULL, NULL, NULL);
		currentStage->timerOn = false;//暂停计时器只是暂停了绘制，还要防止按钮和建塔
		break;
	case 0x57://0x57表示按钮W
		keyWDown = false;
		break;
	case 0x41://表示按钮A
		keyADown = false;
		break;
	case 0x53://按钮S
		keySDown = false;
		break;
	case 0x52:
		keyRDown = false;
		break;
	case 0x44://按钮D
		keyDDown = false;
		break;
	case 0x47:
		keyGDown = false;
		break;
	case VK_SPACE:
		SpaceDown = false;
		break;
	case 0x48:
		keyHDown = false;
		break;
	default:
		break;
	}
}

// 鼠标移动事件处理函数
void MouseMove(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	mouseX = LOWORD(lParam);
	mouseY = HIWORD(lParam);
	
	for (int i = 0; i < towers.size(); i++) towers[i]->yes = 0;

	int** map = GetMap(currentStage->stageID);
	int kk; Button* button = NULL; Tower* tower=NULL;
	kk = 0; 
	for (int k = 0; k < buttons.size(); k++)
	{
		if (buttons[k]->buttonID == BUTTON_INFO1)
			button = buttons[k];
	}
	for (int i = 0; i < BG_NEW_ROWS; i++)
	{
		for (int j = 0; j < BG_NEW_COLUMNS; j++)
		{
			if (map[i][j] == 2 && mapp[i][j] == 1)
			{	
				if (mouseX > j * BG_NEW_CELL_WIDTH
					&& mouseX < (j + 1) * BG_NEW_CELL_WIDTH
					&& mouseY > i * BG_NEW_CELL_HEIGHT
					&& mouseY < (i + 1) * BG_NEW_CELL_HEIGHT)
				{
					button->visible = true; kk = 1;
					for (int cc = 0; cc < buttons.size(); cc++)
						if (buttons[cc]->buttonID == BUTTON_INFO2 || buttons[cc]->buttonID == BUTTON_INFO3 || buttons[cc]->buttonID == BUTTON_INFO4)
							buttons[cc]->visible = false;
					for (int mm = 0; mm < towers.size(); mm++)
					{
						if (towers[mm]->x == j * BG_NEW_CELL_WIDTH && towers[mm]->y == i * BG_NEW_CELL_HEIGHT)
						{
							towers[mm]->yes = 1;
							tower = towers[mm]; 
						}
					}
				}
			}
			
		}
	}
	if (kk == 0)
	{
		button->visible = false;
	}

	kk = 0;
	for (int k = 0; k < buttons.size(); k++)
	{
		if (buttons[k]->buttonID == BUTTON_INFO2)
			button = buttons[k];
	}
	for (int i = 0; i < BG_NEW_ROWS; i++)
	{
		for (int j = 0; j < BG_NEW_COLUMNS; j++)
		{
			if (map[i][j] == 2 && mapp[i][j] == 2)
			{
				if (mouseX > j * BG_NEW_CELL_WIDTH
					&& mouseX < (j + 1) * BG_NEW_CELL_WIDTH
					&& mouseY > i * BG_NEW_CELL_HEIGHT
					&& mouseY < (i + 1) * BG_NEW_CELL_HEIGHT)
				{
					button->visible = true; kk = 1;
					for (int cc = 0; cc < buttons.size(); cc++)
						if (buttons[cc]->buttonID == BUTTON_INFO1 || buttons[cc]->buttonID == BUTTON_INFO3 || buttons[cc]->buttonID == BUTTON_INFO4)
							buttons[cc]->visible = false;
					for (int mm = 0; mm < towers.size(); mm++)
					{
						if (towers[mm]->x == j * BG_NEW_CELL_WIDTH && towers[mm]->y == i * BG_NEW_CELL_HEIGHT)
						{
							towers[mm]->yes = 1;
							tower = towers[mm];
						}
					}
				}
			}
		}
	}
	if (kk == 0) button->visible = false;

	kk = 0;
	for (int k = 0; k < buttons.size(); k++)
	{
		if (buttons[k]->buttonID == BUTTON_INFO3)
			button = buttons[k];
	}
	for (int i = 0; i < BG_NEW_ROWS; i++)
	{
		for (int j = 0; j < BG_NEW_COLUMNS; j++)
		{
			if (map[i][j] == 2 && mapp[i][j] == 3)
			{
				if (mouseX > j * BG_NEW_CELL_WIDTH
					&& mouseX < (j + 1) * BG_NEW_CELL_WIDTH
					&& mouseY > i * BG_NEW_CELL_HEIGHT
					&& mouseY < (i + 1) * BG_NEW_CELL_HEIGHT)
				{
					button->visible = true; kk = 1;
					for (int cc = 0; cc < buttons.size(); cc++)
						if (buttons[cc]->buttonID == BUTTON_INFO1 || buttons[cc]->buttonID == BUTTON_INFO2 || buttons[cc]->buttonID == BUTTON_INFO4)
							buttons[cc]->visible = false;
					for (int mm = 0; mm < towers.size(); mm++)
					{
						if (towers[mm]->x == j * BG_NEW_CELL_WIDTH && towers[mm]->y == i * BG_NEW_CELL_HEIGHT)
						{
							towers[mm]->yes = 1;
							tower = towers[mm];
						}
					}
				}
			}
		}
	}
	if (kk == 0) button->visible = false;

	kk = 0;
	for (int k = 0; k < buttons.size(); k++)
	{
		if (buttons[k]->buttonID == BUTTON_INFO4)
			button = buttons[k];
	}
	for (int i = 0; i < BG_NEW_ROWS; i++)
	{
		for (int j = 0; j < BG_NEW_COLUMNS; j++)
		{
			if (map[i][j] == 2 && mapp[i][j] == 4)
			{
				if (mouseX > j * BG_NEW_CELL_WIDTH
					&& mouseX < (j + 1) * BG_NEW_CELL_WIDTH
					&& mouseY > i * BG_NEW_CELL_HEIGHT
					&& mouseY < (i + 1) * BG_NEW_CELL_HEIGHT)
				{
					button->visible = true; kk = 1;
					for (int cc = 0; cc < buttons.size(); cc++)
						if (buttons[cc]->buttonID == BUTTON_INFO1 || buttons[cc]->buttonID == BUTTON_INFO3 || buttons[cc]->buttonID == BUTTON_INFO2)
							buttons[cc]->visible = false;
					for (int mm = 0; mm < towers.size(); mm++)
					{
						if (towers[mm]->x == j * BG_NEW_CELL_WIDTH && towers[mm]->y == i * BG_NEW_CELL_HEIGHT)
						{
							towers[mm]->yes = 1;
							tower = towers[mm];
						}
					}
				}
			}
		}
	}
	if (kk == 0) button->visible = false;

	for (int i = 0; i < BG_NEW_ROWS; i++) free(map[i]);
	free(map);
}
//鼠标右键按下函数
void RButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	mouseX = LOWORD(lParam);
	mouseY = HIWORD(lParam);
	mouseRdown = true;

	if (currentStage->stageID > STAGE_STARTMENU)
	{
		int** map = GetMap(currentStage->stageID);
		for (int i = 0; i < BG_NEW_ROWS; i++)
		{
			for (int j = 0; j < BG_NEW_COLUMNS; j++)
			{
				if (map[i][j] == 2)
				{
					if (mouseX > j * BG_NEW_CELL_WIDTH
						&& mouseX < (j + 1) * BG_NEW_CELL_WIDTH
						&& mouseY > i * BG_NEW_CELL_HEIGHT
						&& mouseY < (i + 1) * BG_NEW_CELL_HEIGHT)
					{
						if (mapp[i][j] == 0 && currentStage->money >= 40)
						{
							CreateTowers(hWnd, j * BG_NEW_CELL_WIDTH, i * BG_NEW_CELL_HEIGHT, ICE_TOWER, 0, 7, 20, 100);
							currentStage->money -= 40;
							mapp[i][j]++;
						}
						
					}
				}
				
			}
		}

		for (int i = 0; i < BG_NEW_ROWS; i++) free(map[i]);
		free(map);
	}

	if (currentStage->stageID > STAGE_STARTMENU && SpaceDown==true) 
	{
		int** map = GetMap(currentStage->stageID);
		for (int i = 0; i < BG_NEW_ROWS; i++) {
			for (int j = 0; j < BG_NEW_COLUMNS; j++) 
			{
				if (map[i][j] == 2 && mapp[i][j] !=0) 
				{
					if (mouseX > j * BG_NEW_CELL_WIDTH
						&& mouseX < (j + 1) * BG_NEW_CELL_WIDTH
						&& mouseY > i * BG_NEW_CELL_HEIGHT
						&& mouseY < (i + 1) * BG_NEW_CELL_HEIGHT) 
					{
						for (int k = 0; k < towers.size(); k++)
						{
							if (towers[k]->x == j * BG_NEW_CELL_WIDTH && towers[k]->y == i * BG_NEW_CELL_HEIGHT )
							{
								Tower* tower;
								tower = towers[k];
								towers.erase(towers.begin() + k);
								free(tower);
							}
						}
						currentStage->money += 20;
						mapp[i][j]=0;
					}
				}
			}
		}
		
		for (int i = 0; i < BG_NEW_ROWS; i++) free(map[i]);
		free(map);

	}
}
// 鼠标左键按下事件处理函数
void LButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	mouseX = LOWORD(lParam);
	mouseY = HIWORD(lParam);
	mouseDown = true;

	// 按钮处理
	for (int i = 0; i < buttons.size(); i++) {
		Button* button = buttons[i];
		if (button->visible) {
			if (button->x <= mouseX
				&& button->x + button->width >= mouseX
				&& button->y <= mouseY
				&& button->y + button->height >= mouseY) {
				switch (button->buttonID) {
				case BUTTON_STARTGAME:
					//TODO：判断进入哪个关卡
					InitStage(hWnd, STAGE_1);
					//InitStage(hWnd,STAGE_2);
					break;
					//重启计时器
				case BUTTON_CONTINUE:
					PlaySound((LPCTSTR)IDR_WAVE_LOL, NULL, SND_RESOURCE | SND_ASYNC);
					currentStage->timerOn = true;
					for (int i = 0; i < buttons.size(); i++)
					{
						Button* button = buttons[i];
						if (button->buttonID == BUTTON_CONTINUE || button->buttonID == BUTTON_RESTART || button->buttonID == BUTTON_INTRODUCTION)
							button->visible = false;
						else if (currentStage->stageID == STAGE_WIN && button->buttonID == BUTTON_NEXT)
							button->visible = true;
					}
					break;


				case BUTTON_NEXT:
					currentStage->timerOn = false;
					currentStage->stageID = STAGE_2;
					InitStage(hWnd, STAGE_2);
					pass = 1;
					break;


				case BUTTON_RESTART:
					if (pass == 0)
					{
						InitStage(hWnd, STAGE_STARTMENU);
						currentStage->timeCountDown = TIME_COUNT_DOWN;
						pdCountdown = TIME_COUNT_DOWN + 151;
						ffCountdown = TIME_COUNT_DOWN +8;
						//currentStage->timerOn = true;
						for (int i = 0; i < buttons.size(); i++)
						{
							Button* button = buttons[i];
							if (button->buttonID == BUTTON_CONTINUE || button->buttonID == BUTTON_RESTART || button->buttonID == BUTTON_INTRODUCTION)
								button->visible = false;
						}
						break;
					}
					else
					{
						currentStage->timerOn = false;
						currentStage->stageID = STAGE_WIN;
						InitStage(hWnd, STAGE_WIN);
						break;
					}
				case BUTTON_INTRODUCTION:
					MessageBox(NULL, _T("Hello~\n这是一个很简单的塔防游戏\nTowerDefence Version 0.1.4游戏说明\n已经实现功能：\nWASD完成魄罗上下左右\nR发射炮弹可以杀死遇到的第一个小兵（炮弹路线为当前魄罗位置和鼠标位置连成的直线）\nG发射小火苗普攻对遇到的第一个小兵造成伤害H发射冰攻击可以减速小兵\n金币自动增加，40金币可以造一座塔\n杀死小兵加金币，金币余额显示在左下角，鼠标左击基座就可以建火属性塔，右击冰属性,再次左击50金币升到2级100到3级，第二关可以300到4级）\n鼠标右击+空格键防御塔可以拆除获得20金币\n如果有小兵走完赛道就会显示游戏失败\n左上角显示游戏倒计时，倒计时走完游戏胜利\n任何时候按ESC可以出现图标“继续游戏”“重新开始”“游戏说明”，点击即有相关功能\n敌方血量会和时间增长呈正比\n左击地面生成地鼠路障(10金币)\n约13s随机刷新一个火苗，左击生成地火"), _T("游戏说明"), NULL);
					break;
				case BUTTON_MONEY:
				{
					wchar_t ss[100];
					wsprintf(ss, L"The money you left is:%d\n", currentStage->money);
					MessageBox(NULL, ss,_T("金币余量"), NULL);
					break;
				}
				}
			}
		}
	}

	// 建塔处理
	if (currentStage->stageID > STAGE_STARTMENU) 
	{
		int** map = GetMap(currentStage->stageID);
		for (int i = 0; i < BG_NEW_ROWS; i++)
		{
			for (int j = 0; j < BG_NEW_COLUMNS; j++)
			{
				if (map[i][j] == 0 && currentStage->money >= 15 && mapp[i][j] == 0)
				{
					if (mouseX > j * BG_NEW_CELL_WIDTH
						&& mouseX < (j + 1) * BG_NEW_CELL_WIDTH
						&& mouseY > i * BG_NEW_CELL_HEIGHT
						&& mouseY < (i + 1) * BG_NEW_CELL_HEIGHT)
					{
						tds.push_back(CreateTD(j * BG_NEW_CELL_WIDTH, i * BG_NEW_CELL_HEIGHT));
						currentStage->money -= 15;
						mapp[i][j] = 1;
					}
				}
			}
		}
		for (int i = 0; i < BG_NEW_ROWS; i++) 
		{
			for (int j = 0; j < BG_NEW_COLUMNS; j++) 
			{
				if (map[i][j] == 2) 
				{
					if (mouseX > j * BG_NEW_CELL_WIDTH
						&& mouseX < (j + 1) * BG_NEW_CELL_WIDTH
						&& mouseY > i * BG_NEW_CELL_HEIGHT
						&& mouseY < (i + 1) * BG_NEW_CELL_HEIGHT)
					{
						if (mapp[i][j] == 0 && currentStage->money >= 40)
						{
							CreateTowers(hWnd, j * BG_NEW_CELL_WIDTH, i * BG_NEW_CELL_HEIGHT, FIRE_TOWER, 0, 1, 20, 100);
							currentStage->money -= 40;
							mapp[i][j]++;
						}
						else if (mapp[i][j] == 1 && currentStage->money >= 50)
						{
							for (int k = 0; k < towers.size(); k++)
							{
								if (towers[k]->x == j * BG_NEW_CELL_WIDTH && towers[k]->y == i * BG_NEW_CELL_HEIGHT)
								{
									if (towers[k]->type == FIRE_TOWER)
									{
										towers[k]->distance = 105;
										mapp[i][j]++;
										towers[k]->frame_row = 5;
										towers[k]->frame_column = 3;
										currentStage->money -= 50;
										towers[k]->level++;
									}
									else if (towers[k]->type == ICE_TOWER)
									{
										towers[k]->distance = 105;
										mapp[i][j]++;
										towers[k]->frame_row = 6;
										towers[k]->frame_column = 3;
										currentStage->money -= 50;
										towers[k]->level++;
									}
								}
							}
						}
						else if (mapp[i][j] == 2 && currentStage->money >= 100)
						{
							for (int k = 0; k < towers.size(); k++)
							{
								if (towers[k]->x == j * BG_NEW_CELL_WIDTH && towers[k]->y == i * BG_NEW_CELL_HEIGHT)
								{
									if (towers[k]->type == FIRE_TOWER)
									{
										towers[k]->distance = 108;
										towers[k]->attack = 25;
										mapp[i][j]++;
										towers[k]->frame_row = 6;
										towers[k]->frame_column = 7;
										currentStage->money -= 100;
										towers[k]->level++;
									}
									else if (towers[k]->type == ICE_TOWER)
									{
										towers[k]->distance = 108;
										towers[k]->attack = 25;
										mapp[i][j]++;
										towers[k]->frame_row = 5;
										towers[k]->frame_column = 1;
										currentStage->money -= 100;
										towers[k]->level++;
									}
								}
							}
						}
						else if (mapp[i][j] == 3 && currentStage->money >= 300 && currentStage->stageID == STAGE_2)
						{
							for (int k = 0; k < towers.size(); k++)
							{
								if (towers[k]->x == j * BG_NEW_CELL_WIDTH && towers[k]->y == i * BG_NEW_CELL_HEIGHT)
								{
									if (towers[k]->type==FIRE_TOWER)
								{
									towers[k]->distance = 111;
									towers[k]->attack = 25;
									mapp[i][j]++;
									towers[k]->width = towers[k]->width * 2;
									towers[k]->frame_row = 6;
									towers[k]->frame_column = 5;
									currentStage->money -= 300;
									towers[k]->level++;
								}
									else if (towers[k]->type == ICE_TOWER)
									{
										towers[k]->distance = 111;
										towers[k]->attack = 25;
										mapp[i][j]++;
										towers[k]->width = towers[k]->width * 2;
										towers[k]->frame_row = 5;
										towers[k]->frame_column = 5;
										currentStage->money -= 300;
										towers[k]->level++;
									}

								}
							}
						}
					}
				}
				else if (map[i][j] == 0 && mapp[i][j] == 2)
				{
					if (mouseX > j * BG_NEW_CELL_WIDTH
						&& mouseX < (j + 1) * BG_NEW_CELL_WIDTH
						&& mouseY > i * BG_NEW_CELL_HEIGHT
						&& mouseY < (i + 1) * BG_NEW_CELL_HEIGHT)
					{
						for (int k = 0; k < fs.size(); k++)
						{
							if (fs[k]->x == j * BG_NEW_CELL_WIDTH && fs[k]->y == i * BG_NEW_CELL_HEIGHT)
							{
								F* f = fs[k];
								for (int m = -1; m <= 1; m++)
									for (int n = -1; n <= 1; n++)
									{
										ffs.push_back(CreateFF(f->x + m*8+16, f->y + n*8+16));
										poloX.push_back(f->x + m*8+16);
										poloY.push_back(f->y + n*8+16);
										mousexx.push_back(f->x + m*8+16);
										mouseyy.push_back(f->y + n*8+16);
									}
								mapp[i][j] = 0;
								fs.erase(fs.begin() + k);
								free(f);
							}
						}
					}
				}
			}
		}
		
		for (int i = 0; i < BG_NEW_ROWS; i++) free(map[i]);
		free(map);
	}
}
	// 鼠标左键松开事件处理函数
	void LButtonUp(HWND hWnd, WPARAM wParam, LPARAM lParam) {
		mouseX = LOWORD(lParam);
		mouseY = HIWORD(lParam);
		mouseDown = false;
	}

	void RButtonUp(HWND hWnd, WPARAM wParam, LPARAM lParam)
	{
		mouseX = LOWORD(lParam);
		mouseY = HIWORD(lParam);
		mouseRdown = false;
	}

	// 定时器事件处理函数
	void TimerUpdate(HWND hWnd, WPARAM wParam, LPARAM lParam) {
		UpdateUnits(hWnd);
		currentStage->timeCountDown -= 1;
		if (currentStage->stageID == STAGE_1)
		{
			if (currentStage->timeCountDown % 50 == 0 &&
				(
				(currentStage->timeCountDown <= 10000 && currentStage->timeCountDown >= 9900) ||
					(currentStage->timeCountDown <= 9700 && currentStage->timeCountDown >= 9600) ||
					(currentStage->timeCountDown <=9500 && currentStage->timeCountDown>=9000) ||
					(currentStage->timeCountDown <=8800 && currentStage->timeCountDown>=7800) ||
					(currentStage->timeCountDown<=7700 && currentStage->timeCountDown>=6900) ||
					(currentStage->timeCountDown <= 6800 && currentStage->timeCountDown >= 5450)
					)
				)
			{
				if (currentStage->timeCountDown % 100 == 0)
					units.push_back(CreateUnit(UNIT_SIDE_BLUE, UNIT_TYPE_CASTER, 0, 170, 90*((11000-currentStage->timeCountDown)/800)));
				else
					units.push_back(CreateUnit(UNIT_SIDE_RED, UNIT_TYPE_SABER, 0, 170, 90 * ((11000-currentStage->timeCountDown)/ 800)));
			}
			if (currentStage->timeCountDown < 4970)
		    {
			   currentStage->timerOn = false;
			   InitStage(hWnd, STAGE_WIN);
		     }
		}
		
		else if (currentStage->stageID == STAGE_2)
		{
			if (currentStage->timeCountDown % 25 == 0 &&
				(
				(currentStage->timeCountDown <= 10000 && currentStage->timeCountDown >= 9900) ||
					(currentStage->timeCountDown <= 9700 && currentStage->timeCountDown >= 9600) ||
					(currentStage->timeCountDown <= 9500 && currentStage->timeCountDown >= 9000) ||
					(currentStage->timeCountDown <= 8800 && currentStage->timeCountDown >= 7800) ||
					(currentStage->timeCountDown <= 7700 && currentStage->timeCountDown >= 6900) ||
					(currentStage->timeCountDown <= 6800 && currentStage->timeCountDown >= 4800) ||
					(currentStage->timeCountDown <= 4600 && currentStage->timeCountDown >= 4000) ||
					(currentStage->timeCountDown <= 3800 && currentStage->timeCountDown >= 400)
					)
				)
			{
				if (currentStage->timeCountDown % 50 == 0)
					units.push_back(CreateUnit(UNIT_SIDE_BLUE, UNIT_TYPE_CASTER, 0, 145, 110 * ((11000-currentStage->timeCountDown) / 500)));
				else
					units.push_back(CreateUnit(UNIT_SIDE_RED, UNIT_TYPE_SABER, 0, 145, 110 * ((11000-currentStage->timeCountDown) / 500)));
			}
			if (currentStage->timeCountDown < 50)
			{
				currentStage->timerOn = false;
				InitStage(hWnd, STAGE_OVER);
			}
		}
		if (currentStage->stageID == STAGE_1 || currentStage->stageID == STAGE_2)
		{
			if (currentStage->timeCountDown % 500 == 0)
			{
				int** map = GetMap(currentStage->stageID);
				int t = 0;
				for (int i = 0; i < BG_NEW_ROWS; i++)
				{
					for (int j = 0; j < BG_NEW_COLUMNS; j++)
					{
						if (map[i][j] == 0 && mapp[i][j] == 0) t++;
					}
				}
				srand(unsigned(time(NULL)));
				int kk = rand() % t; int p = 0;
				for (int i = 0; i < BG_NEW_ROWS; i++)
				{
					for (int j=0;j<BG_NEW_COLUMNS;j++)
					{
						if (map[i][j] == 0 && mapp[i][j] == 0)
						{
							p++;
							if (p == kk)
							{
								fs.push_back(CreateF(j * BG_NEW_CELL_WIDTH, i * BG_NEW_CELL_HEIGHT));
								mapp[i][j] = 2; break;
							}
						}
					}
				}
				for (int i = 0; i < BG_NEW_ROWS; i++) free(map[i]);
				free(map);
			}
		}
			
		if (currentStage->stageID != STAGE_STARTMENU) {
			if (currentStage->timeCountDown % 100 == 0) {
				currentStage->money++;
			}
		}
		//刷新显示
		InvalidateRect(hWnd, NULL, FALSE);
	}


#pragma endregion



#pragma region 其它游戏状态处理函数



//TODO: 添加游戏需要的更多函数

// 添加按钮函数
Button* CreateButton(int buttonID, HBITMAP img, int width, int height, int x, int y) {
	Button* button = new Button();//创建新Button 
	button->buttonID = buttonID;//输入按钮编号
	button->img = img;//存入Button图案
	button->width = width;
	button->height = height;
	button->x = x;
	button->y = y;
	button->visible = false;
	return button;
}
//添加POLO函数
POLO* CreatePOLO(int x, int y, int health)
{
	POLO* polo = new POLO();
	polo->x = x;
	polo->y = y;
	polo->health = health;
	polo->state = UNIT_STATE_HOLD;
	polo->img = bmp_POLOL;
	polo->ax = polo->ay = 0;
	polo->vx = 0;
	polo->vy = 0;
	polo->energy = Maxenergy;
	return polo;
}
//添加炮弹函数
PD* CreatePD(int x, int y)
{
	PD* pd = new PD();
	pd->x = x;
	pd->y = y;
	pd->img = bmp_PD;
	return pd;
}
FF* CreateFF(int x, int y)
{
	FF* ff = new FF();
	ff->x = x;
	ff->y = y;
	ff->img = bmp_FF;
	return ff;
}
ICE* CreateICE(int x, int y)
{
	ICE* ice = new ICE();
	ice->x = x;
	ice->y = y;
	ice->img = bmp_ICE;
	return ice;
}
//添加烟雾函数
MIST* Createmist(int x, int y)
{
	MIST* mist = new MIST();
	mist->img = bmp_MIST;
	mist->x = x;
	mist->y = y;
	mist->frame_sequence = FRAMES_MIST;
	mist->frame_count = FRAMES_MIST_COUNT;
	mist->frame_id = 0;
	return mist;
}
FOG* Createfog(int x, int y)
{
	FOG* fog = new FOG();
	fog->img = bmp_FOG;
	fog->x = x;
	fog->y = y;
	fog->frame_id = 0;
	fog->frame_count = FRAMES_FOG_COUNT;
	fog->frame_sequence = FRAMES_FOG;
	return fog;
}
// 添加主角函数
Unit* CreateUnit(int side, int type, int x, int y, int health) {
	Unit* unit = new Unit();
	unit->side = side;
	if (side == UNIT_SIDE_RED) {
		unit->img = bmp_Unit_Red;
		
	}
	else if (side == UNIT_SIDE_BLUE) {
		unit->img = bmp_Unit_Blue;
	}

    unit->direction = UNIT_DIRECT_RIGHT;

	unit->type = type;
	unit->state = UNIT_STATE_WALK;
	unit->condition = 0;
	unit->frame_row = type;
	unit->frame_column = UNIT_LAST_FRAME * unit->direction;

	unit->frame_sequence = FRAMES_HOLD;
	unit->frame_count = FRAMES_HOLD_COUNT;
	unit->frame_id = 0;

	unit->x = x;
	unit->y = y;
	unit->vx = 0;
	unit->vy = 0;
	unit->health = health;
	unit->maxhealth = health;
	return unit;
}
// 添加塔函数
void CreateTowers(HWND hWnd, int x, int y, int type,int row,int column,int attack,int distance) {
	Tower* tower = new Tower();
	tower->img = bmp_Tower;
	tower->frame_column = column;
	tower->frame_row = row;
	tower->height = BG_TOWER_HEIGHT;
	tower->width = BG_TOWER_WIDTH;
	tower->x = x;
	tower->y = y;
	tower->type = type;
	tower->attack = attack;
	tower->distance = distance;
	tower->level = 1;
	tower->yes = 0;
	towers.push_back(tower);
}
TD* CreateTD(int x, int y)
{
	TD* td = new TD();
	td->img = bmp_TOMATO;
	td->x = x;
	td->y = y;
	td->health = 50;
	return td;
}
F* CreateF(int x, int y)
{
	F* f = new F();
	f->img = bmp_F;
	f->x = x;
	f->y = y;
	return f;
}

// 初始化游戏场景函数   其中Currentstage是一个全局变量
void InitStage(HWND hWnd, int stageID) {
	// 初始化场景实例
	PlaySound((LPCTSTR)IDR_WAVE_LOL,NULL, SND_RESOURCE | SND_ASYNC | SND_LOOP);
	if (currentStage != NULL) delete currentStage;
	currentStage = new Stage();
	currentStage->stageID = stageID;

	for (int i = 0; i < 22; i++)
		for (int j = 0; j < 44; j++)
			mapp[i][j] = 0;
	pdCountdown = TIME_COUNT_DOWN + 151;
	ffCountdown = TIME_COUNT_DOWN +8;
	if (stageID == STAGE_STARTMENU) {
		currentStage->bg = bmp_Back;
		currentStage->timeCountDown = 0;
		currentStage->timerOn = false;
		for (int i = 0; i < buttons.size(); i++) {
			Button* button = buttons[i];
			if (button->buttonID == BUTTON_MONEY || button->buttonID == BUTTON_POLO || button->buttonID == BUTTON_PD) //TODO：加载游戏界面需要的按钮
			{
				button->visible = true;
			}
			else {
				button->visible = false;
			}
		}
		for (int i = 0; i < towers.size(); i++)
			free(towers[i]);
		for (int i = 0; i < units.size(); i++)
			free(units[i]);
		for (int i = 0; i < polos.size(); i++)
			free(polos[i]);
		for (int i = 0; i < pds.size(); i++)
			free(pds[i]);
		for (int i = 0; i < ffs.size(); i++)
			free(ffs[i]);
		for (int i = 0; i < tds.size(); i++)
			free(tds[i]);
		for (int i = 0; i < fs.size(); i++)
			free(fs[i]);
		for (int i = 0; i < ices.size(); i++)
			free(ices[i]);
		ices.clear();
		fs.clear();
		towers.clear();
		units.clear();
		polos.clear();
		pds.clear();
		ffs.clear(); mousx.clear(); mousy.clear(); px.clear(); py.clear();
		mousex.clear(); mousey.clear(); mousexx.clear(); mouseyy.clear();
		polox.clear(); poloX.clear(); poloy.clear(); poloY.clear(); tds.clear();

		//显示开始界面的按钮
		for (int i = 0; i < buttons.size(); i++) {
			Button* button = buttons[i];
			if (button->buttonID == BUTTON_STARTGAME) {
				button->visible = true;
			}
			else {
				button->visible = false;
			}
		}


	}
	else if (stageID == STAGE_1) //TODO：添加多个游戏场景
	{
		currentStage->bg = bmp_Background;
		currentStage->timeCountDown = 10000;
		currentStage->timerOn = true;
		currentStage->money = 180;
		//显示游戏界面的按钮
		for (int i = 0; i < buttons.size(); i++) {
			Button* button = buttons[i];
			if (button->buttonID==BUTTON_MONEY || button->buttonID==BUTTON_POLO || button->buttonID==BUTTON_PD) //TODO：加载游戏界面需要的按钮
			{
				button->visible = true;
			}
			else {
				button->visible = false;
			}
		}
		for (int i = 0; i < towers.size(); i++)
			free(towers[i]);
		for (int i = 0; i < units.size(); i++)
			free(units[i]);
		for (int i = 0; i < polos.size(); i++)
			free(polos[i]);
		for (int i = 0; i < pds.size(); i++)
			free(pds[i]);
		for (int i = 0; i < ffs.size(); i++)
			free(ffs[i]);
		for (int i = 0; i < tds.size(); i++)
			free(tds[i]);
		for (int i = 0; i < fs.size(); i++)
			free(fs[i]);
		for (int i = 0; i < ices.size(); i++)
			free(ices[i]);
		ices.clear();
		fs.clear();
		towers.clear();
		units.clear();
		polos.clear();
		pds.clear();
		ffs.clear(); mousx.clear(); mousy.clear(); px.clear(); py.clear();
		mousex.clear(); mousey.clear(); mousexx.clear(); mouseyy.clear();
		polox.clear(); poloX.clear(); poloy.clear(); poloY.clear(); tds.clear();
			polos.push_back(CreatePOLO(1200, 575, 100));

	}
	else if (currentStage->stageID == STAGE_2)
	{
		currentStage->bg = bmp_BackRound2;
		currentStage->timeCountDown = 10000;
		currentStage->timerOn = true;
		currentStage->money = 450;
		for (int i = 0; i < buttons.size(); i++)
		{
			Button* button = buttons[i];
			if (button->buttonID == BUTTON_MONEY || button->buttonID == BUTTON_POLO || button->buttonID == BUTTON_PD) //TODO：加载游戏界面需要的按钮
			{
				button->visible = true;
			}
			else {
				button->visible = false;
			}
		}
		polos.push_back(CreatePOLO(1200, 575, 100));
	}
	else if (stageID == STAGE_LOSE)
	{
		
		currentStage->bg = bmp_BackLOSE;
		currentStage->timeCountDown = 10000;
		currentStage->timerOn = true;
		currentStage->money = 0;
		for (int i = 0; i < buttons.size(); i++)
		{
			Button* button = buttons[i];
			button->visible = false;
		}
		for (int i = 0; i < towers.size(); i++)
			free(towers[i]);
		for (int i = 0; i < units.size(); i++)
			free(units[i]);
		for (int i = 0; i < polos.size(); i++)
			free(polos[i]);
		for (int i = 0; i < pds.size(); i++)
			free(pds[i]);
		for (int i = 0; i < ffs.size(); i++)
			free(ffs[i]);
		for (int i = 0; i < tds.size(); i++)
			free(tds[i]);
		for (int i = 0; i < fs.size(); i++)
			free(fs[i]);
		for (int i = 0; i < ices.size(); i++)
			free(ices[i]);
		ices.clear();
		fs.clear(); mousx.clear(); mousy.clear(); px.clear(); py.clear();
		towers.clear();
		units.clear();
		polos.clear();
		pds.clear(); ffs.clear();
		mousex.clear(); mousey.clear(); mousexx.clear(); mouseyy.clear(); tds.clear();
		polox.clear(); poloX.clear(); poloy.clear(); poloY.clear();
	}
	else if (stageID == STAGE_WIN)
	{
		
		currentStage->bg = bmp_BackWIN;
		currentStage->timeCountDown = 10000;
		currentStage->timerOn = true;
		currentStage->money = 0;
		for (int i = 0; i < buttons.size(); i++)
		{
			Button* button = buttons[i];
			if (button->buttonID == BUTTON_NEXT)
				button->visible = true;
			else button->visible = false;
		}
		for (int i = 0; i < towers.size(); i++)
			free(towers[i]);
		for (int i = 0; i < units.size(); i++)
			free(units[i]);
		for (int i = 0; i < polos.size(); i++)
			free(polos[i]);
		for (int i = 0; i < pds.size(); i++)
			free(pds[i]);
		for (int i = 0; i < ffs.size(); i++)
			free(ffs[i]);
		for (int i = 0; i < tds.size(); i++)
			free(tds[i]);
		for (int i = 0; i < fs.size(); i++)
			free(fs[i]);
		for (int i = 0; i < ices.size(); i++)
			free(ices[i]);
		ices.clear();
		fs.clear();
		towers.clear();
		units.clear();
		polos.clear();
		pds.clear(); ffs.clear(); mousx.clear(); mousy.clear(); px.clear(); py.clear();
		mousex.clear(); mousey.clear(); mousexx.clear(); mouseyy.clear();
		polox.clear(); poloX.clear(); poloy.clear(); poloY.clear(); tds.clear();
	}
	else if (stageID == STAGE_OVER)
	{

	currentStage->bg = bmp_BackWIN;
	currentStage->timeCountDown = 10000;
	currentStage->timerOn = true;
	currentStage->money = 0;
	for (int i = 0; i < buttons.size(); i++)
	{
		buttons[i]->visible = false;
	}
	for (int i = 0; i < towers.size(); i++)
		free(towers[i]);
	for (int i = 0; i < units.size(); i++)
		free(units[i]);
	for (int i = 0; i < polos.size(); i++)
		free(polos[i]);
	for (int i = 0; i < pds.size(); i++)
		free(pds[i]);
	for (int i = 0; i < ffs.size(); i++)
		free(ffs[i]);
	for (int i = 0; i < tds.size(); i++)
		free(tds[i]);
	for (int i = 0; i < fs.size(); i++)
		free(fs[i]);
	for (int i = 0; i < ices.size(); i++)
		free(ices[i]);
	ices.clear();
	fs.clear();
	towers.clear(); tds.clear();
	units.clear();
	polos.clear();
	pds.clear(); ffs.clear(); mousx.clear(); mousy.clear(); px.clear(); py.clear();
	mousex.clear(); mousey.clear(); mousexx.clear(); mouseyy.clear();
	polox.clear(); poloX.clear(); poloy.clear(); poloY.clear();
	}

	//刷新显示
	InvalidateRect(hWnd, NULL, FALSE);
}


// 刷新单位状态函数
void UpdateUnits(HWND hWnd) {
	for (int i = 0; i < units.size(); i++) {
		Unit* unit = units[i];

		if (currentStage->stageID == STAGE_1)
		{
			UnitBehaviour_stage1(unit, hWnd);
		}
		else if (currentStage->stageID == STAGE_2)
		{
			UnitBehaviour_stage2(unit, hWnd);
		}
	}
	for (int i = 0; i < polos.size(); i++)
	{
		POLO* polo = polos[i];
		POLOBehaviour(polo);
	}
	for (int i = 0; i < mists.size(); i++)
	{
		MIST* mist = mists[i];
		MISTBehaviour(mist);
	}
	for (int i = 0; i < fogs.size(); i++)
	{
		FOG* fog = fogs[i];
		FOGBehaviour(fog);
	}
	for (int i = 0; i < tds.size(); i++)
	{
		TD* td = tds[i];
		TDBehaviour(td);
	}
	for (int i = 0; i < pds.size(); i++)
	{
		PD* pd = pds[i];
		double dirx = mousex[i] - polox[i];
		double diry = mousey[i] - poloy[i];
		double dirlen = sqrt(dirx*dirx + diry * diry);
		double vx = double(PD_SPEED*(dirx/dirlen));
		double vy = double(PD_SPEED*(diry / dirlen));
		PDBehaviour(pd,vx,vy);
	}
	for (int i = 0; i < ffs.size(); i++)
	{
		FF* ff = ffs[i];
		double dirx = mousexx[i] - poloX[i];
		double diry = mouseyy[i] - poloY[i];
		double dirlen = sqrt(dirx*dirx + diry * diry);
		double vx, vy;
		if (dirlen != 0)
		{
			 vx = double(FF_SPEED*(dirx / dirlen));
			 vy = double(FF_SPEED*(diry / dirlen));
		}
		else
		{
			 vx = 0;
			 vy = 0;
		}
		FFBehaviour(ff, vx, vy);
	}
	for (int i = 0; i < ices.size(); i++)
	{
		ICE* ice = ices[i];
		double dirx = mousx[i] - px[i];
		double diry = mousy[i] - py[i];
		double dirlen = sqrt(dirx*dirx + diry * diry);
		double vx, vy;
		if (dirlen != 0)
		{
			vx = double(FF_SPEED*(dirx / dirlen));
			vy = double(FF_SPEED*(diry / dirlen));
		}
		else
		{
			vx = 0;
			vy = 0;
		}
		ICEBehaviour(ice, vx, vy);
	}
}
//烟雾行为函数
void MISTBehaviour(MIST*mist)
{
	mist->frame_id++;
	if (mist->frame_id == FRAMES_MIST_COUNT)
	{
		MIST* u = mist;
		for (int i = 0; i < mists.size(); i++)
		{
			if (mists[i] == mist)
			{
				mists.erase(mists.begin() + i);
				free(u);
			}
		}
	}
}

void FOGBehaviour(FOG* fog)
{
	fog->frame_id++;
	if (fog->frame_id == FRAMES_FOG_COUNT)
	{
		FOG* u = fog;
		for (int i = 0; i < fogs.size(); i++)
		{
			if (fogs[i] == fog)
			{
				fogs.erase(fogs.begin() + i);
				free(u);
			}
		}
	}
}
void TDBehaviour(TD * td)
{
	for (int i = 0; i < units.size(); i++)
	{
		double dirx = td->x - units[i]->x+4;
		double diry = td->y - units[i]->y;
		double dirlen = sqrt(dirx*dirx + diry * diry);
		if (dirlen <= 32 && currentStage->timeCountDown%20==0)
			td->health -= 5;
	}
	if (td->health <= 0)
	{
		for (int i = 0; i < tds.size(); i++)
		{
			if (tds[i] == td)
			{
				mapp[td->y/BG_NEW_CELL_WIDTH][td->x/BG_NEW_CELL_HEIGHT] = 0;
				TD* tdd = td;
				tds.erase(tds.begin() + i);
				free(tdd);
			}
		}
	}
}
void FFBehaviour(FF* ff, double vx, double vy)
{
	ff->vx = vx;
	ff->vy = vy;
	int kk = 0;
	for (int i = 0; i < units.size(); i++)
	{
		Unit* unit = units[i];
		double dirx = unit->x + 16 - ff->x;
		double diry = unit->y + 30 - ff->y;
		double dirlen = sqrt(dirx*dirx + diry * diry);
		if (dirlen <= 35)
		{
			units[i]->health-=13; kk = 1;
		}
	}
	if (kk == 1 || ff->x <= 20 || ff->y <= 20)
		for (int i = 0; i < ffs.size(); i++)
		{
			if (ffs[i] == ff)
			{
				FF* fff;
				fff = ff;
				ffs.erase(ffs.begin() + i);
				poloX.erase(poloX.begin() + i);
				poloY.erase(poloY.begin() + i);
				mousexx.erase(mousexx.begin() + i);
				mouseyy.erase(mouseyy.begin() + i);
				free(fff);
			}
		}
	if (ff->vx != 0 && ff->vy!= 0)
	{
		ff->x += ff->vx;
		ff->y += ff->vy;
	}
}

void ICEBehaviour(ICE* ice, double vx, double vy)
{
	ice->vx = vx;
	ice->vy = vy;
	int kk = 0;
	for (int i = 0; i < units.size(); i++)
	{
		Unit* unit = units[i];
		double dirx = unit->x + 16 - ice->x;
		double diry = unit->y + 30 - ice->y;
		double dirlen = sqrt(dirx*dirx + diry * diry);
		if (dirlen <= 35)
		{
			units[i]->health -= 9; kk = 1;
			units[i]->condition = -2;
		}
	}
	if (kk == 1 || ice->x <= 20 || ice->y <= 20)
		for (int i = 0; i < ices.size(); i++)
		{
			if (ices[i] == ice)
			{
				ICE* icc;
				icc = ice;
				ices.erase(ices.begin() + i);
				px.erase(px.begin() + i);
				py.erase(py.begin() + i);
				mousx.erase(mousx.begin() + i);
				mousy.erase(mousy.begin() + i);
				free(icc);
			}
		}
	if (ice->vx != 0 && ice->vy != 0)
	{
		ice->x += ice->vx;
		ice->y +=ice->vy;
	}
}

//炮弹行为函数
void PDBehaviour(PD* pd,double vx,double vy)
{
	pd->vx = vx;
	pd->vy = vy;
	int kk = 0;
	for (int i = 0; i < units.size(); i++)
	{
		Unit* unit = units[i];
		double dirx = unit->x+30 - pd->x;
		double diry = unit->y+30 - pd->y;
		double dirlen = sqrt(dirx*dirx + diry * diry);
		if (dirlen <= 35)
		{
			Unit* UU = unit;
			units.erase(units.begin() + i);
			free(UU); kk = 1;
			break;
		}
	}
	if (kk == 1 || pd->x<=20 || pd->y<=20)
		for (int i = 0; i < pds.size(); i++)
		{
			if (pds[i] == pd)
			{
				PD*pdd;
				pdd = pd;
				pds.erase(pds.begin() + i);
				polox.erase(polox.begin() + i);
				poloy.erase(poloy.begin() + i);
				mousex.erase(mousex.begin() + i);
				mousey.erase(mousey.begin() + i);
				free(pdd);
			}
		}
	pd->x += pd->vx;
	pd->y += pd->vy;
}
//单位行为函数
void POLOBehaviour(POLO* polo)
{
	int next_state = polo->state;
	if (keyDDown == true && polo->x<=1355)
	{
		polo->state = UNIT_STATE_WALK;
		polo->vx = 3;
		polo->vy = 0;
	}
	else if (keyADown == true && polo->x>=45)
	{
		polo->state = UNIT_STATE_WALK;
		polo->vx = -3;
		polo->vy = 0;
	}
	else if (keyWDown == true && polo->y>=40)
	{
		polo->state = UNIT_STATE_WALK;
		polo->vx = 0;
		polo->vy = -3;
	}
	else if (keySDown == true && polo->y<=660)
	{
		polo->state = UNIT_STATE_WALK;
		polo->vx = 0;
		polo->vy = 3;
	}
	else polo->state = UNIT_STATE_HOLD;

	if (keyRDown == true && pdCountdown-currentStage->timeCountDown>=150 && polo->energy>=15)
	{
		pds.push_back(CreatePD(polo->x, polo->y));
		polox.push_back(double(polo->x));
		poloy.push_back(double(polo->y));
		mousex.push_back(double(mouseX));
		mousey.push_back(double(mouseY));
		pdCountdown = currentStage->timeCountDown;
		polo->energy -= 15;
	}
	if (keyHDown == true && ffCountdown - currentStage->timeCountDown >= 5 && polo->energy>=1)
	{
		ices.push_back(CreateICE(polo->x, polo->y));
		px.push_back(double(polo->x));
		py.push_back(double(polo->y));
		mousx.push_back(double(mouseX));
		mousy.push_back(double(mouseY));
		ffCountdown = currentStage->timeCountDown;
		polo->energy -= 0.45;
	}
	if (keyGDown == true && ffCountdown - currentStage->timeCountDown >= 5 && polo->energy >= 1)
	{
		ffs.push_back(CreateFF(polo->x, polo->y));
		poloX.push_back(double(polo->x));
		poloY.push_back(double(polo->y));
		mousexx.push_back(double(mouseX));
		mouseyy.push_back(double(mouseY));
		ffCountdown = currentStage->timeCountDown;
		polo->energy -= 0.45;
	}
	if ((currentStage->timeCountDown % 100 == 25 || currentStage->timeCountDown % 100 == 75) && polo->energy<Maxenergy)
		polo->energy+=currentStage->stageID;
	if ((currentStage->timeCountDown % 100 == 0) && polo->health < Maxhealth)
		polo->health+=currentStage->stageID;
	if (pdCountdown - currentStage->timeCountDown >= 150 && polo->energy >= 20)
	{
		for (int i = 0; i < buttons.size(); i++)
		{
			Button* button = buttons[i];
			if (button->buttonID == BUTTON_PD) button->visible = true;
			else if (button->buttonID == BUTTON_PDD) button->visible = false;
		}
	}
	else
	{
		for (int i = 0; i < buttons.size(); i++)
		{
			Button* button = buttons[i];
			if (button->buttonID == BUTTON_PD) button->visible = false;
			else if (button->buttonID == BUTTON_PDD) button->visible = true;
		}
	}
	for (int i = 0; i < units.size(); i++)
	{
		Unit* unit = units[i];
		double dirx = unit->x - polo->x;
		double diry = unit->y - polo->y;
		double dirlen = sqrt(dirx*dirx + diry * diry);
		if (dirlen <= 72 && (currentStage->timeCountDown % 100) == 75)
			polo->health -= 10;
	}

	if (next_state != polo->state) {
		//状态变化
		//polo->state = next_state;

		switch (polo->state) {
		case UNIT_STATE_HOLD:
			polo->vx = 0;
			polo->vy = 0;
			break;
		case UNIT_STATE_WALK:
			break;
		};
	}
	if (polo->health <= 0)
	{
		for (int i=0;i<polos.size();i++)
			if (polos[i] == polo)
			{
				POLO* po = polos[i];
				polos.erase(polos.begin() + i);
				free(po);
			}
	}
		polo->x += polo->vx;
		polo->y += polo->vy;
}

void UnitBehaviour_stage1(Unit* unit, HWND hwnd) {
	//沿着路线走
	if (unit->state == UNIT_STATE_WALK)
	{
		int **map = GetMap(STAGE_1);
		int x_box = (unit->x) / 32;
		int y_box = (unit->y + 16) / 32;
		if (x_box < 46 && y_box < 21)
		{
			if (unit->direction == UNIT_DIRECT_RIGHT) {
				if (map[(int)y_box][(int)(x_box + 1)] == 0)
				{
					unit->direction = UNIT_DIRECT_RIGHT;
					unit->vx = UNIT_SPEED+unit->condition;
					unit->vy = 0;
				}
				else if (map[(int)(y_box + 1)][(int)x_box] == 0)
				{
					unit->vx = 0;
					unit->vy = UNIT_SPEED+unit->condition;
				}
				else
				{
					unit->direction = UNIT_DIRECT_LEFT;
					unit->vx = -UNIT_SPEED-unit->condition;
					unit->vy = 0;
				}
			}
			else {
				if (map[(int)y_box][(int)(x_box - 1)] == 0)
				{
					unit->direction = UNIT_DIRECT_LEFT;
					unit->vx = -UNIT_SPEED-unit->condition;
					unit->vy = 0;
				}
				else if (map[(int)(y_box + 1)][(int)x_box] == 0)
				{
					unit->vx = 0;
					unit->vy = UNIT_SPEED+unit->condition;
				}
				else
				{
					unit->direction = UNIT_DIRECT_RIGHT;
					unit->vx = UNIT_SPEED+unit->condition;
					unit->vy = 0;
				}
			}

		}
		else
		{
			unit->vx = unit->vy = 0;
		}
		for (int i = 0; i < BG_NEW_ROWS; i++) free(map[i]);
		free(map);
	}
	if (unit->condition != 0) unit->condition = 0;
	//TO DO：进入防御塔射程后，受到持续伤害
	for (int i = 0; i < towers.size(); i++)
	if (towers[i]->level==2)
	{
		Tower* tower = towers[i];
		double dirX = tower->x + 16 - unit->x;
		double dirY = tower->y + 32 - unit->y;
		double dirLen = sqrt(dirX * dirX + dirY * dirY);
		if (dirLen < tower->distance && ((currentStage->timeCountDown % 100) == 75 || (currentStage->timeCountDown %100)==25))
		{
			unit->health -= tower->attack;
			mists.push_back(Createmist(tower->x, tower->y));
			fogs.push_back(Createfog(unit->x, unit->y));
		}

	}
	else if (towers[i]->level == 3)
	{
		Tower* tower = towers[i];
		double dirX = tower->x + 16 - unit->x;
		double dirY = tower->y + 32 - unit->y;
		double dirLen = sqrt(dirX * dirX + dirY * dirY);
		if (dirLen < tower->distance && ((currentStage->timeCountDown % 100) == 75 || (currentStage->timeCountDown % 100) == 25))
		{
			unit->health-=tower->attack*2;
				mists.push_back(Createmist(tower->x, tower->y));
				if (towers[i]->type == FIRE_TOWER)
				{
					mousexx.push_back(unit->x);
					mouseyy.push_back(unit->y);
					poloX.push_back(tower->x);
					poloY.push_back(tower->y);
					ffs.push_back(CreateFF(tower->x, tower->y));
				}
				else
				{
					mousx.push_back(unit->x);
					mousy.push_back(unit->y);
					px.push_back(tower->x);
					py.push_back(tower->y);
					ices.push_back(CreateICE(tower->x, tower->y));
				}
		}
	}
	
	bool pd = false; bool pdd = false;

	for (int i = 0; i < polos.size(); i++)
	{
		POLO* polo = polos[i];
		double dirx = polo->x - unit->x;
		double diry = polo->y - unit->y;
		double dirlen = sqrt(dirx*dirx + diry * diry);
		if (dirlen < 70)
		{
			unit->state = UNIT_STATE_ATTACK;
			if (dirx < 0) unit->direction = UNIT_DIRECT_LEFT;
			else unit->direction = UNIT_DIRECT_RIGHT;
			unit->vx = 0;
			unit->vy = 0;
			pd = true;
		}
	}
	for (int i = 0; i < tds.size(); i++)
	{
		TD* td = tds[i];
		double dirx = td->x - unit->x+4;
		double diry = td->y - unit->y;
		double dirlen = sqrt(dirx*dirx + diry * diry);
		if (dirlen < 32)
		{
			unit->state = UNIT_STATE_ATTACK;
			if (dirx < 0) unit->direction = UNIT_DIRECT_LEFT;
			else unit->direction = UNIT_DIRECT_RIGHT;
			unit->vx = 0;
			unit->vy = 0;
			pdd = true;
		}
	}
	if (!pd && !pdd) unit->state = UNIT_STATE_WALK;
	if (unit->x >= 1350)
	{
		currentStage->timerOn = false;
		InitStage(hwnd, STAGE_LOSE);
	}
	if (unit->health <= 0) {
		Unit* UNit = unit;
		for (int i = 0; i < units.size(); i++)
		{
			if (units[i] == UNit)
			{
				units.erase(units.begin() + i);
				free(UNit);
				break;
			}
		}
		currentStage->money += 10;
	}
	//下一帧
	if (unit->state == UNIT_STATE_WALK)
	{
		unit->frame_sequence = FRAMES_WALK;
		unit->frame_count = FRAMES_WALK_COUNT;
	}
	else
	{
		unit->frame_sequence = FRAMES_ATTACK;
		unit->frame_count = FRAMES_ATTACK_COUNT;
	}


		
	unit->x += unit->vx;
	unit->y += unit->vy;

	unit->frame_id++;
	unit->frame_id = unit->frame_id % unit->frame_count;

	int column = unit->frame_sequence[unit->frame_id];
	unit->frame_column = column + unit->direction * (UNIT_LAST_FRAME - 2 * column);

}

void UnitBehaviour_stage2(Unit* unit, HWND hwnd) {
	//沿着路线走
	if (unit->state == UNIT_STATE_WALK)
	{
		int **map = GetMap(STAGE_2);
		int x_box = (unit->x) / 32;
		int y_box = (unit->y + 16) / 32;
		if (x_box < 46 && y_box < 21)
		{
			if (unit->direction == UNIT_DIRECT_RIGHT) {
				if (map[(int)y_box][(int)(x_box + 1)] == 0)
				{
					unit->direction = UNIT_DIRECT_RIGHT;
					unit->vx = UNIT_SPEED+unit->condition;
					unit->vy = 0;
				}
				else if (map[(int)(y_box + 1)][(int)x_box] == 0)
				{
					unit->vx = 0;
					unit->vy = UNIT_SPEED+unit->condition;
				}
				else
				{
					unit->direction = UNIT_DIRECT_LEFT;
					unit->vx = -UNIT_SPEED-unit->condition;
					unit->vy = 0;
				}
			}
			else {
				if (map[(int)y_box][(int)(x_box - 1)] == 0)
				{
					unit->direction = UNIT_DIRECT_LEFT;
					unit->vx = -UNIT_SPEED-unit->condition;
					unit->vy = 0;
				}
				else if (map[(int)(y_box + 1)][(int)x_box] == 0)
				{
					unit->vx = 0;
					unit->vy = UNIT_SPEED+unit->condition;
				}
				else
				{
					unit->direction = UNIT_DIRECT_RIGHT;
					unit->vx = UNIT_SPEED+unit->condition;
					unit->vy = 0;
				}
			}

		}
		else
		{
			unit->vx = unit->vy = 0;
		}
		for (int i = 0; i < BG_NEW_ROWS; i++) free(map[i]);
		free(map);
	}
	if (unit->condition != 0) unit->condition = 0;
	//TO DO：进入防御塔射程后，受到持续伤害
	for (int i = 0; i < towers.size(); i++)
		if (towers[i]->level == 2)
		{
			Tower* tower = towers[i];
			double dirX = tower->x + 16 - unit->x;
			double dirY = tower->y + 32 - unit->y;
			double dirLen = sqrt(dirX * dirX + dirY * dirY);
			if (dirLen < tower->distance && ((currentStage->timeCountDown % 100) == 75 || (currentStage->timeCountDown % 100) == 25))
			{
				unit->health -= tower->attack*2;
				mists.push_back(Createmist(tower->x, tower->y));
				fogs.push_back(Createfog(unit->x, unit->y));
			}

		}
		else if (towers[i]->level == 3)
		{
			Tower* tower = towers[i];
			double dirX = tower->x + 16 - unit->x;
			double dirY = tower->y + 32 - unit->y;
			double dirLen = sqrt(dirX * dirX + dirY * dirY);
			if (dirLen < tower->distance && ((currentStage->timeCountDown % 100) == 75 || (currentStage->timeCountDown % 100) == 25))
			{
				unit->health -= tower->attack * 3;
				mists.push_back(Createmist(tower->x, tower->y));
				if (towers[i]->type == FIRE_TOWER)
				{
					mousexx.push_back(unit->x);
					mouseyy.push_back(unit->y);
					poloX.push_back(tower->x);
					poloY.push_back(tower->y);
                    ffs.push_back(CreateFF(tower->x, tower->y));
				}
					
				else
				{
					ices.push_back(CreateICE(tower->x, tower->y));
					mousx.push_back(unit->x);
					mousy.push_back(unit->y);
					px.push_back(tower->x);
					py.push_back(tower->y);
				}
			}
		}
		else if (towers[i]->level == 4)
		{
			Tower* tower = towers[i];
			double dirX = tower->x + 16 - unit->x;
			double dirY = tower->y + 32 - unit->y;
			double dirLen = sqrt(dirX*dirX + dirY * dirY);
			if (dirLen < tower->distance && ((currentStage->timeCountDown % 100) == 75 || (currentStage->timeCountDown % 100) == 25))
			{
				unit->health -= tower->attack * 2;
				mists.push_back(Createmist(tower->x, tower->y));
				
						if (towers[i]->type == FIRE_TOWER)
							for (int i = -1; i <= 1; i++)
								for (int j = -1; j <= 1; j++)
								{
									{
										mousexx.push_back(unit->x + i * 8);
										mouseyy.push_back(unit->y + j * 8);
										poloX.push_back(tower->x);
										poloY.push_back(tower->y);
										ffs.push_back(CreateFF(tower->x + i * 8, tower->y + j * 8));
									}
								}
						else
						{
							for (int i = -1; i <= 1; i++)
								for (int j = -1; j <= 1; j++)
								{
									ices.push_back(CreateICE(tower->x + i * 8, tower->y + j * 8));
									mousx.push_back(unit->x + i * 8);
									mousy.push_back(unit->y + j * 8);
									px.push_back(tower->x);
									py.push_back(tower->y);
								}
						}
			}
		}
	bool pd = false; bool pdd = false;

	for (int i = 0; i < polos.size(); i++)
	{
		POLO* polo = polos[i];
		double dirx = polo->x - unit->x;
		double diry = polo->y - unit->y;
		double dirlen = sqrt(dirx*dirx + diry * diry);
		if (dirlen < 70)
		{
			unit->state = UNIT_STATE_ATTACK;
			if (dirx < 0) unit->direction = UNIT_DIRECT_LEFT;
			else unit->direction = UNIT_DIRECT_RIGHT;
			unit->vx = 0;
			unit->vy = 0;
			pd = true;
		}
	}
	for (int i = 0; i < tds.size(); i++)
	{
		TD* td = tds[i];
		double dirx = td->x - unit->x+4;
		double diry = td->y - unit->y;
		double dirlen = sqrt(dirx*dirx + diry * diry);
		if (dirlen < 32)
		{
			unit->state = UNIT_STATE_ATTACK;
			if (dirx < 0) unit->direction = UNIT_DIRECT_LEFT;
			else unit->direction = UNIT_DIRECT_RIGHT;
			unit->vx = 0;
			unit->vy = 0;
			pdd = true;
		}
	}
	if (!pd && !pdd) unit->state = UNIT_STATE_WALK;
	if (unit->x >= 1350)
	{
		currentStage->timerOn = false;
		currentStage->stageID = STAGE_LOSE;
		InitStage(hwnd, STAGE_LOSE);
	}
	if (unit->health <= 0) {
		Unit* UNit = unit;
		for (int i = 0; i < units.size(); i++)
		{
			if (units[i] == UNit)
			{
				units.erase(units.begin() + i);
				free(UNit);
				break;
			}
		}
		currentStage->money += 10;
	}
	//下一帧
	if (unit->state == UNIT_STATE_WALK)
	{
		unit->frame_sequence = FRAMES_WALK;
		unit->frame_count = FRAMES_WALK_COUNT;
	}
	else
	{
		unit->frame_sequence = FRAMES_ATTACK;
		unit->frame_count = FRAMES_ATTACK_COUNT;
	}

	

	unit->x += unit->vx;
	unit->y += unit->vy;

	unit->frame_id++;
	unit->frame_id = unit->frame_id % unit->frame_count;

	int column = unit->frame_sequence[unit->frame_id];
	unit->frame_column = column + unit->direction * (UNIT_LAST_FRAME - 2 * column);

}


void UnitBehaviour_1(Unit* unit) {

	double dirX = mouseX - unit->x;//表示鼠标和Unit位置的x距离
	double dirY = mouseY - unit->y;//表示鼠标和Unit位置的y距离
	double dirLen = sqrt(dirX * dirX + dirY * dirY) + 0.0001;//表示鼠标和Unit位置的距离+0.0001补全


	if (dirX > 0) {
		unit->direction = UNIT_DIRECT_RIGHT;//单位方向向右
	}
	else {
		unit->direction = UNIT_DIRECT_LEFT;//单位方向向左
	}


	//判断当前状态, 以及判断是否需要状态变化
	int next_state = unit->state;
	switch (unit->state) {
	case UNIT_STATE_HOLD://定义为单位静止
		if (dirLen < 400) {
			next_state = UNIT_STATE_WALK;
		}
		break;
	case UNIT_STATE_WALK://定义为单位移动
		if (dirLen >= 400) {
			next_state = UNIT_STATE_HOLD;
		}
		else if (dirLen < 200) {
			next_state = UNIT_STATE_ATTACK;
		}
		else {
			unit->vx = dirX / dirLen * UNIT_SPEED;
			unit->vy = dirY / dirLen * UNIT_SPEED;
		}
		break;
	case UNIT_STATE_ATTACK:
		if (dirLen >= 200) {
			next_state = UNIT_STATE_WALK;
		}
		break;
	};

	if (next_state != unit->state) {
		//状态变化
		unit->state = next_state;
		unit->frame_id = -1;

		switch (unit->state) {
		case UNIT_STATE_HOLD:
			unit->frame_sequence = FRAMES_HOLD;
			unit->frame_count = FRAMES_HOLD_COUNT;
			unit->vx = 0;
			unit->vy = 0;
			break;
		case UNIT_STATE_WALK:
			unit->frame_sequence = FRAMES_WALK;
			unit->frame_count = FRAMES_WALK_COUNT;
			unit->vx = dirX / dirLen * UNIT_SPEED;
			unit->vy = dirY / dirLen * UNIT_SPEED;
			break;
		case UNIT_STATE_ATTACK:
			unit->frame_sequence = FRAMES_ATTACK;
			unit->frame_count = FRAMES_ATTACK_COUNT;
			unit->vx = 0;
			unit->vy = 0;
			break;
		};
	}

	//动画运行到下一帧
	unit->x += unit->vx;
	unit->y += unit->vy;

	unit->frame_id++;
	unit->frame_id = unit->frame_id % unit->frame_count;

	int column = unit->frame_sequence[unit->frame_id];
	unit->frame_column = column + unit->direction * (UNIT_LAST_FRAME - 2 * column);


}

void UnitBehaviour_2(Unit* unit) {

	double dirX = mouseX - unit->x;
	double dirY = mouseY - unit->y;
	double dirLen = sqrt(dirX * dirX + dirY * dirY) + 0.0001;


	if (dirX > 0) {
		unit->direction = UNIT_DIRECT_RIGHT;
	}
	else {
		unit->direction = UNIT_DIRECT_LEFT;
	}


	//判断当前状态, 以及判断是否需要状态变化
	int next_state = unit->state;
	switch (unit->state) {
	case UNIT_STATE_HOLD:
		next_state = UNIT_STATE_WALK;
		break;
	case UNIT_STATE_WALK:
		if (dirLen < 32) {
			next_state = UNIT_STATE_ATTACK;
		}
		else {
			unit->vx = dirX / dirLen * UNIT_SPEED;
			unit->vy = dirY / dirLen * UNIT_SPEED;
		}
		break;
	case UNIT_STATE_ATTACK:
		if (dirLen >= 32) {
			next_state = UNIT_STATE_WALK;
		}
		break;
	};

	if (next_state != unit->state) {
		//状态变化
		unit->state = next_state;
		unit->frame_id = -1;

		switch (unit->state) {
		case UNIT_STATE_HOLD:
			unit->frame_sequence = FRAMES_HOLD;
			unit->frame_count = FRAMES_HOLD_COUNT;
			unit->vx = 0;
			unit->vy = 0;
			break;
		case UNIT_STATE_WALK:
			unit->frame_sequence = FRAMES_WALK;
			unit->frame_count = FRAMES_WALK_COUNT;
			unit->vx = dirX / dirLen * UNIT_SPEED;
			unit->vy = dirY / dirLen * UNIT_SPEED;
			break;
		case UNIT_STATE_ATTACK:
			unit->frame_sequence = FRAMES_ATTACK;
			unit->frame_count = FRAMES_ATTACK_COUNT;
			unit->vx = 0;
			unit->vy = 0;
			break;
		};
	}

	
	//动画运行到下一帧
	unit->x += unit->vx;
	unit->y += unit->vy;

	unit->frame_id++;
	unit->frame_id = unit->frame_id % unit->frame_count;

	int column = unit->frame_sequence[unit->frame_id];
	unit->frame_column = column + unit->direction * (UNIT_LAST_FRAME - 2 * column);


}


#pragma endregion



#pragma region 绘图函数
// 绘图函数
void drawdistance(int distance, int x, int y)
{
	HDC hdc_memBuf = HDC_MEMORY;
	SelectObject(hdc_memBuf, hbBck);
	SelectObject(hdc_memBuf, GetStockObject(NULL_BRUSH));
	Ellipse(hdc_memBuf, x - distance, y - distance, x + distance, y + distance);
}
void DrawHealthLine(int midx, int midy, int health,int maxhealth)
{
	HDC hdc_memBuf = HDC_MEMORY;

	SelectObject(hdc_memBuf, hbBck);
	MoveToEx(hdc_memBuf, midx - (maxhealth / 8)*100/maxhealth, midy - 35, NULL);
	LineTo(hdc_memBuf, midx + (maxhealth / 8)*100/maxhealth, midy - 35);
	SelectObject(hdc_memBuf, hbBar);
	MoveToEx(hdc_memBuf, midx - (maxhealth / 8)*100/maxhealth, midy - 34,NULL);
	LineTo(hdc_memBuf, midx + ((health-maxhealth/2) / 4)*100/maxhealth, midy - 34);
	SelectObject(hdc_memBuf, hbBar);
}
void DrawTDHealthLine(int midx, int midy, int health, int maxhealth)
{
	HDC hdc_memBuf = HDC_MEMORY;

	SelectObject(hdc_memBuf, hbBck);
	MoveToEx(hdc_memBuf, 32+midx - (maxhealth / 8) * 100 / maxhealth, midy - 16, NULL);
	LineTo(hdc_memBuf, 32+midx + (maxhealth / 8) * 100 / maxhealth, midy - 16);
	SelectObject(hdc_memBuf, hbBar);
	MoveToEx(hdc_memBuf, 32+midx - (maxhealth / 8) * 100 / maxhealth, midy - 15, NULL);
	LineTo(hdc_memBuf, 32+midx + ((health - maxhealth / 2) / 4) * 100 / maxhealth, midy - 15);
	SelectObject(hdc_memBuf, hbBar);
}
void DrawPOLOLine(int midx, int midy, int health,int energy)
{
	HDC hdc_memBuf = HDC_MEMORY;
	//绘制魄罗头顶上的血条
	SelectObject(hdc_memBuf, hbBck);
	MoveToEx(hdc_memBuf, midx - Maxhealth / 4, midy - 40, NULL);
	LineTo(hdc_memBuf, midx + Maxhealth / 4, midy - 40);
	SelectObject(hdc_memBuf, hbBar);
	MoveToEx(hdc_memBuf, midx - Maxhealth / 4, midy - 39, NULL);
	LineTo(hdc_memBuf, midx + (health - Maxhealth / 2) / 2, midy - 39);
	SelectObject(hdc_memBuf, hbBck);

	MoveToEx(hdc_memBuf, midx - Maxhealth / 4, midy - 35, NULL);
	LineTo(hdc_memBuf, midx + Maxhealth / 4, midy - 35);
	SelectObject(hdc_memBuf, hbBlue);
	MoveToEx(hdc_memBuf, midx - Maxhealth / 4, midy - 34, NULL);
	LineTo(hdc_memBuf, midx + (energy - Maxhealth / 2)/2 , midy - 34);
	//绘制状态栏血条
	SelectObject(hdc_memBuf, hbBck1);
	MoveToEx(hdc_memBuf, WINDOW_WIDTH -130- Maxhealth * 6, 25, NULL);
	LineTo(hdc_memBuf, WINDOW_WIDTH - 130, 25);
	SelectObject(hdc_memBuf, hbBar1);
	MoveToEx(hdc_memBuf, WINDOW_WIDTH -130-health * 6, 25, NULL);
	LineTo(hdc_memBuf, WINDOW_WIDTH - 130, 25);
	SelectObject(hdc_memBuf, hbBck1);
	MoveToEx(hdc_memBuf, WINDOW_WIDTH - 130-Maxenergy * 6, 45, NULL);
	LineTo(hdc_memBuf, WINDOW_WIDTH - 130, 45);
	SelectObject(hdc_memBuf, hbBlue1);
	MoveToEx(hdc_memBuf, WINDOW_WIDTH - 130-energy * 6, 45, NULL);
	LineTo(hdc_memBuf, WINDOW_WIDTH - 130, 45);

	SelectObject(hdc_memBuf, hbBck);
}
void DrawattackLine(int xbx, int xby, int towerx, int towery)
{
	HDC hdc_memBuf = HDC_MEMORY;
	SelectObject(hdc_memBuf, hbll);
	MoveToEx(hdc_memBuf, towerx, towery, NULL);
	LineTo(hdc_memBuf, xbx, xby);
	SelectObject(hdc_memBuf, hbBck);
}
void Drawmoney(int x, int y)
{
	HDC hdc_memBuf = HDC_MEMORY;
    wchar_t sss[20];
	wsprintf(sss, L"%d", currentStage->money);
	COLORREF color1 = RGB(0,0, 0);
	COLORREF color2 = RGB(255,215,0);
	::SetTextColor(hdc_memBuf, color1);
	::SetBkColor(hdc_memBuf, color2);
	::TextOut(hdc_memBuf, x, y, sss, lstrlen(sss));
}
void DrawDeadline(int x, int y)
{
	HDC hdc_memBuf = HDC_MEMORY;
	wchar_t ssss[25];
	if (currentStage->stageID==STAGE_1)wsprintf(ssss, L"TimeCountDown:%d", (currentStage->timeCountDown -5000)/30);
	else if (currentStage->stageID == STAGE_2) wsprintf(ssss, L"TimeCountDown:%d", currentStage->timeCountDown/30);
	COLORREF color1 = RGB(0, 0, 0);
	COLORREF color2 = RGB(238, 232,170);
	::SetTextColor(hdc_memBuf, color1);
	::SetBkColor(hdc_memBuf, color2);
	::TextOut(hdc_memBuf, x, y, ssss, lstrlen(ssss));
}
void Paint(HWND hWnd) {

	PAINTSTRUCT ps;
	HDC hdc_window = BeginPaint(hWnd, &ps);//hdc_window实际窗口
	//HDC hdc = hdc_window;
	HDC hdc_memBuffer = CreateCompatibleDC(hdc_window);//HDC为上下文句柄 内存中的窗口
	HDC_MEMORY = hdc_memBuffer;
	HDC hdc_loadBmp = CreateCompatibleDC(hdc_window);
    

	

	
	//初始化缓存
	HBITMAP	blankBmp = CreateCompatibleBitmap(hdc_window, WINDOW_WIDTH, WINDOW_HEIGHT);
	SelectObject(hdc_memBuffer, blankBmp);

	// 绘制背景到缓存
	SelectObject(hdc_loadBmp, currentStage->bg);

	BitBlt(hdc_memBuffer, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdc_loadBmp, 0, 0, SRCCOPY);

	// 绘制塔到缓存
	for (int i = 0; i < towers.size(); i++) {
		Tower* tower = towers[i];
		if (towers[i]->yes == 1)
			drawdistance(towers[i]->distance, towers[i]->x, towers[i]->y);
		SelectObject(hdc_loadBmp, tower->img);
		TransparentBlt(
			hdc_memBuffer, tower->x, tower->y - 0.5 * BG_TOWER_HEIGHT,
			tower->width, tower->height,
			hdc_loadBmp, tower->frame_column * BG_TOWER_WIDTH, tower->frame_row * BG_TOWER_HEIGHT,
			tower->width, tower->height,
			RGB(255, 255, 255)
		);
	}

	for (int i = 0; i < mists.size(); i++)
	{
		MIST* mist = mists[i];
		SelectObject(hdc_loadBmp, mist->img);
		TransparentBlt(
			hdc_memBuffer, mist->x+8, mist->y-24,
			32, 32,
			hdc_loadBmp, 0,mist->frame_id*16,
			16, 16,
			RGB(255, 255, 255)
		);
	}
	for (int i = 0; i < tds.size(); i++)
	{
		TD* td = tds[i];
		SelectObject(hdc_loadBmp, td->img);
		TransparentBlt(
			hdc_memBuffer, td->x + 16, td->y,
			32, 32,
			hdc_loadBmp, 0, 0,
			32, 22,
			RGB(255, 255, 255)
		);
	}
	for (int i = 0; i < fogs.size(); i++)
	{
		FOG* fog = fogs[i];
		SelectObject(hdc_loadBmp, fog->img);
		TransparentBlt(
			hdc_memBuffer, fog->x, fog->y,
			32, 32,
			hdc_loadBmp, 0, fog->frame_id * 32,
			32, 32,
			RGB(255, 255, 255)
		);
	}
	// 按场景分类绘制内容到缓存
	if (currentStage->stageID == STAGE_STARTMENU) {

	}
	else if (currentStage->stageID >= STAGE_1 && currentStage->stageID <= STAGE_2) //TODO：添加多个游戏场景
	{
		// 绘制单位到缓存
		for (int i = 0; i < units.size(); i++) {
			Unit* unit = units[i];
			SelectObject(hdc_loadBmp, unit->img);
			TransparentBlt(
				hdc_memBuffer, unit->x - 0.5 * UNIT_SIZE_X, unit->y - 0.5 * UNIT_SIZE_Y,
				UNIT_SIZE_X, UNIT_SIZE_Y,
				hdc_loadBmp, UNIT_SIZE_X * unit->frame_column, UNIT_SIZE_Y * unit->frame_row, UNIT_SIZE_X, UNIT_SIZE_Y,
				RGB(255, 255, 255)
			);
		}
		for (int i = 0; i < polos.size(); i++)
		{
			POLO* polo = polos[i];
			SelectObject(hdc_loadBmp, polo->img);
			TransparentBlt
			(
				hdc_memBuffer, polo->x - 0.5*POLO_SIZE_X, polo->y - 0.5*POLO_SIZE_Y,
				POLO_SIZE_X, POLO_SIZE_Y,
				hdc_loadBmp, 0,0,POLO_SIZE_X,POLO_SIZE_Y,
				RGB(255, 255, 255)
			);
		}
		for (int i = 0; i < fs.size(); i++)
		{
			F* f = fs[i];
			SelectObject(hdc_loadBmp, f->img);
			TransparentBlt
			(
				hdc_memBuffer, f->x, f->y - 16,
				32, 32,
				hdc_loadBmp, 0, 0, 32, 32,
				RGB(255, 255, 255)
			);
		}
		for (int i = 0; i < pds.size(); i++)
		{
			PD* pd = pds[i];
			SelectObject(hdc_loadBmp, pd->img);
			TransparentBlt
			(
				hdc_memBuffer, pd->x - 0.5*PD_SIZE_X, pd->y - 0.5*PD_SIZE_Y,
				PD_SIZE_X, PD_SIZE_Y,
				hdc_loadBmp, 0, 0, PD_SIZE_X, PD_SIZE_Y,
				RGB(255, 255, 255)
			);
		}
		for (int i = 0; i < ffs.size(); i++)
		{
			FF* ff = ffs[i];
			SelectObject(hdc_loadBmp, ff->img);
			TransparentBlt
			(
				hdc_memBuffer, ff->x - 0.5 * 8, ff->y - 0.5 * 8,
				8, 8,
				hdc_loadBmp, 0, 0, 8, 8,
				RGB(255, 255, 255)
			);
		}
		for (int i = 0; i < ices.size(); i++)
		{
			ICE* ice = ices[i];
			SelectObject(hdc_loadBmp, ice->img);
			TransparentBlt
			(
				hdc_memBuffer, ice->x - 0.5 * 8, ice->y - 0.5 * 8,
				8, 8,
				hdc_loadBmp, 0, 0, 8, 8,
				RGB(255, 255, 255)
			);
		}
	}

	// 绘制按钮到缓存
	for (int i = 0; i < buttons.size(); i++) {
		Button* button = buttons[i];
		if (button->buttonID != BUTTON_INFO1 && button->buttonID != BUTTON_INFO2 && button->buttonID != BUTTON_INFO3 && button->buttonID != BUTTON_INFO4)
		{
			if (button->visible) {
				SelectObject(hdc_loadBmp, button->img);
				TransparentBlt(
					hdc_memBuffer, button->x, button->y,
					button->width, button->height,
					hdc_loadBmp, 0, 0, button->width, button->height,
					RGB(255, 255, 255)
				);
			}
		}
		else
			if (button->visible)
			{
				SelectObject(hdc_loadBmp, button->img);
				TransparentBlt(
					hdc_memBuffer, button->x, button->y,
					button->width/2, button->height/2,
					hdc_loadBmp, 0, 0, button->width, button->height,
					RGB(255, 255, 255)
				);
			}
	}

	for (int i=0;i<towers.size();i++)
	{
		if (towers[i]->level==1)
		for (int j = 0; j < units.size(); j++)
		{
			double dirx = towers[i]->x - units[j]->x;
			double diry = towers[i]->y - units[j]->y;
			double dirlen = sqrt(dirx*dirx + diry * diry);
			if (dirlen <= towers[i]->distance)
			{
				DrawattackLine(units[j]->x, units[j]->y, towers[i]->x, towers[i]->y);
				if (currentStage->timeCountDown % 10 == 0) units[j]->health-=5;
				break;
			}
		}
	}

	// 最后将所有的信息绘制到屏幕上
	for (auto u : units) {
		//SelectObject(hdc_memBuffer, hbBar);
		DrawHealthLine(u->x, u->y, u->health,u->maxhealth);
	}
	for (auto u : tds)
	{
		DrawTDHealthLine(u->x, u->y, u->health, 50);
	}
	if (currentStage->stageID==STAGE_1 || currentStage->stageID==STAGE_2)
	{
		Drawmoney(42, 672);
		DrawDeadline(20, 20);
	}
	for (auto u : polos)
	{
		DrawPOLOLine(u->x, u->y, u->health,u->energy);
	}
	BitBlt(hdc_window, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdc_memBuffer, 0, 0, SRCCOPY);

	// 回收资源所占的内存（非常重要）
	DeleteObject(blankBmp);
	DeleteDC(hdc_memBuffer);
	DeleteDC(hdc_loadBmp);

	// 结束绘制
	EndPaint(hWnd, &ps);
}

// 关卡地图设计函数
int** GetMap(int stage) { 
	int** map;

	//动态创建场景地图
	map = (int**)malloc(BG_NEW_ROWS * sizeof(int*));
	for (int k = 0; k < BG_NEW_ROWS; k++) {
		map[k] = (int*)malloc(BG_NEW_COLUMNS * sizeof(int));
	}

	if(stage == STAGE_1 || stage==0) //关卡1地图
	{ 
		for (int i = 0; i < BG_NEW_ROWS; i++) {
			for (int j = 0; j < BG_NEW_COLUMNS; j++) {
				if (((i == 4 && j <= 20) || (i == 7 && j <= 17)) && (j % 3 == 1) ||
					((i == 16 && j >= 14) || (i == 19 && j >= 12)) && (j % 3 == 0) ||
					(i == 13 && j >= 14 && j <= 18 && j % 3 == 0)
					|| (i == 10 && j >= 13 && j <= 17 && j % 3 == 1) ||
					(j == 19 && i >= 5 && i <= 12 && i % 3 == 1) || (j == 12 && i >= 11 && i <= 18 && i % 3 == 1)
					) {				//塔基位置
					map[i][j] = 2;
				}
				else if (i >= 5 && i <= 6 && j < 19 ||
					i <= 18 && i >= 17 && j >= 13 || i <= 10 && i >= 7 && j >= 17 && j <= 18 ||
					i >= 13 && i <= 16 && j <= 14 && j >= 13 || i >= 11 && i <= 12 && j >= 13 && j <= 18) {							//道路位置
					map[i][j] = 0;
				}
				
			}
		}
	}
	else if (stage==STAGE_2) 		
	{ 
		for (int i = 0; i < BG_NEW_ROWS; i++) {
			for (int j = 0; j < BG_NEW_COLUMNS; j++) {
				if ((i==3 && j<=37 && j%6==0 && j>0) || (i==6 && j<=36 && (j-3)%6==0) 
					||(i==7&&j==40)||(i==14 && (j==4))
					||((i==9 || i==12) && j>=8 && j<=36 && j%6==0) ||((i==16||i==19) && j>=8 && j%6==0)
					) {				//塔基位置
					map[i][j] = 2;
				}
				else if (((i==4|| i==5)&&j<=38)|| ((j==38||j==39) && i>=4 &&i<=11) ||((i==11 || i==10)&& j<=38 && j>=5) || ((j==5||j==6) && i>=11 && i<=18) || ((i==18||i==17) && j>=5))
				{							//道路位置
					map[i][j] = 0;
				}

			}
		}
	}
	return map;
}



// 初始化背景函数
HBITMAP InitBackGround(HWND hWnd, HBITMAP bmp_src, HBITMAP bmp_src1,HBITMAP bmp_tower) {

	srand(time(NULL));
	PAINTSTRUCT ps;
	HDC hdc_window = BeginPaint(hWnd, &ps);

	HDC hdc_memBuffer = CreateCompatibleDC(hdc_window);
	HDC hdc_loadBmp = CreateCompatibleDC(hdc_window);
	HDC hdc_loadBmp1 = CreateCompatibleDC(hdc_window);

	//初始化缓存
	HBITMAP	bmp_output = CreateCompatibleBitmap(hdc_window, WINDOW_WIDTH, WINDOW_HEIGHT);
	SelectObject(hdc_memBuffer, bmp_output);

	//加载资源
	SelectObject(hdc_loadBmp, bmp_src);
	SelectObject(hdc_loadBmp1, bmp_src1);
	//加载地形
	
	TransparentBlt(
		hdc_memBuffer, 0, 0,
		WINDOW_WIDTH, WINDOW_HEIGHT,
		hdc_loadBmp1, 0, 0,
		WINDOW_WIDTH, WINDOW_HEIGHT,
		RGB(255, 255, 255)
	);
	if (bmp_src1 == bmp_Map1)
	{
		int** map = GetMap(STAGE_1);
		int style_x, style_y;
		for (int i = 0; i < BG_NEW_ROWS; i++) {

			for (int j = 0; j < BG_NEW_COLUMNS; j++) {
				if (map[i][j] == 0) {			//路径砖块位置
					style_x = 1;
					style_y = 5;
					TransparentBlt(
						hdc_memBuffer, j * BG_NEW_CELL_WIDTH, i * BG_NEW_CELL_HEIGHT,
						BG_NEW_CELL_WIDTH, BG_NEW_CELL_HEIGHT,
						hdc_loadBmp, style_x * BG_NEW_CELL_WIDTH, style_y * BG_NEW_CELL_HEIGHT,
						BG_NEW_CELL_WIDTH, BG_NEW_CELL_HEIGHT,
						RGB(255, 255, 255));
				}

				else if (map[i][j] == 2)
				{
					style_x = 3;
					style_y = 9;

					TransparentBlt(
						hdc_memBuffer, j * BG_NEW_CELL_WIDTH, i * BG_NEW_CELL_HEIGHT,
						BG_NEW_CELL_WIDTH, BG_NEW_CELL_HEIGHT,
						hdc_loadBmp, style_x * BG_NEW_CELL_WIDTH, style_y * BG_NEW_CELL_HEIGHT,
						BG_NEW_CELL_WIDTH, BG_NEW_CELL_HEIGHT,
						RGB(255, 255, 255));
				}
			}

		}
        for (int i = 0; i < BG_NEW_ROWS; i++) free(map[i]);
	    free(map);
	}
	else if(bmp_src1==bmp_MAP2)
	{
		int** map = GetMap(STAGE_2);
		int style_x, style_y;
		for (int i = 0; i < BG_NEW_ROWS; i++) {

			for (int j = 0; j < BG_NEW_COLUMNS; j++) {
				if (map[i][j] == 0) {			//路径砖块位置
					style_x = 1;
					style_y = 5;
					TransparentBlt(
						hdc_memBuffer, j * BG_NEW_CELL_WIDTH, i * BG_NEW_CELL_HEIGHT,
						BG_NEW_CELL_WIDTH, BG_NEW_CELL_HEIGHT,
						hdc_loadBmp, style_x * BG_NEW_CELL_WIDTH, style_y * BG_NEW_CELL_HEIGHT,
						BG_NEW_CELL_WIDTH, BG_NEW_CELL_HEIGHT,
						RGB(255, 255, 255));
				}

				else if (map[i][j] == 2)
				{
					style_x = 3;
					style_y = 9;

					TransparentBlt(
						hdc_memBuffer, j * BG_NEW_CELL_WIDTH, i * BG_NEW_CELL_HEIGHT,
						BG_NEW_CELL_WIDTH, BG_NEW_CELL_HEIGHT,
						hdc_loadBmp, style_x * BG_NEW_CELL_WIDTH, style_y * BG_NEW_CELL_HEIGHT,
						BG_NEW_CELL_WIDTH, BG_NEW_CELL_HEIGHT,
						RGB(255, 255, 255));
				}
			}

		}
		for (int i = 0; i < BG_NEW_ROWS; i++) free(map[i]);
		free(map);
	}
	

	// 最后将所有的信息绘制到屏幕上
	BitBlt(hdc_window, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdc_memBuffer, 0, 0, SRCCOPY);

	// 回收资源所占的内存（非常重要）
	DeleteDC(hdc_memBuffer);
	DeleteDC(hdc_loadBmp);
	DeleteDC(hdc_loadBmp1);

	// 结束绘制
	EndPaint(hWnd, &ps);

	return bmp_output;
}

#pragma endregion