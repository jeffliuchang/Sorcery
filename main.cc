#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include "player.h"

using namespace std;


bool overwrite(ifstream &ifs, istream &is, string &s) {
	if (!getline(ifs,s)) {
		if (!getline(is,s)) {
			cout << "read fails" << endl;
			return false;
		}
	}
	cout << "s is: " << s << endl;
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
	  string p1;
	  string p2;
	  overwrite(init,cin,p1);
	  overwrite(init,cin,p2);
	  Player player1{p1, loadDeck("default.deck")};
	  Player player2{p2, loadDeck("default.deck")};
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
	  while (overwrite(init,cin,cmd)) {
		  cout << cmd << endl;
		  if (cmd == "help") {

		  } else if (cmd == "end") {

		  } else if (cmd == "quit") {

		  } else if (cmd == "draw") {

		  } else if (cmd == "discard") {

		  } else if (cmd == "attack") {

		  } else if (cmd == "play") {

		  } else if (cmd == "use") {

		  } else if (cmd == "describe") {

		  } else if (cmd == "hand") {

		  } else if (cmd == "board") {

		  }
	  }
	  cout << "loop ends" << endl;
  }
  catch (ios::failure &) {cout << "got here" << endl;}
}
