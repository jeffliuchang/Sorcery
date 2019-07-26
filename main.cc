#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include "player.h"
#include "cardtype.h"
#include "minion.h"
#include "spell.h"
using namespace std;


bool overwrite(ifstream &ifs, istream &is, string &s) {
	if (!getline(ifs,s)) {
		if (!getline(is,s)) {
			return false;
		}
	}
 	return true;
}

vector<string> loadDeck(string file) {
	ifstream ifs{file};
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

  for (int i = 1; i < argc - 1; i++) {
	  istringstream iss(argv[i]);
	  string argument;
	  iss >> argument;
	  if (argument == "-deck1") {

	  } else if (argument == "-deck2") {

	  } else if (argument == "-init") {
		  istringstream iss(argv[i+1]);
		  iss >> argument;
		  init.open(argument,ifstream::in);
		  i++;
	  } else if (argument == "-testing") {

	  } else if (argument == "-graphics") {

	  }
  }


  try {
	  Cardtype ct{};
	  string p1;
	  string p2;
	  overwrite(init,cin,p1);
	  overwrite(init,cin,p2);
	  Player player1{p1, loadDeck("default.deck"), false};
	  Player player2{p2, loadDeck("default.deck"), false};
/*
	  cout << player1.getName() << endl;
	  	  for (string &s : player1.getDeck()) {
	  		  cout << s << endl;
	  	  }
	  	  cout << player2.getName() << endl;
	  	  for (string &s : player2.getDeck()) {
	  	  		  cout << s << endl;
	  	  }
*/
	  Player *curr = &player1;

	  while (overwrite(init,cin,cmd)) {
		  cout << cmd << endl;
		  istringstream line(cmd);
		  string next;
		  line >> next;
		  if (next == "help") {

		  } else if (next == "end") {
			  curr->endTurn();
			  updateCurr(curr,&player1,&player2);
			  curr->startTurn();
		  } else if (next == "quit") {

		  } else if (next == "draw") {

		  } else if (next == "discard") {

		  } else if (next == "attack") {
			  int attacker, victim;
			  if (line >> attacker) {
				  if (line >> victim) {
					  if (curr == &player1) {
						  int takeDamage = player2.getBoard().at(victim-1).getAtk();
						  int dealDamage = player1.getBoard().at(attacker-1).getAtk();
						  curr->minionDamaged(attacker-1,takeDamage);
						  player2.minionDamaged(victim-1, dealDamage);
					  } else {
						  int takeDamage = player1.getBoard().at(victim-1).getAtk();
						  int dealDamage = player2.getBoard().at(attacker-1).getAtk();
						  curr->minionDamaged(attacker-1,takeDamage);
						  player1.minionDamaged(victim-1, dealDamage);
					  }
				  } else {
					  std::cout << "reach 1" << std::endl;
					  if (curr == &player1) {
						  curr->attack(attacker-1, player2);
					      std::cout << "reach 2" << std::endl;
					  }
					  else curr->attack(attacker-1, player1);
				  }
			  }
		  } else if (next == "play") {
			  //std::cout << "reach play in main" << std::endl;
			  int mine, player, yourPos;
			  string yours;
			  if (line >> mine) {
				  std::string name = curr->getHand().at(mine-1);
				  std::pair<Type,int> p = ct.construct(name);
				  bool played = false;
				  if ((line >> player) && (line >> yours)) {
					  Player* target = &player1;
					  if (player == 2) target = &player2;
					  if (yours == "r") {
						  yourPos = 6;
					  } else {
						  istringstream pos(yours);
						  pos >> yourPos;
					  }

					  if (p.first == Type::Minion) {
					  } else if (p.first == Type::Spell) {
						  played = ct.spells.at(p.second).usedOn(*target, yourPos-1);

					  } else if (p.first == Type::Enchantment) {
					  } else if (p.first == Type::Ritual) {
					  } else if (p.first == Type::NA) {
					  }
				  } else {
					  //cout << "got here" << endl;
					  if (p.first == Type::Minion) {
						  //cout << "play minion" << endl;
						  played = curr->play(ct.minions.at(p.second));
					  } else if (p.first == Type::Spell) {
						  //cout << "play spell" << endl;
						  if (curr == &player1) ct.spells.at(p.second).usedOn(player1, player2);
						  else ct.spells.at(p.second).usedOn(player1, player2);
					  } else if (p.first == Type::Enchantment) {
					  } else if (p.first == Type::Ritual) {
					  } else if (p.first == Type::NA) {
					  }
				  }
				  if (played) curr->removeHand(mine-1);
			  }
		  } else if (next == "use") {
			  int mine, player, yourPos;
			  string yours;
			  if (line >> mine) {
				  if ((line >> player) && (line >> yours)) {
					  if (yours == "r") {
						  if (player == 1) {
							  curr->getBoard().at(mine-1).getActivated().usedOn(player1);
						  } else {
							  curr->getBoard().at(mine-1).getActivated().usedOn(player2);
						  }
					  } else {
						  istringstream pos(yours);
						  pos >> yourPos;
						  if (player == 1) {
							  curr->getBoard().at(mine-1).getActivated().usedOn(player1, yourPos-1);
						  } else {
							  curr->getBoard().at(mine-1).getActivated().usedOn(player2, yourPos-1);
						  }
					  }
				  }
			  } else {
				  curr->getBoard().at(mine-1).getActivated().usedOn(*curr);
			  }
		  } else if (next == "describe") {

		  } else if (next == "hand") {

		  } else if (next == "board") {
			  curr->displayBoard();
		  }
	  }
	  cout << "loop ends" << endl;
  }
  catch (ios::failure &) {cout << "got here" << endl;}
}
