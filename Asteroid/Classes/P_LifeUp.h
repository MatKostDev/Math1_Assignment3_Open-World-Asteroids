#pragma once
#include "Powerup.h"
class P_LifeUp : public Powerup
{
public:
	P_LifeUp(Vect2 startVelocity, Vect2 position);

	static std::vector<P_LifeUp*> pLifeUpList;

	void performPowerup(Ship* ship);
	void removeObject();
	void updatePhysics(float dt, Ship* ship);
};