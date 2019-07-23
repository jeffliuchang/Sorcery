#ifndef HAND_H
#define HAND_H
#include <iostream>

class Card;

class Hand {
	vector<Card> cards;
	int max;

	public:
	Card(vector<Card> cards, int max);
	void add(Card card);
	Card play(Card card);
}

#endif
