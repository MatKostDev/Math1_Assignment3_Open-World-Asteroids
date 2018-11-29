#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class GameObject
{
public:
	GameObject(Vec2 position, std::string spriteFilePath);
	virtual ~GameObject();
	void setVelocity(float newX, float newY);
	void setAcceleration(float newX, float newY);

	Vec2 getPosition();

	void updatePhysics(float dt);

	float radius;
	float theta;
	Vec2 velocity;
	Vec2 acceleration;

	Sprite* sprite;
};