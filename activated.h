<<<<<<< HEAD

#ifndef ACTIVATED_H_
#define ACTIVATED_H_
#include "ability.h"

class Activated : public Ability {
	int cost;
public:
	Activated(std::string description, int cost);
	virtual ~Activated() = default;
	virtual void usedOn(std::shared_ptr<Minion> minion) override;
	virtual void usedOn(std::shared_ptr<Player> player) override;
};




#endif /* ACTIVATED_H_ */
=======

#ifndef ACTIVATED_H_
#define ACTIVATED_H_
#include "ability.h"

class Activated : public Ability {
	int cost;
public:
	Activated(std::string description, int cost);
	~Activated() = default;
	virtual void usedOn(std::shared_ptr<Minion> minion) override;
	virtual void usedOn(std::shared_ptr<Player> player) override;
};




#endif /* ACTIVATED_H_ */
>>>>>>> 0e54d17d96ad052dad7e0600b907d2ea4b0089ed
