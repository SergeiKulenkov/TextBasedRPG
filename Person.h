#pragma once
#include "Character.h"
#include "time.h"
#include "stdlib.h"


class Person : public Character
{
	private:

		enum character
		{
			Knight = 1, Thief, Archer
		};

		int stealth, rangedDamage;
	public:

		Person() { stealth = 0; rangedDamage = 0; }

		/*Person(int hp, int st, int ranDam, int melDam) : Character(hp, melDam)
		{
			stealth = st;
			rangedDamage = ranDam;
		}*/

		Person(int character)
		{
			switch (character)
			{
				case Knight: health = 45;
					stealth = 20;
					rangedDamage = 15;
					damage = 40;
					break;
				case Thief: health = 30;
					stealth = 40;
					rangedDamage = 30;
					damage = 25;
					break;
				case Archer: health = 35;
					stealth = 30;
					rangedDamage = 45;
					damage = 30;
					break;
			}
		}

		int Stealth() { return stealth; }

		void Attack(int& hp, int difficulty = 0) override
		{
			std::srand(time(0));
			int prob = std::rand() % 100 - 10 * difficulty; //making random number depending on the difficulty
			if (prob > 50) hp -= damage; //using certain amount of damage depending on the random
			else if (prob <= 50 && prob > 25) hp -= (damage - 5);
			else if (prob <= 25) hp -= (damage - 10);
			return;
		}

		void RangedAttack(int& hp, int difficulty = 1)
		{
			std::srand(time(0));
			int prob = std::rand() % 100 - rangedDamage; //making random depending on the ranged damage
			if (prob >= 40) return; //player missed 
			if (prob < 40 && prob >= 15) hp -= (damage - 5 * difficulty); //using certain amount of damage depending on the random
			else if (prob < 15 && prob >= -5) hp -= (damage - 10);
			else if (prob < (-5) * difficulty) hp -= 100; //player shot enemy in the head
			return;
		}
};