#ifndef _GAMEBULLET_H_
#define _GAMEBULLET_H_

#include "cocos2d.h"
#include "GameHero.h"
#include "MainScene.h"
USING_NS_CC;

class GameBullet : public CCSprite
{
public:
	GameBullet();
	~GameBullet();
	static GameBullet* createBullet(float BulletSpeed);
	virtual bool initBullet(float BulletSpeed);
	CREATE_FUNC(GameBullet);
	void update(float dt);
	void CloseScheduler(float dt);
	void BulletMove();

private:
	float m_fBulletSpeed;
	float m_fySpeed; 
	float accelerate;
	bool isActive;
	CCTMXLayer* tmxLayer;
};

#endif