#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class GameObject
{
public:
	GameObject(Vec2 position, std::string spriteFilePath);
	virtual ~GameObject();
	Sprite* getSprite();
	float getRadius();

private:
	Sprite* sprite;
	float radius;
};