#ifndef _LOADSCENE_H_
#define _LOADSCENE_H_

#include "cocos2d.h"
USING_NS_CC;
class LoadScene : public CCLayer
{
public:
	static CCScene* createScene();
	virtual bool init();
	void menuCallback(CCObject* pSender);
	void loadingCallBack(CCObject* pSender);
	void turnToHelloScene();

private:
	CCSize size;
	CCLabelTTF *labelLoading; //Loading字样
	CCLabelTTF *labelPercent; //进度条数字
	int numberOfSprites; //需要加载的资源数目
	int numberOfLoadSprites; //已经加载完的资源数目  
	CCProgressTimer *loadProgress; //进度条
	CREATE_FUNC(LoadScene);
};

#endif






