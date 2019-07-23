#ifndef DECK_H
#define DECK_H

class Deck {
	vector<Card> cards;

	public:
	Deck(vector<Card> cards);
	void shuffle();
	Card draw();
}

#endif
