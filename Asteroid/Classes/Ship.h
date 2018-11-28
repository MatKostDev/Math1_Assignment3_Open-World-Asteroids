#pragma once
#include "GameObject.h"
#include "cocos2d.h"
using namespace cocos2d;

class Ship : public GameObject
{
public:
	Ship();

	const int MOVESPEED;

	bool isMovingForward;
	bool isMovingBackward;
	bool isMovingLeft;
	bool isMovingRight;

	void moveForward();
	void moveBackward();
	void moveLeft();
	void moveRight();
};