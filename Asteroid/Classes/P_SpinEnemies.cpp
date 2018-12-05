#include "P_SpinEnemies.h"

std::vector<P_SpinEnemies*> P_SpinEnemies::pSpinEnemiesList = std::vector<P_SpinEnemies*>();

P_SpinEnemies::P_SpinEnemies(Vect2 startVelocity, Vect2 position) : Powerup(startVelocity, position, "SpinEnemies.png")
{
	pSpinEnemiesList.push_back(this);
}

void P_SpinEnemies::updatePhysics(float dt, Ship* ship)
{
	Powerup::updatePhysics(dt);

	if (this->isCollidingWith(ship))
	{
		performPowerup(ship);
		destroySprite();
		pSpinEnemiesList.erase(
			std::remove(pSpinEnemiesList.begin(), pSpinEnemiesList.end(), this),
			pSpinEnemiesList.end());
	}
}

void P_SpinEnemies::performPowerup(Ship* ship)
{
	//loop through all enemies and set their spin timers
	for (int i = 0; i < ShootingShip::shootingShipList.size(); i++)
		ShootingShip::shootingShipList[i]->spinTimer = 5;

	for (int i = 0; i < MovingShip::movingShipList.size(); i++)
		MovingShip::movingShipList[i]->spinTimer = 5;
}