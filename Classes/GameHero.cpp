#include "GameHero.h"
#include "MainScene.h"

Person::Person( void )
{
	_idleAction = NULL;
	_attackAction = NULL;
	_jumpAction = NULL;
	_walkAction = NULL;
	m_fYSpeed = 0;
	m_fXSpeed = 0;
	m_bFaceToRight = true;
}

Person::~Person( void )
{

}

float Person::isCollisionFloor( bool bTouch,float fOldSpeed ,float fAccelerate )
{
	float fSpeedNew=0;
	if (!bTouch)
	{
		fSpeedNew = fOldSpeed - fAccelerate;
		setPosition(getPosition() + CCPoint(0,fOldSpeed));
	}

	return fSpeedNew;
}

//float GameEnemy::isCollisionFloor( bool bTouch,float fOldSpeed,float accelerate )
//{
//	Person::isCollisionFloor( bTouch,fOldSpeed,accelerate ) ;
//	if (!bTouch)
//	{
//		return -5;
//	}else{
//		return 0;
//	}
//}

Person* Person::createPerson()
{
	Person *ret = new Person();
	if (ret && ret->init())
	{
		ret->autorelease();
		return ret;
	}
	else
	{
		CC_SAFE_DELETE(ret);
		return nullptr;
	}
}

bool Person::init()
{

	return true;
}

void Person::idle()
{
	if (_actionState != kActionStateIdle)
	{
		this->stopAllActions();
		this->runAction(_idleAction);
		_actionState = kActionStateIdle;
	}
}

void Person::attack()
{
	if (_actionState == kActionStateIdle || _actionState == kActionStateAttack || _actionState == kActionStateWalk)
	{
		this->stopAllActions();
		this->runAction(_attackAction);
		_actionState = kActionStateAttack;
	}
}

void Person::jump()
{
	if (_actionState == kActionStateIdle || _actionState == kActionStateWalk || _actionState == kActionStateAttack)
	{
		this->stopAllActions();
		this->runAction(_jumpAction);
		_actionState = kActionStateJump;
	}
}

void Person::walk()
{
	if (_actionState != kActionStateJump)
	{
		this->stopAllActions();
		this->runAction(_walkAction);
		_actionState = kActionStateWalk;
	}
}

GameHero* GameHero::createHero()
{
	GameHero *ret = new GameHero();
	if (ret && ret->init())
	{
		ret->initWithSpriteFrameName("idle.png");
		ret->initHero();
		ret->autorelease();
		return ret;
	}
	else
	{
		CC_SAFE_DELETE(ret);
		return nullptr;
	}
}

bool GameHero::initHero()
{
	int i;

	//idle
	CCArray* idleFrames = CCArray::createWithCapacity(1);
	
	idleFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("idle.png")->getCString()));
	CCAnimation* idleAnimation = CCAnimation::createWithSpriteFrames(idleFrames, 1.0f);
	this->setIdleAction(CCRepeatForever::create((CCAnimate::create(idleAnimation))));


	//jump
	CCArray* jumpFrames = CCArray::createWithCapacity(6);
	for(i = 1; i < 7; i++)
	{
		jumpFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("jump%d.png",i)->getCString()));
	}  
	CCAnimation* jumpAnimation = CCAnimation::createWithSpriteFrames(jumpFrames, 0.08f);
	this->setJumpAction(CCSequence::create(CCAnimate::create(jumpAnimation), CCCallFunc::create(this, callfunc_selector(GameHero::idle)), NULL));

	//attack
	CCArray* attackFrames = CCArray::createWithCapacity(2);
	for(i = 1; i < 3; i++)
	{
		attackFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("attack%d.png",i)->getCString()));
	}  
	CCAnimation* attackAnimation = CCAnimation::createWithSpriteFrames(attackFrames, 0.1f);
	this->setAttackAction(CCSequence::create(CCAnimate::create(attackAnimation), CCCallFunc::create(this, callfunc_selector(GameHero::idle)), NULL));

	//walk 
	CCArray* walkFrames = CCArray::createWithCapacity(8); 
	for(i = 1; i < 9; i++)
	{
		walkFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("walk%d.png",i)->getCString()));
	}  
	CCAnimation* walkAnimation = CCAnimation::createWithSpriteFrames(walkFrames, 0.08f);
	//this->setWalkAction(CCSequence::create(CCAnimate::create(walkAnimation), CCCallFunc::create(this, callfunc_selector(GameHero::idle)), NULL));
	this->setWalkAction(CCRepeatForever::create(CCAnimate::create(walkAnimation)));
	return true;
}

void GameHero::walkAction( bool bWalk )
{
	if (!bWalk)
	{
		CCDirector::sharedDirector()->getActionManager()->pauseTarget(this);
	}else{
		CCDirector::sharedDirector()->getActionManager()->resumeTarget(this);
	}
}

GameEnemy* GameEnemy::createEnemy()
{
	GameEnemy *ret = new GameEnemy();
	if (ret && ret->init())
	{
		ret->initEnemy();
		ret->autorelease();
		return ret;
	}
	else
	{
		CC_SAFE_DELETE(ret);
		return nullptr;
	}
}

