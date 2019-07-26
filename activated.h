
#ifndef ACTIVATED_H_
#define ACTIVATED_H_
#include "ability.h"

class Activated : public Ability {
	int actCost;
public:
	Activated(std::string description, int cost);
	virtual ~Activated() = default;
	int getCost();
	virtual bool usedOn(Player &player) override;
	virtual bool usedOn(Player &player, int pos) override;
};




#endif /* ACTIVATED_H_ */
