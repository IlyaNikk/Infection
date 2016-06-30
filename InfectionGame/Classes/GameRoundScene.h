#ifndef __GAME_OVER_SCENE_H__
#define __GAME_OVER_SCENE_H__

#include "cocos2d.h"

class GameRoundScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameRoundScene);
private:
    void SetPhysicsWorld( cocos2d::PhysicsWorld *world){sceneWorld = world; };
    cocos2d::PhysicsWorld *sceneWorld;
    
    void GoToMainScene(cocos2d::Ref *sender);
};

#endif // __GAME_OVER_SCENE_H__

