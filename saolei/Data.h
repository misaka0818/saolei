#pragma once
#include<vector>
#include<stdlib.h>
#include<time.h>
class Data
{
public:
	int col;
	int row;
	int num;
	int mode;
	Data(int mode);
	Data();
	std::vector<std::vector<int>> p;
	std::vector<std::vector<int>> creatmap();
};

