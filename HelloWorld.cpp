#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "CardSprite.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	auto scene = Scene::create();
	auto layer = HelloWorld::create();
	scene->addChild(layer);
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

	grade = 0;
	Size visibleSize = Director::getInstance()->getVisibleSize();
    
	auto labTTFCardNumberName = LabelTTF::create("Grade", "HirakakuProN-W6", 35);
	labTTFCardNumberName->setPosition(Point(visibleSize.width / 3, visibleSize.height - 30));
	addChild(labTTFCardNumberName);

	labTTFCardNumber = LabelTTF::create("0", "HirakakuProN-W6", 35);
	labTTFCardNumber->setPosition(Point(visibleSize.width / 3+100, visibleSize.height - 30));
	addChild(labTTFCardNumber);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	createCardSprite(visibleSize);

	autoCreateCardNumber();
	autoCreateCardNumber();

    return true;
}

void HelloWorld::doCheckGameOver() 
{
	bool isGameOver = true;
	for (int y = 0; y < 4; y++) 
	{
		for (int x = 0; x < 4; x++)
		{
			if (cardArr[x][y]->getNumber() == 0 ||
				(x > 0 && (cardArr[x][y]->getNumber() == cardArr[x - 1][y]->getNumber())) ||
				(x < 3 && (cardArr[x][y]->getNumber() == cardArr[x + 1][y]->getNumber())) ||
				(y > 0 && (cardArr[x][y]->getNumber() == cardArr[x][y - 1]->getNumber())) ||
				(y < 3 && (cardArr[x][y]->getNumber() == cardArr[x][y + 1]->getNumber()))) {
				isGameOver = false;
			}
		}
	}

	if (isGameOver)
	{
		Director::getInstance()->replaceScene(TransitionFade::create(1, HelloWorld::createScene()));
	}
}

void HelloWorld::autoCreateCardNumber()
{
	int i = CCRANDOM_0_1() * 4;
	int j = CCRANDOM_0_1() * 4;

	if (cardArr[i][j]->getNumber() > 0) {
		autoCreateCardNumber();
	}
	else {
		cardArr[i][j]->setNumber(CCRANDOM_0_1() * 10 < 1 ? 4 : 2);
	}
}

void HelloWorld::createCardSprite(cocos2d::Size size)
{
	int lon = (size.width - 270) / 4;
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			CardSprite *card = CardSprite::createCardSprite(0, lon, lon, lon*j + 100, lon*i + 20 + size.height / 6);
			addChild(card);
			cardArr[j][i] = card;
		}
	}
}

bool HelloWorld::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	Point touchP0 = touch->getLocation();

	firstX = touchP0.x;
	firstY = touchP0.y;

	return true;
}
bool HelloWorld::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event) 
{
	Point touchPO = touch->getLocation();

	endX = firstX - touchPO.x;
	endY = firstY - touchPO.y;

	if (abs(endX) > abs(endY))
	{
		if (endX + 5 > 0) {
			if (doLeft()) {
				autoCreateCardNumber();
				doCheckGameOver();
			}
		}
		else {
			if (doRight()) {
				autoCreateCardNumber();
				doCheckGameOver();
			}
		}
	}
	else{
		if (endY + 5 > 0) {
			if (doDown()) {
				autoCreateCardNumber();
				doCheckGameOver();
			}
		}
		else {
			if (doUp()) {
				autoCreateCardNumber();
				doCheckGameOver();
			}
		}
	}

	return true;
}

bool HelloWorld::doLeft()
{
	bool isdo = false;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			for (int x1 = x + 1; x1 < 4; x1++)
			{
				if (cardArr[x1][y]->getNumber() > 0)
				{
					if (cardArr[x][y]->getNumber() <= 0)
					{
						cardArr[x][y]->setNumber(cardArr[x1][y]->getNumber());
						cardArr[x1][y]->setNumber(0);

						x--;
						isdo = true;
					}
					else if(cardArr[x][y]->getNumber() == cardArr[x1][y]->getNumber()){
						cardArr[x][y]->setNumber(cardArr[x][y]->getNumber() * 2);
						cardArr[x1][y]->setNumber(0);

						grade += cardArr[x][y]->getNumber();
						labTTFCardNumber->setString(__String::createWithFormat("%i", grade)->getCString());

						isdo = true;
					}
					break;
				}
			}
		}
	}
	return isdo;
}
bool HelloWorld::doRight()
{
	bool isdo = false;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 3; x >= 0; x--)
		{
			for (int x1 = x - 1; x1 >= 0; x1--)
			{
				if (cardArr[x1][y]->getNumber() > 0)
				{
					if (cardArr[x][y]->getNumber() <= 0)
					{
						cardArr[x][y]->setNumber(cardArr[x1][y]->getNumber());
						cardArr[x1][y]->setNumber(0);

						x++;
						isdo = true;
					}
					else if (cardArr[x][y]->getNumber() == cardArr[x1][y]->getNumber()) {
						cardArr[x][y]->setNumber(cardArr[x][y]->getNumber() * 2);
						cardArr[x1][y]->setNumber(0);

						grade += cardArr[x][y]->getNumber();
						labTTFCardNumber->setString(__String::createWithFormat("%i", grade)->getCString());

						isdo = true;
					}
					break;
				}
			}
		}
	}
	return isdo;
}
bool HelloWorld::doUp()
{
	bool isdo = false;
	for (int x = 0; x < 4; x++)
	{
		for (int y = 3; y >= 0; y--)
		{
			for (int y1 = y - 1; y1 >= 0; y1--)
			{
				if (cardArr[x][y1]->getNumber() > 0)
				{
					if (cardArr[x][y]->getNumber() <= 0)
					{
						cardArr[x][y]->setNumber(cardArr[x][y1]->getNumber());
						cardArr[x][y1]->setNumber(0);

						y++;
						isdo = true;
					}
					else if (cardArr[x][y]->getNumber() == cardArr[x][y1]->getNumber()) {
						cardArr[x][y]->setNumber(cardArr[x][y]->getNumber() * 2);
						cardArr[x][y1]->setNumber(0);

						grade += cardArr[x][y]->getNumber();
						labTTFCardNumber->setString(__String::createWithFormat("%i", grade)->getCString());

						isdo = true;
					}
					break;
				}
			}
		}
	}
	return isdo;
}
bool HelloWorld::doDown()
{
	bool isdo = false;
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			for (int y1 = y + 1; y1 < 4; y1++)
			{
				if (cardArr[x][y1]->getNumber() > 0)
				{
					if (cardArr[x][y]->getNumber() <= 0)
					{
						cardArr[x][y]->setNumber(cardArr[x][y1]->getNumber());
						cardArr[x][y1]->setNumber(0);

						y--;
						isdo = true;
					}
					else if (cardArr[x][y]->getNumber() == cardArr[x][y1]->getNumber()) {
						cardArr[x][y]->setNumber(cardArr[x][y]->getNumber() * 2);
						cardArr[x][y1]->setNumber(0);

						grade += cardArr[x][y]->getNumber();
						labTTFCardNumber->setString(__String::createWithFormat("%i", grade)->getCString());

						isdo = true;
					}
					break;
				}
			}
		}
	}
	return isdo;
}
