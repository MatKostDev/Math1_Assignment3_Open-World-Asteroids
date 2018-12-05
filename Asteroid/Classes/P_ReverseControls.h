#pragma once
#include "Powerup.h"
class P_ReverseControls : public Powerup
{
public:
	P_ReverseControls(Vect2 startVelocity, Vect2 position);

	static std::vector<P_ReverseControls*> pReverseControlsList;

	void performPowerup(Ship* ship);
	void updatePhysics(float dt, Ship* ship);
};

