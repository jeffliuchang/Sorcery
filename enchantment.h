#ifndef ENCHANTMENT_H
#define ENCHANTMENT_H
#include <iostream>
<<<<<<< HEAD
#include <memory>
#include "card.h"

class Minion;
class Ability;

=======
#include "card.h"

class Minion;
class Ability
>>>>>>> 0e54d17d96ad052dad7e0600b907d2ea4b0089ed

class Enchantment final : public Card {
        int addAttack;
        int multiAttack;
        int addDefense;
        int multiDefense;
        std::shared_ptr<Ability> ability;

        public:
        Enchantment(std::string name, int cost, int addAttack, int multiAttack, int addDefense, int multiDefense);
        void effect(std::shared_ptr<Minion> target);
};

#endif
