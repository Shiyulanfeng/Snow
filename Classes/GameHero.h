#ifndef _GAMEHERO_H_
#define _GAMEHERO_H_
#include "cocos2d.h"
#include "Defines.h"
USING_NS_CC;

class Person : public CCSprite
{
public:
	Person(void);
	~Person(void);

	static Person* createPerson();
	bool init();
	CREATE_FUNC(Person);

	void idle();
	void attack();
	void jump();
	void walk();

	CC_SYNTHESIZE_RETAIN(CCAction*,_idleAction,IdleAction);
	CC_SYNTHESIZE_RETAIN(CCAction*,_attackAction,AttackAction);
	CC_SYNTHESIZE_RETAIN(CCAction*,_jumpAction,JumpAction);
	CC_SYNTHESIZE_RETAIN(CCAction*,_walkAction,WalkAction);

	CC_SYNTHESIZE(float,m_fYSpeed,YSpeed);
	CC_SYNTHESIZE(float,m_fXSpeed,XSpeed);
	CC_SYNTHESIZE(bool,m_bFaceToRight,FaceRight);
	CC_SYNTHESIZE(ActionState,_actionState,EnemyState);

	virtual float isCollisionFloor(bool bTouch,float fOldSpeed,float fAccelerate);

protected:

	int iTag; 
};

class GameHero : public Person
{
public:
	static GameHero* createHero();
	bool initHero();
	void walkAction(bool bWalk);
	CREATE_FUNC(GameHero);
};

class GameEnemy : public Person
{
public:
	GameEnemy();
	~GameEnemy();
	static GameEnemy* createEnemy();
	virtual bool initEnemy();
	CREATE_FUNC(GameEnemy);
	
	//virtual float isCollisionFloor(bool bTouch,float fOldSpeed,float accelerate);

private:
	bool m_bIsHit;
	void update(float delta);
	void EnemyWake(float dt);
	void decidePath();
	float m_fFindPathTime;
	bool m_bIsEnemyMove;
	bool m_bIsEnemyJump;
	CCTMXLayer* _floor;
	CCArray* m_arrGameEnemy;
	float myRand_0_1();
};



#endif