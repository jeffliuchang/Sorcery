#ifndef CARD_H
#define CARD_H
#include <iostream>
#include <string>

class Card{
	std::string name;
	int cost;

	public:
	Card(std::string name, int cost);
	virtual ~Card() = default;
	std::string getName() const;
	int getCost() const;
	void setName(std::string name);
	void setCost(int cost);
};

#endif
