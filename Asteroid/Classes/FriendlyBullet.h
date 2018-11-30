#pragma once
#include "Bullet.h"

class FriendlyBullet : public Bullet
{
public:
	FriendlyBullet(Vect2 position, float theta);
	static std::vector<FriendlyBullet*> friendlyBulletList;

	void updatePhysics(float dt);
};