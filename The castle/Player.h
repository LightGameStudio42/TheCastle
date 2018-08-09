#pragma once
#ifndef PLAYER_H_
#define PLAYER_H_
#include"Engine.h"
using sf::Keyboard;
float frame = 0.f;
bool isAlive = true;
//// 0-leather, 1 - bronze, 2 - silver, 3 - gold, 4 - SUPER
//change it to change its sprites
int currentWeapon = 9;
int currentHelmet = 2;
int currentArmor = 2;
int currentLegs = 2;

class Player : public Person
{
public:
	float x, y, dx, dy, speed = 0;
	int  State = 0, colliderX, colliderY, Cash = 0;
	dir direction;
	Player()
	{
		direction = down;
		x = 64;
		y = 64;
		colliderX = 25;
		colliderY = 62;
		lives = 40;
		damage = 4;
		maxLives = lives;
	};
	void input()
	{
		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			direction = left; 
			speed = 0.18f;
			frame += 0.028f;
			if (frame > 5) { frame -= 5; }
		}
		else  if (Keyboard::isKeyPressed(Keyboard::D)) //бопюбн
		{
			direction = right;
			speed = 0.18f;
			frame += 0.028f;
			if (frame > 5) { frame -= 5; }
		}
		else if (Keyboard::isKeyPressed(Keyboard::W))
		{
			direction = up;
			speed = -0.15f;
			frame += 0.02f;
			if (frame > 3) { frame -= 3; }
		}
		else if (Keyboard::isKeyPressed(Keyboard::S))
		{
			direction = down;
			speed = -0.15f;
			frame += 0.02f;
			if (frame > 3) { frame -= 3; }
		};
	}
	void Update(float time)
	{
		switch (direction)
		{
		case right:  dx = speed;  dy = 0; break;
		case left:  dx = -speed;  dy = 0;   break;
		case up: dx = 0;  dy = speed;   break;
		case down:  dx = 0;  dy = -speed;   break;
		}

		x += dx*time;
		y += dy*time;
        speed = 0;
		if (x <= 2) x=2;
		if (y <= 2) y = 2;

		if (x >= 2530) x -= 3;
		if (y >= 1538) y -= 5;
	}
};
#endif // !PLAYER_H_