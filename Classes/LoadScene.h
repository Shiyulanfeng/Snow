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
	CCLabelTTF *labelLoading; //Loading����
	CCLabelTTF *labelPercent; //����������
	int numberOfSprites; //��Ҫ���ص���Դ��Ŀ
	int numberOfLoadSprites; //�Ѿ����������Դ��Ŀ  
	CCProgressTimer *loadProgress; //������
	CREATE_FUNC(LoadScene);
};

#endif






