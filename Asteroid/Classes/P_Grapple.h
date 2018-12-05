#pragma once
#include "Powerup.h"
class P_Grapple : public Powerup
{
public:
	P_Grapple(Vect2 startVelocity, Vect2 position);

	static std::vector<P_Grapple*> pGrappleList;

	void performPowerup(Ship* ship);
	void updatePhysics(float dt, Ship* ship);
};