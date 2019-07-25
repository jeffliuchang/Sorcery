#include "minion.h"
#include <memory>
#include "ability.h"
#include "player.h"
#include "card.h"
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
		int atk, int def):Card(name,cost),atk(atk),def(def){}


void Minion::attack(Player& player) {
	player.loseHp(atk);
}

