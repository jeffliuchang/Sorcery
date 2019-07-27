#include "cardtype.h"
#include "minion.h"
#include "spell.h"
#include "activated.h"
#include "triggered.h"
/*
#include "spell.h"
#include "enchantment.h"
#include "ritual.h"
*/

#include <vector>
#include <string>
#include <map>
#include <memory>

Cardtype::Cardtype() {

	triggered.emplace_back(Triggered{"Gain +1/+1 whenever a minion leaves play.",Condition::MinionExitPlay});
	triggered.emplace_back(Triggered{"Whenever an opponent's minion enters play, deal 1 damage to it.",Condition::MinionEnterPlay});
	triggered.emplace_back(Triggered{"At the end of your turn, all your minions gain +0/+1.",Condition::EndOfTurn});
	triggered.emplace_back(Triggered{"NA",Condition::MinionExitPlay});

	activated.emplace_back(Activated{"Deal 1 damage to target minion",1});
	activated.emplace_back(Activated{"Summon a 1/1 air elemental",1});
	activated.emplace_back(Activated{"Summon up to three 1/1 air elementals",2});
	activated.emplace_back(Activated{"NA",1000});

	minions.emplace_back(Minion("Air Elemental",0,1,1,activated.at(3),triggered.at(3)));
	minions.emplace_back(Minion("Earth Elemental",3,4,4,activated.at(3),triggered.at(3)));
	minions.emplace_back(Minion("Bone Golem",2,1,3,activated.at(3),triggered.at(0)));
	minions.emplace_back(Minion("Fire Elemental",2,2,2,activated.at(3),triggered.at(1)));
	minions.emplace_back(Minion("Potion Seller",2,1,3,activated.at(3),triggered.at(2)));
	minions.emplace_back(Minion("Novice Pyromancer",1,0,1,activated.at(0),triggered.at(3)));
	minions.emplace_back(Minion("Apprentice Summoner",1,1,1,activated.at(1),triggered.at(3)));
	minions.emplace_back(Minion("Master Summoner",3,2,3,activated.at(2),triggered.at(3)));

	spells.emplace_back(Spell("Banish", "Destroy target minion or ritual", 2));
	spells.emplace_back(Spell("Unsummon", "Return target minion to its owner's hand", 1));
	spells.emplace_back(Spell("Recharge", "Your ritual gains 3 charges", 1));
	spells.emplace_back(Spell("Disenchant", "Destroy the top enchantment on target minion", 1));
	spells.emplace_back(Spell("Raise Dead", "Resurrect the top minion in your graveyard and set its defence to 1", 1));
	spells.emplace_back(Spell("Blizzard", "Deal 2 damage to all minions", 3));

}

std::pair<Type,int> Cardtype::construct(std::string name) {
	int size = minions.size();
	for (int i = 0; i < size; ++i) {
		if (minions.at(i).getName() == name){
			return std::pair<Type,int>{Type::Minion,i};
		}

	}

	int size2 = spells.size();
	for (int i = 0; i < size2; ++i) {
		if (spells.at(i).getName() == name){
			//std::cout << name << std::endl;
			return std::pair<Type,int>{Type::Spell,i};
		}

	}
	return std::pair<Type,int>{Type::NA,-1};
}

