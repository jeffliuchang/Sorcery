#include "player.h"
#include "minion.h"
#include "card.h"
#include "spell.h"
#include "ascii_graphics.h"
#include "triggered.h"
#include "enchantment.h"
#include "ritual.h"
#include "cardtype.h"
#include <iostream>
#include <vector>
#include <cstdlib>

Player::Player(std::string name, std::vector<std::string> mydeck,bool shuffle)
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

	Cardtype ct{};
	std::pair<Type, int> p;
	for (int i = 0; i < 5; ++i) {
		p = ct.construct(deck.at(0));
		if (p.first == Type::Minion) hand.emplace_back(ct.minions.at(p.second));
		else if (p.first == Type::Spell) hand.emplace_back(ct.spells.at(p.second));
		else if (p.first == Type::Enchantment) hand.emplace_back(ct.enchantments.at(p.second));
		else if (p.first == Type::Ritual) {
			//std::cout << "put ritual in hand" << std::endl;
			hand.emplace_back(ct.rituals.at(p.second));
		}
		else if (p.first == Type::NA) {
			std::cout << "no card matching name " << deck.at(0) << std::endl;
			i--;
		}
		deck.erase(deck.begin());
	}


	//std::cout << "player constructor for " << name << std::endl;
}

std::string Player::getName() {
	return name;
}

std::vector<std::string> Player::getDeck() {
	return deck;
}

std::vector<Card> Player::getHand() {
	return hand;
}

std::vector<Minion> Player::getBoard() {
	return board;
}

int Player::getHp() {
	return hp;
}

std::vector<Ritual> Player::getRitual() {
	return ritual;
}

bool Player::removeRitual() {
	int size = ritual.size();
	if (size == 0) {
		std::cout << "player has no ritual" << std::endl;
		return false;
	}
	ritual.erase(ritual.begin());
	return true;
}

bool Player::setRitual(Ritual other) {
	int size = ritual.size();
	if ( size > 0 ) {
		ritual.erase(ritual.begin());
	}
	ritual.emplace_back(other);
	return true;
}
void Player::rechargeRitual(int recharge) {
	ritual.at(0).setCharge(ritual.at(0).getCharge()+recharge);
}

std::vector<Minion> Player::getGy() {
	return gy;
}

void Player::loseHp(int hpLost) {
	hp -= hpLost;
	if (hp <= 0) {
		throw PlayerDies(getName());
	}
}

int Player::getMagic() {
	return magic;
}

void Player::gainMagic(int gain) {
	magic += gain;
}

bool Player::spendMagic(int spend, bool testing) {
	if (magic >= spend) {
		magic -= spend;
		return true;
	} else {
		if (testing) {
			magic = 0;
			return true;
		}
	}
	return false;
}

void Player::removeHand(int pos) {
	//std::cout << "printing first two cards before erase: " << std::endl;
	//for (int j = 0; j < 2; ++j) std::cout << hand.at(j) << std::endl;
	std::vector<Card>::iterator it = hand.begin();
	for (int i = 0; i < pos; ++it) { ++i; }
	hand.erase(it);
}

void Player::endTurn(Player& opponent) {
	std::cout << getName() << " ends turn" << std::endl;
	std::cout << "hp: " << getHp() << std::endl;
	std::cout << "magic: " << getMagic() << std::endl;
	trigger(opponent, Condition::EndOfTurn,-1,1);
}

void Player::startTurn(Player& opponent) {
	std::cout << getName() << " starts turn" << std::endl;
	this->draw();
	magic++;
	int size = board.size();
	for (int i = 0; i < size; ++i) {
		board.at(i).recoverActions();
	}
	trigger(opponent, Condition::StartOfTurn,-1,1);
}

void Player::draw() {
	Cardtype ct{};
	std::pair<Type, int> p;
	if (hand.size() < 5) {
		p = ct.construct(deck.at(0));
		if (p.first == Type::Minion) hand.emplace_back(ct.minions.at(p.second));
		else if (p.first == Type::Spell) hand.emplace_back(ct.spells.at(p.second));
		else if (p.first == Type::Enchantment) hand.emplace_back(ct.enchantments.at(p.second));
		else if (p.first == Type::Ritual) hand.emplace_back(ct.rituals.at(p.second));
		else if (p.first == Type::NA) {
			std::cout << "no card matching name " << deck.at(0);
			draw();
			return;
		}
		deck.erase(deck.begin());
	}
}

bool Player::checkSilenced(int pos) {
	return board.at(pos).getSilenced();
}

