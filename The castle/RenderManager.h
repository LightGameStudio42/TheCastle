#ifndef RENDER_MANAGER
#define RENDER_MANAGER
#include<SFML\Graphics.hpp>
#include<vector>
#include"Engine.h"
#include"Beings.h"
#include"TextNode.h"
#include<conio.h>
#include"Inventory.h"
#include"ObjectHolder.h"
#include"Crafting.h"
#pragma once
#pragma warning(disable : 4996)

using std::endl;
using std::cout;
using std::to_string;
ObjectHolders ObjectHolder;
RectangleShape LifeBar;
RectangleShape MonsterLifeBar;
unint idDescription = 222;//empty


bool isShowMenu = false;
bool isShowSettings = false;
bool isShowQuest = true;
bool IsShowProfile = false;

class RenderManager
{
public:
	RenderWindow mWindow;
	TextNode textCash;
	TextNode playerHealth;
	TextNode monsterHealth;
	TextNode IventoryItems;
	TextNode textDamage;
	TextNode timeLeft;
	TextNode textQuest;
	TextNode textDescription;
	TextNode chestItems;
	RenderManager() :
		//textCash(31, "Candarab"),  //size, fontName.ttf
		//playerHealth(28, "Candarab"),
	 //   monsterHealth(28, "Candarab"),
		//IventoryItems(11,"Monaco"),
	 //   textDamage(24, "ahronbd"),
		//timeLeft(40, "Candarab"),
		//textQuest(23,"britannicBold"), 
		//textDescription(20, "Candarab"), 
		//chestItems(11, "Monaco"),

		textCash(31, "LuckiestGuy"),  //size, fontName.ttf
		playerHealth(28, "LuckiestGuy"),
		monsterHealth(28, "LuckiestGuy"),
		IventoryItems(11, "LuckiestGuy"),
		textDamage(24, "LuckiestGuy"),
		timeLeft(40, "LuckiestGuy"),
		textQuest(23, "LuckiestGuy"),
		textDescription(20, "LuckiestGuy"),
		chestItems(11, "LuckiestGuy"),

		mWindow(sf::VideoMode(933.3, 700), "The Castle by Light Game Studio")
	{
		mWindow.setPosition(Vector2i(200, 0));
		//Tilesets
		ObjectHolder.add(eProfile, "Profile"); //fileName.png
		ObjectHolder.add(eOrcHarpy, "OrcHarpy");
		ObjectHolder.add(eMap, "Map");
		ObjectHolder.add(eQuest, "Quests");
		ObjectHolder.add(eMenu, "Menu");
		ObjectHolder.add(eKnight, "knight");

		textCash.mText.setStyle(Text::Bold);
		textCash.mText.setColor(Color::Color(20, 0, 0));

		playerHealth.mText.setStyle(Text::StrikeThrough);
		monsterHealth.mText.setStyle(Text::StrikeThrough);

		IventoryItems.mText.setColor(Color(255, 255, 255, 160));
		chestItems.mText.setColor(Color(255, 255, 255, 160));



		LifeBar.setFillColor(Color::Color(166, 13, 13));
		textQuest.mText.setStyle(Text::Regular);

		textDescription.mText.setStyle(Text::Regular);


		for (int i = 0; i <= 4; i++)
		{
			ObjectHolder.mSprites[i].setTexture(ObjectHolder.mTextures[i]);
		}
	}

	unint FPS = 0; 
	void showFPS()
	{
		if (mClock.getElapsedTime().asSeconds() >= 1)
		{
			cout << "FPS: " << FPS << endl;
			FPS = 0;
			mClock.restart();
		}
		else { FPS++; }
	}
    void renderWithPositionRect(unint ID, int x, int y, IntRect rect)
	{
		ObjectHolder.mSprites[ID].setPosition(x, y);
		ObjectHolder.mSprites[ID].setTextureRect(rect);
		mWindow.draw(ObjectHolder.mSprites[ID]);
	}

	void renderWithPositionRectFromCenter(unint ID, int x, int y, IntRect rect)
	{
		ObjectHolder.mSprites[ID].setPosition(view.getCenter().x+x, view.getCenter().y+y);
		ObjectHolder.mSprites[ID].setTextureRect(rect);
		mWindow.draw(ObjectHolder.mSprites[ID]);
	}

