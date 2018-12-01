#include "Bullet.h"

Bullet::Bullet(Vect2 position, float shipTheta, std::string spriteFilePath) : GameObject(position, spriteFilePath)
{
	theta = shipTheta;
}

Bullet::~Bullet()
{
	sprite = NULL;
}

void Bullet::moveBullet(float speed)
{
	velocity = Vect2(
		sinf(theta / 180 * M_PI),
		cosf(theta / 180 * M_PI))
		* moveSpeed;
}

void Bullet::updatePhysics(float dt)
{
	//call base class update
	GameObject::updatePhysics(dt);

	lifetime -= dt;
}

