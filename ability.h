
#ifndef ABILITY_H_
#define ABILITY_H_
#include <string>

class Ability {
	std::string description;
public:
	Ability(std::string description);
	virtual ~Ability() = default;
	virtual void usedOn(std::shared_ptr<Minion> minion) = 0;
	virtual void usedOn(std::shared_ptr<Player> player) = 0;
};



#endif
