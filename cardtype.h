
#ifndef CARDTYPE_H_
#define CARDTYPE_H_

#include <vector>
#include <string>

enum class Type{Minion, Spell, Enchantment, Ritual, Triggered, Activated, NA};

struct Cardtype {
	std::vector<std::string> minions{"Air Elemental", "Earth Elemental", "Bone Golem",
		"Fire Elemental", "Potion Seller", "Novice Pyromancer", "Apprentice Summoner",
		"Master Summoner"};

	std::vector<std::string> spell{"Banish", "Unsummon", "Recharge", "Disenchant",
		"Raise Dead", "Blizzard"};

	std::vector<std::string> enchantments{"Giant Strength", "Enrage", "Haste",
		"Magic Fatigue", "Silence"};

	std::vector<std::string> rituals{"Dark Ritual", "Aura of Power", "Standstill"};

	Type classify(std::string name) {
		for (int i = 0; i < minions.size(); ++i) {
			if (minions.at(i) == name) return Type::Minion;
		}
		for (int j = 0; j < spell.size(); ++j) {
			if (spell.at(j) == name) return Type::Spell;
		}
		for (int m = 0; m < enchantments.size(); ++m) {
			if (enchantments.at(m) == name) return Type::Enchantment;
		}
		for (int n = 0; n < rituals.size(); ++n) {
			if (rituals.at(n) == name) return Type::Ritual;
		}
		return Type::NA;
	}
};



#endif /* CARDTYPE_H_ */
