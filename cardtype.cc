#include "cardtype.h"
#include "minion.h"
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
	minions.emplace_back(Minion("Air Elemental",0,1,1));
	minions.emplace_back(Minion("Earth Elemental",3,4,4));
	minions.emplace_back(Minion("Bone Golem",2,1,3));
	minions.emplace_back(Minion("Fire Elemental",2,2,2));
	minions.emplace_back(Minion("Potion Seller",2,1,3));
	minions.emplace_back(Minion("Novice Pyromancer",1,0,1));
	minions.emplace_back(Minion("Apprentice Summoner",1,1,1));
	minions.emplace_back(Minion("Master Summoner",3,2,3));
}

std::pair<Type,int> Cardtype::construct(std::string name) {
	int size = minions.size();
	for (int i = 0; i < size; ++i) {
		if (minions.at(i).getName() == name)
			return std::pair<Type,int>{Type::Minion,i};
	}
	return std::pair<Type,int>{Type::NA,-1};
}

