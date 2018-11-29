#pragma once
#include "cocos2d.h"
#include "Ship.h"
#include "Bullet.h"

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
	Vec2 mousePosition;

	Sprite* background;
	Ship* ship;

	std::vector<Bullet*> bulletList;
};
