#include "Ship.h"

//start ship in the middle of the screen
Ship::Ship() : GameObject::GameObject(Vec2(5000, 5000), "Ship.png"), MOVESPEED(10)
{
	isMovingForward = false;
	isMovingBackward = false;
	isMovingLeft = false;
	isMovingRight = false;
}

void Ship::moveForward()
{
	getSprite()->setPositionY(getSprite()->getPositionY() + MOVESPEED);
}
void Ship::moveBackward()
{
	getSprite()->setPositionY(getSprite()->getPositionY() - MOVESPEED);
}
void Ship::moveLeft()
{
	getSprite()->setPositionX(getSprite()->getPositionX() - MOVESPEED);
}
void Ship::moveRight()
{
	getSprite()->setPositionX(getSprite()->getPositionX() + MOVESPEED);
}
