#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include "player.h"

using namespace std;


bool overwrite(ifstream &ifs, istream &is, string &s) {
	if (!(ifs >> s)) {
		if (!(is >> s)) {
			return false;
		}
	}
	return true;
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
	  Player player1{p1};
	  Player player2{p2};
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
  }
  catch (ios::failure &) {}
}
