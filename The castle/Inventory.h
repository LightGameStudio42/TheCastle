#pragma once
#ifndef INVENTORY_H
#define INVENTORY_H
#include<vector>
#include<string>
using std::string;
// Fight action
#define DRAGON_ACTION 0
#define PLAYER_ACTION 1
//Так удобнее
#define BLUE_POTION 0
#define PINK_POTION 1
#define GREEN_POTION 2
#define COIN 3
#define PAPER 4
#define ROPE 5
#define BRANCH 6
#define BRONZE 7
#define IRON 8
#define DRAGON_BLOOD 9
#define SHARKBEAR_FANG 10
#define ORCHARPY_HEAD 11
#define AMANITA 12

#define LEATHER_HELMET 13
#define BRONZE_HELMET 14
#define SILVER_HELMET 15
#define GOLD_HELMET 16
#define SUPER_HELMET 17

#define LEATHER_LEGS 18
#define BRONZE_LEGS 19
#define SILVER_LEGS 20
#define GOLD_LEGS 21
#define SUPER_LEGS 22

#define LEATHER_ARMOR 23
#define BRONZE_ARMOR 24
#define SILVER_ARMOR 25
#define GOLD_ARMOR 26
#define SUPER_ARMOR 27

#define HOOK 28
#define KAMA 29
#define TANTO 30
#define AX 31
#define SWORD 32
#define MACE 33
#define SABER 34
#define LABRYS 35
#define HAMMER 36
#define SUPER_HAMMER 37

#define SILVER 36
#define GOLD 35
struct Item
{
	unint count;
	unint ID;
	unint slot;
	string description;//text when item is choosen
	Item()
	{
		count = 0;
	}
	Item(unint mID, unint mCount)
	{
		ID = mID;
		count = mCount;
	}
	void initializate(string about, int id)
	{
		description = about;
		ID = id;
	}
	bool isEmpty() const
	{
		if (count < 0)  return true;
		else return false;
	}
};
std::vector<Item> inventory(50);
void initializate(string about, int id)
{
	inventory[id].initializate(about,id);
}
struct craftSlot {
	int ID;
	int count;
	craftSlot() { count = 0; ID = 0; }
};

struct Chest
{
	unint range;
	Coords coords; 
	std::vector<Item> items;
	Chest(unint mRange,int x, int y):coords(x,y)
	{
		range = mRange;
		if (range == BRONZE) //bronze chest
		{
			for (int i = 0; i <= 8; i++)
			{
				Item tmpItem(random(24), random(5)+1);
				items.push_back(tmpItem);
			}
		}
	}
};
std::vector<Chest> chests;
craftSlot craftSlots[4];
int currentChest = -1;

#endif