#include "GameLost.h"
#include "MainScene.h"
#include "Defines.h"

GameLost* GameLost::createGameLost()
{
	GameLost* pGameLost = new GameLost();
	if (pGameLost && pGameLost->init())
	{
		pGameLost->initGameLost();
		pGameLost->autorelease();
		return pGameLost;
	}
	else
	{
		CC_SAFE_DELETE(pGameLost);
		return nullptr;
	}
}

bool GameLost::initGameLost()
{
	if (!CCLayer::init())
	{
		return false;
	}

	CCLayerColor* layerColor = CCLayerColor::create(ccc4(150,150,255,255));
	layerColor->setAnchorPoint(ccp(0,0));
	layerColor->setPosition(ccp(0,0));
	MainScene::getMainScene()->addChild(layerColor,10);

	CCLabelTTF* pWinLabel = CCLabelTTF::create("Game Lost", "Arial", 80);
	pWinLabel->setPosition(ccp(SCREEN.width/2,SCREEN.height/2 + 40));
	pWinLabel->setColor(ccc3(255,100,0));
	MainScene::getMainScene()->addChild(pWinLabel,10);

	CCMenuItemFont* pBackGame = CCMenuItemFont::create("Again",this,menu_selector(GameLost::menuBackGameCallback));
	pBackGame->setColor(ccc3(255,0,0));

	CCMenu* menu = CCMenu::create(pBackGame,NULL);
	menu->alignItemsHorizontallyWithPadding(80);
	menu->setPosition(ccp(SCREEN.width/2, SCREEN.height/2 - 40));
	MainScene::getMainScene()->addChild(menu, 100);

	return true;
}

void GameLost::menuBackGameCallback(CCObject* pSender)
{
	MainScene::getMainScene()->removeChildByTag(100);
	MainScene::getMainScene()->removeFromParent();
	CCDirector::sharedDirector()->replaceScene(MainScene::createScene());
	CCDirector::sharedDirector()->resume();
}


