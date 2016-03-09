#ifndef _GAMEWIN_H_
#define _GAMEWIN_H_

#include "cocos2d.h"
USING_NS_CC;

class GameWin : public CCLayer
{
public:
	static GameWin* createGameWin();
	virtual bool initGameWin();
	CREATE_FUNC(GameWin);
	void menuBackGameCallback(CCObject* pSender);
	void onEnter();
	void onExit();
};

#endif