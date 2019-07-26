#include "spell.h"

Spell::Spell(std::string name, std::string description, int cost)
:Card(name, cost), Activated(description, cost){}

void Spell::usedOn(Player &player) {
	if (getDescription() == "Your ritual gains 3 charges") {

	} else if (getDescription() == "Resurrect the top minion in your graveyard and set its defence to 1") {

	}
}
void Spell::usedOn(Player &player, int pos) {
	if (getDescription() == "Destroy target minion or ritual") {

	} else if (getDescription() == "Return target minion to its owner's hand") {

	} else if (getDescription() == "Destroy the top enchantment on target minion") {

	}
}

void Spell::usedOn(Player &player1, Player &player2) {
	if (getDescription() == "Deal 2 damage to all minions") {

	}
}
