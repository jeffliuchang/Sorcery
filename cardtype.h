
#ifndef CARDTYPE_H_
#define CARDTYPE_H_

#include <vector>
#include <string>
#include <map>
#include <memory>

class Card;
class Minion;
class Spell;
class Enchantment;
class Ritual;
class Activated;

enum class Type{Minion, Spell, Enchantment, Ritual, Triggered, Activated, NA};

struct Cardtype {
	std::vector<Minion> minions;
	std::vector<Activated> activated;
/*
	std::vector<std::string> spells{"Banish", "Unsummon", "Recharge", "Disenchant",
		"Raise Dead", "Blizzard"};

	std::vector<std::string> enchantments{"Giant Strength", "Enrage", "Haste",
		"Magic Fatigue", "Silence"};

	std::vector<std::string> rituals{"Dark Ritual", "Aura of Power", "Standstill"};
*/
	Cardtype();
	std::pair<Type,int> construct(std::string name);
};



#endif /* CARDTYPE_H_ */
