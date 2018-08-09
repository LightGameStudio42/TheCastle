#include <SFML\Graphics.hpp>
#include"Tools.h"
#ifndef MAP_H
#define MAP_H
int HEIGHT_MAP = 25;
int WIDTH_MAP = 40;
#define stdTileSize 64//Textre size
///////////////////////////
enum mapTypes { GREEN, DESERT, CASTLE, ValleyOfDeath, HOUSE };
mapTypes currentMap = GREEN;
///////////////////////////
/*
*0- Rock
*i- Rock
*w - Water
*p- potion
*s - money
f/r/l - chest
*IsCreateMonster- sharkbear
*/
sf::String *TileMap=new sf::String[HEIGHT_MAP];
void createMap()
{
	for (size_t i = 0; i < HEIGHT_MAP; i++)
	{
		TileMap[i] = "                                        ";
	}
	if (currentMap == GREEN) {
		for (int i = 2; i <= HEIGHT_MAP - 2; i++)
		{
			for (int j = 2; j <= WIDTH_MAP - 2; j++)
			{
				if (random(15) == 1) { TileMap[i][j] = 's'; }
				else if (random(18) == 1)
				{
					if (random(2) == 1) { TileMap[i][j] = '0'; }
					else { TileMap[i][j] = '1'; }
					if (random(15)) { TileMap[i][j + 1] = '1'; }
				}
				else if (random(99) == 1) { TileMap[i][j] = 'p'; }
				else if (random(50) == 1)
				{
					TileMap[i][j] = 'w';
					if (random(2)) {
						TileMap[i][j + 1] = 'w';
						if (random(3))TileMap[i + 1][j] = 'w';
						if (random(2)) TileMap[i + 1][j + 1] = 'w';
						if (random(2)) TileMap[i - 1][j + 1] = 'w';
					}
					else	if (random(33) == 1 && i < (HEIGHT_MAP + 3) && j < (WIDTH_MAP + 3))
					{
						TileMap[i][j + 1] = 'w';
						TileMap[i + 1][j] = 'w';
						TileMap[i + 1][j + 1] = 'w';
					TileMap[i + 2][j + 2] = '0'; 
						TileMap[i - 1][j - 1] = '0';
						TileMap[i + 1][j + 2] = '0';
						TileMap[i + 2][j + 1] = '0';
					}
				}
			}

		}
		TileMap[5][3] = 'f';
		TileMap[6][3] = 'r';
		TileMap[7][3] = 'l'; \
	}
	else if (currentMap == DESERT)
	{
		for (int i = 2; i <= HEIGHT_MAP - 2; i++)
		{
			for (int j = 2; j <= WIDTH_MAP - 2; j++)
			{
				if (random(35) == 1) { TileMap[i][j] = 's'; }
				else if (random(18) == 1)
				{
					if (random(20) == 1) { TileMap[i][j] = '0'; }
					else { TileMap[i][j] = '1'; }
					if (random(15)) { TileMap[i][j + 1] = '1'; }
				}
				else if (random(99) == 1) { TileMap[i][j] = 'p'; }
				else if (random(50) == 1)
				{
					TileMap[i][j] = 'w';
					if (random(2)) {
						TileMap[i][j + 1] = 'w';
					}
				}
			}

		}
	}
	else if (currentMap == ValleyOfDeath)
	{
		for (int i = 2; i <= HEIGHT_MAP - 2; i++)
		{
			for (int j = 2; j <= WIDTH_MAP - 2; j++)
			{
				if(j%2==0) TileMap[i][j] = '0';
				else if (random(68) == 1) TileMap[i][j] = 'w';
			}

		}
	}
	else if (currentMap == HOUSE)
	{
		delete[]TileMap; //???
		HEIGHT_MAP = 17;
		sf::String *TileMap = new sf::String[HEIGHT_MAP];
		for (size_t i = 0; i < HEIGHT_MAP; i++)
		{
			TileMap[i] = "      ";
		}
	}
}
#endif