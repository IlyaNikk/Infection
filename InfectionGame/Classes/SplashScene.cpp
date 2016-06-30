#include "SplashScene.h"
#include "MainMenu.h"
#include "Defenitions.h"

USING_NS_CC;

Scene* SplashScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SplashScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SplashScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    
    this->scheduleOnce( schedule_selector(SplashScene::GoToMainMenu), DISPLAY_TIME_SPLASH_SCENE );


    // add "HelloWorld" splash screen"
    
    auto backgroundSprite = Sprite::create("TechnoPark.png");
    backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    backgroundSprite->setScaleX(2.5);
    backgroundSprite->setScaleY(2.5);
    this->addChild(backgroundSprite);


    
    return true;
}

void SplashScene::GoToMainMenu(float dt){
    
    auto scene = MainMenu::createScene();
    
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
    
}



