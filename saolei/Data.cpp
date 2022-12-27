#include "Data.h"

std::vector<std::vector<int>> Data::creatmap() {
	std::vector<std::vector<int>> arr(row, std::vector<int>(col, 0));
	p = arr;
	srand(time(NULL));
	int dir_x[8] = { 0,1,0,-1,1,1,-1,-1 };
	int dir_y[8] = { 1,0,-1,0,1,-1,1,-1 };
	for (int i = 0, cnt = 0; cnt < num; i++)
	{
		int a = rand() % (col * row);
		int x = a / col;
		int y = a % col;
		if (p[x][y] == 0)
		{
			p[x][y] = 9;
			cnt++;
		}
	}
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			int cnt = 0;
			if (p[i][j] != 9)
			{
				for (int k = 0; k < 8; k++)
				{
					if (i + dir_x[k] < 0 || i + dir_x[k] >= row || j + dir_y[k] < 0 || j + dir_y[k] >= col)
						continue;
					if (p[i + dir_x[k]][j + dir_y[k]] == 9)
						cnt++;
				}
				p[i][j] = cnt;
			}
		}
	}
	return p;
}
Data::Data(int mode) {
	Data::mode = mode;
	if (mode == 1)
	{
		col = 8;
		row = 8;
		num = 10;
	}
	if (mode == 2)
	{
		col = 16;
		row = 16;
		num = 40;
	}
	if (mode == 3)
	{
		col = 30;
		row = 16;
		num = 99;
	}
	p=creatmap();
}

Data::Data()
{
}
