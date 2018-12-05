#pragma once
#include "cocos2d.h"
#include "Ship.h"
#include "EnemyBullet.h"
#include "FriendlyBullet.h"
#include "ShootingShip.h"
#include "MovingShip.h"
#include "Planet.h"
#include "BlackHole.h"
#include "P_Grapple.h"
#include "P_LifeUp.h"
#include "P_ReverseControls.h"
#include "P_ShieldUp.h"
#include "P_SpinEnemies.h"
#include "P_SpinShip.h"
#include "LargeAsteroid.h"
#include "EnergyCube.h"
#include "Boss.h"

using namespace cocos2d;

class Gameplay : public cocos2d::Scene
{
public:
	CREATE_FUNC(Gameplay);
	static Scene* createScene();

	virtual bool init();
	void initUI();
	void initSprites();
	void initListeners();
	void initMouseListener();
	void initKeyboardListener();

	void update(float dt);
	void spawnEnemies();
	void spawnPowerups();
	void updateEnemies(float dt);
	void updateBullets(float dt);
	void updatePowerups(float dt);
	void spawnBoss();
	void removeAllObjects();

	void flickerShip();

	//Callbacks
	void mouseDownCallback(Event* event);
	void mouseUpCallback(Event* event);
	void mouseMoveCallback(Event* event);
	void mouseScrollCallback(Event* event);
	void keyDownCallback(EventKeyboard::KeyCode keycode, Event* event);
	void keyUpCallback(EventKeyboard::KeyCode keycode, Event* event);

private:
	Director* director;

	EventListenerMouse* mouseListener;
	EventListenerKeyboard* keyboardListener;
	Vect2 mousePosition;

	Sprite* background;
	Ship* ship;

	//entities
	ShootingShip* shootingShip;
	MovingShip* movingShip;
	Planet* planet;
	BlackHole* blackHole;
	SmallAsteroid* smallAsteroid;
	LargeAsteroid* largeAsteroid;

	//P_Grapple* pGrapple;
	//P_LifeUp* pLifeUp;
	//P_ShieldUp* pShieldUp;
	P_ReverseControls* pReverseControls;
	P_SpinEnemies* pSpinEnemies;
	P_SpinShip* pSpinShip;

	Boss* boss;
};