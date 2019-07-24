#ifndef MINION_H
#define MINION_H
#include "card.h"
#include <iostream>
#include <vector>
<<<<<<< HEAD
#include <memory>
=======
>>>>>>> 0e54d17d96ad052dad7e0600b907d2ea4b0089ed

class Triggered;
class Activated;
class Ability;
class Player;
class Enchantment;

class Minion final: public Card {
        int attack;
        int defense;
        int actions;
        std::shared_ptr<Triggered> triggered;
        std::shared_ptr<Activated> activated;
<<<<<<< HEAD
        std::vector<Enchantment> enchantments;
=======
        vector<Enchantment> enchantments;
>>>>>>> 0e54d17d96ad052dad7e0600b907d2ea4b0089ed

        public:
        Minion(std::string name, int cost, int attack, int defense, std::shared_ptr<Triggered> triggered, std::shared_ptr<Activated> activated);
        void castedBy(Ability& ability);
        void attack(Minion& minion);
        void attack(Player& player);
<<<<<<< HEAD
};
=======
}
>>>>>>> 0e54d17d96ad052dad7e0600b907d2ea4b0089ed

#endif