bool GameEnemy::initEnemy()
{
	m_fFindPathTime = 0.0f;
	m_bIsHit = false;
	m_bIsEnemyMove = true;
	m_bIsEnemyJump = false;

	CCTMXTiledMap* pTiledMap = MainScene::getMainScene()->getTiledMap();
	_floor = pTiledMap->layerNamed("floor");

	m_arrGameEnemy = MainScene::getMainScene()->getArrayEnemy();

	CCSpriteBatchNode* pBatchNode = CCSpriteBatchNode::create("enemy.png");
 	CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
 	cache->addSpriteFramesWithFile("enemy.plist");  
 	this->initWithSpriteFrameName("enemy1.png");

 	CCArray* animFrame = CCArray::createWithCapacity(4);
 	for(int i = 1; i < 5; i++)
 	{
		animFrame->addObject(cache->spriteFrameByName(CCString::createWithFormat("enemy%d.png",i)->getCString()));
 	}  
 	CCAnimation* animations = CCAnimation::createWithSpriteFrames(animFrame, 0.1f);
 	CCAction *pAction = CCRepeatForever::create(CCAnimate::create(animations));
 	this->runAction(pAction);

	this->scheduleUpdate();
	return true;
}

void GameEnemy::update(float delta)
{
	if (this->getEnemyState() == kActionStateAttack)
	{
		this->scheduleOnce(schedule_selector(GameEnemy::EnemyWake),5.f);
	}

	m_fFindPathTime += delta;
	float randNum = myRand_0_1()*2+2;
	if( m_fFindPathTime > randNum )
	{ 
		m_fFindPathTime = 0.0f;
		decidePath();
	}

	if (m_bIsEnemyJump && this->getEnemyState() == kActionStateWalk)
	{
		if (_floor->tileGIDAt(ccp(EnemyGrid_X,29-EnemyGrid_Y-4)))
		{
			this->setYSpeed(20);
			m_bIsEnemyJump = false;
			m_bIsEnemyMove = false;
		}
		else
		{
			m_bIsEnemyMove = true;
			m_bIsEnemyJump = false;
		}
	}

	if (!_floor->tileGIDAt(ccp(EnemyGrid_X,29-EnemyGrid_Y)) && this->getYSpeed() == 0 /*&&*/
		/*_floor->tileGIDAt(ccp(EnemyGrid_X,28-EnemyGrid_Y))*/
		)
	{
		m_bIsEnemyMove = true;
	}

	if (m_bIsEnemyMove)
	{
		if (this->getEnemyState() == kActionStateWalk && this->getFaceRight() == true)
		{
			this->setFlipX(true);
			this->setPositionX(this->getPositionX()+EnemyMoveAmount);
			if (m_fFindPathTime>1.5)
			{
				if (_floor->tileGIDAt(ccp(EnemyGrid_X,30-EnemyGrid_Y))
					&& !_floor->tileGIDAt(ccp(EnemyGrid_X+1,30-EnemyGrid_Y))
					)
				{
					this->setFaceRight(false);
				}
			}
 			
		}
		else if (this->getEnemyState() == kActionStateWalk && this->getFaceRight () == false)
		{
			this->setFlipX(false);
			this->setPositionX(this->getPositionX()-EnemyMoveAmount);
			if (m_fFindPathTime>0 && m_fFindPathTime<1.5)
			{
				if (_floor->tileGIDAt(ccp(EnemyGrid_X,30-EnemyGrid_Y))
					&& !_floor->tileGIDAt(ccp(EnemyGrid_X-1,30-EnemyGrid_Y))
					)
				{
					this->setFaceRight(true);
				}
			}
			
		}
	}
	
	if (this->getPositionX()>=RIGHTRANGE)
	{
		this->setFaceRight(false);
	}
	else if (this->getPositionX()<=LEFTRANGE)
	{
		this->setFaceRight(true);
	}
	
	for (unsigned int i=1;i<m_arrGameEnemy->count();++i)
	{
		Person* pTemp = (Person*)m_arrGameEnemy->objectAtIndex(i);
		if (this->getTag()== i || !this->getYSpeed() == 0)
			continue;
		if (this->getEnemyState() == kActionStateWalk)
		{
			COLLISIONAREA(this,pTemp)

			if (rect_HeroForCrash.intersectsRect(rect_EnemyForCrash))
			{
				if (this->getPositionX()<pTemp->getPositionX())
				{
					this->setFaceRight(false);
					pTemp->setFaceRight(true);
				}
			}

		}
	}
}

void GameEnemy::decidePath()
{
	CCArray* pTempArray = MainScene::getMainScene()->getArrayEnemy();
	Person* _hero = (Person*)pTempArray->objectAtIndex(0);
	float fHeroX = _hero->getPositionX();
	float fHeroY = _hero->getPositionY();
	float fEnemyX = this->getPositionX();
	float fEnemyY = this->getPositionY();

	if ( fEnemyX < fHeroX )
	{
		if (fEnemyY < fHeroY)  //左下
		{
			m_bIsEnemyJump = true;
		}
		else   //左上
		{
			this->setFaceRight(true);
			m_bIsEnemyMove = true;
		}
	}
	else
	{
		if (fEnemyY < fHeroY)   //右下
		{
			m_bIsEnemyJump = true;
		}
		else   //右上
		{
			this->setFaceRight(false);
			m_bIsEnemyMove = true;
		}
	}

}

void GameEnemy::EnemyWake(float dt)
{
	if (this->getEnemyState() == kActionStatePush)
	{
		return;
	}
	this->removeAllChildren();
	this->getActionManager()->resumeTarget(this);
	this->setEnemyState(kActionStateWalk);
}

GameEnemy::GameEnemy()
{
	_actionState = kActionStateWalk;
}

GameEnemy::~GameEnemy()
{

}

float GameEnemy::myRand_0_1()
{
	cc_timeval psv;  
	CCTime::gettimeofdayCocos2d( &psv, NULL );    // 获取本地时间
	//根据时间产生随机种子
	unsigned int tsrans = psv.tv_sec * 1000 + psv.tv_usec / 1000; 
	srand(tsrans);    //设定随机数种子
	return CCRANDOM_0_1();
}






