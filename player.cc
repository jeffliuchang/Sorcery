#include "player.h"
#include "minion.h"
#include "card.h"
#include "spell.h"
#include "ascii_graphics.h"
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

std::vector<Minion> Player::getBoard() {
	return board;
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
	//std::cout << "printing first two cards before erase: " << std::endl;
	//for (int j = 0; j < 2; ++j) std::cout << hand.at(j) << std::endl;
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

bool Player::play(Minion newM) {
	if (board.size() < 5) {
		board.emplace_back(newM);
		return true;
	}
	return false;
	/*
	std::cout << "board size is " << board.size() << std::endl;
	for (int i = 0; i < board.size(); ++i) {
		std::cout << board.at(i).getName() << std::endl;
	}*/
}

void Player::attack(int attacker, Player& player){
	//std::cout << "begin attack for " << name << std::endl;
	board.at(attacker).attack(player);
}

void Player::minionToGraveyard(int boardPos) {
	gy.emplace(gy.begin(),board.at(boardPos));
	auto it = board.begin();
	for (int i = 0; i < boardPos; ++i) { ++it; }
	board.erase(it);
}

bool Player::minionDamaged(int pos, int damage) {
	bool die;
	int size = board.size();
	if (size <= pos) {
		std::cout << "Victim position out of range." << std::endl;
		return false;
	}
	die = board.at(pos).takeDamage(damage);
	if (die) {
		minionToGraveyard(pos);
		return true;
	}
	return false;
}
/*
std::vector<bool> multipleMinionsDamaged(int damage, int start = 0, int end = 5) {
	int size = board.size();
	int realEnd = size<end ? size : end;
	std::vector<bool> die;
	for (int i = start; i < realEnd; i++) {
		die.emplace_back(board.at(i).takeDamage(damage));
	}
	return die;
}
*/
void Player::displayBoard() {
	std::vector<std::vector<std::string>> myBoard;
	int boardSize = board.size();
	for (int i = 0; i < boardSize; ++i) {
		myBoard.emplace_back(board.at(i).display());
	}

	int size = 11;
	if (boardSize == 0) {
		for (int a = 0; a < size; ++a) {
			for (int b = 0; b < 5; ++b) {
				std::cout << CARD_TEMPLATE_BORDER[a];
			}
			std::cout << std::endl;
		}
		return;
	}
	for (int a = 0; a < size; ++a) {
		int size2 = myBoard.size();
		for (int j = 0; j < size2; ++j) {
			std::cout << myBoard.at(j).at(a);
			if (j == size2 - 1) {
				for (int b = 0; b < (5 - size2); ++b) {
					std::cout << CARD_TEMPLATE_BORDER[a];
				}
				std::cout << std::endl;
			}
		}
	}
}

void Player::displayBoardRest(int playerNum) {
        std::vector<std::vector<std::string>> myBoard;
        int boardSize = board.size();
        card_template_t player = display_player_card(playerNum, name, hp, magic);
        card_template_t grave = gy.at(o).display();

        int lines = 11;
        int blocks = 5;
        for (int a = 0; a < lines; ++a) {
                for (int b = 0; b < blocks; ++b) {
                        if (b == 0) std::cout << CARD_TEMPLATE_BORDER[a];
                        else if ((b == 1) || (b == 3)) std::cout << CARD_TEMPLATE_EMPTY[a];
                        else if (b == 2) std::cout << player.at(a);
                        else if (b == 5) std::cout << grave.at(a);
                }
                std::cout << std::endl;
        }
}


bool Player::resurrect() {
	if (board.size() >= 5) {
		std::cout << "Board is full" << std::endl;
		return false;
	} else if (gy.size() < 1) {
		std::cout << "No dead minion" << std::endl;
		return false;
	}
	gy.at(0).setDef(1);
	board.emplace_back(gy.at(0));
	gy.erase(gy.begin());
	return true;
}

bool Player::minionToHand(int boardPos) {
	int boardSize = getBoard().size();
	int handSize = getHand().size();
	if (boardSize >= 5) {
		std::cout << "Target board is full, cannot use this spell." << std::endl;
		return false;
	} else if (handSize >= 5) {
		std::cout << "Target hand is full, cannot use this spell." << std::endl;
		return false;
	} else {
		hand.emplace_back(board.at(boardPos).getName());
		std::vector<Minion>::iterator it = board.begin();
		for (int i = 0; i < boardPos; ++it) { ++i; }
		board.erase(it);
	}
	return true;

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

