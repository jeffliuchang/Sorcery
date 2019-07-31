#include "minion.h"
#include <memory>
#include "ability.h"
#include "player.h"
#include "card.h"
#include "ascii_graphics.h"
#include "cardtype.h"
#include "enchantment.h"


Minion::Minion(std::string name, int cost,
		int atk, int def, Activated activated, Triggered triggered)
:Card(name,cost),actions(0), maxActions(1), oriDef(def), silenced(false), activated(activated), triggered(triggered){
	setAtk(atk);
	setDef(def);
}

void Minion::setOriDef(int newDef) {
	oriDef = newDef;
}
int Minion::getOriDef() {
	return oriDef;
}

bool Minion::spendActions(int spend) {
	if (actions >= spend) {
		actions -= spend;
		return true;
	}
	return false;
}

void Minion::recoverActions() {
	actions = maxActions;
}

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
	def -= damage;
	oriDef -= damage;
	if (def <= 0) {
		return true;
	}
	int size = myEnchants.size();
	for (int i = 0; i < size; ++i) {
		myEnchants.at(i).setDefence(myEnchants.at(i).getDefence() - damage);
	}
	return false;
}

std::vector<std::string> Minion::display() {
	if ((activated.getDescription() != "NA")) {
		return display_minion_activated_ability(getName(), getCost(), atk, def,
				activated.getCost(), activated.getDescription());
	} else if (triggered.getDescription() != "NA") {
		return display_minion_triggered_ability(getName(),getCost(), atk, def, triggered.getDescription());
	} else {
		return display_minion_no_ability(getName(), getCost(), atk, def);
	}
}

bool Minion::getSilenced() {
	return silenced;
}

void Minion::addEnch(Enchantment newE) {
        myEnchants.emplace_back(newE);
        if (newE.getName() == "Giant Strength") {
                def += 2;
		atk += 2;
        } else if (newE.getName() == "Enrage") {
		def *= 2;
                atk *= 2;
        } else if (newE.getName() == "Haste") {
		maxActions +=1;
                actions += 1;
        } else if (newE.getName() == "Magic Fatigue") {
                activated.setCost(activated.getCost() + 2);
        } else if (newE.getName() == "Silence") {
                silenced = true;
        }
	myEnchants.at(myEnchants.size()-1).setDefence(def);
}

bool Minion::removeEnch(int pos) {
        Cardtype ct{};
        std::string eName = myEnchants.at(pos).getName();
        std::pair<Type,int> p = ct.construct(getName());
        int enchSize = myEnchants.size();

        Minion tempM = ct.minions.at(p.second);

        if (eName == "Giant Strength") {
		atk -=2;
        } else if (eName == "Enrage") {
		atk /= 2;
        } else if (eName == "Haste") {
                maxActions -= 1;
		if (actions > maxActions) actions = maxActions;
        } else if (eName == "Magic Fatigue") {
                activated.setCost(activated.getCost()-2);
        } else if (eName == "Silence") {
                for (int a = 0; a < pos; ++a) tempM.addEnch(myEnchants.at(a));
                for (int b = pos+1; b < enchSize; ++b) tempM.addEnch(myEnchants.at(b));
		silenced = tempM.getSilenced();
        }

        std::vector<Enchantment>::iterator it = myEnchants.begin();
        for (int i = 0; i < pos; ++it) { ++i; }
        myEnchants.erase(it);

	if (myEnchants.size() != 0) def = myEnchants.at(myEnchants.size()-1).getDefence();
	else def = oriDef;
	if (def < 0) return true;
	return false;
}

bool Minion::removeAllEnch() {
        bool died = false;
        for (int i = myEnchants.size() - 1; i >= 0; --i) {
                if (removeEnch(i)) died = true;
        }
	if (died) def = oriDef;
        return died;
}

