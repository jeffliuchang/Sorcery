#ifndef BOARD_H
#define BOARD_H
#include <iostream>

class Minion;

class Board {
	vector<Minion> minions;
	int max;

	public:
	Board(vector<Minion> minions, int max);
}



#endif
