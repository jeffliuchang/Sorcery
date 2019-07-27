#include "triggered.h"
#include "minion.h"
#include "player.h"

Triggered::Triggered(std::string description, Condition condition)
:Ability(description), condition(condition), myPlayer(nullptr) {}


bool Triggered::usedOn(Player &player) {
	return false;
}

bool Triggered::usedOn(Player &player, int pos) {
	return false;
}

bool Triggered::usedOn(Player &player, Minion &owner, int enterOrExit, Condition condition) {
	if (getDescription() == "Gain +1/+1 whenever a minion leaves play.") {
		if (condition == Condition::MinionExitPlay) {
			owner.setAtk(owner.getAtk()+1);
			owner.setDef(owner.getDef()+1);
			return false;
		}
	} else if (getDescription() == "Whenever an opponent's minion enters play, deal 1 damage to it.") {
		if (condition == Condition::MinionEnterPlay) {
			if (myPlayer != &player) {
				return player.minionDamaged(enterOrExit,1);
			}
		}
	} else if (getDescription() == "At the end of your turn, all your minions gain +0/+1.") {
		if (condition == Condition::EndOfTurn) {
			int size = player.getBoard().size();
			int pos = 0;
			for (int i = 0; i < size; ++i) {
				if (player.minionDamaged(pos,-1)) {
					--pos;
				}
				++pos;
			}
			return false;
		}
	}
	return false;
}
