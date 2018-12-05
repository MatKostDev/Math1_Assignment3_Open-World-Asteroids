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

	srand(time(NULL)); //seed rng
	director = Director::getInstance();

	initListeners();
	initSprites();

	scheduleUpdate();

	return true;
}

//initializes the user interface
void Gameplay::initUI()
{
	Label* labelLives = Label::create("Lives: " + std::to_string(ship->lives), "fonts/arial.ttf", 50.0f, Size::ZERO, TextHAlignment::LEFT, TextVAlignment::BOTTOM);
	labelLives->setAnchorPoint(Vec2(0.f, 0.f));
	labelLives->setPosition(Vec2(2500, 2500));
	this->addChild(labelLives, 15);
}

void Gameplay::initSprites()
{
	//add background
	background = Sprite::create("TestingBackground.png");
	background->setAnchorPoint(Vec2(0.0f, 0.0f));
	this->addChild(background, 1);

	//add ship
	ship = new Ship();
	this->addChild(ship->sprite, 10);
	//set camera to follow ship
	runAction(Follow::create(ship->sprite));

	////powerups for testing
	//pReverseControls = new P_ReverseControls(Vect2(0, 0), Vec2(2200, 2500));
	//this->addChild(pReverseControls->sprite, 6);
	//pReverseControls = new P_ReverseControls(Vect2(0, 0), Vec2(2100, 2500));
	//this->addChild(pReverseControls->sprite, 6);

	//pSpinEnemies = new P_SpinEnemies(Vect2(0, 0), Vec2(2400, 2500));
	//this->addChild(pSpinEnemies->sprite, 6);

	//pSpinShip = new P_SpinShip(Vect2(0, 0), Vec2(2400, 2800));
	//this->addChild(pSpinShip->sprite, 6);

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
	ship->updatePhysics(dt, this); //update our ship
	if (ship->invincibilityTimer > 0)
		flickerShip(); //flicker ship if it's invincible

	spawnEnemies();     //spawn enemies if needed 
	updateEnemies(dt);  //update enemy ships
	updateBullets(dt);  //update bullets
	updatePowerups(dt); //update powerups
}

void Gameplay::spawnEnemies()
{
	//spawns all enemies to keep a certain amount of each in the map

	//shooting ships
	if (ShootingShip::shootingShipList.size() < 3)
	{
		shootingShip = new ShootingShip(Vect2(myRand::getRandNum(4600, 200), myRand::getRandNum(4600, 200)));
		this->addChild(shootingShip->sprite, 8);
	}
	//moving ships
	if (MovingShip::movingShipList.size() < 1)
	{
		movingShip = new MovingShip(Vect2(myRand::getRandNum(4600, 200), myRand::getRandNum(4600, 200)));
		this->addChild(movingShip->sprite, 8);
	}
	//planets
	if (Planet::planetList.size() < 2)
	{
		planet = new Planet(Vect2(myRand::getRandNum(4600, 200), myRand::getRandNum(4600, 200)));
		this->addChild(planet->sprite, 8);
	}
	//blackholes
	if (BlackHole::blackHoleList.size() < 2)
	{
		blackHole = new BlackHole(Vect2(myRand::getRandNum(4600, 200), myRand::getRandNum(4600, 200)));
		this->addChild(blackHole->sprite, 8);
	}
	//small asteroids
	if (SmallAsteroid::smallAsteroidList.size() < 3)
	{
		smallAsteroid = new SmallAsteroid(Vect2(0, 0), Vect2(myRand::getRandNum(150, 80, true), myRand::getRandNum(150, 80, true))); //velocity is random for x and y)
		if (rand() % 2)
			smallAsteroid->sprite->setPosition(0, rand() % 5000);
		else
			smallAsteroid->sprite->setPosition(rand() % 5000, 0);
		this->addChild(smallAsteroid->sprite, 8);
	}
	//large asteroids
	if (LargeAsteroid::largeAsteroidList.size() < 2)
	{
		largeAsteroid = new LargeAsteroid(Vect2(0, 0), Vect2(myRand::getRandNum(120, 80, true), myRand::getRandNum(120, 80, true))); //velocity is random for x and y)
		if (rand() % 2)
			largeAsteroid->sprite->setPosition(0, rand() % 5000);
		else
			largeAsteroid->sprite->setPosition(rand() % 5000, 0);
		this->addChild(largeAsteroid->sprite, 8);
	}
}

