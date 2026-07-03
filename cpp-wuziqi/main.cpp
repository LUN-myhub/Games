#include <stdio.h>
#include <math.h>
#include <graphics.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")//多媒体音频接口

int flag = 0;//标记 黑与白
int ChessMap[20][20] = { 0 };//记录棋盘棋子的数组

//初始化游戏
void initGame()
{
	//1.创建界面
	initgraph(600, 500);
	//2.插入图片
	loadimage(NULL, "fy.jpg");
	//3.绘制棋盘
	setlinecolor(BLACK);
	for (int i=1; i < 20; i++) {
		line(0, i*25, 500, i*25);
		line(i * 25, 0, i * 25, 500);
	}
	setlinestyle(PS_SOLID, 2);
	line(500, 0, 500, 500);//边界线


	//4.设置背景模式：0 透明
	setbkmode(0);
	//5.设置文字颜色
	settextcolor(RED);
	//6.插入文字
	outtextxy(505, 50, "玩家1：黑棋");
	outtextxy(505, 100, "玩家2：白棋");

}
//游戏的判断
int judge(int MapX, int MapY) {
	int temp = 2 - flag % 2;//2-0 2-1
	//判断竖是否连接在一起
	for (int i = MapX - 4, j = MapY; i <= MapX; i++) {
		if (i >= 1 && i < 16 && temp == ChessMap[i][j] && temp == ChessMap[i + 1][j] && temp == ChessMap[i + 2][j] && temp == ChessMap[i + 3][j] && temp == ChessMap[i + 4][j])
		
		return 1;
	}
	//判断横是否连接在一起
	for (int i = MapX, j = MapY-4; j <= MapY; j++) {
		if (j >= 1 && j< 16 && temp == ChessMap[i][j] && temp == ChessMap[i ][j+1] && temp == ChessMap[i][j+2] && temp == ChessMap[i ][j + 3] && temp == ChessMap[i][j + 4])

			return 1;
	}
	//判断左斜是否连接在一起
	for (int i = MapX+4, j = MapY - 4; i>=MapX,j <= MapY; i--,j++) {
		if (j >= 1&&i>=1 && i<16&&j < 16 && temp == ChessMap[i][j] && temp == ChessMap[i-1][j + 1] && temp == ChessMap[i-2][j + 2] && temp == ChessMap[i-3][j + 3] && temp == ChessMap[i-4][j + 4])

			return 1;
	}
	//判断右斜是否连接在一起
	for (int i = MapX - 4, j = MapY - 4; i <= MapX, j <= MapY; i++, j++) {
		if (j >= 1 && i >= 1 && i < 16 && j < 16 && temp == ChessMap[i][j] && temp == ChessMap[i + 1][j + 1] && temp == ChessMap[i + 2][j + 2] && temp == ChessMap[i + 3][j + 3] && temp == ChessMap[i + 4][j + 4])

			return 1;
	}

	return 0;
}






//开始游戏
void playGame() {
	int ChessX = 0, ChessY = 0;//记录棋子的坐标
	int MapX = 0, MapY = 0;//记录棋盘地图的下标
	//定义变量存储鼠标消息
	MOUSEMSG Msg;

	HWND hwnd = GetHWnd();//获取窗口句柄

	while (1) {
		//获取鼠标消息
		Msg = GetMouseMsg();
		//计算优化鼠标的位置 在线条交汇的点位上
		for (int i = 1; i < 20; i++) {
			for (int j = 1; j < 20; j++) {
				if (abs(Msg.x - j * 25) < 12 && abs(Msg.y - i * 25) < 12) {
					ChessX = j * 25;
					ChessY = i * 25;
					MapX = i;
					MapY = j;
				}
			}
		}
		//printf("ChessX:%d,ChessY:%d\n", ChessX, ChessY);
		if (Msg.uMsg == WM_LBUTTONDOWN) {
			if (ChessMap[MapX][MapY] != 0) {
				MessageBox(hwnd, "这里有棋子了", "五子棋", MB_OK);
				continue;
			}


			if (flag % 2 == 0) {
				setfillcolor(BLACK);//设置填充颜色为黑色
				//画圆
				solidcircle(ChessX, ChessY, 10);
				ChessMap[MapX][MapY] = 1;//黑色的棋子 标记为1
			}
			else {
				setfillcolor(WHITE);//设置填充颜色为白色
				//画圆
				solidcircle(ChessX, ChessY, 10);
				ChessMap[MapX][MapY] = 2;//白色的棋子 标记为2

			}
			flag++;//改变角色
		}
		if (judge(MapX, MapY)) {
			if (1 == flag % 2) {
				MessageBox(hwnd, "玩家1：黑棋胜利", "Game Over", MB_OK);
				return;
			}
			else {
				MessageBox(hwnd, "玩家2：白棋胜利", "Game Over", MB_OK);
				return;
			}
		}
		

	}
}

int main()
{
	mciSendString("play music.mp3", 0, 0, 0);

	initGame();
	playGame();


	//卡屏
	//getchar();
	//关闭界面
	closegraph();
	return 0;
}




/*

	//创建界面 宽度 高度 PX 像素
	initgraph(600,500);
	//加载过程中如果没有指定加载的变量 默认加载到界面
	loadimage(NULL, "fy.jpg");
	//设置线条颜色
	setlinecolor(BLACK);
	for (int i = 0; i <=20; i++) {
		//画线 X1,Y1点1		X2,Y2点2	500*500棋盘 25 20*20格子的棋盘
		line(0, i * 25, 500, i * 25);
		line(i*25, 0, i*25, 500);
	}
	/ 1、定义变量
	IMAGE img;
	//2、加载图片
	loadimage(&img, "fy.jpg");
	//贴图	X,Y就是图片显示界面的位置 显示的图片变量
	putimage(0, 0, &img);


 贴图三部曲：
				定义变量	int val;		IMAGE img;存储图片
				赋值		scanf("%d",&val);
				显示输出	printf("%d",val);
		

	//插入文字
		// 设置背景模式：0 透明
		setbkmode(0);
	// 1.设置文字颜色
	settextcolor(BLACK);
	//根据坐标插入文字  X,Y就是文字显示的坐标
	outtextxy(505, 50, "玩家1：黑棋");
	outtextxy(505, 100, "玩家2：白棋");
*/

/* //定义变量存储鼠标消息
	MOUSEMSG Msg;
	
	while (1) {
		Msg = GetMouseMsg();//获取鼠标消息
		/*if (Msg.uMsg == WM_LBUTTONDOWN) {//左键
			printf("X:%d Y:%d\n",Msg.x,Msg.y);
		}
		else if (Msg.uMsg == WM_RBUTTONDOWN) {//右键
			printf("X:%d Y:%d\n", Msg.x, Msg.y);
		}
		

int ChessX = 0, ChessY = 0;

for (int i = 1; i < 20; i++) {
	for (int j = 1; j < 20; j++) {
		if (abs(Msg.x - j * 25) < 12.5 && abs(Msg.y - i * 25) < 12.5) {
			ChessX = j * 25;
			ChessY = i * 25;
		}
	}
}
printf("ChessX=%d,ChessY=%d\n", ChessX, ChessY);

if (Msg.uMsg == WM_LBUTTONDOWN) {//判断是否点击了鼠标左键
	//画圆 X,Y,半径
	solidcircle(ChessX, ChessY, 10);
}

	}
*/
