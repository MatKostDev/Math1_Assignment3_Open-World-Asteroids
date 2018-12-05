#pragma once
#include "GameObject.h"
#include "EnemyBullet.h"

class ShootingShip : public GameObject
{
public:
	ShootingShip(Vect2 position);

	int health;
	float shootTimer;
	float spinTimer;
	static std::vector<ShootingShip*> shootingShipList;

	void takeDamage();
	void removeShip();
	EnemyBullet* shootBullet();
	void updatePhysics(float dt, Vect2 shipPosition);
};