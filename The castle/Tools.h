#pragma once
#include<Windows.h>
#include<ctime>
#include<iostream>
enum dir { right, down, left, up };//0-RIGHT,1-LEFT,2-UP,3-DOWN
typedef unsigned int unint;
struct Coords
{
	unint x;
	unint y;
	Coords() {};
	Coords(unint mX, unint mY) { x = mX; y = mY; }
};

void beep()
{
	std::cout << "\a";
}
int random(int n)
{
	static char once_rand_init = (srand(static_cast<unsigned int> (time(0))), (void)once_rand_init, '\0');
	int i = rand() % n;
	return i;
}
float getDistance(int x, int y, int x1, int y1)
{
	return sqrt(abs(pow((x1 - x), 2) + pow((y1 - y), 2)));
}
