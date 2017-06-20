#include "CardSprite.h"

USING_NS_CC;

//初始化游戏卡片
CardSprite* CardSprite::createCardSprite(int numbers, int wight, int height, float CardSpriteX, float CardSpriteY) 
{
	CardSprite *enemy = new CardSprite();
	if (enemy && enemy->init())
	{
		enemy->autorelease();
		enemy->enemyInit(numbers, wight, height, CardSpriteX, CardSpriteY);

		return enemy;
	}

	CC_SAFE_DELETE(enemy);
	return NULL;
}

bool CardSprite::init()
{
	if (!Sprite::init()){
		return false;
	}
	return true;
}

void CardSprite::setNumber(int num)
{
	number = num;

	if (number >= 0) {
		labTTFCardNumber->setFontSize(40);
	}
	if (number >= 16) {
		labTTFCardNumber->setFontSize(36);
	}
	if (number >= 128) {
		labTTFCardNumber->setFontSize(24);
	}
	if (number >= 1024) {
		labTTFCardNumber->setFontSize(16);
	}

	if (number > 0){
		labTTFCardNumber->setString(__String::createWithFormat("%i",number)->getCString());
	}
	else {
		labTTFCardNumber->setString("");
	}
}

//获取数字
int CardSprite::getNumber() {
	return number;
}

void CardSprite::enemyInit(int numbers, int wight, int height, float CardSpriteX, float CardSpriteY)
{
	number = numbers;

	layerColorBG = cocos2d::LayerColor::create(cocos2d::Color4B(100, 190, 50, 255), wight - 5, height - 5);
	layerColorBG->setPosition(Point(CardSpriteX, CardSpriteY));

	if (number > 0) 
	{
		labTTFCardNumber = cocos2d::LabelTTF::create(__String::createWithFormat("%i", number)->getCString(), "HirakakuProN-W6", 60);
		labTTFCardNumber->setPosition(Point(layerColorBG->getContentSize().width / 2, layerColorBG->getContentSize().height / 2));
		layerColorBG->addChild(labTTFCardNumber);
	}
	else 
	{
		labTTFCardNumber = cocos2d::LabelTTF::create("", "HirakakuProN-W6", 100);
		labTTFCardNumber->setPosition(Point(layerColorBG->getContentSize().width / 2, layerColorBG->getContentSize().height / 2));
		layerColorBG->addChild(labTTFCardNumber);
	}

	this->addChild(layerColorBG);
}
