#ifndef HAND_H
#define HAND_H
#include <iostream>
#include <vector>

class Card;

class Hand {
	std::vector<Card> cards;
	int max;

	public:
	Hand(std::vector<Card> cards, int max);
	void add(Card &card);
	Card &play(Card &card);
};

#endif
