#include "player.h"
#include <iostream>
#include <vector>

Player::Player(std::string name, std::vector<std::string> deck):name(name),deck(deck){
	std::cout << "player constructor for " << name << std::endl;
}

std::string Player::getName() {
	return name;
}

std::vector<std::string> Player::getDeck() {
	return deck;
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

