#ifndef MINION_H
#define MINION_H
#include "card.h"
#include <iostream>
#include <vector>

class Triggered;
class Activated;
class Ability;
class Player;
class Enchantment;

class Minion final: public Card {
	int attack;
	int defense;
	int actions;
	std::shared_ptr<Triggered> triggered;
	std::shared_ptr<Activated> activated;
	vector<Enchantment> enchantments; 
	
	public:
	Minion(string name, int cost, int attack, int defense, std::shared_ptr<Triggered> triggered, std::shared_ptr<Activated> activated);
	void castedBy(Ability& ability);
	void attack(Minion& minion);
	void attack(Player& player);
}

#endif
