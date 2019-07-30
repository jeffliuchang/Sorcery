#ifndef MINION_H
#define MINION_H
#include "card.h"
#include "activated.h"
#include "triggered.h"
#include "enchantment.h"
#include <iostream>
#include <vector>
#include <memory>

class Ability;
class Player;



class Minion final: public Card {
        int actions;
        int maxActions;
        bool silenced;
        std::vector<Enchantment> myEnchants;
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
        bool spendActions(int spend);
        void recoverActions();
        Activated getActivated();
        Triggered getTriggered();
        std::vector<Enchantment> getEnchants();
        void attack(Player& player);
        bool takeDamage(int damage);
        /*
        void setDef(int defence);
        void setAtk(int attack);
        int getDef();
        int getAtk();
        */
        bool getSilenced();
        std::vector<std::string> display();
        void addEnch(Enchantment newE);
        bool removeEnch(int pos);
        bool removeAllEnch();

};


#endif
