#pragma once
#include "cocos2d.h"
#include "Vect2.h"

using namespace cocos2d;

class GameObject
{
public:
	GameObject(Vect2 position, std::string spriteFilePath);
	virtual ~GameObject();

	float radius;
	float theta;
	Vect2 velocity;
	Vect2 acceleration;

	Sprite* sprite;

	void setVelocity(float newX, float newY);
	void setAcceleration(float newX, float newY);

	Vect2 getPosition();
	void destroySprite();

	void updatePhysics(float dt);
};