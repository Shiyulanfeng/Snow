#pragma once
#include "cocos2d.h"

#define SCREEN CCDirector::sharedDirector()->getWinSize()
#define CENTER ccp(SCREEN.width / 2, SCREEN.height / 2)
#define LEFTRANGE 45
#define RIGHTRANGE 595

#define EnemyGrid_X (int)this->getPositionX()/32
#define EnemyGrid_Y (int)this->getPositionY()/32
#define EnemyMoveAmount 2

#define COLLISIONAREA(Tar1,Tar2) CCRect rectHero = Tar1->boundingBox();  \
float x = rectHero.origin.x + rectHero.size.width * 0.2;        \
float y = rectHero.origin.y + rectHero.size.height * 0.2;       \
float width = rectHero.size.width * 0.6;                        \
float height = rectHero.size.height * 0.6;                      \
CCRect rect_HeroForCrash = CCRectMake(x, y, width, height);     \
CCRect rect_enemy = Tar2->boundingBox();                        \
float x1 = rect_enemy.origin.x + rect_enemy.size.width * 0.2;   \
float y1 = rect_enemy.origin.y + rect_enemy.size.height * 0.2;  \
float width1 = rect_enemy.size.width * 0.6;						\
float height1 = rect_enemy.size.height * 0.6;					\
CCRect rect_EnemyForCrash = CCRectMake(x1, y1, width1, height1);

typedef enum {
	kActionStateIdle = 0,
	kActionStateJump,
	kActionStateFrozen,
	kActionStateWalk,
	kActionStateAttack,
	kActionStatePush,
} ActionState;