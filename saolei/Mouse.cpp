#include <graphics.h>
#include "Mouse.h"

void Mouse::getxy(int* x, int* y, ExMessage msg)
{
	*y = (msg.x) / 20;
	*x = (msg.y - 40) / 20;
}
