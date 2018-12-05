#include "P_Grapple.h"

std::vector<P_Grapple*> P_Grapple::pGrappleList = std::vector<P_Grapple*>();

P_Grapple::P_Grapple(Vect2 startVelocity, Vect2 position) : Powerup(startVelocity, position, "Grapple.png")
{
	velocity = startVelocity;
	pGrappleList.push_back(this);
}

void P_Grapple::performPowerup(Ship * ship)
{
}

void P_Grapple::updatePhysics(float dt, Ship * ship)
{
	Powerup::updatePhysics(dt);

	if (this->isCollidingWith(ship))
	{
		performPowerup(ship);
		destroySprite();
		pGrappleList.erase(
			std::remove(pGrappleList.begin(), pGrappleList.end(), this),
			pGrappleList.end());
	}
}