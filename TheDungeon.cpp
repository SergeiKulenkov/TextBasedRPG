
#include <iostream>
#include "stdlib.h"
#include "vector"
#include "string"
#include "algorithm"
#include "Game.h"

using std::cout;
using std::endl;
using std::cin;

void Choice(int& choice)
{
	cin >> choice; //choosing within range
	while (choice < 0 || choice > 3)
	{
		cout << "choose from 0 to 3" << endl;
		cin >> choice;
	}
}

std::string  PrintCharacter(int character)
{
	switch (character)
	{
		case 1: return "Knight ";
		case 2: return "Thief ";
		case 3: return "Archer ";
		default: return " ";
	}
}

int main()
{
	int character = 1, difficulty = 0, gold = 0;
	bool best = false;
	std::vector<int> goldTotal, characters;

	cout << "The Dungeon" << endl << endl;
	while (character > 0)
	{	
		cout << "Choose your character: 1 - Knight, 2 - Thief, 3 - Archer. Or press 0 to exit" << endl;
		cout << "Knight: hp - 45, attack - 45, ranged attack - 15, stealth - 20" << endl;
		cout << "Thief: hp - 30, attack - 25, ranged attack - 30, stealth - 40" << endl;
		cout << "Archer: hp - 35, attack - 30, ranged attack - 45, stealth - 30" << endl;
		Choice(character);
		if (character == 0) break; //if 0 was entered - exit

		cout << "choose difficulty: 1 - easy walk, 2 - normal one, 3 - nightmare" << endl;
		Choice(difficulty);
		cout << "you enter the dark and scary dungeon" << endl;

		Game TheGame(character); // gameplay inside TheGame function
		gold = TheGame.TheGame(difficulty);

		goldTotal.emplace_back(gold); //adding gold and character to vectors 
		characters.emplace_back(character);

		cout << endl << "you have " << gold << " total gold!" << endl << endl;
		if (goldTotal.size() > 1) //showing all results if played more than 1 time
		{
			cout << "your adventures:" << endl;
			for (int i = 0; i < goldTotal.size(); i++) //printing all characters and thier gold
				cout << i + 1 << ". " << PrintCharacter(characters[i]) << goldTotal[i] << " total gold" << endl;
		}
		cout << endl;
	}

	cout << "THE END" << endl << endl;

	return 0;
}