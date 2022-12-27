#pragma once
#include "Window.h"
#include"Data.h"
#include<graphics.h>
#include<string>
class Window
{
public:
	int imgsize = 20;
	int width;
	int heigh;
	int mode;
	int vic = 0;
	bool end = false;
	int dir_x[8] = { 0,1,0,-1,1,1,-1,-1 };
	int dir_y[8] = { 1,0,-1,0,1,-1,1,-1 };
	Data data;
	IMAGE img[12];
	std::vector<std::vector<int>> ctl;
	void creatgraph();
	Window(Data data);
	void loadimg(IMAGE img[]);
	void creatgame();
	void mousel(ExMessage msg);
	void mouser(ExMessage msg);
	void mouselr(ExMessage msg);
	void find0(int x, int y);
	int gend();
	void nums();
	Window();
};

