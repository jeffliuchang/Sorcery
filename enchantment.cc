#include "enchantment.h"
#include "ascii_graphics.h"

Enchantment::Enchantment(std::string name, std::string description, int cost)
:Card(name,cost), description(description) {}

std::string Enchantment::getDes() {
	return description;
}

std::vector<std::string> Enchantment::display() {
	if (getName() == "Giant Strength") {
		return display_enchantment_attack_defence(getName(), getCost(), description, "+2", "+2");
	} else if (getName() == "Enrage") {
		return display_enchantment_attack_defence(getName(), getCost(), description, "*2", "*2");
	} else {
		return display_enchantment(getName(), getCost(), description);
	}
}