	void renderTextWithPosition(TextNode &mTextNode, string text, int x, int y)
	{
		mTextNode.mText.setPosition(x, y);
		mTextNode.mText.setString(text);
		mWindow.draw(mTextNode.mText);
	}

	void render()
	{
	//showFPS();
		//cout << endl << view.getCenter().y;
		//cout << endl << view.getCenter().x;

		mWindow.clear();
		MapRender();
		KnightRender();
		OrcHarpyRender();
		InventoryRender();
		if (isFight) fightRender();
		if (isShowQuest) QuestRender();
		//////////////////////////////////////////////////////////////////////////
		renderWithPositionRectFromCenter(eMenu, + 485,- 384, IntRect(0, 0, 35, 48));
		if (isShowMenu)
		{
			renderWithPositionRect(eMenu, view.getCenter().x + 240, view.getCenter().y - 390, IntRect(0, 432, 245, 134));
			if (isShowSettings)
			{
				//renderWithPositionRect(eMenu, view.getCenter().x - 7, view.getCenter().y - 310, IntRect(245, 432, 280, 134));//316 350
				renderWithPositionRectFromCenter(eMenu, -7, -310, IntRect(245, 432, 280, 134));
			}
		}
		TextRender();
		if (IsShowProfile) ProfileRender();
		if (isChestOpen) chestRender();
		if (!isAlive)
		{
			renderWithPositionRect(eMenu, view.getCenter().x - 260, view.getCenter().y - 220, IntRect(48, 0, 576, 432));
		}
		mWindow.display();
	}
private:
	inline void ProfileRender()
	{
		////Rendering background
		renderWithPositionRectFromCenter(eProfile, -400, -250, IntRect(0, 43, 760, 495));
		////Slots render
		int currentSlot = 0;
		int i = 0;
		while (currentSlot != 7) {
			if (inventory[i].count >= 1)
			{
				inventory[i].slot = currentSlot;

				renderWithPositionRectFromCenter(eProfile,-12 + (currentSlot * 42), -57,IntRect(0 + (i * 41), 0, 41, 41));

				renderTextWithPosition(IventoryItems, to_string(inventory[i].count), view.getCenter().x + 21 + (currentSlot * 42), view.getCenter().y - 57);
				currentSlot++;
			}
			i++;
		}

		int j = 7;
		for (int p = 0; p <= 4; p++)
		{
			i = j;
			j = 7 + p * 8;
			currentSlot = 0;
			while (j != i + 8)
			{
				if (inventory[j].count >= 1)
				{
					renderWithPositionRect(eProfile,
						view.getCenter().x - 12 + (currentSlot * 42), view.getCenter().y + 2 + 42 * p,
						IntRect((j * 41), 0, 41, 41)
					);

					IventoryItems.mText.setPosition(view.getCenter().x + 20 + (currentSlot * 42), view.getCenter().y + 2 + 42 * p);
					IventoryItems.mText.setString(to_string(inventory[j].count));
					mWindow.draw(IventoryItems.mText);
					currentSlot++;
				}
				j++;
			}
		}
        ////Render the craft boxes
		//  |-|
		//  |-|
			if (craftSlots[0].count > 0)
			{

				//renderWithPositionRect(eProfile, view.getCenter().x - 12, view.getCenter().y - 210, IntRect((craftSlots[0].ID * 41), 0, 41, 41));
				renderWithPositionRectFromCenter(eProfile, -12, -210, IntRect((craftSlots[0].ID * 41), 0, 41, 41));

				IventoryItems.mText.setPosition(view.getCenter().x +23, view.getCenter().y -210);
				IventoryItems.mText.setString(to_string(craftSlots[0].count));
				mWindow.draw(IventoryItems.mText);
		}
			if (craftSlots[1].count > 0)
			{
				renderWithPositionRect(eProfile,view.getCenter().x + 43, view.getCenter().y - 210, IntRect((craftSlots[0].ID * 41), 0, 41, 41));

				IventoryItems.mText.setPosition(view.getCenter().x + 79, view.getCenter().y - 210);
				IventoryItems.mText.setString(to_string(craftSlots[1].count));
				mWindow.draw(IventoryItems.mText);
			}
			if (craftSlots[2].count > 0)
			{

				renderWithPositionRect(eProfile, view.getCenter().x - 12, view.getCenter().y - 153, IntRect((craftSlots[0].ID * 41), 0, 41, 41));//-224

				IventoryItems.mText.setPosition(view.getCenter().x + 23, view.getCenter().y - 153);
				IventoryItems.mText.setString(to_string(craftSlots[2].count));
				mWindow.draw(IventoryItems.mText);
			}
			if (craftSlots[3].count > 0)
			{
				renderWithPositionRect(eProfile, view.getCenter().x +45, view.getCenter().y - 153, IntRect((craftSlots[0].ID * 41), 0, 41, 41));//-224

				IventoryItems.mText.setPosition(view.getCenter().x + 79, view.getCenter().y - 153);
				IventoryItems.mText.setString(to_string(craftSlots[3].count));
				mWindow.draw(IventoryItems.mText);
			}
			if (craftingResult.count > 0)
			{
				renderWithPositionRect(eProfile, view.getCenter().x +122, view.getCenter().y - 182, IntRect(0 + (craftingResult.ID * 41), 0, 41, 41));//-224
			}

			if (idDescription != 222)//empty
			{
				ObjectHolder.mSprites[eProfile].setTextureRect(IntRect(760, 80, 140, 140));
				ObjectHolder.mSprites[eProfile].setPosition(view.getCenter().x+186, view.getCenter().y-220);
				mWindow.draw(ObjectHolder.mSprites[eProfile]);

				textDescription.mText.setPosition(view.getCenter().x + 190, view.getCenter().y - 220);
				textDescription.mText.setString(inventory[idDescription].description);
				mWindow.draw(textDescription.mText);
			}

			//body
			ObjectHolder.mSprites[eKnight].scale(2.0f, 2.0f);
			renderWithPositionRect(eKnight,view.getCenter().x - 225, view.getCenter().y - 76,IntRect(220 + 24 * currentArmor, 84, 24, 28));//-224
			ObjectHolder.mSprites[eKnight].scale(0.5f, 0.5f);
			//helmet
			ObjectHolder.mSprites[eKnight].scale(4.0f, 4.0f);
			renderWithPositionRect(eKnight, view.getCenter().x - 215, view.getCenter().y - 122, IntRect(185 + 7 * currentHelmet, 12, 7, 12));//-110y
			ObjectHolder.mSprites[eKnight].scale(0.25f, 0.25f);
			//legs
			ObjectHolder.mSprites[eKnight].scale(2.0f, 2.0f);
			renderWithPositionRect(eKnight, view.getCenter().x - 222, view.getCenter().y - 23, IntRect(0, currentLegs * 25, 18, 25));
			ObjectHolder.mSprites[eKnight].scale(0.5f, 0.5f);
			//Weapon
			ObjectHolder.mSprites[eKnight].scale(2.0f, 2.0f);
			renderWithPositionRect(eKnight, view.getCenter().x - 270, view.getCenter().y - 80, IntRect(186 + currentWeapon * 34, 217, 34, 34));
			ObjectHolder.mSprites[eKnight].scale(0.5f, 0.5f);

	}
	void fightRender()
	{
			renderTextWithPosition(textDamage, to_string(tmpPlayerDamage), 64 * monster->y + 26, 64 * monster->x - 26);

			renderTextWithPosition(monsterHealth, monster->getName() + "\'s health: " + to_string(monster->lives), view.getCenter().x + 240, view.getCenter().y + 330);

			//////////////////////////

			ObjectHolder.mSprites[eMenu].setPosition(monster->y * 64 + 20, monster->x * 64 - 2);
			LifeBar.setPosition((monster->y) * 64 + 20, (monster->x) * 64 - 2);
			LifeBar.setSize(Vector2f((monster->lives) * 50 / monster->maxLives, 4));

			ObjectHolder.mSprites[eMenu].setTextureRect(IntRect(0, 566, 48, 4));
			mWindow.draw(ObjectHolder.mSprites[eMenu]);

			mWindow.draw(LifeBar);

			//damage 
			renderTextWithPosition(textDamage, to_string(tmpMonsterDamage), player.x + 6, player.y - 34);


			// Time 
			timeLeft.mText.setPosition(view.getCenter().x, view.getCenter().y - 360);
			if (FightAction<10) { timeLeft.mText.setString("0:0" + to_string(FightAction)); }
			else { timeLeft.mText.setString("0:" + to_string(FightAction)); }//задаем
			mWindow.draw(timeLeft.mText);
	}
	void TextRender()
	{

		renderTextWithPosition(textCash, 
			"Cash: " + to_string(player.Cash),
			view.getCenter().x - 500, view.getCenter().y - 375
			);

		renderTextWithPosition(monsterHealth,
			"Your Health: " + to_string(player.lives),
			view.getCenter().x - 500, view.getCenter().y + 330
		);
	}
	void HeadRender()
	{

		int dx = 0;//helmet's offset
		int helmetX = 185 + (currentHelmet * 7);
		int helmetY = player.direction * 12;

		if (player.direction == right)  dx = -6;
		else if (player.direction == left)  dx = 7;

		renderWithPositionRect(eKnight, player.x + dx + 12, player.y, IntRect(helmetX, helmetY, 7, 12));
	}
	void ArmorRender()
	{
		int	 dx = 0;//armor's offset
		int armorX = 220 + (currentArmor * 24);
		int armorY = player.direction * 28;

		renderWithPositionRect(eKnight,
			player.x + 3, player.y + 12,
			IntRect(armorX, armorY, 24, 28)
		);
	}
	void LegsRender()
	{
		int offset = 0;
		switch (player.direction)
		{
		case down:ObjectHolder.mSprites[eKnight].setTextureRect(IntRect(18 * int(frame), currentLegs * 25, 18, 25)); break;
		case up:ObjectHolder.mSprites[eKnight].setTextureRect(IntRect(18 * int(frame), 125 + currentLegs * 25, 18, 25)); offset = 1; break;
		case right:ObjectHolder.mSprites[eKnight].setTextureRect(IntRect(55 + 26 * int(frame), 23 * currentLegs, 26, 23));offset = -8; break;
		case left:ObjectHolder.mSprites[eKnight].setTextureRect(IntRect(55 + 26 * int(frame), 125 + 23 * currentLegs, 26, 23));offset = 3; break;
		}

		ObjectHolder.mSprites[eKnight].setPosition(player.x + 6 + offset, player.y + 39);
		mWindow.draw(ObjectHolder.mSprites[eKnight]);
	}
	void WeaponRender()
	{
		if (player.direction != up)
		{
			//frameWeapon = 3;
			int dx = 0, dy = 0;
			switch (player.direction)
			{
			case right: dx = -15; break;
			case left:dx = -15; dy = 5; break;
			case down:dx = -7; dy = 6; break;
			}
			renderWithPositionRect(eKnight,
				player.x + 5 + dx, player.y + dy + 2,
				IntRect(186 + 34 * currentWeapon, 115 + 34 * player.direction + 34 * frameWeapon, 34, 34));
		}
	}
	void KnightRender()
	{
		ObjectHolder.mSprites[eMenu].setTextureRect(IntRect(0, 566, 48, 4));
		ObjectHolder.mSprites[eMenu].setPosition(player.x, player.y - 10);

		LifeBar.setPosition(player.x, player.y - 10);
		LifeBar.setSize(Vector2f((player.lives)*50 / player.maxLives, 4));

        mWindow.draw(ObjectHolder.mSprites[eMenu]); //Lifebar 
		mWindow.draw(LifeBar);

		LegsRender();
		if (player.direction == right)
		{
			WeaponRender();
			HeadRender();
			ArmorRender();
		}
		else
		{
			ArmorRender();
			HeadRender();
			WeaponRender();
		}
	}
	void MapRender()
	{
			int xBlockCoord = int(player.x / 64);
			int yBlockCoord = int(player.y / 64);
			//Occlusion Culling
			int minY = yBlockCoord - 5;
			if (minY <= 2) minY = 0;

			int minX = xBlockCoord - 8;
			if (minX <= 2) minX = 0;

			int tmpHeight = yBlockCoord + 12;
			if (tmpHeight >= HEIGHT_MAP) { tmpHeight = HEIGHT_MAP; minY = yBlockCoord - 11; }

			int tmpWidth = xBlockCoord + 16;
			if (tmpWidth >= WIDTH_MAP) { tmpWidth = WIDTH_MAP; minX = (WIDTH_MAP - xBlockCoord - 1); }
	if (currentMap == HOUSE) {
			 minY = 1;
			 minX = 1;
			 tmpHeight = 5;
			 tmpWidth = 5;
		}
	int SpriteMapX = 0;
		for (int i = int(minY); i < int(tmpHeight); i++) {
			for (int j = int(minX); j < int(tmpWidth); j++)	//Occlusion culling
			{  
				switch (TileMap[i][j])//the best way to render tilemap
				{
				case ' ':SpriteMapX = 0; break;
				case '0':SpriteMapX = 1; break;
				case 's':SpriteMapX = 2; break;
				case 'p':SpriteMapX = 3; break;
				case 'w':SpriteMapX = 4; break;
				case '1':SpriteMapX = 5; break;
				case 'b':SpriteMapX = 6; break;
				case 'q':SpriteMapX = 7; break;
				case 'd':SpriteMapX = 8; break;
				case 'm':SpriteMapX = 9; break;
				case 'f':SpriteMapX = 10; break; 
				case 'r':SpriteMapX = 11; break;
				case 'l':SpriteMapX = 12; break;
				default:break;
				}
				renderWithPositionRect(eMap,
					j * stdTileSize, i * stdTileSize, //position
					IntRect(SpriteMapX * stdTileSize, currentMap*stdTileSize, stdTileSize, stdTileSize)
					);
			}
		}
	}
	void InventoryRender()
	{
		renderWithPositionRectFromCenter(eProfile, - 240, 340, IntRect(387, 234, 339, 45));

		int currentSlot = 0;
		int i = 0;
		while (currentSlot != 7) 
		{
			if (inventory[i].count >= 1)
			{
				renderWithPositionRect(eProfile,
					view.getCenter().x - 238 + (currentSlot * 42), view.getCenter().y + 340,
					IntRect(i * 41, 0, 41, 41));

				renderTextWithPosition(IventoryItems,
					to_string(inventory[i].count),
					view.getCenter().x - 207 + (currentSlot * 42), view.getCenter().y + 343);

				currentSlot++;
			}
			i++;
		}
	}
	void QuestRender()
	{
		//King
		renderWithPositionRectFromCenter(eMenu,- 240,  244, //240 224
			IntRect(624, 0, 96, 96));

		switch (CurrentQuest) {
		case 0:
			if (CountSharkBear != 0){ CurrentQuest++; }
			else { textQuest.mText.setString(" Come toward \n Sharkbear\n and try to\n kill him."); } break;
		case 1:if (CountSharkBear != 0) { 
			CurrentQuest++; textQuest.mText.setString(" Well! Click to\n the potion in\n inventory,\n and heal.");
			inventory[BLUE_POTION].count = 1;
		}break;
		case 2: if (inventory[BLUE_POTION].count == 0)
		{ 
			CurrentQuest++; 
			textQuest.mText.setString(" Keep killing\n them until you \n get 3\n bronze ingots.");
		}break;
		case 3:
			if (inventory[BRONZE].count >= 3)
			{ 
				CurrentQuest++;
				textQuest.mText.setString(" Open profile,\n craft the\n bronze helmet\n use 3  bronze.");
			}break;
		case 4:
			if (inventory[BRONZE_HELMET].count>=2)
			{
				CurrentQuest++;
				textQuest.mText.setString("  Well! now try\n  to kill the\n  red Dragon.");
			}break;
			break;
		}//Switch

		renderWithPositionRect(eQuest, view.getCenter().x - 144, view.getCenter().y + 244, IntRect(0, 0, 166, 96));

		renderTextWithPosition(textQuest,
			textQuest.mText.getString(),
			view.getCenter().x - 144, view.getCenter().y + 244);
	}
	void OrcHarpyRender()
	{
		for (int i = 0; i < CurrentMonster; i++) {
			ObjectHolder.mSprites[eOrcHarpy].setRotation(OrcHarpy[i]->angle);
			renderWithPositionRect(eOrcHarpy, OrcHarpy[i]->x, OrcHarpy[i]->y, IntRect(0, 0, 45, 45));
		}
	}
	void chestRender()
	{
		if (getDistance(chestCoords[currentChest].x, chestCoords[currentChest].y, player.y / 64, player.x / 64) >= 1.4) isChestOpen = false;

		renderWithPositionRect(eProfile,
			view.getCenter().x - 200, view.getCenter().y - 100,
			IntRect(387, 294, 339, 213)
		);

		//8 items in the chest's inventory
		for (int i = 0; i < 8; i++)
		{
			renderWithPositionRect(eProfile,
				view.getCenter().x - 200 + (i * 42), view.getCenter().y - 100,
				IntRect(chests[0].items[i].ID * 41, 0, 41, 41));
			//count of current item
			renderTextWithPosition(chestItems,
				to_string(chests[0].items[i].count),
				view.getCenter().x - 166 + (i * 42), view.getCenter().y - 97
			);
		}
	}
};
#endif