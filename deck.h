#ifndef DECK_H
#define DECK_H
<<<<<<< HEAD
#include <vector>

class Card;

class Deck {
	std::vector<Card> cards;

	public:
	Deck(std::vector<Card> cards);
	void shuffle();
	Card &draw();
};
=======

class Deck {
	vector<Card> cards;

	public:
	Deck(vector<Card> cards);
	void shuffle();
	Card draw();
}
>>>>>>> 0e54d17d96ad052dad7e0600b907d2ea4b0089ed

#endif
