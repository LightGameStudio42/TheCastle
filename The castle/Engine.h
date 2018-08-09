//Copyright(C) 2016-2018 LightGameStudio <theLightGameStudio@gmail.com>
#pragma once
#ifndef ENGINE
#define ENGINE
#include<SFML\Graphics.hpp>
#include<sfml\Audio.hpp>
#include<math.h>
#include<conio.h>
#include<ctime>
#include<vector>
#include"map.h"
#include"camera.h"
#include"Beings.h"
#include"Inventory.h"
#include"Player.h"
using namespace sf;
using std::vector;
typedef int timer;

sf::Clock mClock;
timer FightAction;
OrcHarpys* OrcHarpy[3];
Monster* monster;
Player player;
int tmpMonsterDamage, tmpPlayerDamage; // to rener the text of damage
int frameWeapon = 0;
vector<Coords> chestCoords;

unint CreateMonsterTimer = 0;
unint CurrentQuest = 0;
unint CountDragons = 0;
unint CountSharkBear = 0;
unint CurrentMonster = 0;

bool IsCreateMonster = true;
bool MonsterIsLive = false;
bool isFight = false;
bool Action = PLAYER_ACTION;
bool isChestOpen = false;

void getLoot()
{
	if (random(3) == 1)
	{
		inventory[BRONZE].count++;
	}
	else if (random(2) == 1)
	{
		inventory[SILVER].count++;
	}
	else if (random(3) == 1)
	{
		inventory[GOLD].count++;
	}
	if (random(2) == 1) { inventory[BLUE_POTION].count++; };
}
class GameEngine
{
public:
	GameEngine() //constuctor
	{
		createMap();
		if (currentMap != ValleyOfDeath && currentMap != HOUSE) {
		for (int k = 0; k < 35; k++)
		{
			unint x = 1 + random(23);
			unint y = 1 + random(38);
			random(2) == 0 ? TileMap[x][y] = 'b' : TileMap[x][y] = 'q';
		}
		for (int k = 0; k < 20; k++)
		{
			unint x = 1 + random(23);
			unint y = 1 + random(38);
			random(2) == 0 ? TileMap[x][y] = 'd' : TileMap[x][y] = 'm';
		}
		//fill inventory, for debug
		for (int i = 0; i <= 39; i++)
		{
			inventory[i].count = random(5) + 1;
		}

	}
//initialization items block 
		    initializate("The blue potion\n+2 hp",0);
		    initializate("The pink potion\n+6 hp", 1);
		    initializate("The green po-\ntion\n+11 hp", 2);
		    initializate("1 Coin", 3);
		    initializate("Silver ingot",37);
		    initializate("Gold ingot",38);
		    initializate("Paper",4);
		    initializate("Rope",5);
		    initializate("Branch",6);
		    initializate("Bronze ingot", BRONZE);
		    initializate("Iron ingot",8);
		    initializate("Dragon\'s blood",9);
		    initializate("SharkBear\'s\nfang",10);
		    initializate("Orcharpy\'s had",11);
		    initializate("Amanita\nmushroom",12);
		    initializate("Leather helmet", 13);
		    initializate("Bronze helmet", 14);
		    initializate("Silver helmet", 15);
		    initializate("Gold helmet", 16);
		    initializate("Super-helmet", 17);

		    initializate("Leather greave", 18);
		    initializate("Bronze greave", 19);
		    initializate("Silver greave", 20);
		    initializate("Gold greave", 21);
		    initializate("Super-greave", 22);

		    initializate("Leather armor", 23);
		    initializate("Bronze armor", 24);
		    initializate("Silver armor", 25);
		    initializate("Gold armor", 26);
		    initializate("Super-armor", 27);

			initializate("Hook", 28);
			initializate("Kama sickle", 29);
			initializate("Tanto", 30);
			initializate("Ax", 31);
			initializate("Sword", 32);
		    initializate("Mace", 33);

			initializate("Saber", 34);
			initializate("Labrys", 35);
			initializate("Hammer", 36);
			initializate("Super-hammer", 37);
			initializate("Aluminium ingot", 38);
			initializate("Gold ingot", 39);
	}
	void CheckMapCollision();
	void Update(float time);
};
void fight(float time)
{
	FightAction = int(mClock.getElapsedTime().asSeconds());
	if (Action == PLAYER_ACTION)
	{
		if (FightAction > 20) Action=DRAGON_ACTION;
		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			if (frameWeapon <= 3) {frameWeapon++;}
			else frameWeapon = 0;
			//frameWeapon = 1;

			int tmpdmg= random(player.damage);
			monster->lives -= tmpdmg;
			tmpPlayerDamage = -1 * tmpdmg;
			Action = DRAGON_ACTION;
			//std::cout << std::endl << monster->x;
			//std::cout << std::endl << monster->y;
			if (monster->lives <= 0)
			{
				isFight = false;
				MonsterIsLive = false;
				IsCreateMonster = true;
				getLoot();
				(strcmp("Sharkbear", monster->getName().c_str())) ? CountDragons++ : CountSharkBear++;
				TileMap[monster->x][monster->y] = '0';
				if (random(3) == 1)  TileMap[monster->x][monster->y] = '1';
				else TileMap[monster->x][monster->y] = ' ';
				delete monster;
			}
		}
	}
	else if (Action == DRAGON_ACTION)
	{
		mClock.restart();
		int Damage = random(monster->damage) + 1;
		Sleep(100); //coroutine
		player.lives -= Damage;
		tmpMonsterDamage = -1 * Damage;
		Action = PLAYER_ACTION;
		if (player.lives <= 0) { player.lives = 0; isAlive = false; }
	}
}
void createOrcHarpy(float time)
{
	CreateMonsterTimer += time;
	if (CreateMonsterTimer > 9000 && CurrentMonster <= 3)
	{
		OrcHarpy[CurrentMonster] = new OrcHarpys(random(300) + 64, random(200) + 64, 2, 2);
		CreateMonsterTimer = 0;
		CurrentMonster++;
	}
	if (CreateMonsterTimer % 20 == 0) {
		for (int i = 0; i < CurrentMonster; i++) OrcHarpy[i]->Update(time);
		if (CreateMonsterTimer % 800 == 0)
		{
			for (int i = 0; i < CurrentMonster; i++) OrcHarpy[i]->changeDirection();
		}
	}
}
#endif