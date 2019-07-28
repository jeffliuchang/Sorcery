#include "activated.h"
#include "minion.h"
#include "player.h"
#include "cardtype.h"

Activated::Activated(std::string description, int cost)
	:Ability(description),actCost(cost) {}

Activated::Activated(const Activated& other)
	:Ability(other.getDescription(), other.getCost(){}


int Activated::getCost() {
	return actCost;
}

bool Activated::usedOn(Player &player1, Player &player2, int pos) {
	Cardtype ct{};
	if (getDescription() == "Summon a 1/1 air elemental") {
		return player1.play(player2, ct.minions.at(0));
	} else if (getDescription() == "Summon up to three 1/1 air elementals") {
		player1.play(player2, ct.minions.at(0));
		player1.play(player2, ct.minions.at(0));
		return player1.play(player2, ct.minions.at(0));
	} else if (getDescription() == "Deal 1 damage to target minion") {
		int position = pos;
		player1.minionDamaged(player2, position ,1);
		return true;
	}
	return false;
}

bool Activated::usedOn(Player &player, int pos) {
	/*
	if (getDescription() == "Deal 1 damage to target minion") {
		player.minionDamaged(pos,1);
		return true;
	}
	*/
	return false;
}

bool Activated::usedOn(Player &player) {return false;}
