
#ifndef TRIGGERED_H_
#define TRIGGERED_H_
#include "ability.h"

enum class Condition{EndOfTurn, StartOfTurn, MinionEnterPlay, MinionExitPlay};

class Triggered : public Ability {
	Condition condition;
	Player *myPlayer;
public:
	Triggered(std::string description, Condition condition);
	~Triggered() = default;
	virtual bool usedOn(Player &player) override;
	virtual bool usedOn(Player &player, int pos) override;
	bool usedOn(Player &player, Minion &owner, int enterOrExit, Condition condition);
};


#endif /* TRIGGERED_H_ */
