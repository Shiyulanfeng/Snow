#include "GameScene.h"

GameScene::GameScene()
{

}

GameScene::~GameScene()
{

}

GameScene* GameScene::create(void)
{
	GameScene *pGameScene = new GameScene(); 
	if (pGameScene && pGameScene->init()) 
	{ 
		pGameScene->autorelease(); 
		return pGameScene; 
	} 
	else 
	{ 
		CC_SAFE_DELETE(pGameScene);
		return NULL;
	} 
}

