#include "spell.h"
#include "player.h"
#include "minion.h"
#include "enchantment.h"
#include "ritual.h"

Spell::Spell(std::string name, std::string description, int cost)
:Card(name, cost), Activated(description, cost){}


bool Spell::usedOn(Player &player1, Player &player2, int pos, int activePlayer) {
	if (getDescription() == "Destroy target minion or ritual") {// pos = 6 for ritual
		if (pos == 5) {
			return player1.removeRitual();
		} else {
			int size = player1.getBoard().size();
			if (size <= pos) {
				std::cout << "target out of range" << std::endl;
				return false;
			}
			player1.minionToGraveyard(player2, pos, activePlayer);
			return true;
		}
	} else if (getDescription() == "Return target minion to its owner's hand") {
		return player1.minionToHand(player2, pos, activePlayer);
	} else if (getDescription() == "Destroy the top enchantment on target minion") {
		int boardSize = player1.getBoard().size();
		if (boardSize <= pos or pos < 0) {
			std::cout << "invalid use of spell" << std::endl;
			return false;
		}
		int size = player1.getBoard().at(pos).getEnchants().size();
		if (size == 0) {
			std::cout << "minion has no enchantments" << std::endl;
			return false;
		}
		if (player1.removeTopEnchant(pos)) {
			player1.minionToGraveyard(player2,pos,activePlayer);
		}
		return true;
	} else if (getDescription() == "Your ritual gains 3 charges") {
		int size = player1.getRitual().size();
		if (size == 0) {
			std::cout << player1.getName() << " has no ritual" << std::endl;
			return false;
		}
		player1.rechargeRitual(3);
		return true;
	} else if (getDescription() == "Resurrect the top minion in your graveyard and set its defence to 1") {
		return player1.resurrect(player2);
	} else if (getDescription() == "Deal 2 damage to all minions") {
		int boardSize1 = player1.getBoard().size();
		int boardSize2 = player2.getBoard().size();
		int pos = 0;
		for (int i = 0; i < boardSize1; ++i) {
			if (player1.minionDamaged(player2,pos,2, activePlayer)) {
				--pos;
			}
			++pos;
		}
		pos = 0;
		for (int j = 0; j < boardSize2; ++j) {
			if (player2.minionDamaged(player1,pos,2, activePlayer)) {
				--pos;
			}
			++pos;
		}
		return true;
	}
	return false;
}
