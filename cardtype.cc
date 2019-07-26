#include "cardtype.h"
#include "minion.h"
#include "activated.h"
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
	activated.emplace_back(Activated{"Deal 1 damage to target minion",1});
	activated.emplace_back(Activated{"Summon a 1/1 air elemental",1});
	activated.emplace_back(Activated{"Summon up to three 1/1 air elementals",2});
	activated.emplace_back(Activated{"NA",1000});

	minions.emplace_back(Minion("Air Elemental",0,1,1,activated.at(3)));
	minions.emplace_back(Minion("Earth Elemental",3,4,4,activated.at(3)));
	minions.emplace_back(Minion("Bone Golem",2,1,3,activated.at(3)));
	minions.emplace_back(Minion("Fire Elemental",2,2,2,activated.at(3)));
	minions.emplace_back(Minion("Potion Seller",2,1,3,activated.at(3)));
	minions.emplace_back(Minion("Novice Pyromancer",1,0,1,activated.at(0)));
	minions.emplace_back(Minion("Apprentice Summoner",1,1,1,activated.at(1)));
	minions.emplace_back(Minion("Master Summoner",3,2,3,activated.at(2)));

}

std::pair<Type,int> Cardtype::construct(std::string name) {
	int size = minions.size();
	for (int i = 0; i < size; ++i) {
		if (minions.at(i).getName() == name)
			return std::pair<Type,int>{Type::Minion,i};
	}
	return std::pair<Type,int>{Type::NA,-1};
}

