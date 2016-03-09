#include "LoadScene.h"
#include "MainScene.h"

CCScene* LoadScene::createScene()
{
	CCScene* scene = CCScene::create(); 
	LoadScene* layer = LoadScene::create(); 
	scene->addChild(layer);
	return scene;
}

//��ʼ����ǰ��ͼ��
bool LoadScene::init()
{
	if(!CCLayer::init()) //��ʼ������
		return false;

	//��ȡ��Ļ��С
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

	//����һ��������
 	loadProgress = CCProgressTimer::create(CCSprite::create("game_loader_bar.png"));
 	loadProgress->setBarChangeRate(ccp(1, 0)); //�����ƶ�
 	loadProgress->setType(kCCProgressTimerTypeBar);
 	loadProgress->setMidpoint(ccp(0, 0));
 	loadProgress->setPosition(ccp(size.width/2, size.height*0.2));
 	loadProgress->setPercentage(0.0f);
 	this->addChild(loadProgress, 1);

	//������Դ������ͼƬ���٣��������ٶȹ��죬�����������ͼƬ��һЩ���ܹ�200��
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
	float value = ((float)numberOfLoadSprites / numberOfSprites)*100; //�Ѽ��صİٷֱ�
	sprintf(tmp, "%d%%", (int)(value));
	labelPercent->setString(tmp);

	loadProgress->setPercentage(value);

	//������ɣ��л�����
	if (numberOfLoadSprites == numberOfSprites) {
		turnToHelloScene();
	}
}

void LoadScene::turnToHelloScene()
{
	//�������������ת��HelloWorld����
	CCDirector::sharedDirector()->replaceScene(CCTransitionJumpZoom::create(1.f,MainScene::createScene()));
}