#pragma once
#include <iostream>
#include "time.h"
#include "stdlib.h"
#include "Person.h"
#include "Enemy.h"

using std::cout;
using std::cin;
using std::endl;

class Game
{
	private:

		enum Action
		{
			Attack = 1, Sneak, Ranged
		};

		enum Character
		{
			Knight = 1, Thief, Archer
		};

		enum Difficulty
		{
			Easy = 0, Normal, Hard
		};

		int enemyCount, chosenAction, enemyType, gold;
		Person guy;
		Enemy monster;

		void Dungeon()
		{
			while (enemyCount > 0)
			{
				enemyType = std::rand() % 5 + 1;
				monster = Enemy(enemyType); //making new monster using random type
				cout << "you go further into the dungeon and see " << monster.PrintType() << endl;

				cout << "you can: 1 - come closer and ATTACK, 2 - try to SNEAK around, 3 - try to use RANGED attack" << endl;
				cin >> chosenAction; //choosing action within range
				while (chosenAction <= 0 || chosenAction > 3)
				{
					cout << "choose from 1 to 3" << endl;
					cin >> chosenAction;
				}

				switch (chosenAction)
				{
				case Attack:
					cout << "you're running towards your enemy with weapon drawn, willing to kill it" << endl;
					if (!AttackAction()) return; //player did not make it, return from this function
					cout << "you've successefully killed the enemy and now you get " << AddGold() << " gold!" << endl << endl;
					break;

				case Sneak:
					cout << "you're crouching near the wall, trying not to make any sound" << endl;
					if (monster.Detect(guy.Stealth(), enemyType)) cout << "you've successfully sneaked around this monster, but you couldn't take the gold that was guarded by the monster" << endl << endl;
					else // player's detected
					{
						cout << "monster has noticed you, so now you'll have to fight" << endl;
						Detected(); //monster attacks
						if (!AttackAction()) return; //player did not make it, return from this function
						cout << "you've successefully killed the enemy and now you get " << AddGold() << " gold!" << endl << endl;
					}
					break;

				case Ranged:
					cout << "you're drawing your bow and aim at the enemy" << endl;
					if (!RangedAction()) //if false, player missed or just damaged the monster
					{
						cout << "now the enemy is running to attack you" << endl;
						PersonHealthMessage();
						EnemyAttacksMessage();
						monster.Attack(guy.health);
						if (Death()) return; //if player's dead - return from this function
						if (!AttackAction()) return; //player did not make it, return from this function
					}
					cout << "you've successefully killed the enemy and now you get " << AddGold() << " gold!" << endl << endl;
					break;
				}

				cout << "your total gold -  " << gold << endl << endl;
				enemyCount--;
			}
			//player completed the dungeon
			cout << "you've reached the final treasure of this dungeon, you take it and finally get out of this place!" << endl;
			gold += std::rand() % 25 + 1;
			return;
		}

		void HardDungeon()
		{
			while (enemyCount > 0)
			{
				enemyType = std::rand() % 5 + 1;
				monster = Enemy(enemyType); //making anemy using random type
				cout << "you go further into the dungeon and see " << monster.PrintType() << endl;

				cout << "you can: 1 - come closer and ATTACK, 2 - try to SNEAK around, 3 - try to use RANGED attack" << endl;
				cin >> chosenAction; //choosing action within range
				while (chosenAction <= 0 || chosenAction > 3)
				{
					cout << "choose from 1 to 3" << endl;
					cin >> chosenAction;
				}

				switch (chosenAction)
				{
				case Attack:
					cout << "you're running towards your enemy with weapon drawn, willing to kill it" << endl;
					if (!AttackAction(Hard)) return; //player did not make it, return from this function
					cout << "you've successefully killed the enemy and now you get " << AddGold(Hard) << " gold!" << endl << endl;
					break;

				case Sneak:
					cout << "you're crouching near the wall, trying not to make any sound" << endl;
					if (monster.Detect(guy.Stealth(), enemyType)) cout << "you've successfully sneaked around this monster, but you couldn't take the gold that was guarded by the monster" << endl << endl;
					else //player's detected
					{
						cout << "monster has noticed you, so now you'll have to fight" << endl;
						Detected(); //monster attacks
						if (!AttackAction(Hard)) return; //player did not make it, return from this function
						cout << "you've successefully killed the enemy and now you get " << AddGold(Hard) << " gold!" << endl << endl;
					}
					break;

				case Ranged:
					cout << "you're drawing your bow and aim at the enemy" << endl;
					if (!RangedAction(Hard)) //if false - player missed
					{
						cout << "now the enemy is running to attack you" << endl;
						PersonHealthMessage();
						EnemyAttacksMessage();
						monster.Attack(guy.health, Hard); //monster attacks the player
						if (Death()) return; //if player's dead - return from this function
						if (!AttackAction(Hard)) return; //player did not make it, return from this function
					}
					cout << "you've successefully killed the enemy and now you get " << AddGold(Hard) << " gold!" << endl << endl;
					break;
				}

				cout << "your total gold -  " << gold << endl << endl;
				enemyCount--;
			}
			//player completed the dungeon
			cout << "you've reached the final treasure of this dungeon, you take it and finally get out of this place!" << endl;
			gold += std::rand() % 50 + 50;
			return;
		}
		
