#include "ability.h"

Ability::Ability(std::string description):description(description){};

std::string Ability::getDescription() {
	return description;
}
