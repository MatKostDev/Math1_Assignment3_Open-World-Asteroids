#pragma once
#include "GameObject.h"
class Bullet : public GameObject
{
public:
	Bullet(Vect2 position, float theta);

	const float SPEED;

	float lifetime;

	void updatePhysics(float dt);
};

