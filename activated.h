
#ifndef ACTIVATED_H_
#define ACTIVATED_H_
#include "ability.h"

class Activated : public Ability {
	int actCost;
public:
	Activated(std::string description, int cost);
	Activated(const Activated& other);
	virtual ~Activated() = default;
	int getCost();
	virtual bool usedOn(Player &player) override;
	virtual bool usedOn(Player &player, int pos) override;
	bool usedOn(Player &player1, Player &player2, int pos);
};




#endif /* ACTIVATED_H_ */
