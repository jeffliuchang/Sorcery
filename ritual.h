#ifndef RITUAL_H
#define RITUAL_H
#include <iostream>
#include <string>
#include "card.h"
#include "triggered.h"

class Minion;
class Player;

class Ritual final : public Card, public Triggered {
	int charge;
	int activationCost;

	public:
	Ritual(std::string name, std::string description, int cost, Condition condition, int charge, int activationCost);
	bool usedOn(Player &player) override;
	bool usedOn(Player &player, int pos) override;
};




#endif
