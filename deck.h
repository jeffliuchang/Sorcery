#ifndef DECK_H
#define DECK_H
#include <vector>

class Card;

class Deck {
	std::vector<Card> cards;

	public:
	Deck(std::vector<Card> cards);
	void shuffle();
	Card &draw();
};

#endif
