#include "MainScene.h"
#include "GameLost.h"
#include "GameWin.h"
#include "Defines.h"

static MainScene* m_pMainScene = NULL;
CCScene* MainScene::createScene()
{
	CCScene* scene = CCScene::create();
	MainScene* layer = MainScene::create();
	scene->addChild(layer);
	return scene;
}

bool MainScene::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());


	bRet = true;  
	} while (0);
	
	return bRet; 
}

void MainScene::onEnter()
{
	CCLayer::onEnter();
	m_arrEnemy = CCArray::create();
	m_arrEnemy->retain();

	m_pMainScene = this;
	
	accelerate = 0.94f;
	isJumping = false;

	winSize = CCDirector::sharedDirector()->getWinSize();

	CCSprite* pBgSprite = CCSprite::create("main_sceneBt.png");   
	pBgSprite->setPosition(ccp(winSize.width/2,winSize.height/2));
	this->addChild(pBgSprite,0);

	_tiledMap = CCTMXTiledMap::create("floorMap.tmx");
	CCLOG("xxxxxxxxxxxxxxxxxxxx   %f,%f",_tiledMap->getTileSize().width,_tiledMap->getMapSize().height);
	addChild(_tiledMap,1);
	_floor = _tiledMap->layerNamed("floor");

	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("luoli.plist");
	CCSpriteBatchNode *batchNode = CCSpriteBatchNode::create("luoli.png");

	hero = GameHero::createHero();
	hero->setAnchorPoint(ccp(0.5,0.02));
	hero->setTag(0);
	m_arrEnemy->addObject(hero);

	batchNode->addChild(hero, 2);
	hero->setVisible(false);
	hero->setPosition(ccp(250,33));
	this->addChild(batchNode,1,0);
	hero->idle();
//	hero->walkAction(false);

	createControlFont();
	initEnemy();
	
	this->scheduleUpdate();
	scheduleOnce(schedule_selector(MainScene::HeroShow),1.5f);
	

	//创建摇杆下面部分  
	CCSprite *joystick1=CCSprite::create("joystick1.png");  
	//设置透明度，锚点，位置  
	joystick1->setOpacity(191);  
	joystick1->setAnchorPoint(ccp(0,0));  
	joystick1->setPosition(ccp(150,800));  
	//大圆半径  
	R=joystick1->getContentSize().width/2;  
	//中心点  
	O=ccp(215,865);  
	//添加进布景  
	this->addChild(joystick1,1);  

	//创建摇杆上面圆圈部分  
	joystick=CCSprite::create("joystick2.png");  
	//设置位置为摇杆中心点并添加进布景  
	joystick->setPosition(ccp(O.x,O.y));  
	this->addChild(joystick,2);  

	//设置可触摸  
	this->setTouchEnabled(true);  

	//初始化需要的变量  
	isMoveing=false;  
	speedX=0;  
}

void MainScene::HeroShow(float dt)
{
	hero->setVisible(true);
}

void MainScene::update(float dt)
{
	
	//MotionDetection();
	for (unsigned int i =0;i< m_arrEnemy->count();++i)
	{
		PersonCollision(i);		
	}
  	EnemyStatusAction();
	Moveing();
}
	

void MainScene::initEnemy()
{
	for (int j=1;j<6;++j)
	{ 
		GameEnemy* pGameEnemy = GameEnemy::createEnemy();
		pGameEnemy->setAnchorPoint(ccp(0.5,0));
		this->addChild(pGameEnemy,1);
		pGameEnemy->setTag(j);
		m_arrEnemy->addObject(pGameEnemy);

// 		float randX = (myRand_0_1()*6 + 2)*64;
// 		float randY = (myRand_0_1()*5 + 5)*96;
// 		pGameEnemy->setPosition(ccp(randX,randY));	
		switch (j)
		{
		case 1:
		{
		pGameEnemy->setPosition(ccp(120,900));
		}
		break;
		case 2:
		{
		pGameEnemy->setPosition(ccp(544,900));
		}
		break;
		case 3:
		{
		pGameEnemy->setPosition(ccp(224,900));
		}
		break;
		case 4:
		{
		pGameEnemy->setPosition(ccp(448,900));
		}
		break;
		case 5:
		{
		pGameEnemy->setPosition(ccp(335,900)); 
		}
		break;
		}
	}	
}

void MainScene::MotionDetection()
{	
	
	for (unsigned int i=1;i<m_arrEnemy->count();++i)
	{
		GameEnemy* pTemp = (GameEnemy*)m_arrEnemy->objectAtIndex(i);

		COLLISIONAREA(hero,pTemp)

		if (rect_HeroForCrash.intersectsRect(rect_EnemyForCrash) && pTemp->getEnemyState() == kActionStateWalk)
		{
			this->unscheduleUpdate();
			this->getLostGame();
		}
	}
}