void Gameplay::updateEnemies(float dt)
{
	//update all shooting ships
	for (int i = 0; i < ShootingShip::shootingShipList.size(); i++)
	{
		ShootingShip::shootingShipList[i]->updatePhysics(dt, ship->getPosition());

		if (ShootingShip::shootingShipList[i]->shootTimer > 1.2) //delay between shots (in seconds)
			this->addChild(ShootingShip::shootingShipList[i]->shootBullet()->sprite, 5); //shoot bullet and reset timer
	}
	//update all moving ships
	for (int i = 0; i < MovingShip::movingShipList.size(); i++)
		MovingShip::movingShipList[i]->updatePhysics(dt, ship->getPosition());

	//update all planets
	for (int i = 0; i < Planet::planetList.size(); i++)
	{
		Planet::planetList[i]->updatePhysics(dt, ship->getPosition());
		if (Planet::planetList[i]->shootTimer > 2) //delay between shots (in seconds)
			this->addChild(Planet::planetList[i]->shootBullet()->sprite, 5); //shoot bullet and reset timer
	}

	//update all blackholes
	for (int i = 0; i < BlackHole::blackHoleList.size(); i++)
		BlackHole::blackHoleList[i]->updatePhysics(dt, ship);

	//update all small asteroids
	for (int i = 0; i < SmallAsteroid::smallAsteroidList.size(); i++)
		SmallAsteroid::smallAsteroidList[i]->updatePhysics(dt, ship);

	//update all large asteroids
	for (int i = 0; i < LargeAsteroid::largeAsteroidList.size(); i++)
		LargeAsteroid::largeAsteroidList[i]->updatePhysics(dt, ship, this);
}

void Gameplay::updateBullets(float dt)
{
	//update all bullets
	for (int i = 0; i < FriendlyBullet::friendlyBulletList.size(); i++)
		FriendlyBullet::friendlyBulletList[i]->updatePhysics(dt);
	
	for (int i = 0; i < EnemyBullet::enemyBulletList.size(); i++)
		EnemyBullet::enemyBulletList[i]->updatePhysics(dt);
}

void Gameplay::updatePowerups(float dt)
{
	//update all powerups
	for (int i = 0; i < P_Grapple::pGrappleList.size(); i++)
		P_Grapple::pGrappleList[i]->updatePhysics(dt, ship);

	for (int i = 0; i < P_LifeUp::pLifeUpList.size(); i++)
		P_LifeUp::pLifeUpList[i]->updatePhysics(dt, ship);

	for (int i = 0; i < P_ReverseControls::pReverseControlsList.size(); i++)
		P_ReverseControls::pReverseControlsList[i]->updatePhysics(dt, ship);

	for (int i = 0; i < P_ShieldUp::pShieldUpList.size(); i++)
		P_ShieldUp::pShieldUpList[i]->updatePhysics(dt, ship);

	for (int i = 0; i < P_SpinEnemies::pSpinEnemiesList.size(); i++)
		P_SpinEnemies::pSpinEnemiesList[i]->updatePhysics(dt, ship);

	for (int i = 0; i < P_SpinShip::pSpinShipList.size(); i++)
		P_SpinShip::pSpinShipList[i]->updatePhysics(dt, ship);
}

//flickers ship's sprite every 1/10th of a second if it's invincible
void Gameplay::flickerShip()
{
	if (((int)(ship->invincibilityTimer * 10)) % 2 == 1)
		ship->sprite->setZOrder(0); //flicker the ship (hide it behind background)
	else
		ship->sprite->setZOrder(10); //show the ship again
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

	if (!ship->reverseControls)
	{
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
	}
	else //reverse controls
	{
		if (keyCode == EventKeyboard::KeyCode::KEY_W)
			ship->isMovingBackward = true;
		else if (keyCode == EventKeyboard::KeyCode::KEY_S)
			ship->isMovingForward = true;
		if (keyCode == EventKeyboard::KeyCode::KEY_A)
			ship->isMovingRight = true;
		else if (keyCode == EventKeyboard::KeyCode::KEY_D)
			ship->isMovingLeft = true;

		if (keyCode == EventKeyboard::KeyCode::KEY_Q)
			ship->isRotatingClockwise = true;
		else if (keyCode == EventKeyboard::KeyCode::KEY_E)
			ship->isRotatingCounterClockwise = true;
	}

	if (keyCode == EventKeyboard::KeyCode::KEY_SPACE)
		this->addChild(ship->shootBullet()->sprite, 5); //shoot bullet

	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
	{

	}
}

void Gameplay::keyUpCallback(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (!ship->reverseControls)
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
		if (keyCode == EventKeyboard::KeyCode::KEY_E)
			ship->isRotatingClockwise = false;
	}
	else //reverse controls
	{
		if (keyCode == EventKeyboard::KeyCode::KEY_W)
			ship->isMovingBackward = false;
		if (keyCode == EventKeyboard::KeyCode::KEY_S)
			ship->isMovingForward = false;
		if (keyCode == EventKeyboard::KeyCode::KEY_A)
			ship->isMovingRight = false;
		if (keyCode == EventKeyboard::KeyCode::KEY_D)
			ship->isMovingLeft = false;

		if (keyCode == EventKeyboard::KeyCode::KEY_Q)
			ship->isRotatingClockwise = false;
		if (keyCode == EventKeyboard::KeyCode::KEY_E)
			ship->isRotatingCounterClockwise = false;
	}
}