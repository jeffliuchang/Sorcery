#ifndef HAND_H
#define HAND_H
#include <iostream>
<<<<<<< HEAD
#include <vector>
=======
>>>>>>> 0e54d17d96ad052dad7e0600b907d2ea4b0089ed

class Card;

class Hand {
<<<<<<< HEAD
	std::vector<Card> cards;
	int max;

	public:
	Hand(std::vector<Card> cards, int max);
	void add(Card &card);
	Card &play(Card &card);
};
=======
	vector<Card> cards;
	int max;

	public:
	Card(vector<Card> cards, int max);
	void add(Card card);
	Card play(Card card);
}
>>>>>>> 0e54d17d96ad052dad7e0600b907d2ea4b0089ed

#endif
