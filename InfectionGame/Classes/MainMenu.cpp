#include "MainMenu.h"
#include "MainMenuScene.h"
#include "Rules.h"
#include "ChoosePlayers.h"
#include "Defenitions.h" 

USING_NS_CC;

Scene* MainMenu::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenu::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();



    // add "HelloWorld" splash screen"

    auto backgroundSprite = Sprite::create("background.png");
    backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    backgroundSprite->setScaleX(visibleSize.width / backgroundSprite->getContentSize().width);
    backgroundSprite->setScaleY(visibleSize.height / backgroundSprite->getContentSize().height);
    this->addChild(backgroundSprite);
    

    Vector<MenuItem*> MenuItems;
    
    auto labelName = Label::createWithTTF("INFECTION","fonts/orange.ttf", 48 * 4 );
    labelName->setColor(ccc3(255,255,255));
    

    
    auto labelPlayRectangleScene = Label::createWithTTF("Play Game","fonts/orange.ttf", 32 * 4);
    labelPlayRectangleScene->setColor(ccc3(0,0,0));
    
    auto labelPlayRoundScene = Label::createWithTTF("Read Rules","fonts/orange.ttf", 32 * 4);
        labelPlayRoundScene->setColor(ccc3(0,0,0));
    
    
    auto playName = MenuItemLabel::create(labelName);
    playName ->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y) );

    auto playRectangleScene = MenuItemLabel::create(labelPlayRectangleScene, CC_CALLBACK_1(MainMenu::GoToChouseGame, this));
    playRectangleScene ->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y) );

    auto playRoundScene = MenuItemLabel::create(labelPlayRoundScene, CC_CALLBACK_1(MainMenu::GoToRules, this));
    playRectangleScene ->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y) );
    
    
    MenuItems.pushBack(playName);
    MenuItems.pushBack(playRectangleScene);
    MenuItems.pushBack(playRoundScene);

    auto menu = Menu::createWithArray(MenuItems);
    menu->alignItemsVerticallyWithPadding(15);
    this->addChild(menu, 1);

    
    return true;
}


void MainMenu::GoToChouseGame(cocos2d::Ref *sender){
    auto scene = ChoosePlayers::createScene();
    
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));

}

void MainMenu::GoToRules(cocos2d::Ref *sender){
    auto scene = Rules::createScene();
    
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
    
}
