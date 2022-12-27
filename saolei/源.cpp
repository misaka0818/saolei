#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<vector>
#include<easyx.h>
#include<graphics.h>
#include<Windows.h>
#include<mmsystem.h>
#include"data.h"
#include "Window.h"
#pragma comment(lib, "WINMM.LIB")
using namespace std;

int main()
{
	int flag = 1;
	while (flag==1)
	{
		Window window = Window();
		if (window.mode == -1)
			return 0;
		Data data = Data(window.mode);
		Window gwindow = Window(data);
		ExMessage msg;
		while (1)
		{
			getmessage(&msg, EM_MOUSE);
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (msg.lbutton && !msg.rbutton)
				{
					gwindow.mousel(msg);

				}
			}
			else if (msg.message == WM_RBUTTONDOWN)
			{
				bool flag = false;
				while (1)
				{
					getmessage(&msg, EM_MOUSE);
					if (msg.message == WM_RBUTTONUP)
					{
						break;
					}
					else if (msg.message == WM_LBUTTONDOWN)
					{
						flag = true;
						break;
					}
				}
				if (flag)
					gwindow.mouselr(msg);
				else
					gwindow.mouser(msg);

			}
			if (gwindow.end || gwindow.vic == (data.row * data.col - data.num))
			{
				flag = gwindow.gend();
				break;
			}
		}
		if (gwindow.end)
			mciSendString(L"stop ./resource/fail.mp3", NULL, 0, NULL);
		else
			mciSendString(L"stop ./resource/victory.mp3", NULL, 0, NULL);
		closegraph();
	}
	return 0;
}