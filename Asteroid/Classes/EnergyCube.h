#pragma once
#include "GameObject.h"
#include "Ship.h"
class EnergyCube : public GameObject
{
public:
	EnergyCube(Vect2 startVelocity, Vect2 position);

	static std::vector<EnergyCube*> energyCubeList;

	void removeObject();
	void updatePhysics(float dt, Ship* ship);
};