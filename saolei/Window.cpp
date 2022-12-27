#include "Window.h"
#include"Data.h"
#include<graphics.h>
#include<string>
#include"Mouse.h"
Mouse mouse;
void Window::creatgraph() {
	initgraph(width, heigh);
	mciSendString(L"open ./resource/ing.mp3", NULL, 0, NULL);
	mciSendString(L"play ./resource/ing.mp3 repeat", NULL, 0, NULL);
	setbkcolor(WHITE);
	cleardevice();
}
void Window::creatgame() {
	
	loadimg(img);
	IMAGE a;
	nums();
	for (int i = 0; i < data.row; i++)
	{
		for (int j = 0; j < data.col; j++)
		{
			putimage(j * 20, i * 20 + 40, &img[10]);
		}
	}
	
}
void Window::mousel(ExMessage msg)
{
	int x, y;
	mouse.getxy(&x, &y, msg);
	if (ctl[x][y] == 0)
	{
		
		if (data.p[x][y] == 9)
		{
			putimage(y * 20, x * 20 + 40, &img[data.p[x][y]]);
			end = true;
		}
		else if (data.p[x][y] == 0)
		{
			find0(x, y);
		}
		else
		{
			putimage(y * 20, x * 20 + 40, &img[data.p[x][y]]);
			ctl[x][y] = 1;
			vic++;
		}
	}
}
void Window::mouser(ExMessage msg)
{
	int x, y;
	mouse.getxy(&x, &y, msg);
	if (ctl[x][y] == 0)
	{
		putimage(y * 20, x * 20 + 40, &img[11]);
		ctl[x][y] = 2;
		data.num--;
		nums();
	}
	else if (ctl[x][y] == 2)
	{
		putimage(y * 20, x * 20 + 40, &img[10]);
		ctl[x][y] = 0;
		data.num++;
		nums();
	}
}
void Window::mouselr(ExMessage msg)
{
	int x, y;
	mouse.getxy(&x, &y, msg);
	if (ctl[x][y] == 1)
	{
		if (data.p[x][y] != 0)
		{
			int cnt = 0;
			for (int i = 0; i < 8; i++)
			{
				if (x + dir_x[i] < 0 || x + dir_x[i] >= data.row || y + dir_y[i] < 0 || y + dir_y[i] >= data.col)
					continue;
				if (ctl[x + dir_x[i]][y + dir_y[i]] == 1 || ctl[x + dir_x[i]][y + dir_y[i]] == 0)
					continue;
				if (ctl[x + dir_x[i]][y + dir_y[i]] == 2)
				{
					cnt++;
				}
			}
			if (cnt == data.p[x][y])
			{
				for (int i = 0; i < 8; i++)
				{
					if (x + dir_x[i] < 0 || x + dir_x[i] >= data.row || y + dir_y[i] < 0 || y + dir_y[i] >= data.col)
						continue;
					if (ctl[x + dir_x[i]][y + dir_y[i]] == 1 || ctl[x + dir_x[i]][y + dir_y[i]] == 2)
						continue;
					if (ctl[x + dir_x[i]][y + dir_y[i]] == 0)
					{
						
						if (data.p[x + dir_x[i]][y + dir_y[i]] == 9)
						{
							putimage((y + dir_y[i]) * 20, (x + dir_x[i]) * 20 + 40, &img[data.p[x + dir_x[i]][y + dir_y[i]]]);
							end = true;
						}
						else if (data.p[x + dir_x[i]][y + dir_y[i]] == 0)
							find0(x + dir_x[i], y + dir_y[i]);
						else
						{
							putimage((y + dir_y[i]) * 20, (x + dir_x[i]) * 20 + 40, &img[data.p[x + dir_x[i]][y + dir_y[i]]]);
							ctl[x + dir_x[i]][y + dir_y[i]] = 1;
							vic++;
						}
					}
				}
			}
		}
	}
}
void Window::find0(int x, int y)
{
	if (ctl[x][y] == 1 || data.p[x][y] != 0 || ctl[x][y] == 2)
	{
		if (data.p[x][y] < 9 && ctl[x][y] == 0)
		{
			putimage(y * 20, x * 20 + 40, &img[data.p[x][y]]);
			ctl[x][y] = 1;
			vic++;
		}
		return;
	}
	if (ctl[x][y] == 0 && data.p[x][y] == 0)
	{
		putimage(y * 20, x * 20 + 40, &img[0]);
		ctl[x][y] = 1;
		vic++;
	}
	
	if (x - 1 >= 0)
		find0(x - 1, y);
	if (x + 1 < data.row)
		find0(x + 1, y);
	if (y - 1 > 0)
		find0(x, y - 1);
	if (y + 1 < data.col)
		find0(x, y + 1);

}
int Window::gend()
{
	mciSendString(L"stop ./resource/ing.mp3", NULL, 0, NULL);
	cleardevice();
	if (!end)
	{
		mciSendString(L"open ./resource/victory.mp3", NULL, 0, NULL);
		mciSendString(L"play ./resource/victory.mp3 repeat", NULL, 0, NULL);
		outtextxy(data.col * 10 - 40, 15, L"winwinwin!");
	}
	else
	{
		mciSendString(L"open ./resource/fail.mp3", NULL, 0, NULL);
		mciSendString(L"play ./resource/fail.mp3 repeat", NULL, 0, NULL);
		outtextxy(data.col * 10 - 40, 15, L"就这就这？");
	}
	setfillcolor(LIGHTGRAY);
	setbkmode(TRANSPARENT);
	fillrectangle(data.col * 10 - 45, 55, data.col * 10 + 30, 82);
	fillrectangle(data.col * 10 - 45, 105, data.col * 10 + 30, 132);
	outtextxy(data.col * 10 - 40, 60, L"再来一局");
	outtextxy(data.col * 10 - 23, 110, L"退出");
	while (1)
	{
		ExMessage msg;
		getmessage(&msg, EM_MOUSE);
		if (msg.message == WM_LBUTTONDOWN)
		{
			fillrectangle(data.col * 10 - 45, 55, data.col * 10 + 30, 82);
			fillrectangle(data.col * 10 - 45, 105, data.col * 10 + 30, 132);
			if (msg.x >= data.col * 10 - 45 && msg.x <= data.col * 10 + 30 && msg.y >= 55 && msg.y <= 82)
			{
				return 1;
				break;
			}
			if (msg.x >= data.col * 10 - 45 && msg.x <= data.col * 10 + 30 && msg.y >= 105 && msg.y <= 132)
			{
				return 0;
				break;
			}
		}
	}
}
void Window::loadimg(IMAGE img[]) {
	loadimage(&img[0], L"./resource/0.jpg", imgsize, imgsize);
	loadimage(&img[1], L"./resource/1.jpg", imgsize, imgsize);
	loadimage(&img[2], L"./resource/2.jpg", imgsize, imgsize);
	loadimage(&img[3], L"./resource/3.jpg", imgsize, imgsize);
	loadimage(&img[4], L"./resource/4.jpg", imgsize, imgsize);
	loadimage(&img[5], L"./resource/5.jpg", imgsize, imgsize);
	loadimage(&img[6], L"./resource/6.jpg", imgsize, imgsize);
	loadimage(&img[7], L"./resource/7.jpg", imgsize, imgsize);
	loadimage(&img[8], L"./resource/8.jpg", imgsize, imgsize);
	loadimage(&img[9], L"./resource/9.jpg", imgsize, imgsize);
	loadimage(&img[10], L"./resource/10.jpg", imgsize, imgsize);
	loadimage(&img[11], L"./resource/11.jpg", imgsize, imgsize);
}
Window::Window(Data data)
{
	if (data.mode == 1)
	{
		width = 160;
		heigh = 200;
	}
	if (data.mode == 2)
	{
		width = 320;
		heigh = 360;
	}
	if (data.mode == 3)
	{
		width = 600;
		heigh = 360;
	}
	this->data = data;
	std::vector<std::vector<int>> a(data.row, std::vector<int>(data.col, 0));
	this->ctl = a;
	creatgraph();
	creatgame();
}
void Window::nums()
{
	clearrectangle(0, 0, data.col*20, 40);
	wchar_t s[8] = L"剩余数量:";
	wchar_t s2[3];
	_itow_s(data.num, s2, 10);
	_tcscat_s(s, s2);
	settextcolor(BLACK);
	outtextxy(data.col*10-40, 15, s);
}
Window::Window() {
	mciSendString(L"open ./resource/start.mp3", NULL, 0, NULL);
	mciSendString(L"play ./resource/start.mp3 repeat", NULL, 0, NULL);  
	initgraph(200, 200);
	setbkcolor(WHITE);
	cleardevice();
	setlinecolor(BLACK);
	setbkmode(TRANSPARENT);
	setfillcolor(LIGHTGRAY);
	fillrectangle(55, 8, 145, 48);
	fillrectangle(55, 56, 145, 96);
	fillrectangle(55, 104, 145, 144);
	fillrectangle(55, 152, 145, 192);
	settextcolor(BLACK);
	outtextxy(60, 19, L"难度：新手");
	outtextxy(60, 67, L"难度：一般");
	outtextxy(60, 115, L"难度：困难");
	outtextxy(68, 162, L"退出游戏");
	ExMessage msg;
	while (1)
	{
		peekmessage(&msg, EM_MOUSE);
		if (msg.message != WM_LBUTTONDOWN)
			continue;
		if (msg.x >= 55 && msg.x <= 145 && msg.y >= 8 && msg.y <= 48)
		{
			mode = 1;
			break;
		}
		if (msg.x >= 55 && msg.x <= 145 && msg.y >= 56 && msg.y <= 96)
		{
			mode = 2;
			break;
		}
		if (msg.x >= 55 && msg.x <= 145 && msg.y >= 104 && msg.y <= 144)
		{
			mode = 3;
			break;
		}
		if (msg.x >= 55 && msg.x <= 145 && msg.y >= 152 && msg.y <= 192)
		{
			mode = -1;
			break;
		}
	}
	mciSendString(L"stop ./resource/start.mp3", NULL, 0, NULL);
	closegraph();
}