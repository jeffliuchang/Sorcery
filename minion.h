#ifndef MINION_H
#define MINION_H
#include "card.h"
#include "activated.h"
#include "triggered.h"
#include <iostream>
#include <vector>
#include <memory>

class Triggered;
class Ability;
class Player;
class Enchantment;


class Minion final: public Card {
        int atk;
        int def;
        int actions;
        int maxActions;
        vector<Enchantment> myEnchants;
        Activated activated;
        Triggered triggered;
        /*
        int actions;
        std::shared_ptr<Triggered> triggered;
        std::shared_ptr<Activated> activated;
        */
        //std::vector<Enchantment> enchantments;

        public:
        Minion(std::string name, int cost,int atk, int def, Activated activated, Triggered triggered);
        //~Minion() override;
        /*
        Minion(std::string name, int cost, int attack, int defense, int actions,
        		std::shared_ptr<Triggered> triggered, std::shared_ptr<Activated> activated);
        void castedBy(Ability& ability);

        void attack(Minion& minion);
        */

        Activated getActivated();
        Triggered getTriggered();
        void attack(Player& player);
        bool takeDamage(int damage);
        void setDef(int defence);
        void setAtk(int attack);
        int getDef();
        int getAtk();
        std::vector<std::string> display();
        void addEnch(Enchantment newE);
        bool removeEnch(int pos);
        bool removeAllEnch();

};


#endif
