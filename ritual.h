#ifndef RITUAL_H
#define RITUAL_H
#include <iostream>
#include <string>
#include "card.h"
#include "triggered.h"

<<<<<<< HEAD
class Minion;
class Player;

class Ritual final : public Card, public Triggered {
	int charge;
	int activationCost;

	public:
	Ritual(std::string name, int cost, std::string description, Condition condition, int charge, int activationCost);
	void usedOn(Minion& minion) override;
	void usedOn(Player& player) override;
};
=======
class Ritual final : public Card, public Triggered {
        int charge;
        int activationCost;

        public:
        Ritual(std::string name, int cost, std::string description, Condition condition, int charge, int activationCost);
        void usedOn(Minion& minion);
        void usedOn(Player& player);
}
>>>>>>> 0e54d17d96ad052dad7e0600b907d2ea4b0089ed




#endif
