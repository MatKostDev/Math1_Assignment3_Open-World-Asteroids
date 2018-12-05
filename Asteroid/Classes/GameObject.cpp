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

//checks for collision on two circular objects
bool GameObject::isCollidingWith(GameObject* otherObject)
{
	if (otherObject != NULL && otherObject->sprite != NULL)
	{
		float dist;
		float sumRadii;

		//take squared values so we don't have to sqrt the distance
		sumRadii = (radius + otherObject->radius) * (radius + otherObject->radius);

		dist = (sprite->getPositionX() - otherObject->sprite->getPositionX()) * (sprite->getPositionX() - otherObject->sprite->getPositionX()) +
			(sprite->getPositionY() - otherObject->sprite->getPositionY()) * (sprite->getPositionY() - otherObject->sprite->getPositionY());

		if (dist < sumRadii)
			return true;
	}

	return false;
}

//updates the object's physics properties
void GameObject::updatePhysics(float dt)
{
	velocity += acceleration * dt; //update velocity
	sprite->setPosition(sprite->getPosition() + Vec2(velocity.x, velocity.y) * dt); //update position

	//check for out of bounds
	//on x
	if (getPosition().x < 0)
		sprite->setPositionX(5000);
	else if (getPosition().x > 5000)
		sprite->setPositionX(0);
	//on y
	if (getPosition().y < 0)
		sprite->setPositionY(5000);
	else if (getPosition().y > 5000)
		sprite->setPositionY(0);
}