
#ifndef TRIGGERED_H_
#define TRIGGERED_H_
#include "ability.h"

enum class Condition{EndOfTurn, StartOfTurn, MinionEnterPlay, MinionExitPlay};

class Triggered : public Ability {
	Condition condition;
public:
	Triggered(std::string description, Condition condition);
	~Triggered() = default;
	virtual void usedOn(std::shared_ptr<Minion> minion) override;
	virtual void usedOn(std::shared_ptr<Player> player) override;
};


#endif /* TRIGGERED_H_ */
