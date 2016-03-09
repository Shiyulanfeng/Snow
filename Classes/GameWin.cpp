#include "GameWin.h"
#include "MainScene.h"
#include "Defines.h"

GameWin* GameWin::createGameWin()
{ 
	GameWin* pGameWin = new GameWin();
	if (pGameWin && pGameWin->init())
	{
		pGameWin->initGameWin();
		pGameWin->autorelease();
		return pGameWin;
	}
	else
	{
		CC_SAFE_DELETE(pGameWin);
		return nullptr;
	}
}

bool GameWin::initGameWin()
{
	if (!CCLayer::init())
	{
		return false;
	}	

	CCLayerColor* layerColor = CCLayerColor::create(ccc4(150,150,255,255));
	layerColor->setAnchorPoint(ccp(0,0));
	layerColor->setPosition(ccp(0,0));
	MainScene::getMainScene()->addChild(layerColor,10);

	CCLabelTTF* pWinLabel = CCLabelTTF::create("Game Win", "Arial", 80);
	pWinLabel->setPosition(ccp(SCREEN.width/2,SCREEN.height/2 + 40));
	pWinLabel->setColor(ccc3(255,100,0));
	MainScene::getMainScene()->addChild(pWinLabel,11);

	CCMenuItemFont* pBackGame = CCMenuItemFont::create("Again",this,menu_selector(GameWin::menuBackGameCallback));
	pBackGame->setColor(ccc3(255,0,0));
	CCMenu* menu = CCMenu::create(pBackGame,NULL);
	menu->alignItemsHorizontallyWithPadding(50);
	menu->setPosition(ccp(SCREEN.width/2, SCREEN.height/2-40));
	MainScene::getMainScene()->addChild(menu, 100);

// 	CCSpriteBatchNode* batch = CCSpriteBatchNode::create("boxlight.png");
// 	CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
// 	cache->addSpriteFramesWithFile("boxlight.plist");
// 
// 	CCSprite* pSprite = CCSprite::createWithSpriteFrameName("boxlight1.png");
// 	pSprite->setPosition(ccp(winSize.width/2,winSize.height/2));
// 	batch->addChild(pSprite);
// 	addChild(batch); 
// 
// 	CCArray* animFrames = CCArray::createWithCapacity(10);
// 	char str[10] = {0};
// 	for(int i = 1; i < 5; i++)
// 	{
// 		sprintf(str, "boxlight%d.png", i);
// 		CCSpriteFrame* frame = cache->spriteFrameByName(str);
// 		animFrames->addObject(frame);
// 	}  
// 
// 	CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames, 0.1f);
// 	CCAnimate *animate = CCAnimate::create(animation);
// 	CCRepeatForever *repeat = CCRepeatForever::create(animate);
// 	this->runAction(repeat);

	return true;
}

void GameWin::menuBackGameCallback(CCObject* pSender)
{
	MainScene::getMainScene()->removeChildByTag(100);
	MainScene::getMainScene()->removeFromParent();
	CCDirector::sharedDirector()->replaceScene(MainScene::createScene());
	CCDirector::sharedDirector()->resume();
}

void GameWin::onEnter()
{
	CCLayer::onEnter();

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	
}

void GameWin::onExit()
{
	MainScene::getMainScene()->unscheduleUpdate();
	CCLayer::onExit();
}


