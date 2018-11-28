#include "GameObject.h"

GameObject::GameObject(Vec2 position, std::string spriteFilePath)
{
	sprite = Sprite::create(spriteFilePath);
	sprite->setPosition(position);
	
	radius = sprite->getBoundingBox().size.width / 2;
}

GameObject::~GameObject()
{
	sprite = NULL; //delete sprite
}

Sprite * GameObject::getSprite()
{
	return sprite;
}

float GameObject::getRadius()
{
	return radius;
}
