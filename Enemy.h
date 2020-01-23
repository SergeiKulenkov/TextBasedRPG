#pragma once
#include "Character.h"
#include "time.h"
#include "stdlib.h"
#include "string.h"

class Enemy : public Character
{
	private:

		enum Type
		{
			Orc = 1, Undead, Spider, Mage, Wolf
		};

		std::string name;
	public:

		Enemy() { name = ""; }

		Enemy(int type)
		{
			switch (type)
			{
				case Orc: health = 40;
					damage = 25;
					name = "Green Orc"; 
					break;
				case Undead: health = 30;
					damage = 25;
					name = "Slow Undead";
					break;
				case Spider: health = 10;
					damage = 10;
					name = "White Spider";
					break;
				case Mage: health = 40;
					damage = 40;
					name = "Old Mage";
					break;
				case Wolf: health = 20;
					damage = 15;
					name = "Grey Wolf";
					break;
			}
		}

		bool Detect(int stealth, int type)
		{
			srand(time(0));
			int prob = type * 10 + 5; //making random number using type of the enemy
			if (std::rand() % 100 - prob <= stealth) return true; //detecting player using stealth parameter
			return false;
		}

		std::string PrintType() { return name; }

		void Attack(int& hp, int difficulty = 0) override
		{
			std::srand(time(0));
			int prob = std::rand() % 100;
			if (prob > 60 - 10 * difficulty) hp -= damage; //using certain amount of damage depending on random number
			else hp -= (damage - 10 + 10* difficulty);
			return;
		}
};