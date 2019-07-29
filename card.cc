#include "card.h"

Card::Card(std::string name, int cost):name(name), cost(cost) {}

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
