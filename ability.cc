#include "ability.h"

Ability::Ability(std::string description):description(description){};

std::string Ability::getDescription() const {
	return description;
}

void Ability::setDescription(std::string description) {
	this->description = description;
}
