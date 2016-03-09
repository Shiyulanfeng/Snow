#ifndef _GAMELOST_H_
#define _GAMELOST_H_

#include "cocos2d.h"
USING_NS_CC;

class GameLost : public CCLayer
{
public:
	static GameLost* createGameLost();
	virtual bool initGameLost();
	CREATE_FUNC(GameLost);
	void menuBackGameCallback(CCObject* pSender);
};

#endif