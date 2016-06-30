#include "ChoosePlayers.h"
#include "MainMenuScene.h"
#include "Defenitions.h"
#include "MainMenu.h"
#include "Players.h"

using namespace std;



USING_NS_CC;

Scene* ChoosePlayers::createScene()
{
       // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = ChoosePlayers::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}


// on "init" you need to initialize your instance
bool ChoosePlayers::init()
{
    
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    
    //создаем фон
    auto Background = Sprite::create("background.png");
    Background->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    Background->setScaleX(visibleSize.width / Background->getContentSize().width);
    Background->setScaleY(visibleSize.height / Background->getContentSize().height);
    this->addChild(Background);

    
    Vector<MenuItem*> MenuItems;
    
    auto labelTwoPlayers = Label::createWithTTF("Two Playres","fonts/orange.ttf", 32 * 4);
    labelTwoPlayers->setColor(ccc3(0,0,0));
    
    auto labelThreePlayers = Label::createWithTTF("Three Players","fonts/orange.ttf", 32 * 4);
    labelThreePlayers->setColor(ccc3(0,0,0));
    
    auto labelFourPlayers = Label::createWithTTF("Four Players","fonts/orange.ttf", 32 * 4);
    labelFourPlayers->setColor(ccc3(0,0,0));
    
    
    auto BackToMenu = Label::createWithTTF("Back", "fonts/orange.ttf", 32 * 4);
    BackToMenu->setColor(ccc3(0,0,0));
    
    
    auto TwoPlayers = MenuItemLabel::create(labelTwoPlayers, CC_CALLBACK_1(ChoosePlayers::GoToChooseGame2, this));
    TwoPlayers ->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y) );
    
    auto ThreePlayers = MenuItemLabel::create(labelThreePlayers, CC_CALLBACK_1(ChoosePlayers::GoToChooseGame3, this));
    ThreePlayers ->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y) );
    
    auto FourPlayers = MenuItemLabel::create(labelFourPlayers, CC_CALLBACK_1(ChoosePlayers::GoToChooseGame4, this));
    FourPlayers ->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y) );
    
    auto closeItem = MenuItemLabel::create(BackToMenu, CC_CALLBACK_1(ChoosePlayers::GoToMainMenu, this));
    closeItem->setPosition(Point(20, -30));
    
    MenuItems.pushBack(TwoPlayers);
    MenuItems.pushBack(ThreePlayers);
    MenuItems.pushBack(FourPlayers);
    MenuItems.pushBack(closeItem);

    UserDefault::getInstance()->setIntegerForKey("Resume", 0);

    auto menu = Menu::createWithArray(MenuItems);
    menu->alignItemsVerticallyWithPadding(15);
    this->addChild(menu, 1);
    
    
    return true;
}

void ChoosePlayers::GoToMainMenu(cocos2d::Ref *sender){
    auto scene = MainMenu::createScene();
    
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
    
}

void ChoosePlayers::GoToChooseGame2(cocos2d::Ref *sender){
    UserDefault::getInstance()->setIntegerForKey("Players", 2);
    auto scene = MainMenuScene::createScene();
    
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
    
}

void ChoosePlayers::GoToChooseGame3(cocos2d::Ref *sender){
    UserDefault::getInstance()->setIntegerForKey("Players", 3);
    auto scene = MainMenuScene::createScene();
    
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
    
}

void ChoosePlayers::GoToChooseGame4(cocos2d::Ref *sender){
    UserDefault::getInstance()->setIntegerForKey("Players", 4);
    auto scene = MainMenuScene::createScene();

    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
    
}



