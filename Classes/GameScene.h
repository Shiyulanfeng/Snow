#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

#include "cocos2d.h"
USING_NS_CC;

class GameScene :public CCScene
{
public:
	static GameScene* create(void);
	GameScene();
	virtual ~GameScene();

protected:
	GameScene(const GameScene&);
	GameScene& operator = (const GameScene&);
};

#endif