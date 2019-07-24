#ifndef SPELL_H
#define SPELL_H
#include <iostream>
#include <vector>
#include "card.h"
#include "activated.h"

class Minion;
class Player;

class Spell final : public Card, public Activated {
        public:
        Spell(std::string description, int cost);
        void usedOn(Minion& minion);
        void usedOn(Player& player);
        void usedOn(std::vector<Minion> minions);
};


#endif
