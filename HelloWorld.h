#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "CardSprite.h"

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(HelloWorld);

	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual bool onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);

	bool doLeft();
	bool doRight();
	bool doUp();
	bool doDown();

	void autoCreateCardNumber();

	void doCheckGameOver();


private:
	//点击的位置，移动的距离
	int firstX, firstY, endX, endY;
	CardSprite *cardArr[4][4];
	void createCardSprite(cocos2d::Size size);
	int grade;
	cocos2d::LabelTTF *labTTFCardNumber;
};

#endif // __HELLOWORLD_SCENE_H__
