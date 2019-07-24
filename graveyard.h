#ifndef GRAVEYARD_H
#define GRAVEYARD_H
#include <iostream>
#include <vector>

class Minion;

class Graveyard {
	std::vector<Minion> minions;

	public:
	Graveyard(std::vector<Minion> minions);
};



#endif
