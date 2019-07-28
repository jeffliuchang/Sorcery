#include "enchantment.h"

Enchantment::Enchantment(std::string name, std::string description, int cost)
:Card(name,cost), description(description) {}

std::string Enchantment::getDes() {
	return description;
}
