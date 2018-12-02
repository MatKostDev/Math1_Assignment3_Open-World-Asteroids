#include "Ship.h"

//start ship in the middle of the screen
Ship::Ship() : GameObject::GameObject(Vect2(2500, 2500), "Ship.png"), MOVESPEED(400), MAX_VELOCITY(300)
{
	isMovingForward = false;
	isMovingBackward = false;
	isMovingLeft = false;
	isMovingRight = false;

	isRotatingClockwise = false;
	isRotatingCounterClockwise = false;
}

//--MOVEMENT FUNCTIONS--
void Ship::moveForward(float dt)
{
	velocity += Vect2(
		sinf(theta / 180 * M_PI),
		cosf(theta / 180 * M_PI))
		* dt * MOVESPEED;
}
void Ship::moveBackward(float dt)
{
	velocity += Vect2(
		-sinf(theta / 180 * M_PI),
		-cosf(theta / 180 * M_PI))
		* dt * MOVESPEED;
}
void Ship::moveLeft(float dt)
{
	velocity += Vect2(
		-cosf(theta / 180 * M_PI),
		sinf(theta / 180 * M_PI))
		* dt * MOVESPEED;
}
void Ship::moveRight(float dt)
{
	velocity += Vect2(
		cosf(theta / 180 * M_PI),
		-sinf(theta / 180 * M_PI))
		* dt * MOVESPEED;
}

//ship rotation
void Ship::rotateClockwise(float dt)
{
	theta += 200 * dt;
	sprite->runAction(RotateTo::create(0, theta)); //update the sprite's rotation
}
void Ship::rotateCounterClockwise(float dt)
{
	theta -= 200 * dt;
	sprite->runAction(RotateTo::create(0, theta)); //update the sprite's rotation
}

FriendlyBullet* Ship::shootBullet()
{
	FriendlyBullet* newFriendlyBullet = new FriendlyBullet(Vect2(sprite->getPosition()), theta);
	FriendlyBullet::friendlyBulletList.push_back(newFriendlyBullet);
	return newFriendlyBullet;
}

//updating physics properties
void Ship::updatePhysics(float dt)
{
	//call base class update
	GameObject::updatePhysics(dt);

	if (isMovingForward)
		moveForward(dt);
	else if (isMovingBackward)
		moveBackward(dt);
	if (isMovingLeft)
		moveLeft(dt);
	else if (isMovingRight)
		moveRight(dt);

	if (isRotatingClockwise)
		rotateClockwise(dt);
	else if (isRotatingCounterClockwise)
		rotateCounterClockwise(dt);

	//check for max/min velocities
	if (velocity.x > MAX_VELOCITY)
		velocity.x = MAX_VELOCITY;
	else if (velocity.x < MAX_VELOCITY * -1)
		velocity.x = MAX_VELOCITY * -1;

	if (velocity.y > MAX_VELOCITY)
		velocity.y = MAX_VELOCITY;
	else if (velocity.y < MAX_VELOCITY * -1)
		velocity.y = MAX_VELOCITY * -1;

	//update rect of what's on screen
	GameObject::screenRect->setRect(sprite->getPositionX() - 1920/2, sprite->getPositionY() - 1080/2, 1920, 1080);
}
