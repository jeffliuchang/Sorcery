#ifndef MINION_H
#define MINION_H
#include "card.h"
#include "activated.h"
#include "triggered.h"
#include "enchantment.h"
#include <iostream>
#include <vector>
#include <memory>

class Ability;
class Player;



class Minion final: public Card {
	int actions;
	int maxActions;
	int oriDef;
	bool silenced;
	std::vector<Enchantment> myEnchants;
	Activated activated;
	Triggered triggered;
public:
	Minion(std::string name, int cost,int atk, int def, Activated activated, Triggered triggered);

	void setOriDef(int newDef);
	int getOriDef();
	bool spendActions(int spend);
	void recoverActions();
	Activated getActivated();
	Triggered getTriggered();
	std::vector<Enchantment> getEnchants();
	void attack(Player& player);
	bool takeDamage(int damage);
	bool getSilenced();
	std::vector<std::string> display();
	void addEnch(Enchantment newE);
	bool removeEnch(int pos);
	bool removeAllEnch();

};


#endif
