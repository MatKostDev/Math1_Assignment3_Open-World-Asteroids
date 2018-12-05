#include "P_LifeUp.h"

std::vector<P_LifeUp*> P_LifeUp::pLifeUpList = std::vector<P_LifeUp*>();

P_LifeUp::P_LifeUp(Vect2 startVelocity, Vect2 position) : Powerup(startVelocity, position, "LifeUp.png")
{
	velocity = startVelocity;
	pLifeUpList.push_back(this);
}

void P_LifeUp::performPowerup(Ship* ship)
{
	ship->lives++;
}

void P_LifeUp::updatePhysics(float dt, Ship * ship)
{
	Powerup::updatePhysics(dt);

	if (this->isCollidingWith(ship))
	{
		performPowerup(ship);
		destroySprite();
		pLifeUpList.erase(
			std::remove(pLifeUpList.begin(), pLifeUpList.end(), this),
			pLifeUpList.end());
	}
}
