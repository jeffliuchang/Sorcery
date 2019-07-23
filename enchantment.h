#ifndef ENCHANTMENT_H
#define ENCHANTMENT_H
#include <iostream>
#include "card.h"

class Minion;
class Ability

class Enchantment final : public Card {
        int addAttack;
        int multiAttack;
        int addDefense;
        int multiDefense;
        std::shared_ptr<Ability> ability;

        public:
        Enchantment(std::string name, int cost, int addAttack, int multiAttack, int addDefense, int multiDefense);
        void effect(std::shared_ptr<Minion> target);
}

#endif
