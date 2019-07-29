#ifndef RITUAL_H
#define RITUAL_H
#include <iostream>
#include <string>
#include "card.h"
#include "triggered.h"
#include <vector>

class Minion;
class Player;

class Ritual final : public Card, public Triggered {
	int charge;
	int activationCost;

	public:
	Ritual(std::string name, std::string description, Condition condition,
			int cost, int charge, int activationCost);
	int getCharge() const;
	void setCharge(int charge);
	int getActCost() const;
	void setActCost(int actCost);
	bool usedOn(Player &player1, Player &player2, int owner,int enterOrExit, Condition condition);
	std::vector<std::string> display();
};




#endif
