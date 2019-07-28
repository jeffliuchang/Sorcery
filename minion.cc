#include "minion.h"
#include <memory>
#include "ability.h"
#include "player.h"
#include "card.h"
#include "ascii_graphics.h"
#include "cardtype.h"
#include "enchantment.h"
/*
Minion::Minion(std::string name, int cost, int attack, int defense, int actions,
		std::shared_ptr<Triggered> triggered, std::shared_ptr<Activated> activated)
:Card{name,cost},atk(attack),def(defense),actions(actions),triggered(triggered),activated(activated) {}

void Minion::castedBy(Ability& ability) {
	ability.usedOn(*this);
}

void Minion::attack(Minion& minion) {

}
*/

Minion::Minion(std::string name, int cost,
		int atk, int def, Activated activated, Triggered triggered)
:Card(name,cost),atk(atk),def(def),actions(0), maxActions(1), silenced(false), activated(activated), triggered(triggered){}

Activated Minion::getActivated() {
	return activated;
}

Triggered Minion::getTriggered() {
	return triggered;
}

std::vector<Enchantment> Minion::getEnchants() {
        return myEnchants;
}

void Minion::attack(Player& player) {
	player.loseHp(atk);
}

bool Minion::takeDamage(int damage) {
	//std::cout << getName() << " defence is " << def << std::endl;
	//std::cout << " it takes damage  " << damage << std::endl;
	def -= damage;
	if (def <= 0) {
		//std::cout << getName() << " defence is " << def << std::endl;
		//std::cout << getName() << " dies" << std::endl;
		return true;
	}
	return false;
}

std::vector<std::string> Minion::display() {
	if (activated.getDescription() != "NA") {
		return display_minion_activated_ability(getName(), getCost(), atk, def,
				activated.getCost(), activated.getDescription());
	} else if (triggered.getDescription() != "NA") {
		return display_minion_triggered_ability(getName(),getCost(), atk, def, triggered.getDescription());
	} else {
		return display_minion_no_ability(getName(), getCost(), atk, def);
	}
}

void Minion::setDef(int defence) {
	def = defence;
}

void Minion::setAtk(int attack) {
	atk = attack;
}

int Minion::getDef() {
	return this->def;
}

int Minion::getAtk() {
	return this->atk;
}

bool Minion::getSilenced() {
	return silenced;
}

void Minion::addEnch(Enchantment newE) {
        myEnchants.emplace_back(newE);
        if (newE.getName() == "Giant Strength") {
                atk += 2;
                def += 2;
        } else if (newE.getName() == "Enrage") {
                atk *= 2;
                def *= 2;
        } else if (newE.getName() == "Haste") {
                maxActions +=1;
        } else if (newE.getName() == "Magic Fatigue") {
                activated.setCost(activated.getCost() + 2);
        } else if (newE.getName() == "Silence") {
        		Cardtype ct();
                silenced = true;
        }
}

bool Minion::removeEnch(int pos) {
        Cardtype ct{};
        std::string eName = myEnchants.at(pos).getName();
        std::pair<Type,int> p = ct.construct(getName());
        int enchSize = myEnchants.size();

        Minion tempM = ct.minions.at(p.second);
        int oriAtk = ct.minions.at(p.second).getAtk();
        int oriDef = ct.minions.at(p.second).getDef();
        bool dead = false;
        //int oriCost = ct.minions.at(p.second).getActivated().getCost();

        if (eName == "Giant Strength") {
                for (int i = 0; i < enchSize; ++i) tempM.addEnch(myEnchants.at(i));
                int hurted = tempM.getDef() - def;
                tempM.setAtk(oriAtk);
                tempM.setDef(oriDef);
                for (int a = 0; a < pos; ++a) tempM.addEnch(myEnchants.at(a));
                for (int b = pos; b < enchSize; ++b) tempM.addEnch(myEnchants.at(b));
                atk = tempM.getAtk();
                def = tempM.getDef() - hurted;
                if (def <= 0) dead = true;
        } else if (eName == "Enrage") {
                for (int i = 0; i < enchSize; ++i) tempM.addEnch(myEnchants.at(i));
                int hurted = tempM.getDef() - def;
                tempM.setAtk(oriAtk);
                tempM.setDef(oriDef);
                for (int a = 0; a < pos; ++a) tempM.addEnch(myEnchants.at(a));
                for (int b = pos; b < enchSize; ++b) tempM.addEnch(myEnchants.at(b));
                atk = tempM.getAtk();
                def = tempM.getDef() - hurted;
                if (def <= 0) dead = true;
        } else if (eName == "Haste") {
                maxActions -= 1;
        } else if (eName == "Magic Fatigue") {
                int oriCost = ct.minions.at(p.second).getActivated().getCost();
                activated.setCost(oriCost);
        } else if (eName == "Silence") {
                for (int a = 0; a < pos; ++a) tempM.addEnch(myEnchants.at(a));
                for (int b = pos; b < enchSize; ++b) tempM.addEnch(myEnchants.at(b));
		silenced = tempM.getSilenced();
        }

        std::vector<Enchantment>::iterator it = myEnchants.begin();
        for (int i = 0; i < pos; ++it) { ++i; }
        myEnchants.erase(it);
        return dead;
}

bool Minion::removeAllEnch() {
        bool died = false;
        for (int i = myEnchants.size() - 1; i >= 0; --i) {
                if (removeEnch(i)) died = true;
        }
        return died;
}