		bool AttackAction(int difficulty = 0)
		{
			while (monster.health > 0 || guy.health > 0)
			{
				EnemyHealthMessage();
				PersonAttacksMessage();
				guy.Attack(monster.health, difficulty); //player attacks the monster
				if (monster.health <= 0) //if monster's dead - return true
				{
					monster.health = 0;
					EnemyHealthMessage();
					return true;
				}
				EnemyHealthMessage();
				PersonHealthMessage();
				EnemyAttacksMessage();
				monster.Attack(guy.health, difficulty); //if monster's not dead - it attack the player
				if (Death()) return false; //if player's dead return false from this function
				PersonHealthMessage();
			}
			return false;
		}

		void Detected()
		{
			PersonHealthMessage();
			EnemyAttacksMessage();
			monster.Attack(guy.health); //monster attacks if player's detected
			if (Death()) return; //if player's dead return from this function
			PersonHealthMessage();
		}

		bool RangedAction(int difficulty = 1)
		{
			int prevHP = monster.health;
			EnemyHealthMessage();
			PersonAttacksMessage();
			guy.RangedAttack(monster.health, difficulty); //player shoots 
			if (monster.health == prevHP - 100) //headshot, monster's dead, return true
			{
				cout << "  HEADSHOT!  " << endl;
				return true;
			}
			else if (monster.health <= 0) //monster's killed
			{
				monster.health = 0;
				EnemyHealthMessage();
				return true;
			}
			else if (monster.health == prevHP) //player missed
			{
				cout << "unfortunately you missed the target " << endl;
				return false;
			}
			else if (monster.health <= prevHP && monster.health > 0) //monster's damaged
			{
				cout << "you hit the target but didn't kill it " << endl;
				EnemyHealthMessage();
				return false;
			}
		}

		bool Death()
		{
			if (guy.health > 0) return false;
			cout << endl << "DEATH" << endl << endl; //if player's dead print these and return true
			cout << endl << "unfortunately you've lost the battle" << endl;
			return true;
		}
	
		int AddGold(int difficulty = 1)
		{	//adiing random amount of gold depending on the difficulty
			int newGold = (std::rand() % 10 + 1) * difficulty;
			gold += newGold;
			return newGold;
		}

		void EnemyHealthMessage() { cout << "monster health is " << monster.health << endl; }

		void PersonHealthMessage() { cout << "monster health is " << guy.health << endl; }

		void EnemyAttacksMessage() { cout << "the monster attacks you ..." << endl; }

		void PersonAttacksMessage() { cout << "you attack the monster ..." << endl; }

	public:

		Game() { enemyCount = 0; chosenAction = 0; enemyType = 0; gold = 0; }
		
		Game(int character)
		{
			gold = 0;
			enemyCount = 0;
			chosenAction = 0;
			enemyType = 0;
			guy = Person(character);
		}

		int TheGame(int difficulty)
		{
			std::srand(time(0));

			switch (difficulty-1)
			{
				case Easy: enemyCount = 3;
					Dungeon(); 
					return gold;
					break;

				case Normal: enemyCount = 5;
					Dungeon();
					return gold;
					break;

				case Hard: enemyCount = 5;
					HardDungeon();
					return gold;
					break;

				default: return gold;
					break;
			}
		}

};