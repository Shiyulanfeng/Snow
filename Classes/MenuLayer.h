#ifndef _MENULAYER_H_
#define _MENULAYER_H_

#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameScene.h"
USING_NS_CC;
USING_NS_CC_EXT;

class MenuLayer : public CCLayer
{
public:
	static MenuLayer *create(GameScene *pGameScene);

	virtual ~MenuLayer();

	virtual void onEnter();  

	virtual void onExit();  

	void touchUpInsideAction(CCObject* sender,CCControlEvent ev);

	void createButton();

protected:	

	MenuLayer(GameScene *pGameScene);

private:

	MenuLayer(const MenuLayer&);
	MenuLayer& operator = (const MenuLayer&);
};

#endif