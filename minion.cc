#include "minion.h"
#include <memory>
#include "ability.h"
#include "player.h"
#include "card.h"
#include "ascii_graphics.h"
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
:Card(name,cost),atk(atk),def(def), activated(activated), triggered(triggered) {}

Activated Minion::getActivated() {
	return activated;
}

Triggered Minion::getTriggered() {
	return triggered;
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
		return display_minion_triggered_ability(getName(),getCost(), atk, def, triggered.getDescription())
	} else {
		return display_minion_no_ability(getName(), getCost(), atk, def);
	}
}

void Minion::setDef(int def) {
	this->def = def;
}

void Minion::setAtk(int atk) {
	this->atk = atk;
}

int Minion::getDef() {
	return this->def;
}

int Minion::getAtk() {
	return this->atk;
}
