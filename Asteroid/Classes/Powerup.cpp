#include "Powerup.h"

Powerup::Powerup(Vect2 startVelocity, Vect2 position, std::string spriteFilePath) : GameObject(position, spriteFilePath)
{
	velocity = startVelocity;
}

void Powerup::updatePhysics(float dt)
{
	GameObject::updatePhysics(dt);
}