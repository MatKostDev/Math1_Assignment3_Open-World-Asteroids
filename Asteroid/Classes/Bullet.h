#pragma once
#include "GameObject.h"
class Bullet : public GameObject
{
public:
	Bullet(Vec2 position, float theta);
	~Bullet();

	const float SPEED;

	float lifetime;

	void updatePhysics(float dt);
};

