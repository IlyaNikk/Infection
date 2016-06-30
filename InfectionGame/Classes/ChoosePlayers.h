#ifndef __CHOOSE_PLAYERS_H__
#define __CHOOSE_PLAYERS_H__

#include "cocos2d.h"

class ChoosePlayers : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(ChoosePlayers);

private:
    void GoToChooseGame2(cocos2d::Ref *sender);
    void GoToChooseGame3(cocos2d::Ref *sender);
    void GoToChooseGame4(cocos2d::Ref *sender);
    void GoToMainMenu(cocos2d::Ref *sender);
};

#endif // __GAME_SCENE_H__
