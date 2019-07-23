#ifndef SPELL_H
#define SPELL_H
#include <iostream>
#include "card.h"
#include "activated.h"

class Spell final : public Card, public Activated {
	public:
	Spell(string description, int cost);
	void usedOn(Minion& minion);
	void usedOn(Player& player);
	void usedOn(vector<Minion> minions);
}

#endif
