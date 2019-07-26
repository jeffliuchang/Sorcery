#include "player.h"
#include "minion.h"
#include <iostream>
#include <vector>
#include <cstdlib>

Player::Player(std::string name, std::vector<std::string> mydeck, bool shuffle)
:name(name),hp(20),magic(3){

	if (shuffle) {
		for (int j = mydeck.size(); j > 0; --j ) {
			int k = rand() % j;
			std::string temp = mydeck[j-1];
			mydeck[j-1] = mydeck[k];
			mydeck[k] = temp;
		}
	}

	deck = mydeck;


	for (int i = 0; i < 5; ++i) {
		hand.emplace_back(deck.at(0));
		deck.erase(deck.begin());
	}

	std::cout << "player constructor for " << name << std::endl;
}

std::string Player::getName() {
	return name;
}

std::vector<std::string> Player::getDeck() {
	return deck;
}

std::vector<std::string> Player::getHand() {
	return hand;
}

int Player::getHp() {
	return hp;
}

void Player::loseHp(int hpLost) {
	hp -= hpLost;
}

int Player::getMagic() {
	return magic;
}

void Player::removeHand(int pos) {
	std::cout << "printing first two cards before erase: " << std::endl;
	for (int j = 0; j < 2; ++j) std::cout << hand.at(j) << std::endl;
	std::vector<std::string>::iterator it = hand.begin();
	for (int i = 0; i < pos; ++it) { ++i; }
	hand.erase(it);
}

void Player::endTurn() {
	std::cout << getName() << " ends turn" << std::endl;
	std::cout << "hp: " << getHp() << std::endl;
	std::cout << "magic: " << getMagic() << std::endl;
}

void Player::startTurn() {
	std::cout << getName() << " starts turn" << std::endl;
	this->draw();
	magic++;
}

void Player::draw() {
	if (hand.size() < 5) {
		hand.emplace_back(deck.at(0));
		deck.erase(deck.begin());
	}
}

void Player::play(Minion newM) {
	board.emplace_back(newM);
	std::cout << "board size is " << board.size() << std::endl;
	for (int i = 0; i < board.size(); ++i) {
		std::cout << board.at(i).getName() << std::endl;
	}
}

void Player::attack(int attacker, Player& player){
	std::cout << "begin attack for " << name << std::endl;
	board.at(attacker).attack(player);
}

void Player::attack(int attacker, Player& player, int victim){
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

