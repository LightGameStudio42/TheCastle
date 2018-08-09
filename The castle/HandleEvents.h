#pragma once
#include"Engine.h"
RenderManager mRenderManager;
using namespace sf;

int yMouse;
int xMouse;
void keyboardHandler(sf::Event event)
{
	if (event.key.code == Keyboard::Tab) (isShowQuest == true) ? isShowQuest = false : isShowQuest = true;
}
bool CheckMouseCollide(IntRect rect)
{
	if (rect.contains(xMouse, yMouse)) return true;
	return false;
} 
//hell
void mouseHandler(sf::Event event)
{
	 yMouse = event.mouseButton.y;
	 xMouse = event.mouseButton.x;
	if (event.key.code == Mouse::Right)
	{
		if (IsShowProfile) {
			if (CheckMouseCollide( IntRect(456, 300, 270, 37)))
			{
				unint tmpSlotX = (event.mouseButton.x - 450) / 40;
				for (int i = 0; i < inventory.size(); i++)
				{
					if (inventory[i].slot == tmpSlotX)//finding an empty slot
					{
						for (int j = 0; j <= 4; j++)
						{
							if (craftSlots[j].ID == inventory[i].ID && inventory[i].count > 0)
							{
								inventory[i].count--;
								craftSlots[j].count++;
								craft_1(craftSlots[j]);
								break;
							}


							else	 if (craftSlots[j].count == 0 && inventory[i].count > 0) {
								craftSlots[j].count++;
								craftSlots[j].ID = inventory[i].ID;
								inventory[i].count--;
								craft_1(craftSlots[j]);
								break;
							}
						}
					}
				}
			}
			else if (CheckMouseCollide( IntRect(456, 352, 308, 213)))
			{
				unint tmpSlotX = (event.mouseButton.x - 450) / 40;
				unint tmpSlotY = (event.mouseButton.y - 352) / 39;
				for (int i = 0; i < inventory.size(); i++)
				{
					if (inventory[i].slot == 7 + tmpSlotX + (tmpSlotY * 8))//finding an empty slot
					{
						for (int j = 0; j <= 4; j++)
						{
							if (craftSlots[j].ID == inventory[i].ID && inventory[i].count > 0)
							{
								inventory[i].count--;
								craftSlots[j].count++;
								craft_1(craftSlots[j]);
								break;
							}
							else	 if (craftSlots[j].count == 0 && inventory[i].count > 0) {
								craftSlots[j].count++;
								craftSlots[j].ID = inventory[i].ID;
								inventory[i].count--;
								craft_1(craftSlots[j]);
								break;
							}
						}
					}
				}
			}
		}
	}
	if (event.key.code == Mouse::Left)
	{
		if (CheckMouseCollide( IntRect(519, 665, 45, 45)))
		{
			(IsShowProfile == true) ? IsShowProfile = false : IsShowProfile = true;
		}
		if (CheckMouseCollide( IntRect(mRenderManager.mWindow.getSize().x - 0.03*mRenderManager.mWindow.getSize().x, 0, 48, 48)))
		{
			(isShowMenu == true) ? isShowMenu = false : isShowMenu = true;
		}
		if (CheckMouseCollide(IntRect(244, 654, 339, 45)))
		{
			unint tmpSlotX = (event.mouseButton.x - 244) / 40;
			if (inventory[BLUE_POTION].slot == tmpSlotX && inventory[BLUE_POTION].count>0) {
				if (player.lives + 2 <= player.maxLives) {
					beep();
					inventory[BLUE_POTION].count--;
					player.lives += 2;
				}
			}
			else if (inventory[GREEN_POTION].slot == tmpSlotX && inventory[GREEN_POTION].count>0)
			{
				if (player.lives + 11 <= player.maxLives) {
					beep();
					inventory[GREEN_POTION].count--;
					player.lives += 11;
				}
			}
			else if (inventory[PINK_POTION].slot == tmpSlotX && inventory[PINK_POTION].count>0)
			{
				if (player.lives + 6 <= player.maxLives) {
					beep();
					inventory[PINK_POTION].count--;
					player.lives += 6;
				}
			}
		}

		if (IsShowProfile)
		{
			if (CheckMouseCollide( IntRect(456, 300, 270, 40)))
			{
				idDescription = (event.mouseButton.x - 450) / 40;
			}
			else  if (CheckMouseCollide( IntRect(456, 352, 308, 213)))
			{
				unint tmpSlotX = (event.mouseButton.x - 450) / 40;
				unint tmpSlotY = (event.mouseButton.y - 352) / 39;
				unint index = 7 + tmpSlotX + 8 * tmpSlotY;

				idDescription = inventory[index].ID;
			}
			else idDescription = 222; //Nothig 
		}
	}
}