#include "ritual.h"
#include "minion.h"
#include "player.h"
#include <string>

Ritual::Ritual(std::string name, std::string description, Condition condition,
		int cost, int charge, int activationCost)
:Card(name,cost), Triggered(description, condition), charge(charge), activationCost(activationCost) {}

bool Ritual::usedOn(Player &player) {return false;}
bool Ritual::usedOn(Player &player, int pos) {return false;}

bool Ritual::usedOn(Player &player1, Player &player2, int owner, int boardPos, int enterOrExit, Condition condition) {
	if (getDescription() == "At the start of your turn, gain 1 magic") {
		if (condition == Condition::StartOfTurn and owner == 1) {
			player1.gainMagic(1);
		}
	} else if (getDescription() == "Whenever a minion enters play under your control, it gains +1/+1") {
		if (condition == Condition::MinionEnterPlay and owner == 1) {
			player1.buffMinion(enterOrExit,1,1);
		}

	} else if (getDescription() == "Whenever a minion enters play, destroy it") {
		if (condition == Condition::MinionEnterPlay) {
			player1.minionToGraveyard(player2,enterOrExit);
		}
	}
	return false;
}
