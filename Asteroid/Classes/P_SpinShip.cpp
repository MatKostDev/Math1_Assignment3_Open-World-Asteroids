#include "P_SpinShip.h"

std::vector<P_SpinShip*> P_SpinShip::pSpinShipList = std::vector<P_SpinShip*>();

P_SpinShip::P_SpinShip(Vect2 startVelocity, Vect2 position) : Powerup(startVelocity, position, "SpinShip.png")
{
	velocity = startVelocity;
	pSpinShipList.push_back(this);
}

void P_SpinShip::performPowerup(Ship* ship)
{
	ship->spinTimer = 5;
}

void P_SpinShip::removeObject()
{
	//remove the object
	destroySprite();
	pSpinShipList.erase(std::remove(pSpinShipList.begin(), pSpinShipList.end(), this), pSpinShipList.end());
}

void P_SpinShip::updatePhysics(float dt, Ship * ship)
{
	Powerup::updatePhysics(dt);

	if (this->isCollidingWith(ship))
	{
		performPowerup(ship);
		destroySprite();
		pSpinShipList.erase(
			std::remove(pSpinShipList.begin(), pSpinShipList.end(), this),
			pSpinShipList.end());
	}
}
