#pragma once
#include "Bullet.h"
#include "ShootingShip.h"
#include "MovingShip.h"
#include "Planet.h"
#include "Boss.h"

class FriendlyBullet : public Bullet
{
public:
	FriendlyBullet(Vect2 position, float theta);
	static std::vector<FriendlyBullet*> friendlyBulletList;

	void removeBullet();
	bool isCollidingWith(ShootingShip* enemyShip);
	bool isCollidingWith(MovingShip* enemyShip);
	bool isCollidingWith(Planet* planet);
	bool isCollidingWith(Boss* boss);
	void updatePhysics(float dt, Boss* boss);
};