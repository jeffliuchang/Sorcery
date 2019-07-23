#ifndef ENCHANTMENT_H
#define ENCHANTMENT_H
#include <iostream>
#include "ability.h"
#include "card.h"

class Minion;

class Enchantment final : public Card {
	int addAttack;
	int multiAttack;
	int addDefense;
	int multiDefense;
	Ability ability;
	
	public:
	Enchantment(string name, int cost, int addAttack, int multiAttack, int addDefense, int multiDefense);
	void effect(std::shared_ptr<Minion> target);
}

#endif
