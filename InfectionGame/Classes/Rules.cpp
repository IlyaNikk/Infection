#include "Rules.h"
#include "MainMenu.h"

#include "Defenitions.h" 

USING_NS_CC;

Scene* Rules::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Rules::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Rules::init()
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
    
    auto BackToMenu = Label::createWithTTF("Back", "fonts/orange.ttf", 32);
    BackToMenu->setColor(ccc3(0,0,0));
    
    
    auto closeItem = MenuItemLabel::create(BackToMenu,CC_CALLBACK_1(Rules::GoToMainMenu, this));
    
    closeItem->setPosition(Point(28, -25));
    
    auto menu = Menu::create(closeItem, NULL);
    backgroundSprite->addChild(menu, 1);
    
    
    
    return true;
}

void Rules::GoToMainMenu(cocos2d::Ref *sender){
    auto scene = MainMenu::createScene();
    
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
    
}