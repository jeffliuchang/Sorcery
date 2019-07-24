#ifndef CARD_H
#define CARD_H
#include <iostream>
#include <string>

class Card{
	std::string name;
	int cost;

	public:
	Card(std::string name, int cost);
	virtual ~Card() = 0;
};

#endif
