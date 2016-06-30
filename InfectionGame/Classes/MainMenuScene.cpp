#include "MainMenuScene.h"
#include "MainMenu.h"
#include "GameTriangleScene.h"
#include "GameScene.h"
#include "GameRoundScene.h"
#include "Players.h"
#include "Defenitions.h" 

USING_NS_CC;

Scene* MainMenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}
/*
MainMenuScene::MainMenuScene(int Players){
    this->Players = Players;
    if (init())
    {
        autorelease();
    }
}
*/
// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    int Players =UserDefault::getInstance()->getIntegerForKey("Players");
    UserDefault::getInstance()->setIntegerForKey("Players", Players);

    // add "HelloWorld" splash screen"
    
    auto backgroundSprite = Sprite::create("background.png");
    backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    backgroundSprite->setScaleX(visibleSize.width / backgroundSprite->getContentSize().width);
    backgroundSprite->setScaleY(visibleSize.height / backgroundSprite->getContentSize().height);
    this->addChild(backgroundSprite);



    Vector<MenuItem*> MenuItems;

    int Resume = UserDefault::getInstance()->getIntegerForKey("Resume");

    //if(Resume == 1) {
        auto labelResumeScene = Label::createWithTTF("Resume", "fonts/orange.ttf", 32 * 4);
        labelResumeScene->setColor(ccc3(0, 0, 0));
        Resume = 0;
    //}

    //UserDefault::getInstance()->setIntegerForKey("Resume", Resume);

    auto labelPlayRectangleScene = Label::createWithTTF("Rectangle Field","fonts/orange.ttf", 32 * 4);
    labelPlayRectangleScene->setColor(ccc3(0,0,0));
    /*
    auto labelPlayRoundScene = Label::createWithTTF("Round Filed","fonts/orange.ttf", 32 * 4);
        labelPlayRoundScene->setColor(ccc3(0,0,0));
 
    auto labelPlayTriangleScene = Label::createWithTTF("Triangle Filed","fonts/orange.ttf", 32 * 4);
        labelPlayTriangleScene->setColor(ccc3(0,0,0));
*/

    auto BackToMenu = Label::createWithTTF("Back", "fonts/orange.ttf", 32 * 4);
    BackToMenu->setColor(ccc3(0,0,0));
    
    
    auto playRectangleScene = MenuItemLabel::create(labelPlayRectangleScene, CC_CALLBACK_1(MainMenuScene::GoToGameScene, this));
    playRectangleScene ->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y) );
/*
    auto playRoundScene = MenuItemLabel::create(labelPlayRoundScene, CC_CALLBACK_1(MainMenuScene::GoToGameRoundScene, this));
    playRectangleScene ->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y) );
    
    auto playTriangleScene = MenuItemLabel::create(labelPlayTriangleScene, CC_CALLBACK_1(MainMenuScene::GoToGameTriangleScene, this));
    playRectangleScene ->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y) );
*/
    auto closeItem = MenuItemLabel::create(BackToMenu,CC_CALLBACK_1(MainMenuScene::GoToMainMenu, this));
    closeItem->setPosition(Point(20, -30));
    
    MenuItems.pushBack(playRectangleScene);
//    MenuItems.pushBack(playRoundScene)
//  MenuItems.pushBack(playTriangleScene);
    MenuItems.pushBack(closeItem);
    
    auto menu = Menu::createWithArray(MenuItems);
    menu->alignItemsVerticallyWithPadding(15);
    this->addChild(menu, 1);

    
    return true;
}

void MainMenuScene::GoToMainMenu(cocos2d::Ref *sender){
    auto scene = MainMenu::createScene();
    
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
    
}

void MainMenuScene::GoToGameScene(cocos2d::Ref *sender){
    auto scene = GameScene::createScene();
    
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));

}

void MainMenuScene::GoToGameRoundScene(cocos2d::Ref *sender){
    auto scene = GameRoundScene::createScene();
    
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
    
}

void MainMenuScene::GoToGameTriangleScene(cocos2d::Ref *sender){
    auto scene = GameTriangleScene::createScene();
    
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
    
}
