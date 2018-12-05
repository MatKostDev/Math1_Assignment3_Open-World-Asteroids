#include "Ship.h"

//start ship in the middle of the screen
Ship::Ship() : GameObject::GameObject(Vect2(2500, 2500), "Ship.png"), MOVESPEED(450), MAX_VELOCITY(300), DRAG(1)
{
	isMovingForward = false;
	isMovingBackward = false;
	isMovingLeft = false;
	isMovingRight = false;

	isRotatingClockwise = false;
	isRotatingCounterClockwise = false;

	reverseControls = false;
	isDead = false;
	lives = 3;
	shieldHealth = 4;
	invincibilityTimer = 0;
	numEnergyCubes = 0;
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
	theta += 150 * dt;
	sprite->runAction(RotateTo::create(0, theta)); //update the sprite's rotation
}
void Ship::rotateCounterClockwise(float dt)
{
	theta -= 150 * dt;
	sprite->runAction(RotateTo::create(0, theta)); //update the sprite's rotation
}

FriendlyBullet* Ship::shootBullet()
{
	FriendlyBullet* newFriendlyBullet = new FriendlyBullet(Vect2(sprite->getPosition()), theta);
	FriendlyBullet::friendlyBulletList.push_back(newFriendlyBullet);
	return newFriendlyBullet;
}

void Ship::takeDamage()
{
	if (invincibilityTimer <= 0)
	{
		if (lives > 0) //if there are any lives left
		{
			if (shieldHealth > 1) //if there are any shields left
				shieldHealth--;
			else
			{
				lives--;
				shieldHealth = 4;
				sprite->setPosition(Vec2(2500, 2500));
			}

			invincibilityTimer = 0.99;
		}
		else
			isDead = true;
	}
}

bool Ship::isCollidingWith(ShootingShip* enemyShip)
{
	if (GameObject::isCollidingWith(enemyShip))
	{
		takeDamage();
		enemyShip->removeShip();
		return true;
	}

	return false;
}

bool Ship::isCollidingWith(MovingShip* enemyShip)
{
	if (GameObject::isCollidingWith(enemyShip))
	{
		takeDamage();
		enemyShip->removeShip();
		return true;
	}

	return false;
}

bool Ship::isCollidingWith(Planet* planet)
{
	if (GameObject::isCollidingWith(planet))
	{
		takeDamage();
		return true;
	}

	return false;
}

bool Ship::isCollidingWith(EnemyBullet* bullet)
{
	if (GameObject::isCollidingWith(bullet))
	{
		takeDamage();
		bullet->removeBullet();
		return true;
	}

	return false;
}

//updating physics properties
void Ship::updatePhysics(float dt, Scene* myScene)
{
	//call base class update
	GameObject::updatePhysics(dt);

	//check for collision on shooting ships
	for (int i = 0; i < ShootingShip::shootingShipList.size(); i++)
	{
		if (isCollidingWith(ShootingShip::shootingShipList[i]))
			break;
	}
	//check for collision on moving ships
	for (int i = 0; i < MovingShip::movingShipList.size(); i++)
	{
		if (isCollidingWith(MovingShip::movingShipList[i]))
			break;
	}
	//check for collision on planets
	for (int i = 0; i < Planet::planetList.size(); i++)
	{
		if (isCollidingWith(Planet::planetList[i]))
			break;
	}
	//check for collision on enemy bullets
	for (int i = 0; i < EnemyBullet::enemyBulletList.size(); i++)
	{
		if (isCollidingWith(EnemyBullet::enemyBulletList[i]))
			break;
	}

	if (spinTimer <= 0)
	{
		//check for movement
		if (isMovingForward)
			moveForward(dt);
		else if (isMovingBackward)
			moveBackward(dt);
		if (isMovingLeft)
			moveLeft(dt);
		else if (isMovingRight)
			moveRight(dt);

		//check for rotations
		if (isRotatingClockwise)
			rotateClockwise(dt);
		else if (isRotatingCounterClockwise)
			rotateCounterClockwise(dt);

		//apply drag
		if (velocity.x > 0)
			velocity.x -= DRAG;
		else if (velocity.x < 0)
			velocity.x += DRAG;
		if (velocity.y > 0)
			velocity.y -= DRAG;
		else if (velocity.y < 0)
			velocity.y += DRAG;
	}
	else //spin
	{
		theta += 250 * dt;
		sprite->runAction(RotateTo::create(0, theta)); //update the sprite's rotation
		spinTimer -= dt;
	}

	//check for max/min velocities
	if (velocity.x > MAX_VELOCITY)
		velocity.x = MAX_VELOCITY;
	else if (velocity.x < -MAX_VELOCITY)
		velocity.x = -MAX_VELOCITY;

	if (velocity.y > MAX_VELOCITY)
		velocity.y = MAX_VELOCITY;
	else if (velocity.y < -MAX_VELOCITY)
		velocity.y = -MAX_VELOCITY;

	//update invincibility timer
	if (invincibilityTimer > 0)
		invincibilityTimer -= dt;

	//update rect of what's on screen
	GameObject::screenRect->setRect(sprite->getPositionX() - 1920/2, sprite->getPositionY() - 1080/2, 1920, 1080);
}
