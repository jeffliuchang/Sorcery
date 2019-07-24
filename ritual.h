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
	Ritual(std::string name, int cost, std::string description, Condition condition, int charge, int activationCost);
	void usedOn(Minion& minion) override;
	void usedOn(Player& player) override;
};




#endif