bool Player::play(Player& opponent, Minion newM) {
	if (board.size() < 5) {
		board.emplace_back(newM);
		int pos = board.size()-1;
		trigger(opponent,Condition::MinionEnterPlay,pos,1);
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

bool Player::minionSpendAction(int boardPos, int spend) {
	return board.at(boardPos).spendActions(spend);
}

bool Player::minionToGraveyard(Player& opponent, int boardPos, int activePlayer) {
	int size = board.size();
	if (size <= boardPos or boardPos < 0) return false;
	gy.emplace(gy.begin(),board.at(boardPos));
	gy.at(0).removeAllEnch();
	auto it = board.begin();
	for (int i = 0; i < boardPos; ++i) { ++it; }
	board.erase(it);
	trigger(opponent,Condition::MinionExitPlay,-1, activePlayer);
	return true;
}

bool Player::minionDamaged(Player& opponent, int pos, int damage, int activePlayer) {
	bool die;
	int size = board.size();
	if (size <= pos) {
		std::cout << "Victim position out of range." << std::endl;
		return false;
	}
	die = board.at(pos).takeDamage(damage);
	if (die) {
		minionToGraveyard(opponent, pos, activePlayer);
		return true;
	}
	return false;
}


void Player::buffMinion(int boardPos, int atkBuff, int defBuff) {
	int size = board.size();
	if (size <= boardPos or boardPos < 0) return;
	int atk = board.at(boardPos).getAtk();
	board.at(boardPos).setAtk(atk+atkBuff);
	int def = board.at(boardPos).getDef();
	board.at(boardPos).setDef(def+defBuff);
}

bool Player::enchantMinion(int pos, Enchantment e) {
	int size = board.size();
	if (size <= pos) {
		std::cout << "position out of range" << std::endl;
		return false;
	}
	board.at(pos).addEnch(e);
	return true;
}

bool Player::removeTopEnchant(int pos) {
	int size = board.at(pos).getEnchants().size();
	return board.at(pos).removeEnch(size-1);
}

void Player::displayBoard() {
	std::vector<std::vector<std::string>> myBoard;
	int boardSize = board.size();
	for (int i = 0; i < boardSize; ++i) {
		myBoard.emplace_back(board.at(i).display());
	}

	int size = 11;
	if (boardSize == 0) {
		for (int a = 0; a < size; ++a) {
			std::cout << EXTERNAL_BORDER_CHAR_UP_DOWN;
			for (int b = 0; b < 5; ++b) {
				std::cout << CARD_TEMPLATE_BORDER[a];
			}
			std::cout << EXTERNAL_BORDER_CHAR_UP_DOWN << std::endl;
		}
		return;
	}
	for (int a = 0; a < size; ++a) {
		int size2 = myBoard.size();
		std::cout << EXTERNAL_BORDER_CHAR_UP_DOWN;
		for (int j = 0; j < size2; ++j) {
			std::cout << myBoard.at(j).at(a);
			if (j == size2 - 1) {
				for (int b = 0; b < (5 - size2); ++b) {
					std::cout << CARD_TEMPLATE_BORDER[a];
				}
				std::cout << EXTERNAL_BORDER_CHAR_UP_DOWN << std::endl;
			}
		}
	}
}

void Player::displayBoardRest(int playerNum) {
	//std::cout << "start display BoardRest in Player for player" << playerNum << std::endl;
	card_template_t player = display_player_card(playerNum, name, hp, magic);
	bool graveEmpty = false;
	card_template_t grave;
	if (gy.size() == 0) graveEmpty = true;
	else grave = gy.at(0).display();
	bool ritualEmpty = false;
	card_template_t ritualTemp;
	if (ritual.size() == 0) ritualEmpty = true;
	else ritualTemp = ritual.at(0).display();

	//std::cout << "starting for loop" << std::endl;
	int lines = 11;
	int blocks = 5;
	for (int a = 0; a < lines; ++a) {
		std::cout << EXTERNAL_BORDER_CHAR_UP_DOWN;
		for (int b = 0; b < blocks; ++b) {
			if (b == 0 and ritualEmpty) std::cout << CARD_TEMPLATE_BORDER[a];
			else if (b == 0 and !ritualEmpty) std::cout << ritualTemp.at(a);
			else if ((b == 1) || (b == 3)) std::cout << CARD_TEMPLATE_EMPTY[a];
			else if (b == 2) std::cout << player.at(a);
			else if ((b == 4) && !graveEmpty) std::cout << grave.at(a);
			else if ((b == 4) && graveEmpty) std::cout << CARD_TEMPLATE_BORDER[a];
		}
		std::cout << EXTERNAL_BORDER_CHAR_UP_DOWN << std::endl;
	}
}

void Player::inspectMinion(int pos) {
	int line = 11;
	std::vector<std::string> minion = board.at(pos).display();
	for (int j = 0; j < line; ++j) std::cout << minion.at(j) << std::endl;

	std::vector<std::vector<std::string>> allE;
	int size = board.at(pos).getEnchants().size();
	for (int i = 0; i < size; ++i) allE.emplace_back(board.at(pos).getEnchants().at(i).display());

	size = allE.size();
	for (int c = 0; c < size; ++c) {
		for (int a = 0; a < line; ++a) {
			int rest = ((size - c) < 5) ? (size - c) : 5;
			for (int j = 0; j < rest; ++j) {
				std::cout << allE.at(c+j).at(a);
			}
			std::cout << std::endl;
		}
		c+=4;
	}
}





bool Player::resurrect(Player& opponent) {
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
	int pos = board.size()-1;
	trigger(opponent, Condition::MinionEnterPlay, pos,1);
	return true;
}

bool Player::minionToHand(Player& opponent, int boardPos, int activePlayer) {
	int boardSize = getBoard().size();
	int handSize = getHand().size();
	if (boardSize <= boardPos or boardPos < 0) {
		std::cout << "Target out of range" << std::endl;
		return false;
	} else if (handSize >= 5) {
		std::cout << "Target hand is full, cannot use this spell." << std::endl;
		return false;
	} else {
		if (board.at(boardPos).removeAllEnch()) {
			minionToGraveyard(opponent,boardPos, activePlayer);
			return true;
		}
		hand.emplace_back(board.at(boardPos));
		std::vector<Minion>::iterator it = board.begin();
		for (int i = 0; i < boardPos; ++it) { ++i; }
		board.erase(it);
	}
	trigger(opponent,Condition::MinionExitPlay, -1, activePlayer);
	return true;

}


void Player::trigger(Player& opponent, Condition condition, int enterOrExit = -1, int activePlayer = 1) {
	if (activePlayer == 1) {
		int size = board.size();
		for (int i = 0; i < size; ++i) {
			board.at(i).getTriggered().usedOn(*this,opponent,1,i,enterOrExit,condition);
		}
		int rSize = ritual.size();
		if (rSize > 0) {
			ritual.at(0).usedOn(*this,opponent,1,enterOrExit,condition);
		}
	}

	int opponentSize = opponent.getBoard().size();
	for (int i = 0; i < opponentSize; ++i) {
		opponent.getBoard().at(i).getTriggered().usedOn(*this,opponent,2,i,enterOrExit,condition);
	}
	int oppRSize = opponent.getRitual().size();
	if (oppRSize > 0) {
		opponent.getRitual().at(0).usedOn(*this,opponent,2,enterOrExit,condition);
	}

	if (activePlayer == 2) {
		int size = board.size();
		for (int i = 0; i < size; ++i) {
			board.at(i).getTriggered().usedOn(*this,opponent,1,i,enterOrExit,condition);
		}
		int rSize = ritual.size();
		if (rSize > 0) {
			ritual.at(0).usedOn(*this,opponent,1,enterOrExit,condition);
		}
	}
}

void Player::displayHand() {
	Cardtype ct{};
	std::pair<Type,int> cur;
	std::vector<std::vector<std::string>> myHands;
	int handSize = hand.size();
	for (int a = 0; a < handSize; ++a) {
		std::string name = hand.at(a).getName();
		cur = ct.construct(name);
		if (cur.first == Type::Minion) {
			Minion minion(hand.at(a).getName(),hand.at(a).getCost(),
					hand.at(a).getAtk(),hand.at(a).getDef(),
					ct.minions.at(cur.second).getActivated(),
					ct.minions.at(cur.second).getTriggered());
			myHands.emplace_back(minion.display());
		} else if (cur.first == Type::Spell) {
			Spell s = ct.spells.at(cur.second);
			myHands.emplace_back(display_spell(s.getName(),s.Card::getCost(),s.getDescription()));
		} else if (cur.first == Type::Enchantment) {
			myHands.emplace_back(ct.enchantments.at(cur.second).display());
		} else if (cur.first == Type::Ritual) {
			Ritual r = ct.rituals.at(cur.second);
			myHands.emplace_back(display_ritual(r.getName(), r.Card::getCost(), r.getActCost(), r.getDescription(), r.getCharge()));
		} else if (cur.first == Type::NA) {
			std::cout << "the " << a << "th card in Hand does not match anything in Cardtype class (Player::displayHand())" << std::endl;
		}
	}

	int lines = 11;
	int size = myHands.size();
	for (int i = 0; i < lines; ++i) {
		for (int j = 0; j < size; ++j) {
			std::cout << myHands.at(j).at(i);
		}
		std::cout << std::endl;
	}
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

