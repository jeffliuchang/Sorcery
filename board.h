#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <vector>


class Minion;

class Board {
	std::vector<Minion> minions;
	int max;

	public:
	Board(std::vector<Minion> minions, int max);
};



#endif
