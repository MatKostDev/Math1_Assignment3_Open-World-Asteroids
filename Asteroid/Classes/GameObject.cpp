#include "GameObject.h"

GameObject::GameObject(Vec2 position, std::string spriteFilePath)
{
	sprite = Sprite::create(spriteFilePath);
	sprite->setPosition(position);
	
	setVelocity(0.f, 0.f);
	setAcceleration(0.f, 0.f);
	radius = sprite->getBoundingBox().size.width / 2;
	theta = 0.f;
}

GameObject::~GameObject()
{
	sprite = NULL; //delete sprite
}

void GameObject::setVelocity(float newX, float newY)
{
	velocity.x = newX;
	velocity.y = newY;
}
void GameObject::setAcceleration(float newX, float newY)
{
	acceleration.x = newX;
	acceleration.y = newY;
}

Vec2 GameObject::getPosition()
{
	return sprite->getPosition();
}

//updates the object's physics properties
void GameObject::updatePhysics(float dt)
{
	velocity += acceleration * dt; //update velocity
	sprite->setPosition(sprite->getPosition() + velocity * dt); //update position
}