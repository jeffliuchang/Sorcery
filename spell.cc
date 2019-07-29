#include "spell.h"
#include "player.h"
#include "minion.h"
#include "enchantment.h"

Spell::Spell(std::string name, std::string description, int cost)
:Card(name, cost), Activated(description, cost){}


bool Spell::usedOn(Player &player1, Player &player2, int pos) {
	if (getDescription() == "Destroy target minion or ritual") {// pos = 6 for ritual
		if (pos == 6) {
			// to be completed ...
		} else {
			int size = player1.getBoard().size();
			if (size <= pos) {
				std::cout << "target out of range" << std::endl;
				return false;
			}
			player1.minionDamaged(player2, pos, player1.getBoard().at(pos).getDef());
			return true;
		}
	} else if (getDescription() == "Return target minion to its owner's hand") {
		return player1.minionToHand(player2, pos);
	} else if (getDescription() == "Destroy the top enchantment on target minion") {
		// to be completed ...
	} else if (getDescription() == "Your ritual gains 3 charges") {
		// to be completed ...
	} else if (getDescription() == "Resurrect the top minion in your graveyard and set its defence to 1") {
		return player1.resurrect(player2);
	} else if (getDescription() == "Deal 2 damage to all minions") {
		int boardSize1 = player1.getBoard().size();
		int boardSize2 = player2.getBoard().size();
		int pos = 0;
		for (int i = 0; i < boardSize1; ++i) {
			if (player1.minionDamaged(player2,pos,2)) {
				--pos;
			}
			++pos;
		}
		pos = 0;
		for (int j = 0; j < boardSize2; ++j) {
			if (player2.minionDamaged(player1,pos,2)) {
				--pos;
			}
			++pos;
		}
		return true;
	}
	return false;
}
