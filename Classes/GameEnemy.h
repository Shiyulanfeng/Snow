#ifndef _GAMEENEMY_H_
#define _GAMEENEMY_H_

#include "cocos2d.h"
#include "GameHero.h"
USING_NS_CC;

class GameEnemy : public Person
{
public:
	static GameEnemy* createEnemy();
	virtual bool initEnemy();
	CREATE_FUNC(GameEnemy);
};

#endif