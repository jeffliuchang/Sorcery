
#ifndef ABILITY_H_
#define ABILITY_H_
#include <string>
#include <memory>

class Minion;
class Player;

class Ability {
	std::string description;
public:
	Ability(std::string description);
	virtual ~Ability() = default;
	virtual void usedOn(Minion &minion) = 0;
	virtual void usedOn(Player &player) = 0;
};



#endif
