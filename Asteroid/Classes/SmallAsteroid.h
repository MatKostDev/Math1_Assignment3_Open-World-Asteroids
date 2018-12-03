#pragma once
#include "GameObject.h"
#include "Ship.h"

class SmallAsteroid : public GameObject
{
public:
	SmallAsteroid(Vect2 position, Vect2 startVelocity);

	static std::vector<SmallAsteroid*> smallAsteroidList;

	bool isCollidingWith(Ship* ship);
	bool isCollidingWith(FriendlyBullet* bullet);
	void updatePhysics(float dt, Ship* ship);
	void removeAsteroid();
};