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
	const int DRAG; //drag applied to the ship every frame if it's moving

	int lives;
	int shieldHealth;
	float invincibilityTimer;

	bool isDead;
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

	FriendlyBullet* shootBullet();
	
	void takeDamage();

	bool isCollidingWith(ShootingShip* enemyShip);
	bool isCollidingWith(MovingShip* enemyShip);
	bool isCollidingWith(Planet* planet);
	bool isCollidingWith(EnemyBullet* bullet);
	void updatePhysics(float dt, Scene* myScene);
};