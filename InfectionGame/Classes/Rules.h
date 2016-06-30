#ifndef __RULES_H__
#define __RULES_H__

#include "cocos2d.h"

class Rules : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(Rules);
    
private:

    void GoToMainMenu(cocos2d::Ref *sender);

};

#endif // __MAIN_MENU_SCENE_H__
