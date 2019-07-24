<<<<<<< HEAD

#ifndef ABILITY_H_
#define ABILITY_H_
#include <string>
#include <memory>

class Minion;
class Player;

class Ability {
	std::string description;
public:
	Ability(std::string description);
	virtual ~Ability() = default;
	virtual void usedOn(std::shared_ptr<Minion> minion) = 0;
	virtual void usedOn(std::shared_ptr<Player> player) = 0;
};



#endif
=======

#ifndef ABILITY_H_
#define ABILITY_H_
#include <string>

class Ability {
	std::string description;
public:
	Ability(std::string description);
	virtual ~Ability() = default;
	virtual void usedOn(std::shared_ptr<Minion> minion) = 0;
	virtual void usedOn(std::shared_ptr<Player> player) = 0;
};



#endif
>>>>>>> 0e54d17d96ad052dad7e0600b907d2ea4b0089ed
