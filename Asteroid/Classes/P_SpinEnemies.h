#pragma once
#include "Powerup.h"
class P_SpinEnemies : public Powerup
{
public:
	P_SpinEnemies(Vect2 startVelocity, Vect2 position);

	static std::vector<P_SpinEnemies*> pSpinEnemiesList;

	void performPowerup(Ship* ship);
	void removeObject();
	void updatePhysics(float dt, Ship* ship);
};