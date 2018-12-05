#pragma once
#include "GameObject.h"
#include "Ship.h"

class Powerup : public GameObject
{
public:
	Powerup(Vect2 startVelocity, Vect2 position, std::string spriteFilePath);

	virtual void performPowerup(Ship* ship) = 0;
	void updatePhysics(float dt);
};