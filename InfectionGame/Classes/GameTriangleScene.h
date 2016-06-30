#ifndef __GAME_TRIANGLE_SCENE_H__
#define __GAME_TRIANGLE_SCENE_H__

#include "cocos2d.h"

class GameTriangleScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameTriangleScene);
private:

    void GoToMainScene(cocos2d::Ref *sender);
};

#endif // __GAME_SCENE_H__
