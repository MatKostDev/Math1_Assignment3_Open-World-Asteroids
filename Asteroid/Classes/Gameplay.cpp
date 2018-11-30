#include "Gameplay.h"

cocos2d::Scene* Gameplay::createScene()
{
	Scene* scene = Gameplay::create();
	return scene;
}

bool Gameplay::init()
{
	if (!Scene::init())
		return false;

	director = Director::getInstance();

	initListeners();
	initSprites();

	scheduleUpdate();

	return true;
}

void Gameplay::initSprites()
{
	//add background
	background = Sprite::create("TestingBackground.png");
	background->setAnchorPoint(Vec2(0.0f, 0.0f));
	this->addChild(background, 0);

	//add ship
	ship = new Ship();
	this->addChild(ship->sprite, 10);
	//set camera to follow ship
	runAction(Follow::create(ship->sprite));

	//shooting ship for testing
	shootingShip = new ShootingShip(Vect2(4500, 4500));
	this->addChild(shootingShip->sprite, 8);
	ShootingShip::shootingShipList.push_back(shootingShip);
}

void Gameplay::initListeners()
{
	//Init the mouse listener
	initMouseListener();

	//Init the keyboard listener
	initKeyboardListener();
}

void Gameplay::initMouseListener()
{
	//Init the mouse listener
	mouseListener = EventListenerMouse::create();

	//On Mouse Down
	mouseListener->onMouseDown = CC_CALLBACK_1(Gameplay::mouseDownCallback, this);

	//On Mouse Up
	mouseListener->onMouseUp = CC_CALLBACK_1(Gameplay::mouseUpCallback, this);

	//On Mouse Move
	mouseListener->onMouseMove = CC_CALLBACK_1(Gameplay::mouseMoveCallback, this);

	//On Mouse Scroll
	mouseListener->onMouseScroll = CC_CALLBACK_1(Gameplay::mouseScrollCallback, this);

	//Add the mouse listener to the dispatcher
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

void Gameplay::initKeyboardListener()
{
	//Create the keyboard listener
	keyboardListener = EventListenerKeyboard::create();

	//Setting up callbacks
	keyboardListener->onKeyPressed = CC_CALLBACK_2(Gameplay::keyDownCallback, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(Gameplay::keyUpCallback, this);

	//Add the keyboard listener to the dispatcher
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

//UPDATE
void Gameplay::update(float dt)
{
	ship->updatePhysics(dt); //update our ship

	updateEnemyShips(dt); //update enemy ships

	updateBullets(dt); //update bullets
}

void Gameplay::updateEnemyShips(float dt)
{
	//update all bullets and check for expired bullets
	for (int i = 0; i < ShootingShip::shootingShipList.size(); i++)
	{
		ShootingShip::shootingShipList[i]->updatePhysics(dt, ship->getPosition());

		if (ShootingShip::shootingShipList[i]->shootTimer > 1.5) //delay between shots (in seconds)
		{
			//shoot bullet and reset timer
			this->addChild(ShootingShip::shootingShipList[i]->shootBullet()->sprite);
			ShootingShip::shootingShipList[i]->shootTimer = 0;
		}
	}
}

void Gameplay::updateBullets(float dt)
{
	//update all bullets
	for (int i = 0; i < FriendlyBullet::friendlyBulletList.size(); i++)
	{
		FriendlyBullet::friendlyBulletList[i]->updatePhysics(dt);
	}
	for (int i = 0; i < EnemyBullet::enemyBulletList.size(); i++)
	{
		EnemyBullet::enemyBulletList[i]->updatePhysics(dt);
	}
}

//--- Callbacks ---//

void Gameplay::mouseDownCallback(Event* event)
{
	////Cast the event as a mouse event
	//EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);

	////Get the position of the mouse button press
	//auto mouseClickPosition = mouseEvent->getLocationInView();
	//mouseClickPosition.y += 540;

	////Get the mouse button from the event handler
	//auto mouseButton = mouseEvent->getMouseButton();

	////Perform different logic depending on which button was pressed
	//if (mouseButton == cocos2d::EventMouse::MouseButton::BUTTON_LEFT)
	//	std::cout << "Left Mouse Button Pressed!" << std::endl;
	//else if (mouseButton == cocos2d::EventMouse::MouseButton::BUTTON_RIGHT)
	//	std::cout << "Right Mouse Button Pressed!" << std::endl;

	//if ((mouseClickPosition - slingshotPosition).length() < 50.0f)
	//{
	//	//Bird grabbed!
	//	birdHeld = true;
	//	std::cout << "Bird Grabbed!!!" << std::endl;
	//}

	//mouseDown = true;
}

void Gameplay::mouseUpCallback(Event* event)
{
	////Cast the event as a mouse event
	//EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);

	////Get the position of the mouse button press
	//auto mouseUpPosition = mouseEvent->getLocation();

	////Init the message to be output in the message box
	//std::stringstream message;

	////Get the mouse button from the event handler
	//auto mouseButton = mouseEvent->getMouseButton();

	////Perform different logic depending on which button was released
	//if (mouseButton == cocos2d::EventMouse::MouseButton::BUTTON_LEFT)
	//	std::cout << "Left Mouse Button Released!" << std::endl;
	//else if (mouseButton == cocos2d::EventMouse::MouseButton::BUTTON_RIGHT)
	//	std::cout << "Right Mouse Button Released!" << std::endl;
	//mouseDown = false;
	//if (birdHeld)
	//{
	//	activeBird->getSprite()->getPhysicsBody()->setDynamic(true);
	//	activeBird->getSprite()->getPhysicsBody()->setVelocity((slingshotPosition - activeBird->getSprite()->getPosition()) * 5.0f);
	//	activeBird->setState(birdState::airborne);
	//	//sceneHandle->runAction(MoveTo::create(1.0f, Vec2(150, 0)));
	//	birdHeld = false;
	//}
}

void Gameplay::mouseMoveCallback(Event* event)
{
	//Cast the event as a mouse event
	EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);

	//Get the position of the mouse from the event handler
	auto mouseEventPos = mouseEvent->getLocationInView();

	//Store the position into the mouse struct
	mousePosition = Vect2(mouseEventPos.x, 540 + mouseEventPos.y);

}

void Gameplay::mouseScrollCallback(Event* event)
{

}

void Gameplay::keyDownCallback(EventKeyboard::KeyCode keyCode, Event* event)
{
	//WASD controls
	if (keyCode == EventKeyboard::KeyCode::KEY_W)
		ship->isMovingForward = true;
	else if (keyCode == EventKeyboard::KeyCode::KEY_S)
		ship->isMovingBackward = true;
	if (keyCode == EventKeyboard::KeyCode::KEY_A)
		ship->isMovingLeft = true;
	else if (keyCode == EventKeyboard::KeyCode::KEY_D)
		ship->isMovingRight = true;

	if (keyCode == EventKeyboard::KeyCode::KEY_Q)
		ship->isRotatingCounterClockwise = true;
	else if (keyCode == EventKeyboard::KeyCode::KEY_E)
		ship->isRotatingClockwise = true;

	if (keyCode == EventKeyboard::KeyCode::KEY_SPACE)
	{
		
	}
}

void Gameplay::keyUpCallback(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_W)
		ship->isMovingForward = false;
	if (keyCode == EventKeyboard::KeyCode::KEY_S)
		ship->isMovingBackward = false;
	if (keyCode == EventKeyboard::KeyCode::KEY_A)
		ship->isMovingLeft = false;
	if (keyCode == EventKeyboard::KeyCode::KEY_D)
		ship->isMovingRight = false;

	if (keyCode == EventKeyboard::KeyCode::KEY_Q)
		ship->isRotatingCounterClockwise = false;
	else if (keyCode == EventKeyboard::KeyCode::KEY_E)
		ship->isRotatingClockwise = false;
}