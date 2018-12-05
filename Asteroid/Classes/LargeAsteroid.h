#pragma once
#include "GameObject.h"
#include "SmallAsteroid.h"

class LargeAsteroid : public GameObject
{
public:
	LargeAsteroid(Vect2 position, Vect2 startVelocity);

	static std::vector<LargeAsteroid*> largeAsteroidList;

	bool isCollidingWith(Ship* ship, Scene* myScene);
	bool isCollidingWith(FriendlyBullet* bullet, Scene* myScene);
	void updatePhysics(float dt, Ship* ship, Scene* myScene);
	void removeAsteroid(Scene* myScene, bool spawnSmallAsteroids = true);
};