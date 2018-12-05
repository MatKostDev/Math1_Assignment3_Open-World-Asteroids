#include "P_ShieldUp.h"

std::vector<P_ShieldUp*> P_ShieldUp::pShieldUpList = std::vector<P_ShieldUp*>();

P_ShieldUp::P_ShieldUp(Vect2 startVelocity, Vect2 position) : Powerup(startVelocity, position, "ShieldUp.png")
{
	velocity = startVelocity;
	pShieldUpList.push_back(this);
}

void P_ShieldUp::performPowerup(Ship* ship)
{
	ship->shieldHealth++;
}

void P_ShieldUp::removeObject()
{
	//remove the object
	destroySprite();
	pShieldUpList.erase(std::remove(pShieldUpList.begin(), pShieldUpList.end(), this), pShieldUpList.end());
}

void P_ShieldUp::updatePhysics(float dt, Ship * ship)
{
	Powerup::updatePhysics(dt);

	if (this->isCollidingWith(ship))
	{
		performPowerup(ship);
		destroySprite();
		pShieldUpList.erase(
			std::remove(pShieldUpList.begin(), pShieldUpList.end(), this),
			pShieldUpList.end());
	}
}
