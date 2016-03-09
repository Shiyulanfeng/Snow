#include "GameEnemy.h"
#include "MainScene.h"
GameEnemy* GameEnemy::createEnemy()
{
	GameEnemy *ret = new GameEnemy();
	if (ret && ret->initWithFile("Clouds.png"))
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

	return true;
}

