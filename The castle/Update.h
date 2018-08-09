#pragma once
#ifndef UPDATE_H
#define UPDATE_H
#include"Engine.h"
#include"RenderManager.h"
void GameEngine::CheckMapCollision()
{
	for (int i = player.y / stdTileSize; i < (player.y + player.colliderY) / stdTileSize; i++)		
	{
		for (int j = player.x / stdTileSize; j < (player.x + player.colliderX) / stdTileSize; j++)
		{
			if (TileMap[i][j] == '1' || TileMap[i][j] == '0' || TileMap[i][j] == 'w' || TileMap[i][j] == 'f' || TileMap[i][j] == 'r' || TileMap[i][j] == 'l')//Rocks or Water
			{
				if (player.dy > 0)//если мы шли вниз
				{
					player.y = i * stdTileSize - player.colliderY;//смопорим Y персонажа. сначала получаем коорд квадратa на карте(стены),  вычитаем из h персонажа.
				}
				if (player.dy < 0)
				{
					player.y = i  * stdTileSize + stdTileSize;//аналогично с ходьбой вверх. dy<0,=> мы идем вверх
				}
				if (player.dx > 0)
				{
					player.x = j * stdTileSize - player.colliderX;//если идем вправо, то координата ’ = стена 0минус ширина персонажа
				}
				if (player.dx < 0)
				{
					player.x = j * stdTileSize + stdTileSize;//аналогично идем влево
				}
				if (TileMap[i][j] == 'f' || TileMap[i][j] == 'r' || TileMap[i][j] == 'l')
				{
					Coords tmpCords(i, j);
					chestCoords.push_back(tmpCords);
					isChestOpen = true;
					//if (i != chestCoords[currentChest].x && j != chestCoords[currentChest].y)
					//{
						beep();
						Chest tmpchest(BRONZE,i,j);
						chests.push_back(tmpchest);
						currentChest++;
					//}
				}
			}//Rock
			else if (TileMap[i][j] == 's')
			{
				player.Cash++;
				inventory[COIN].count++;
				TileMap[i][j] = ' ';            
			}
			else if (TileMap[i][j] == 'p')
			{
				inventory[BLUE_POTION].count++;
				TileMap[i][j] = ' ';
			}
			else if (TileMap[i][j] == 'd' || TileMap[i][j] == 'm')
			{
				if (IsCreateMonster) {
					(player.x / 64)<j ? TileMap[i][j] = 'd' : TileMap[i][j] = 'm';
					mClock.restart();
					MonsterIsLive = true;
					monster = new Monster(i, j, 4 + random(player.damage), 18 + random(player.maxLives) / 4,"Dragon");//x,y,dmg,live
					IsCreateMonster = false;
					isFight = true;
				};
			}
			else if (TileMap[i][j] == 'b' || TileMap[i][j] == 'q')
			{
				if (IsCreateMonster) {
					((player.x/64)<j ? TileMap[i][j] = 'b' : TileMap[i][j] = 'q');
					mClock.restart(); //restart the fight timer
					MonsterIsLive = true;
					monster = new Monster(i, j, random(player.damage / 2) + 2,
						8 + random(4) + CountSharkBear / 2 - (player.maxLives - player.lives) / 10,"Sharkbear");
					IsCreateMonster = false;
					isFight = true;
				}
			}
		}
	}
}
void GameEngine::Update(float time)
{
	createOrcHarpy(time);
	CheckMapCollision();
	if (isFight) { fight(time); return; }
	player.Update(time);
}
#endif