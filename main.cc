
#include <iostream>
#include <string>
#include "player.h"

using namespace std;


int main(int argc, char *argv[]) {
  cin.exceptions(ios::eofbit|ios::failbit);
  string cmd;




  try {
  while (true) {
    cin >> cmd;
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
