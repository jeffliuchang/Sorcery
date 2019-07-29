
#ifndef ACTIVATED_H_
#define ACTIVATED_H_
#include "ability.h"

class Activated : public Ability {
	int actCost;
public:
	Activated(std::string description, int cost);
	virtual ~Activated() = default;
	int getCost();
	void setCost(int cost);
	bool usedOn(Player &player1, Player &player2, int pos);
};




#endif /* ACTIVATED_H_ */
