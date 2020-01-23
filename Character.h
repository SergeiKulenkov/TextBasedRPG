#pragma once


class Character
{
	protected:
		int damage;

		Character() { health = 0; damage = 0; }

		Character(int hp, int dam)
		{
			health = hp;
			damage = dam;
		}

		void virtual Attack(int& hpm, int difficulty = 0) = 0;
	public: 

		int health;
};