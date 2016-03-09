#include "MenuLayer.h"
#include "LoadScene.h"
#include "MainScene.h"
#include "Defines.h"

MenuLayer::MenuLayer(GameScene *pGameScene)	
{
}

MenuLayer::~MenuLayer()
{
}

MenuLayer * MenuLayer::create( GameScene *pGameScene )
{
	MenuLayer *pTempMenuLayer = new MenuLayer(pGameScene); 
	if (pTempMenuLayer && pTempMenuLayer->init()) 
	{ 
		pTempMenuLayer->autorelease(); 
		return pTempMenuLayer; 
	} 
	else 
	{ 
		CC_SAFE_DELETE(pTempMenuLayer);
		return nullptr;
	} 
}

void MenuLayer::onEnter()
{
	CCLayer::onEnter();
	MenuLayer *pLayer = MenuLayer::create(GameScene::create());

	CCSprite* pBgSprite = CCSprite::create("map_bg.png");
	pBgSprite->setPosition(CENTER);
	this->addChild(pBgSprite,0);

	CCSprite* pMedalSprite = CCSprite::create("medal.png");
	pMedalSprite->setPosition(ccp(SCREEN.width/2,SCREEN.height/5*4));
	this->addChild(pMedalSprite,1);

	CCLabelTTF* pTitle = CCLabelTTF::create("SNOW BROS","Marker Felt",80);
	pTitle->setColor(ccc3(0,200,150));
	pTitle->setPosition(ccp(SCREEN.width/2,SCREEN.height/5*4 - 80));   
	this->addChild(pTitle,2);

 	createButton();

}

void MenuLayer::onExit()
{
	CCLayer::onExit();
}

void MenuLayer::touchUpInsideAction(CCObject* sender,CCControlEvent ev)
{
	//CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.2f,LoadScene::createScene()));
	CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.2f,MainScene::createScene()));
}

void MenuLayer::createButton()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCScale9Sprite* ppNormalButton = CCScale9Sprite::create("normal.png");
	CCScale9Sprite* ppHighlightedButton = CCScale9Sprite::create("click.png");

	CCLabelTTF* pButtonTitle = CCLabelTTF::create("Play","Marker Felt",40);
	pButtonTitle->setColor(ccBLUE);

	CCControlButton* control = CCControlButton::create(pButtonTitle,ppNormalButton);
	control->setPosition(CENTER);
	control->setPreferredSize(CCSizeMake(300,50));
	this->addChild(control,2);

	control->setTitleColorForState(ccRED,CCControlStateHighlighted);
	control->setBackgroundSpriteForState(ppHighlightedButton,CCControlStateHighlighted);

	control->addTargetWithActionForControlEvents(this,cccontrol_selector(MenuLayer::touchUpInsideAction),CCControlEventTouchUpInside);
}