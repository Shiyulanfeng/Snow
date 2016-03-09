#include "LoadScene.h"
#include "MainScene.h"

CCScene* LoadScene::createScene()
{
	CCScene* scene = CCScene::create(); 
	LoadScene* layer = LoadScene::create(); 
	scene->addChild(layer);
	return scene;
}

//初始化当前的图层
bool LoadScene::init()
{
	if(!CCLayer::init()) //初始化父类
		return false;

	//获取屏幕大小
	size = CCDirector::sharedDirector()->getVisibleSize();
	//size = Director::getInstance()->getWinSize();

	labelLoading = CCLabelTTF::create("Loading...", "Marker Felt", 50);
	labelLoading->setPosition(ccp(size.width/2, size.height/2));
	this->addChild(labelLoading);

	labelPercent = CCLabelTTF::create("0%", "Marker Felt", 50);
	labelPercent->setPosition(ccp(size.width/2, size.height*0.3));
	this->addChild(labelPercent);

	numberOfSprites = 200;
	numberOfLoadSprites = 0;
 
 	CCSprite* pLoaderBg = CCSprite::create("game_loader_bar_bg.png");
 	pLoaderBg->setPosition(ccp(size.width/2, size.height*0.2));
 	this->addChild(pLoaderBg,1);

	//创建一个进度条
 	loadProgress = CCProgressTimer::create(CCSprite::create("game_loader_bar.png"));
 	loadProgress->setBarChangeRate(ccp(1, 0)); //横向移动
 	loadProgress->setType(kCCProgressTimerTypeBar);
 	loadProgress->setMidpoint(ccp(0, 0));
 	loadProgress->setPosition(ccp(size.width/2, size.height*0.2));
 	loadProgress->setPercentage(0.0f);
 	this->addChild(loadProgress, 1);

	//加载资源，由于图片过少，进度条速度过快，这里让其加载图片多一些，总共200张
	for (int i=0; i<200; i++)
	{
		CCTextureCache::sharedTextureCache()->addImageAsync("HelloWorld.png", this,callfuncO_selector(LoadScene::loadingCallBack));
		CCTextureCache::sharedTextureCache()->addImageAsync("CloseNormal.png", this,callfuncO_selector(LoadScene::loadingCallBack));
	}

	return true;
}

void LoadScene::loadingCallBack(CCObject* pSender)
{
	numberOfLoadSprites++;

	char tmp[10];
	float value = ((float)numberOfLoadSprites / numberOfSprites)*100; //已加载的百分比
	sprintf(tmp, "%d%%", (int)(value));
	labelPercent->setString(tmp);

	loadProgress->setPercentage(value);

	//加载完成，切换场景
	if (numberOfLoadSprites == numberOfSprites) {
		turnToHelloScene();
	}
}

void LoadScene::turnToHelloScene()
{
	//读完进度条后跳转到HelloWorld场景
	CCDirector::sharedDirector()->replaceScene(CCTransitionJumpZoom::create(1.f,MainScene::createScene()));
}