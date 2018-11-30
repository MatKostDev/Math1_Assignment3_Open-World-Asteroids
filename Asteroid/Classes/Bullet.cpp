#include "Bullet.h"



Bullet::Bullet(Vect2 position, float theta) : GameObject(position, "Bullet.png"), SPEED(900)
{
	velocity += Vect2(
		sinf(theta / 180 * M_PI),
		cosf(theta / 180 * M_PI))
		* SPEED;

	lifetime = 1; //lifetime in seconds
}

void Bullet::updatePhysics(float dt)
{
	//call base class update
	GameObject::updatePhysics(dt);

	lifetime -= dt;
}
