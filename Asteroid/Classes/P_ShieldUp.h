#pragma once
#include "Powerup.h"
class P_ShieldUp :
	public Powerup
{
public:
	P_ShieldUp(Vect2 startVelocity, Vect2 position);

	static std::vector<P_ShieldUp*> pShieldUpList;

	void performPowerup(Ship* ship);
	void removeObject();
	void updatePhysics(float dt, Ship* ship);
};