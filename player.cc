#include "player.h"
#include <iostream>

Player::Player(std::string name):name(name){
	std::cout << "player constructor for " << name << std::endl;
}

/*
Player::Player(int hp, int magic, std::string name, std::shared_ptr<Ritual> ritual,
		std::shared_ptr<Board> board, std::shared_ptr<Hand> hand,
		std::shared_ptr<Graveyard> gy, std::shared_ptr<Deck> deck)
:hp(hp),magic(magic),name(name),ritual(ritual),board(board),hand(hand),gy(gy),deck(deck){}

void castedBy(Ability& ability) {

}

void attackedBy(Minion& minion) {

}
*/

