#pragma once
#include "cocos2d.h"
#include "FriendlyBullet.h"
using namespace cocos2d;

class Ship : public GameObject
{
public:
	Ship();

	const int MOVESPEED;
	const int MAX_VELOCITY;

	bool isMovingForward;
	bool isMovingBackward;
	bool isMovingLeft;
	bool isMovingRight;

	bool isRotatingClockwise;
	bool isRotatingCounterClockwise;

	void moveForward(float dt);
	void moveBackward(float dt);
	void moveLeft(float dt);
	void moveRight(float dt);

	void rotateClockwise(float dt);
	void rotateCounterClockwise(float dt);

	void updatePhysics(float dt);
};