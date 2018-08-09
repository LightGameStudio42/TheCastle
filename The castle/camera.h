#ifndef CAMERA_H
#define CAMERA_H
#define Width 1024
#define Height 768 
#include<SFML\Graphics.hpp>
sf::View view;
sf::View SetCamera(int x, int y)
{
	int tempX = x; int tempY = y; //UI doesn't renders right with float

	if (x < Width / 1.999f) tempX = Width / 1.999f;
	else if (x > Width * 1.9f)tempX = Width * 1.9f;
	if (y > Height * 1.58f) tempY = Height*1.58f;
	else if (y < Height / 2) tempY = Height / 2;
	view.setCenter(tempX, tempY); 
	return view;
}
#endif