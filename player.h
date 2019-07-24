
#ifndef PLAYER_H_
#define PLAYER_H_
#include "board.h"
#include "hand.h"
#include "graveyard.h"
#include "deck.h"
#include "ritual.h"
#include <string>
#include <memory>

class Player {
	int hp;
	int magic;
	std::string name;
	std::shared_ptr<Ritual> ritual;
	std::shared_ptr<Board> board;
	std::shared_ptr<Hand> hand;
	std::shared_ptr<Graveyard> gy;
	std::shared_ptr<Deck> deck;
public:
	Player(int hp, int magic, std::string name, std::shared_ptr<Ritual> ritual,
			std::shared_ptr<Board> board, std::shared_ptr<Hand> hand,
			std::shared_ptr<Graveyard> gy, std::shared_ptr<Deck> deck);
	~Player() = default;
	void castedBy(Ability& ability);
};




#endif /* PLAYER_H_ */
