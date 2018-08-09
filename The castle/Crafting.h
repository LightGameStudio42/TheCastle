#pragma once
#ifndef CRAFTING_H_
#define CRAFTING_H_
#include"Inventory.h"
#include"Player.h"
Item craftingResult;
void  craft_1(craftSlot slot)
{
	if (slot.count == 2)
	{ 
		switch (slot.ID) 
		{
		case BRONZE:  inventory[LEATHER_HELMET].count++; craftingResult.ID = 14; craftingResult.count = 1; break;
		case SILVER:  inventory[BRONZE_HELMET].count++; craftingResult.ID = 15; craftingResult.count = 1; break;
		case GOLD:  inventory[GOLD_HELMET].count++; craftingResult.ID = 16; craftingResult.count = 1; break;
		}

	}
	else if (slot.count == 3)
	{
		switch (slot.ID)
		{
		case BRONZE:  inventory[BRONZE_ARMOR].count++; craftingResult.ID = 24; craftingResult.count = 1; break;
		case SILVER:  inventory[SILVER_ARMOR].count++; craftingResult.ID = 25; craftingResult.count = 1; break;
		case GOLD:  inventory[GOLD_ARMOR].count++; craftingResult.ID = 26; craftingResult.count = 1; break;
		}

	}
}

void craft_2(craftSlot slot0, craftSlot slot1)
{
   

};

















#endif