void MainScene::PersonCollision(int iPersonTag)
{
	int nTag = iPersonTag;
	Person* pPerson = (Person *)m_arrEnemy->objectAtIndex(nTag);
	float tempYSpeed = pPerson->getYSpeed();
	float tempXSpeed = pPerson->getXSpeed();
	CCPoint hP = pPerson->getPosition();
	int hx = (int)pPerson->getPositionX()/32;
	int hy = (int)(pPerson->getPositionY())/32;
	int hyPre = (int)(pPerson->getPositionY() + tempYSpeed)/32;
	bool isCrossFloor = false;
	for (unsigned int k = hP.y;k<= hP.y+tempYSpeed;++k)
	{
		if (_floor->tileGIDAt(ccp((int)hP.x/32,(int)hP.y/32)))
		{
			isCrossFloor = true;
			break;
		}
	}

	if (tempYSpeed>0)
	{
		tempYSpeed -= accelerate;
		pPerson->setPosition(pPerson->getPosition() + CCPoint(0,tempYSpeed));
	}
	else
	{
		bool isCollisionFloorAndHero=false;
		if (!_floor->tileGIDAt(ccp(hx,(30-1)-hy)) && _floor->tileGIDAt(ccp(hx,(30-1)-hyPre)) && !isCrossFloor )
		{
			isCollisionFloorAndHero = true;
		}
		else
		{
			isCollisionFloorAndHero = false;
		}

		if (isCollisionFloorAndHero && nTag == 0)
		{
			isJumping = false;
		}
		tempYSpeed = pPerson->isCollisionFloor(isCollisionFloorAndHero,tempYSpeed,accelerate);
	} 

	pPerson->setYSpeed(tempYSpeed);

	if (tempXSpeed >= 0)
	{
		if (pPerson->getPositionX()>=RIGHTRANGE)
		{
			tempXSpeed = -abs(tempXSpeed);
		}
		pPerson->setPosition(pPerson->getPosition()+CCPoint(tempXSpeed,0));
		
	}
	else
	{
		if (pPerson->getPositionX()<=LEFTRANGE)
		{
			tempXSpeed = abs(tempXSpeed);
		}
		pPerson->setPosition(pPerson->getPosition()+CCPoint(tempXSpeed,0));
	}

	pPerson->setXSpeed(tempXSpeed);

	if ((pPerson->getPositionX()>=RIGHTRANGE && pPerson->getPositionY()<=40 && pPerson->getEnemyState() == kActionStatePush ) || 
		(pPerson->getPositionX()<=LEFTRANGE && pPerson->getPositionY()<=40 && pPerson->getEnemyState() == kActionStatePush) )
	{
		CCParticleSystemQuad* quad = CCParticleSystemQuad::create("particle_boom.plist");
		quad->setAutoRemoveOnFinish(true);
		quad->setPosition(pPerson->getPosition()+CCPoint(0,40));
		this->addChild(quad);

		pPerson->setVisible(false);  
		pPerson->removeAllChildrenWithCleanup(true);
		m_arrEnemy->removeObjectAtIndex(nTag);

		if (m_arrEnemy->count() == 1)
		{
			this->getWinGame();
		}
	}
}

void MainScene::EnemyStatusAction()
{
	for (unsigned int i = 1;i<m_arrEnemy->count();++i)
	{
		GameEnemy* pTempGameEnemy = (GameEnemy*)m_arrEnemy->objectAtIndex(i);

		if (pTempGameEnemy->getEnemyState() == kActionStateFrozen)
		{
			continue;
		}

		if (pTempGameEnemy->getEnemyState() == kActionStateAttack)
		{
			CCSprite* pTempSprite = CCSprite::create("clouds.png");
			pTempSprite->setAnchorPoint(ccp(0,0));
			pTempSprite->setPosition(ccp(0,0));
			pTempGameEnemy->addChild(pTempSprite);
			pTempGameEnemy->setEnemyState(kActionStateFrozen);
		
		}
	}
}

void MainScene::createControlFont()
{
	CCMenuItemFont* pFont3 = CCMenuItemFont::create("jump",this,menu_selector(MainScene::toJump));
	pFont3->setPosition(ccp(390,850));

	CCMenuItemFont* pFont4 = CCMenuItemFont::create("bullet",this,menu_selector(MainScene::toBullet));
	pFont4->setPosition(ccp(510,850));

	CCMenu* pMenu = CCMenu::create(pFont3,pFont4,NULL);
	pMenu->setPosition(ccp(0,0));
	this->addChild(pMenu,2);
}

void MainScene::toJump(CCObject* sender)
{	
	if (isJumping)
	{
		return;
	}
	isJumping = true;
	hero->setYSpeed(20);
	hero->jump();
}

