#include "P_ReverseControls.h"

std::vector<P_ReverseControls*> P_ReverseControls::pReverseControlsList = std::vector<P_ReverseControls*>();

P_ReverseControls::P_ReverseControls(Vect2 startVelocity, Vect2 position) : Powerup(startVelocity, position, "ReverseControls.png")
{
	velocity = startVelocity;
	pReverseControlsList.push_back(this);
}

void P_ReverseControls::performPowerup(Ship * ship)
{
	ship->reverseControls = !ship->reverseControls;
	//reset controls
	ship->isMovingForward = false;
	ship->isMovingBackward = false;
	ship->isMovingLeft = false;
	ship->isMovingRight = false;
	ship->isRotatingClockwise = false;
	ship->isRotatingCounterClockwise = false;
}

void P_ReverseControls::removeObject()
{
	//remove the object
	destroySprite();
	pReverseControlsList.erase(std::remove(pReverseControlsList.begin(), pReverseControlsList.end(), this), pReverseControlsList.end());
}

void P_ReverseControls::updatePhysics(float dt, Ship* ship)
{
	Powerup::updatePhysics(dt);

	if (this->isCollidingWith(ship))
	{
		performPowerup(ship);
		destroySprite();
		pReverseControlsList.erase(
			std::remove(pReverseControlsList.begin(), pReverseControlsList.end(), this),
			pReverseControlsList.end());
	}
}
