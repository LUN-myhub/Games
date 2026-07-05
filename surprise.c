#include <stdio.h>
#include "raylib.h"

#define MAX_POPUP 100



/*定义页面*/
enum PageID {
	Start,
	Home,
}; 
/*定义弹出窗*/
typedef struct Popup {
	Rectangle rect;			//矩形
	const char* title;		//标题
	const char* contect;	//内容
	Color color;			//颜色
	bool active;			//是否激活
}Popup;

Texture2D heartImg;

enum PageID pageid = Start;
const char* contents[] = {"Happy New Year!","All the best wishes for you!","May all your wishes come true!","Everything goes well!","Best wishes!","Happy birthday!","Wishing you a happy birthday!","Good luck to you!"};
const Color colors[] = { { 200, 200, 200, 255 },{ 130, 130, 130, 255 },{ 80, 80, 80, 255 },{ 253, 249, 0, 255 },{ 255, 203, 0, 255 },{ 255, 161, 0, 255 },{ 255, 109, 194, 255 },{ 230, 41, 55, 255},{ 190, 33, 55, 255 },{ 0, 228, 48, 255 },{ 0, 158, 47, 255 },{ 0, 117, 44, 255 },{ 102, 191, 255, 255 },{ 0, 121, 241, 255 },{ 0, 82, 172, 255 },{ 200, 122, 255, 255 },{ 135, 60, 190, 255 } };

bool drawDialog(Rectangle rect,const char*title,const char*contect) {
	//绘制标题栏 54
	DrawRectangle(rect.x, rect.y, rect.width, 54, CLITERAL(Color){243, 243, 243, 255});
	//绘制一条线
	DrawLine(rect.x, rect.y + 53, rect.x + rect.width, rect.y + 53, CLITERAL(Color){237, 237, 237, 255});
	DrawLine(rect.x, rect.y + 54, rect.x + rect.width, rect.y + 54, CLITERAL(Color){237, 237, 237, 255});

	//绘制窗口
	DrawRectangle(rect.x, rect.y+54, rect.width,rect.height-54 , WHITE);

	//绘制按钮
	Rectangle btnRect = {
	rect.x + rect.width - 18 - 57,
	rect.y + rect.height - 15 - 36,
	57,36
	};
	Color color = { 0, 120, 212, 255 };
	//判断鼠标是否在按钮上
	if (CheckCollisionPointRec(GetMousePosition(), btnRect) ){
		color = CLITERAL(Color){ 0,126,223,255 };
		//是否点击了按钮
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			return true;
		}
	}
	DrawRectangleRec(btnRect, color);



	//绘制按钮文本
	DrawText("OK", btnRect.x +(57-20)/2, btnRect.y + (36 - 20) / 2, 20, WHITE);
	//绘制正文
	DrawText(contect, rect.x + 10, rect.y + (rect.height+54) / 2-30, 20, BLACK);
	//绘制标题文本
	DrawText(title, rect.x + 30, rect.y+(53-20)/2, 20, BLACK);

	return false;
}

void popup_init(Popup* pthis) {//初始化弹出窗
	pthis->title= "tips";
	int w = 230, h = 60;
	pthis->rect = CLITERAL(Rectangle) {
		GetRandomValue(10,GetRenderWidth()-w-10),
		GetRandomValue(10,GetRenderHeight() - h-10),
		w,h
	};
	pthis->contect = contents[GetRandomValue(0, sizeof(contents) / sizeof(contents[0]) - 1)];
	pthis->color = colors[GetRandomValue(0, sizeof(colors) / sizeof(colors[0]) - 1)];

	pthis->active = false;
}
void popup_draw(Popup* pthis) {//绘画弹出窗
	if (!pthis->active) {
		return;
	}
	//绘画标题栏
	Rectangle r = pthis->rect;
	r.height = 25;
	DrawRectangleRec(r, pthis->color);
	//DrawTexture(heartImg, pthis->rect.x, pthis->rect.y, WHITE);
	float scale = 0.05f;
	DrawTextureEx(heartImg, (Vector2) { pthis->rect.x, pthis->rect.y }, 0, scale, WHITE);
	DrawText(pthis->title, pthis->rect.x + 25, pthis->rect.y + 3, 13, BLACK);

	//绘制正文
	r.y += 25;
	r.height = pthis->rect.height - r.height;
	DrawRectangleRec(r, ColorBrightness(pthis->color,0.7));
	//int tx = pthis->rect.x + (pthis->rect.width - MeasureText(pthis->contect, 10) / 2);
	int tx = r.x + 10;
	int ty = r.y+ (r.height - 10) / 2;
	DrawText(pthis->contect, tx, ty, 10, BLACK);
	//绘制阴影
	Color color = { 199,199,199,255 };
	for (int i = 0; i < 9; i++) {
		DrawRectangleRoundedLines(CLITERAL(Rectangle) { pthis->rect.x - i, pthis->rect.y - i, pthis->rect.width + i * 2, pthis->rect.height + i * 2 },0.5, 0,
			color);
		//修改颜色
		color.a = 255 - 255 / 9.f * i; 
		color.r = color.g = color.b = 199 + (255 - 199) / 9.f * i;
	}
}
int main() {
	//Windows系统微软雅黑，直接读取系统字体
	//Font font = LoadFontEx("C:/Windows/Fonts/msyh.ttc", 32, 0x4E00, 20992);
	//字体抗锯齿，消除文字抗锯齿
	//SetTextureFilter(font.texture, TEXTURE_FILTER_BILINEAR);
	SetConfigFlags(FLAG_MSAA_4X_HINT);//抗锯齿 高质量渲染
	//初始化图形窗口
	//InitWindow(1080,720,"一个神秘的礼物");
	InitWindow(1080, 720, "title");
	//设置帧率	FPS
	SetTargetFPS(60);
	//帧数
	int frameCount = 0;
	
	heartImg = LoadTexture("Resource/heart.png");

	//定义弹出窗数组
	Popup popups[MAX_POPUP];
	//初始化弹出窗
	for (int i = 0; i < MAX_POPUP; i++) {
		popup_init(popups + i);
	}
	//游戏、程序有主循环
	while (!WindowShouldClose()) {
		BeginDrawing();//开始绘图

		if (pageid == Start) {
			//ClearBackground(CLITERAL(Color){ 246, 231, 211, 255 });//用指定的颜色来清屏
			ClearBackground(CLITERAL(Color) { 141, 144, 148, 255 });//用指定的颜色来清屏

			Rectangle rect = { 0,0,520,154 };
			rect.x = (GetRenderWidth() - rect.width) / 2;
			rect.y = (GetRenderHeight() - rect.height) / 2;//获取窗口大小

			if (drawDialog(rect, "Surprise", "Please click it!")) {
				//TraceLog(LOG_INFO, "button clicked");
				pageid = Home;
			}
		}
		else{
			ClearBackground(CLITERAL(Color) { 236, 240, 246, 255 });//用指定的颜色来清屏
			//绘制所有弹出窗
			for (int i = 0; i < MAX_POPUP; i++) {
				popup_draw(popups + i);
			}
			//固定一段时间出现一个弹出窗
			if (frameCount % 30 == 0) {
				for (int i = 0; i < MAX_POPUP; i++) {
					if (popups[i].active == false) {
						popups[i].active = true;
						break;
					}
				}
			}
		}
		
		EndDrawing();//结束绘图
		frameCount++;
	}
	//释放图片
	UnloadTexture(heartImg);
	//关闭窗口
	CloseWindow();





	return 0;
}