void MainScene::toBullet(CCObject* sender)
{
	bool temp =	hero->getFaceRight();
	if (temp)
	{
		GameBullet* tempBullet = GameBullet::createBullet(2);
		tempBullet->setPosition(hero->getPosition() + CCPoint(50,40));
		this->addChild(tempBullet,1);
	}
	else
	{
		GameBullet* tempBullet = GameBullet::createBullet(-2);
		tempBullet->setPosition(hero->getPosition() + CCPoint(-50,40));
		this->addChild(tempBullet,1);
	}
	 
	for (unsigned int i = 1;i< m_arrEnemy->count();++i)
	{
		GameEnemy* pTempGameEnemy = (GameEnemy*)m_arrEnemy->objectAtIndex(i);
		if (pTempGameEnemy->getEnemyState() == kActionStateFrozen )
		{
			if (hero->boundingBox().intersectsRect(pTempGameEnemy->boundingBox()))
			{
				if (temp)
				{
					pTempGameEnemy->setXSpeed(8);
					pTempGameEnemy->setEnemyState(kActionStatePush);
				}
				else
				{
					pTempGameEnemy->setXSpeed(-8);
					pTempGameEnemy->setEnemyState(kActionStatePush);
				}
			}
		}
	}
	hero->attack();
}

void MainScene::Moveing()  
{  
	if (isMoveing&&(speedX!=0)){  
		//飞机飞行  
		CCPoint position=ccp(hero->getPosition().x+speedX,hero->getPosition().y);  

		CCSize size=CCDirector::sharedDirector()->getWinSize();  
		CCRect rect=CCRectMake(50,30,size.width-100,size.height-100); 
		//判断触摸点是否在屏幕内    
		if(rect.containsPoint(position)){  
			hero->setPosition(position);  
		}  
	}  
}  

//触摸开始函数，判断触摸开始点是否在圆圈内，若是，则设置isFlying标志为true  
void MainScene::ccTouchesBegan( CCSet *pTouches, CCEvent *pEvent )  
{  
	CCTouch *touch = (CCTouch*)pTouches->anyObject();  
	CCPoint location = touch->getLocation();  

	CCRect rect=joystick->boundingBox();  
	if (rect.containsPoint(location))  
	{  
		isMoveing=true;  
//		hero->walkAction(true);
		hero->walk();
	}  
}  

//触摸滑动函数  
void MainScene::ccTouchesMoved( CCSet *pTouches, CCEvent *pEvent )  
{  
	CCTouch *touch = (CCTouch*)pTouches->anyObject();  
	CCPoint location = touch->getLocation();  

	//判断触摸滑动点是否在摇杆范围内  
	bool inRange=pow(O.x-location.x,2)+pow(O.y-location.y,2)<pow(R,2);  

	if(isMoveing&&inRange){  
		CCPoint position=hero->getPosition();  
		joystick->setPosition(location);  

		float r=R*2/6;  
		float d=R*2/3;  

		//左，区域4或7  
		if(CCRectMake(O.x-r-d,O.y-r,d,d).containsPoint(location)){  
			speedX=-3;
			hero->setFlipX(true);
		    hero->setFaceRight(false);
		}  
		//右，区域9或8  
		else if(CCRectMake(O.x+r,O.y-r,d,d).containsPoint(location)){  
			speedX=3;
			hero->setFlipX(false);
			hero->setFaceRight(true);
		}   
	}  
}  

//触摸结束函数  
void MainScene::ccTouchesEnded( CCSet *pTouches, CCEvent *pEvent )  
{  
	isMoveing=false;  
	joystick->setPosition(O);  
	speedX=0; 
//	hero->walkAction(false);
	hero->idle();
}

float MainScene::myRand_0_1()
{
	cc_timeval psv;  
	CCTime::gettimeofdayCocos2d( &psv, NULL );    // 获取本地时间
	//根据时间产生随机种子
	unsigned int tsrans = psv.tv_sec * 1000 + psv.tv_usec / 1000; 
	srand(tsrans);    //设定随机数种子
	return CCRANDOM_0_1();
}

GameHero* MainScene::getPlayer()
{
	GameHero *player = (GameHero*)MainScene::getMainScene()->getChildByTag(100);
	return player;
}

CCArray* MainScene::getArrayEnemy()
{
	return m_arrEnemy;
}

MainScene* MainScene::getMainScene()
{
	return m_pMainScene;
}

void MainScene::getWinGame()
{
	CCDirector::sharedDirector()->pause();
	GameWin* pWin = GameWin::createGameWin();
}

void MainScene::getLostGame()
{
	CCDirector::sharedDirector()->pause();
	GameLost* pLost = GameLost::createGameLost();
}

CCTMXTiledMap* MainScene::getTiledMap()
{
	return _tiledMap;
}

void MainScene::onExit()
{
	CCLayer::onExit();
}

