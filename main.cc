#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include "player.h"
#include "cardtype.h"
#include "minion.h"
#include "spell.h"
#include "ascii_graphics.h"
#include "displayGraphic.h"
using namespace std;


bool overwrite(ifstream &ifs, istream &is, string &s) {
	if (!getline(ifs,s)) {
		if (!getline(is,s)) {
			return false;
		}
	}
 	return true;
}

class InvalidFile {};

vector<string> loadDeck(string file) {
	ifstream ifs{file};
	if (ifs.fail()) {
		cout << file << " not found" << endl;
		throw InvalidFile();
	}
	string s;
	vector<string> vec;
	while (getline(ifs,s)) {
		vec.emplace_back(s);
	}
	return vec;
}

void updateCurr(Player *&curr, Player *player1, Player * player2) {
	if (curr == player1) {
		curr = player2;
	} else {
		curr = player1;
	}
}

int main(int argc, char *argv[]) {
	cin.exceptions(ios::eofbit|ios::failbit);
	string cmd;
	ifstream init;
	vector<string> deck1;
	vector<string> deck2;
	bool testing = false;
	bool graphic = false;
	try{
		deck1 = loadDeck("default.deck");
		deck2 = deck1;
		for (int i = 1; i < argc ; i++) {
			istringstream iss(argv[i]);
			string argument;
			cout << argument << endl;
			iss >> argument;
			if (argument == "-deck1") {
				istringstream iss(argv[i+1]);
				iss >> argument;
				deck1 = loadDeck(argument);
				i++;
			} else if (argument == "-deck2") {
				istringstream iss(argv[i+1]);
				iss >> argument;
				deck2 = loadDeck(argument);
				i++;
			} else if (argument == "-init") {
				istringstream iss(argv[i+1]);
				iss >> argument;
				init.open(argument,ifstream::in);
				i++;
			} else if (argument == "-testing") {
				testing = true;
			} else if (argument == "-graphics") {
				graphic = true;
			}
		}
	}
	catch(InvalidFile&) { return 0;}

	string p1;
	string p2;
  try {
	  Cardtype ct{};
	  overwrite(init,cin,p1);
	  overwrite(init,cin,p2);
	  Player player1{p1, deck1, !testing};
	  Player player2{p2, deck2, !testing};
	  Player *curr = &player1;
	  Player *opponent = &player2;
	  int activePlayer = 1;

	  while (overwrite(init,cin,cmd)) {
		  if (curr == &player1) {
			  opponent = &player2;
			  activePlayer = 1;
		  } else {
			  opponent = &player1;
			  activePlayer = 2;
		  }
		  cout << cmd << endl;
		  istringstream line(cmd);
		  string next;
		  line >> next;
		  if (next == "help") {
			  cout << "Commands: help -- Display this message." << endl;
			  cout << "          end -- End the current player's turn." << endl;
			  cout << "          quit -- End the game." << endl;
			  cout << "          attack minion other-minion -- Orders minion to attack other-minion." << endl;
			  cout << "          attack minion -- Orders minion to attack the opponent." << endl;
			  cout << "          play card [target-player target-card] -- Play card, optionally targeting target-card owned by target-player." << endl;
			  cout << "          use minion [target-player target-card] -- Use minion's special ability, optionally targeting target-card owned by target-player." << endl;
			  cout << "          inspect minion -- View a minion's card and all enchantments on that minion." << endl;
			  cout << "          hand -- Describe all cards in your hand." << endl;
			  cout << "          board -- Describe all cards on the board." << endl;
		  } else if (next == "end") {
			  curr->endTurn(*opponent);
			  updateCurr(curr,&player1,&player2);
			  curr->startTurn(*opponent);
		  } else if (next == "quit") {
			  return 0;
		  } else if (next == "draw") {
			  if (testing) {
				  curr->draw();
			  } else {
				  cout << "only available in testing mode" << endl;
			  }
		  } else if (next == "discard") {
			  if (testing) {
				  int toDiscard;
				  if (line >> toDiscard) {
					  int size = curr->getHand().size();
					  if (size < toDiscard) {
						  cout << "card index out of range" << endl;
						  continue;
					  }
					  curr->removeHand(toDiscard-1);
				  }
			  } else {
				  cout << "only available in testing mode" << endl;
			  }
		  } else if (next == "attack") {
			  int attacker, victim;
			  if (line >> attacker) {
				  int size = curr->getBoard().size();
				  if (size < attacker or attacker < 0) {
					  cout << "index out of range" << endl;
					  continue;
				  }

				  if (line >> victim) {
					  if (curr == &player1) {
						  int size = player2.getBoard().size();
						  if (size < victim or victim < 0) {
							  cout << "index out of range" << endl;
							  continue;
						  }
						  if (!(curr->minionSpendAction(attacker-1,1))) {
							  cout << "minion has no action left" << endl;
							  continue;
						  }
						  int takeDamage = player2.getBoard().at(victim-1).getAtk();
						  int dealDamage = player1.getBoard().at(attacker-1).getAtk();
						  curr->minionDamaged(player2,attacker-1,takeDamage,activePlayer);
						  player2.minionDamaged(player1,victim-1, dealDamage,activePlayer);
					  } else {
						  int size = player1.getBoard().size();
						  if (size < victim or victim < 0) {
							  cout << "index out of range" << endl;
							  continue;
						  }
						  if (!(curr->minionSpendAction(attacker-1,1))) {
							  cout << "minion has no action left" << endl;
							  continue;
						  }
						  int takeDamage = player1.getBoard().at(victim-1).getAtk();
						  int dealDamage = player2.getBoard().at(attacker-1).getAtk();
						  curr->minionDamaged(player1,attacker-1,takeDamage,activePlayer);
						  player1.minionDamaged(player2,victim-1, dealDamage,activePlayer);
					  }
				  } else {
					  if (!(curr->minionSpendAction(attacker-1,1))) {
						  cout << "minion has no action left" << endl;
						  continue;
					  }
					  //std::cout << "reach 1" << std::endl;
					  if (curr == &player1) {
						  curr->attack(attacker-1, player2);
					      //std::cout << "reach 2" << std::endl;
					  }
					  else curr->attack(attacker-1, player1);
				  }
			  }
		  } else if (next == "play") {
			  //std::cout << "reach play in main" << std::endl;
			  int mine, player, yourPos;
			  string yours;
			  if (line >> mine) {
				  int size = curr->getHand().size();
				  if (mine > size or mine < 0) {
					  cout << "there is no " << mine << "th card in hand" << endl;
					  continue;
				  }
				  std::string name = curr->getHand().at(mine-1).getName();
				  std::pair<Type,int> p = ct.construct(name);
				  bool played = false;
				  if ((line >> player) && (line >> yours)) {
					  Player* target = &player1;
					  if (player == 2) target = &player2;
					  Player* otherPlayer = &player2;
					  if (player == 2) otherPlayer = &player1;
					  if (yours == "r") {
						  yourPos = 6;
					  } else {
						  istringstream pos(yours);
						  if (!(pos >> yourPos)) continue;
					  }

					  if (p.first == Type::Spell) {
						  int cost = ct.spells.at(p.second).Card::getCost();
						  if (!(curr->spendMagic(cost,testing))) {
							  cout << "not enough magic" << endl;
							  continue;
						  }
						  played = ct.spells.at(p.second).usedOn(*target, *otherPlayer, yourPos-1,activePlayer);
						  if (!played) curr->gainMagic(cost);
						  
					  } else if (p.first == Type::Enchantment) {
						  int cost = ct.enchantments.at(p.second).getCost();
						  if (!(curr->spendMagic(cost,testing))) {
							  cout << "not enough magic" << endl;
							  continue;
						  }
						  if (player == 1) played = player1.enchantMinion(yourPos-1, ct.enchantments.at(p.second));
						  else played = player2.enchantMinion(yourPos-1, ct.enchantments.at(p.second));
						  if (!played) curr->gainMagic(cost);
						  
					  } else if (p.first == Type::NA) {
						  cout << "The given name does not match any card." << endl;
					  }
				  } else {
					  if (p.first == Type::Minion) {
						  int cost = curr->getHand().at(mine-1).getCost();
						  if (!(curr->spendMagic(cost,testing))) {
							  cout << "not enough magic" << endl;
							  continue;
						  }
						  int atk = curr->getHand().at(mine-1).getAtk();
						  int def = curr->getHand().at(mine-1).getDef();
						  Activated activated = ct.minions.at(p.second).getActivated();
						  Triggered triggered = ct.minions.at(p.second).getTriggered();
						  Minion minion(name,cost,atk,def,activated,triggered);
						  played = curr->play(*opponent, minion);
						  if (!played) curr->gainMagic(cost);
					  } else if (p.first == Type::Spell) {
						  int cost = ct.spells.at(p.second).Card::getCost();
						  if (!(curr->spendMagic(cost,testing))) {
							  cout << "not enough magic" << endl;
							  continue;
						  }
						  if (curr == &player1) played = ct.spells.at(p.second).usedOn(player1, player2,-1,activePlayer);
						  else played = ct.spells.at(p.second).usedOn(player2, player1,-1,activePlayer);
						  if (!played) curr->gainMagic(cost);
					  } else if (p.first == Type::Ritual) {
						  int cost = ct.rituals.at(p.second).getCost();
						  if (!(curr->spendMagic(cost,testing))) {
							  cout << "not enough magic" << endl;
							  continue;
						  }
						  played = curr->setRitual(ct.rituals.at(p.second));
					  } else if (p.first == Type::NA) {
						  cout << "The given name does not match any card." << endl;
					  }
				  }
				  if (played) curr->removeHand(mine-1);
			  } else {
				  cout << "invalid play" << endl;
			  }
		  } else if (next == "use") {
			  int mine, player, yourPos;
			  if (line >> mine) {
				  int boardSize = curr->getBoard().size();
				  if (boardSize < mine or mine < 0) {
					  cout << "minion not found at position " << mine << endl;
					  continue;
				  }
				  if (curr->checkSilenced(mine-1)) {
					  cout << "minion silenced" << endl;
					  continue;
				  }
				  if (!(curr->minionSpendAction(mine-1,1))) {
					  cout << "minion has no action left" << endl;
					  continue;
				  }
				  int cost = curr->getBoard().at(mine-1).getActivated().getCost();
				  if (!(curr->spendMagic(cost,testing))) {
					  cout << "not enough magic" << endl;
					  continue;
				  }

				  if ((line >> player) && (line >> yourPos)) {

					  if (player == 1) {
						  curr->getBoard().at(mine-1).getActivated().usedOn(player1, player2, yourPos-1);
					  } else {
						  curr->getBoard().at(mine-1).getActivated().usedOn(player2, player1, yourPos-1);
					  }

				  } else {
					  curr->getBoard().at(mine-1).getActivated().usedOn(*curr,*opponent,-1);
				  }
			  }
		  } else if (next == "inspect") {
			  int pos;
			  if (!(line >> pos)) {
				  cout << "please enter a number after inspect " << endl;
				  continue;
			  }
			  int size = curr->getBoard().size();
			  if (size < pos or pos < 0) {
				  cout << "index out of range" << endl;
				  continue;
			  }
			  curr->inspectMinion(pos-1);
			  if (graphic) describe_minion(curr->getBoard().at(pos));
		  } else if (next == "hand") {
			  curr->displayHand();
			  if (graphic) display_hand(curr->getHand());
		  } else if (next == "board") {
			  cout << EXTERNAL_BORDER_CHAR_TOP_LEFT;
        		  for (int a = 0; a < 165; ++a) cout << EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
        		  cout << EXTERNAL_BORDER_CHAR_TOP_RIGHT << endl; //print first line

        		  //cout << "start displayBoardRest for 1" << endl;
        		  player1.displayBoardRest(1);
        		  //cout << "end displayBoardRest for 1" << endl;
        		  player1.displayBoard();
        		  int size = CENTRE_GRAPHIC.size();
        		  for (int i = 0; i < size; ++i) cout << CENTRE_GRAPHIC.at(i) << endl;
        		  player2.displayBoard();
        		  player2.displayBoardRest(2);
		  
        		  cout << EXTERNAL_BORDER_CHAR_TOP_LEFT;
        		  for (int a = 0; a < 165; ++a) cout << EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
        		  cout << EXTERNAL_BORDER_CHAR_TOP_RIGHT << endl; // print last line
        		  curr->displayHand();
        		  if (graphic) display_board(player1, player2);
        		  if (graphic) display_hand(curr->getHand());
		  }
	  }
  }
  catch (ios::failure &) {}
  catch (PlayerDies &deadPlayer) {
	  if (deadPlayer.getName() == p1) {
		  cout << p2 << " wins!";
	  } else {
		  cout << p1 << " wins!";
	  }
  }
}
