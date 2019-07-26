
#ifndef ACTIVATED_H_
#define ACTIVATED_H_
#include "ability.h"

class Activated : public Ability {
	int actCost;
public:
	Activated(std::string description, int cost);
	virtual ~Activated() = default;
	int getCost();
	virtual void usedOn(Player &player) override;
	virtual void usedOn(Player &player, int pos) override;
};




#endif /* ACTIVATED_H_ */
