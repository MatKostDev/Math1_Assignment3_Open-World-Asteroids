#pragma once
#include "GameObject.h"
class Bullet : public GameObject
{
public:
	Bullet(Vect2 position, float shipTheta, std::string spriteFilePath);

	float theta;
	float moveSpeed;
	float lifetime;

	void moveBullet(float speed);
	void updatePhysics(float dt);
};