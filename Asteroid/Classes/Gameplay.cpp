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
	shootingShip = new ShootingShip(Vect2(2700, 2700));
	this->addChild(shootingShip->sprite, 8);

	//moving ship for testing
	movingShip = new MovingShip(Vect2(3000, 3000));
	this->addChild(movingShip->sprite, 8);

	//planet for testing
	planet = new Planet(Vect2(2000, 2000));
	this->addChild(planet->sprite, 8);

	//blackhole for testing
	blackHole = new BlackHole(Vect2(3050, 2050));
	this->addChild(blackHole->sprite, 8);
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

	updateEnemies(dt); //update enemy ships

	updateBullets(dt); //update bullets
}

void Gameplay::updateEnemies(float dt)
{
	//update all shooting ships
	for (int i = 0; i < ShootingShip::shootingShipList.size(); i++)
	{
		ShootingShip::shootingShipList[i]->updatePhysics(dt, ship->getPosition());

		if (ShootingShip::shootingShipList[i]->shootTimer > 1.2) //delay between shots (in seconds)
			this->addChild(ShootingShip::shootingShipList[i]->shootBullet()->sprite); //shoot bullet and reset timer
	}
	//update all moving ships
	for (int i = 0; i < MovingShip::movingShipList.size(); i++)
		MovingShip::movingShipList[i]->updatePhysics(dt, ship->getPosition());

	//update all planets
	for (int i = 0; i < Planet::planetList.size(); i++)
	{
		Planet::planetList[i]->updatePhysics(dt, ship->getPosition());
		if (Planet::planetList[i]->shootTimer > 2) //delay between shots (in seconds)
			this->addChild(Planet::planetList[i]->shootBullet()->sprite); //shoot bullet and reset timer
	}

	//update all blackholes
	for (int i = 0; i < BlackHole::blackHoleList.size(); i++)
		BlackHole::blackHoleList[i]->updatePhysics(dt, ship);
}

void Gameplay::updateBullets(float dt)
{
	//update all bullets
	for (int i = 0; i < FriendlyBullet::friendlyBulletList.size(); i++)
		FriendlyBullet::friendlyBulletList[i]->updatePhysics(dt);
	
	for (int i = 0; i < EnemyBullet::enemyBulletList.size(); i++)
		EnemyBullet::enemyBulletList[i]->updatePhysics(dt);
}

//--- Callbacks ---//

void Gameplay::mouseDownCallback(Event* event)
{
}

void Gameplay::mouseUpCallback(Event* event)
{
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
		this->addChild(ship->shootBullet()->sprite); //shoot bullet
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

//gets a random number
int Gameplay::getRand(int maxNum, int scaleNum, bool canBeNegative)
{
	int randNum = (rand() % maxNum) + scaleNum;

	//number can be a negative
	if (canBeNegative)
	{
		//check randomly for either a 1 or 0 to determine if number should be negative or not
		if (rand() % 2)
			randNum *= -1;
	}

	return randNum;
}