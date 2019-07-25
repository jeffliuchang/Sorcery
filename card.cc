#include "card.h"

Card::Card(std::string name, int cost):name(name), cost(cost) {}

std::string Card::getName() {
	return name;
}

int Card::getCost() {
	return cost;
}
