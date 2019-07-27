
#ifndef PLAYER_H_
#define PLAYER_H_
/*
#include "board.h"
#include "hand.h"
#include "graveyard.h"
#include "deck.h"
#include "ritual.h"
*/
//#include "triggered.h"
#include <string>
#include <memory>
#include <vector>

class Card;
class Minion;
enum class Condition;

class Player {
	std::string name;
	int hp;
	int magic;
	std::vector<std::string> deck;
	std::vector<std::string> hand;
	std::vector<Minion> board;
	std::vector<Minion> gy;
	/*
	int hp;
	int magic;
	std::string name;
	std::shared_ptr<Ritual> ritual;
	std::shared_ptr<Board> board;
	std::shared_ptr<Hand> hand;
	std::shared_ptr<Graveyard> gy;
	std::shared_ptr<Deck> deck;
	*/
public:
	Player(std::string name, std::vector<std::string> mydeck, bool shuffle);
	std::string getName();
	std::vector<std::string> getDeck();
	std::vector<std::string> getHand();
	std::vector<Minion> getBoard();

	int getHp();
	void loseHp(int hpLost);
	int getMagic();
	void removeHand(int pos);
	void endTurn(Player& opponent);
	void startTurn(Player& opponent);
	void draw();
	bool play(Player& opponent, Minion newM);
	void attack(int attacker, Player& player);
	void minionToGraveyard(Player& opponent, int boardPos);
	bool resurrect(Player& opponent);
	bool minionToHand(Player& opponent, int boardPos);
	bool minionDamaged(Player& opponent, int pos, int damage);
	bool hasMinion(Minion &minion);
	void trigger(Player& opponent, Condition condition, int enterOrExit);
	//std::vector<bool> multipleMinionsDamaged(int damage, int start = 0, int end = 5);

	void displayBoard();
	void displayBoardRest(int playerNum);
	/*
	Player(int hp, int magic, std::string name, std::shared_ptr<Ritual> ritual,
			std::shared_ptr<Board> board, std::shared_ptr<Hand> hand,
			std::shared_ptr<Graveyard> gy, std::shared_ptr<Deck> deck);
	~Player() = default;
	void castedBy(Ability& ability);
	void attackedBy(Minion& minion);
	*/
};




#endif /* PLAYER_H_ */
