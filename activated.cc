#include "activated.h"
#include "minion.h"
#include "player.h"
#include "cardtype.h"

Activated::Activated(std::string description, int cost)
:Ability(description),actCost(cost) {}

int Activated::getCost() {
	return actCost;
}

bool Activated::usedOn(Player &player) {
	Cardtype ct{};
	if (getDescription() == "Summon a 1/1 air elemental") {
		return player.play(ct.minions.at(0));
	} else if (getDescription() == "Summon up to three 1/1 air elementals") {
		player.play(ct.minions.at(0));
		player.play(ct.minions.at(0));
		return player.play(ct.minions.at(0));
	}
	return false;
}

bool Activated::usedOn(Player &player, int pos) {
	if (getDescription() == "Deal 1 damage to target minion") {
		player.minionDamaged(pos,1);
		return true;
	}
	return false;
}
