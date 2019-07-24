
#ifndef ACTIVATED_H_
#define ACTIVATED_H_
#include "ability.h"

class Activated : public Ability {
	int cost;
public:
	Activated(std::string description, int cost);
	virtual ~Activated() = default;
	virtual void usedOn(Minion &minion) override;
	virtual void usedOn(Player &player) override;
};




#endif /* ACTIVATED_H_ */
