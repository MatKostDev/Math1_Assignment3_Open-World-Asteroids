#pragma once
#include "Bullet.h"

class EnemyBullet : public Bullet
{
public:
	EnemyBullet(Vect2 position, float theta);
	static std::vector<EnemyBullet*> enemyBulletList;

	void removeBullet();
	void updatePhysics(float dt);
};