#ifndef BEINGS_H
#define BEINGS_H
#include"Tools.h"
using sf::Text;

class Person
{
public:
	int x, y;
	int lives, damage, maxLives;
	virtual void Update() {};
};
class Monster :public Person
{
private:
	std::string mName;
public:
	dir direction;
	Monster() {};
	Monster(int X, int Y, int dmg, int L, std::string name)
	{
		maxLives = L; x = X, y = Y, damage = dmg, lives = L, mName = name; 
        
	};
	std::string getName() const
	{
		return mName;
    }
};
class OrcHarpys : public Monster
{
public:
	float dx, dy,angle, speed = 0;
	int direction;
	OrcHarpys() {};
	OrcHarpys(int X_, int Y, int D, int L)
	{
		x = X_, y = Y, damage = D, lives = L; direction=1;
	};
	void Update(float time)
	{
		switch (direction) {
		case 0:angle += time*3.2f; x -= (random(9));  break;
		case 1:angle -= time* 3.2f; x += (random(9));  break;
		case 2:angle += time* 3.2f; y -= (random(9)); break;
		case 3:angle -= time* 3.2f; y += (random(9)); break;
		}
			if (x <= 0) x +=10;
			else if (x >= 1024) x = 1022;
			if (y <= 0) y += 10;
			else if (y >= 762) y = 760;
	}
    inline	void changeDirection()
	{
		direction = random(4);
	}
};
#endif