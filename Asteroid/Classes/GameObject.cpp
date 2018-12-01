#include "GameObject.h"

Rect* GameObject::screenRect = new Rect();

GameObject::GameObject(Vect2 position, std::string spriteFilePath)
{
	sprite = Sprite::create(spriteFilePath);
	sprite->setPosition(Vec2(position.x, position.y));
	
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

Vect2 GameObject::getPosition()
{
	return Vect2(sprite->getPosition());
}

//removes the sprite from the screen
void GameObject::destroySprite()
{
	sprite->runAction(RemoveSelf::create());
	delete this;
}

//updates the object's physics properties
void GameObject::updatePhysics(float dt)
{
	velocity += acceleration * dt; //update velocity
	sprite->setPosition(sprite->getPosition() + Vec2(velocity.x, velocity.y) * dt); //update position
}