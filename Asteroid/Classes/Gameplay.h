#pragma once
#include "cocos2d.h"
#include "Ship.h"
#include "EnemyBullet.h"
#include "FriendlyBullet.h"
#include "ShootingShip.h"
#include "MovingShip.h"
#include "Planet.h"

using namespace cocos2d;

class Gameplay : public cocos2d::Scene
{
public:
	CREATE_FUNC(Gameplay);
	static Scene* createScene();

	virtual bool init();
	void initSprites();
	void initListeners();
	void initMouseListener();
	void initKeyboardListener();
	void update(float dt);
	void updateEnemies(float dt);
	void updateBullets(float dt);

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

	ShootingShip* shootingShip;
	MovingShip* movingShip;
	Planet* planet;
};