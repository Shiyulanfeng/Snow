#include "GameBullet.h"

GameBullet::GameBullet()
{

}

GameBullet::~GameBullet()
{

}

GameBullet* GameBullet::createBullet(float BulletSpeed)
{
	GameBullet* pGameBullet = new GameBullet();
	if (pGameBullet && pGameBullet->initWithFile("button.png"))
	{
		pGameBullet->initBullet(BulletSpeed);
		pGameBullet->autorelease();
		return pGameBullet;
	}
	else
	{
		CC_SAFE_DELETE(pGameBullet);
		return nullptr;
	}
}

bool GameBullet::initBullet(float BulletSpeed)
{
	isActive = false;
	accelerate = 0.94f;
	m_fySpeed = 0;
	m_fBulletSpeed = BulletSpeed;

	tmxLayer = MainScene::getMainScene()->getTiledMap()->layerNamed("floor");

	if (m_fBulletSpeed >= 0 )
	{
		CCMoveBy* moveBy = CCMoveBy::create(0.4f,ccp(120,0));
		CCFiniteTimeAction* fun = CCCallFunc::create(this,callfunc_selector(GameBullet::BulletMove));
		this->runAction(CCSequence::create(moveBy,fun,NULL));
	}
	else
	{
		CCMoveBy* moveBy = CCMoveBy::create(0.4f,ccp(-120,0));
		CCFiniteTimeAction* fun = CCCallFunc::create(this,callfunc_selector(GameBullet::BulletMove));
		this->runAction(CCSequence::create(moveBy,fun,NULL));
	}
	if (m_fBulletSpeed>=0)
	{
		CCRotateBy* rotateBy = CCRotateBy::create(1.f,360);
		this->runAction(CCRepeatForever::create(rotateBy));
	}
	else
	{
		CCRotateBy* rotateBy = CCRotateBy::create(1.f,-360);
		this->runAction(CCRepeatForever::create(rotateBy));
	}
	
	
	this->scheduleUpdate();
	this->scheduleOnce(schedule_selector(GameBullet::CloseScheduler),0.7f);
	return true;
}

void GameBullet::update(float dt)
{

	if (isActive)
	{
		m_fySpeed -= accelerate;
		this->setPosition(this->getPosition() + CCPoint(m_fBulletSpeed,m_fySpeed));
	}

	int bX = (int)this->getPositionX()/32;
	int bY = (int)this->getPositionY()/32;

	if ( this->getPositionX() <=20 || this->getPositionX()>=620 || tmxLayer->tileGIDAt(ccp(bX,29-bY)) )
	{
	
		CCParticleSystemQuad *particle = CCParticleSystemQuad::create("particle_boom.plist");
		particle->setPosition(this->getPosition());
		particle->setAutoRemoveOnFinish(true);
		MainScene::getMainScene()->addChild(particle);

		this->setVisible(false);
		this->removeFromParentAndCleanup(true);
		this->unscheduleUpdate();
	}

	CCArray* pTempArray = MainScene::getMainScene()->getArrayEnemy();

	for (unsigned int i = 1; i < pTempArray->count(); ++i) {
		GameEnemy *enemy = (GameEnemy*)pTempArray->objectAtIndex(i);
		if (enemy->boundingBox().intersectsRect(this->boundingBox()))
		{
			if (enemy->getEnemyState() == kActionStateAttack)
			{
				enemy->setEnemyState(kActionStateFrozen);
			}
			else if (enemy->getEnemyState() == kActionStateWalk)
			{
				enemy->getActionManager()->pauseTarget(enemy);
				enemy->setEnemyState(kActionStateAttack); 
			}
			
			MainScene::getMainScene()->removeChild(this, true);
			break;
		}
	}
}
void GameBullet::CloseScheduler(float dt)
{
	CCParticleSystemQuad *particle = CCParticleSystemQuad::create("particle_boom.plist");
	particle->setPosition(this->getPosition());
	particle->setAutoRemoveOnFinish(true);
	MainScene::getMainScene()->addChild(particle);

	this->setVisible(false);
	this->removeFromParentAndCleanup(true);
	this->unscheduleUpdate();
}

void GameBullet::BulletMove()
{
	isActive = true;
}

