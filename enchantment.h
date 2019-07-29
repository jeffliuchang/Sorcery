#ifndef ENCHANTMENT_H
#define ENCHANTMENT_H
#include <iostream>
#include <memory>
#include <vector>
#include "card.h"

class Minion;
class Ability;


class Enchantment final : public Card {
	std::string description;
public:
	Enchantment(std::string name, std::string description, int cost);
	std::string getDes();
	std::vector<std::string> display();
};

#endif
