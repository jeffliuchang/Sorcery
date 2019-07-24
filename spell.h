#ifndef SPELL_H
#define SPELL_H
#include <iostream>
<<<<<<< HEAD
#include <vector>
#include "card.h"
#include "activated.h"

class Minion;
class Player;

=======
#include "card.h"
#include "activated.h"

>>>>>>> 0e54d17d96ad052dad7e0600b907d2ea4b0089ed
class Spell final : public Card, public Activated {
        public:
        Spell(std::string description, int cost);
        void usedOn(Minion& minion);
        void usedOn(Player& player);
<<<<<<< HEAD
        void usedOn(std::vector<Minion> minions);
};
=======
        void usedOn(vector<Minion> minions);
}
>>>>>>> 0e54d17d96ad052dad7e0600b907d2ea4b0089ed

#endif
