#pragma once
#include "Powerup.h"
class P_SpinShip : public Powerup
{
public:
	P_SpinShip(Vect2 startVelocity, Vect2 position);

	static std::vector<P_SpinShip*> pSpinShipList;

	void performPowerup(Ship* ship);
	void updatePhysics(float dt, Ship* ship);
};