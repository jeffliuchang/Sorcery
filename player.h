<<<<<<< HEAD

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
=======

#ifndef PLAYER_H_
#define PLAYER_H_
#include "board.h"
#include "hand.h"
#include "graveyard.h"
#include "deck.h"
#include <string>

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
	Player(int hp, int magic, std::string name, sd::shared_ptr<Ritual> ritual,
			std::shared_ptr<Board> board, std::shared_ptr<Hand> hand,
			std::shared_ptr<Graveyard> gy, std::shared_ptr<Deck> deck);
	~Player() = default;
	void castedBy(Ability& ability);
};




#endif /* PLAYER_H_ */
>>>>>>> 0e54d17d96ad052dad7e0600b907d2ea4b0089ed
