#pragma once
#include "Ship.h"

class BlackHole : public GameObject
{
public:
	BlackHole(Vect2 position);

	const float PULL_SPEED;
	const float RANGE;

	static std::vector<BlackHole*> blackHoleList;

	void updatePhysics(float dt, Ship* ship);
};