#include "Bullet.h"



Bullet::Bullet(Vec2 position, float theta) : GameObject(position, "Bullet.png"), SPEED(800)
{
	velocity += Vec2(
		sinf(theta / 180 * M_PI),
		cosf(theta / 180 * M_PI))
		* SPEED;

	lifetime = 5;
}


Bullet::~Bullet()
{
}

void Bullet::updatePhysics(float dt)
{
	//call base class update
	GameObject::updatePhysics(dt);
}
