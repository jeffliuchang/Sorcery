#include "card.h"

Card::Card(std::string name, int cost):name(name), cost(cost), atk(0), def(0) {}

std::string Card::getName() const{
	return name;
}

int Card::getCost() const{
	return cost;
}

void Card::setName(std::string name) {
	this->name = name;
}

void Card::setCost(int cost) {
	this->cost = cost;
}

int Card::getAtk() {
	return atk;
}

void Card::setAtk(int atk) {
	this->atk = atk;
}

int Card::getDef() {
	return def;
}

void Card::setDef(int def) {
	this->def = def;
}
