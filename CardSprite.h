#pragma once
#ifndef _2048_CardSprite_
#define _2048_CardSprite_

#include "cocos2d.h"

class CardSprite :public cocos2d::Sprite {
public:
	static CardSprite *createCardSprite(int numbers,int wight,int height,float CardSpriteX,float CardSpriteY);
	//初始化的数字，卡片宽高，xy轴
	virtual bool init();
	CREATE_FUNC(CardSprite);

	void setNumber(int num);

	int getNumber();

private:
	int number;
	void enemyInit(int numbers, int wight, int height, float CardSpriteX, float CardSpriteY);

	cocos2d::LabelTTF *labTTFCardNumber;

	cocos2d::LayerColor *layerColorBG;
};

#endif 
