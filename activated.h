
#ifndef ACTIVATED_H_
#define ACTIVATED_H_
#include "ability.h"

class Activated : public Ability {
	int cost;
public:
	Activated(std::string description, int cost);
	~Activated() = default;
	virtual void usedOn(std::shared_ptr<Minion> minion) override;
	virtual void usedOn(std::shared_ptr<Player> player) override;
};




#endif /* ACTIVATED_H_ */
