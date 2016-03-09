#ifndef _MAINSCENE_H_
#define _MAINSCENE_H_

#include "cocos2d.h"
#include "GameHero.h"
#include "GameBullet.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class MainScene : public CCLayer
{
public:
	static CCScene* createScene();
	virtual bool init();  
	CREATE_FUNC(MainScene);

	virtual void onEnter();
	virtual void onExit();  

	void HeroShow(float dt);
	void initEnemy();
	void createControlFont();
	
	void update(float dt);
	void MotionDetection();
	void PersonCollision(int iPersonTag);
	void EnemyStatusAction();

	CCArray* getArrayEnemy();
	static MainScene* getMainScene();
	GameHero* getPlayer();
	CCTMXTiledMap* getTiledMap();
	void getLostGame();
	void getWinGame();
	void toJump(CCObject* sender);
	void toBullet(CCObject* sender);
	float myRand_0_1();

	CCArray* m_arrEnemy;
	
	CCTMXTiledMap* _tiledMap;
	CCTMXLayer* _floor;
	
	CCSize winSize;
	GameHero* hero;
	
	bool isJumping;
	float accelerate;

	//ҡ��ʵ�ֲ���
	/////////////////////////////////////////////////////////////////////////////////////////
	virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);  
	virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);  
	virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);  

private:  
	void Moveing();  
	cocos2d::CCSprite *joystick;  
	//���ĵ�O  
	cocos2d::CCPoint O;  
	//��Բ�뾶  
	float R;  
  
	//�ƶ��ٶȷ���ֵ  
	float speedX;  
	//�Ƿ��ƶ��ı�־  
	bool isMoveing;


	//��ʼ����Ϣ
	float m_fMapMaxHeight;
	int m_iMapCountX;
	int m_iMapCountY;
	float m_fMapCellWidth;
	float m_fMapCellHeight;
	///////////////////////////////////////////////////////////////////////////////////

};

#endif