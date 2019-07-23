#ifndef CARD_H
#define CARD_H
#include <iostream>
#include <string>

class Card{
	string name;
	int cost;

	public:
	Card(string name, int cost);
	virtual ~Card() = 0;
};

#endif
