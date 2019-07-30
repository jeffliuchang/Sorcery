#include "ritual.h"
#include "minion.h"
#include "player.h"
#include "ascii_graphics.h"
#include <string>

Ritual::Ritual(std::string name, std::string description, Condition condition,
		int cost, int charge, int activationCost)
:Card(name,cost), Triggered(description, condition), charge(charge), activationCost(activationCost) {}


int Ritual::getCharge() const {
	return charge;
}

void Ritual::setCharge(int charge) {
	this->charge = charge;
}

int Ritual::getActCost() const {
	return activationCost;
}

void Ritual::setActCost(int actCost) {
	this->activationCost = actCost;
}


bool Ritual::usedOn(Player &player1, Player &player2, int owner,int enterOrExit, Condition condition) {
	if (getDescription() == "At the start of your turn, gain 1 magic") {
		if (condition == Condition::StartOfTurn and owner == 1 and charge >= activationCost) {
			player1.gainMagic(1);
			charge -= activationCost;
		}
	} else if (getDescription() == "Whenever a minion enters play under your control, it gains +1/+1") {
		if (condition == Condition::MinionEnterPlay and owner == 1 and charge >= activationCost) {
			player1.buffMinion(enterOrExit,1,1);
			charge -= activationCost;
		}

	} else if (getDescription() == "Whenever a minion enters play, destroy it") {
		if (condition == Condition::MinionEnterPlay and charge >= activationCost) {
			if (!player1.minionToGraveyard(player2,enterOrExit,1)) {
				return false;
			}
			charge -= activationCost;
			if (owner == 2) {
				Ritual ritual(getName(),getDescription(),getCondition(),getCost(),
						getCharge(),getActCost());
				player2.setRitual(ritual);
			}
		}
	}
	return false;
}


std::vector<std::string> Ritual::display() {
	return display_ritual(getName(),getCost(),activationCost, getDescription(),charge);
}
